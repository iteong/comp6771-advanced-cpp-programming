#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <vector>
#include <exception>

void simple_creation();
void mutexed_creation_bad();
void mutexed_creation_good();
void producer_consumer();

int main()
{
    unsigned int n = std::thread::hardware_concurrency();

    std::cout << "Computer has " << n << " cores" << std::endl << std::endl;

    // MODIFY: uncomment to test the different parts.
    simple_creation();
//    mutexed_creation_bad();
//    mutexed_creation_good();
//    producer_consumer();
}

//--------------------------------------------------------------------
// Example of creating some threads that sleep for a specified period
// of time then print out a message. Problem is that std::cout is a
// shared resource so output of different threads can be interleaved.
// ------------------------------------------------------------------

void simple_creation()
{

    // Lambda that is run for each thread
    auto sleep_and_print = [](unsigned int secs)
    {
        std::cout << "Thread " << std::this_thread::get_id()
                  << " sleeping for " << secs << " seconds" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds{secs});

      std::cout << "Thread " << std::this_thread::get_id()
                  << " slept for " << secs << " seconds" << std::endl;
    };

    // Create threads
    std::vector<std::thread> threads;
    for (auto i = 10; i > 0; --i)
    {
        threads.push_back(std::thread(sleep_and_print , i));
    }

    // Note: need to wait till all threads have finished. Otherwise
    // the thread object will be destroyed. If it is destroyed and the
    // thread is still running then std::terminate will be called.
    for (auto& t : threads) t.join();
}

//--------------------------------------------------------------------
// Use mutex to control access to std::cout.  The bad way is to
// explicitly lock and unlock. This is sensitive to programmer
// mistakes (e.g., an early return that forgets to unlock). However,
// most importantly it is not exception safe!
// --------------------------------------------------------------------

void mutexed_creation_bad()
{
    std::mutex cout_mutex;

    // Lambda that is run for each thread
    auto sleep_and_print = [&](unsigned int secs)
    {
        try
        {
            cout_mutex.lock();
            std::cout << "Thread " << std::this_thread::get_id()
                      << " sleeping for " << secs << " seconds" << std::endl;

            // MODIFY: explicit lock/unlock is not exception safe
//            throw std::runtime_error("exception showing mutex is not released");

            cout_mutex.unlock();

            std::this_thread::sleep_for(std::chrono::seconds{secs});

            cout_mutex.lock();
            std::cout << "Thread " << std::this_thread::get_id()
                      << " slept for " << secs << " seconds" << std::endl;
            cout_mutex.unlock();
        }
        catch(std::runtime_error &e)
        {
                std::cout << "Caught exception: " << e.what() << std::endl;
        }
    };

    // Create threads and wait till they've finised
    std::vector<std::thread> threads;
    for (auto i = 10; i > 0; --i)
    {
        threads.push_back(std::thread(sleep_and_print, i));
    }

    for (auto& t : threads) t.join();
}

//--------------------------------------------------------------------
// Use mutex to control access to std::cout.  The good way is to use a
// std::lock_guard object. It is harder to make mistakes and exception
// safe!
//
// Note: lambda syntax simplification. if parameter list is empty we
// can drop the "()". eg. auto a = []{ return true; };
// --------------------------------------------------------------------

//-----------------
// Helper template for mutex access to a resource by using a
// std::lock_guard. It is not strictly necessary to create this
// function but it does reduce the boilerplate code.

template<typename F>
void locked_scope(std::mutex& m, F f)
{
    std::lock_guard<std::mutex> lg{m};
    f();
}

//-----------------

void mutexed_creation_good()
{
    std::mutex cout_mutex;

    // Lambda that is run for each thread
    auto sleep_and_print = [&](unsigned int secs)
    {
        try
        {
            // locked_scope enforces single usage of std::cout.
            locked_scope(cout_mutex, [&]
            {
                std::cout << "Thread " << std::this_thread::get_id()
                          << " sleeping for " << secs << " seconds" << std::endl;

                // MODIFY: using lock_guard is exception safe
//                throw std::runtime_error("exception showing mutex is released");
            });

            std::this_thread::sleep_for(std::chrono::seconds{secs});

            locked_scope(cout_mutex, [&]
            {
                std::cout << "Thread " << std::this_thread::get_id()
                          << " slept for " << secs << " seconds" << std::endl;
            });
        }
        catch(std::runtime_error &e)
        {
            locked_scope(cout_mutex, [&]
            {
                std::cout << "Caught exception: " << e.what() << std::endl;
            });
        }
    };

    // Create threads and wait till they've finised
    std::vector<std::thread> threads;
    for (auto i = 10; i > 0; --i)
    {
        threads.push_back(std::thread(sleep_and_print, i));
    }
    for (auto& t : threads) t.join();
}

// --------------------------------------------------------------------
// Using condition_variables for a producer-consumer example.  Create
// a bunch of producers that each produce an value and push it onto a
// queue. Then create some consumers that wake up when there is a
// value available and pop it off the queue.

// Note: in this example we could have gotten away with only one mutex
// that controls access to the queue and std::cout. However I think it
// is clearer and instructive to separate the two.
// --------------------------------------------------------------------
void producer_consumer()
{
    std::mutex cout_mutex;
    std::mutex queue_mutex;
    std::vector<int> queue;
    std::condition_variable queue_cond;
    std::vector<std::thread> threads;

    // A producer sleeps for a set time then produces some input
    auto producer = [&](unsigned int secs, int val)
    {
        std::this_thread::sleep_for(std::chrono::seconds{secs});

        locked_scope(queue_mutex, [&]
        {
            queue.push_back(val);
            queue_cond.notify_one();

            locked_scope(cout_mutex, [&]
            {
                std::cout << "Thread " << std::this_thread::get_id()
                          << " producing value " << val << " after "
                          << secs << " seconds" << std::endl;
            });
        });
    };

    // A consumer thread prints that it is waiting for input. Then it
    // waits for the input and consumes it when available.
    auto consumer = [&]
    {
        locked_scope(cout_mutex, [&]
        {
            std::cout << "Thread " << std::this_thread::get_id()
                      << " waiting to consume." << std::endl;
        });

        // Lock queue mutex and wait. Note: once the mutex is
        // re-acquired from the wait() the unique_lock scope ensure
        // that the mutex remains locked till the consumer exits.
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cond.wait(lock, [&]{ return !queue.empty();});

        auto val = queue.back();
        queue.pop_back();

        locked_scope(cout_mutex, [&]
        {
            std::cout << "Thread " << std::this_thread::get_id()
                      << " consumed " << val << std::endl;
        });
    };


    // Create the consumer threads
    for (auto i = 0; i < 10; ++i)
        threads.push_back(std::thread(consumer));

    // Create producer threads: 3 second sleep then produce value.
    for (auto val=0; val < 10; ++val)
        threads.push_back(std::thread(producer, 3, val));

    for (auto& t : threads) t.join();
}
