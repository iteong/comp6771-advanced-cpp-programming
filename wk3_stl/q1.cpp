/*
q1.cpp
week 3 tutorial 2
Ivan Teong
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <algorithm> // sort, copy
#include <list>
#include <iterator>
#include <map>
#include <utility> // std::pair

int main()
{

	// variables
	const char *args[] = { "one","two","three" };
	std::vector<std::string> words(args, std::end(args)); // initializer list does not seem to be supported

	std::array<int, 3> numbers = {{3,2,1}}; // array cannot change size dynamically like vector
	// perform a lexicographical comparison/sort of each element of the vector recursively
	std::sort(words.begin(), words.end());

    // print check values for vector<string>, words
	typedef std::vector<std::string>::iterator vec_str_it;
	for (vec_str_it it = words.begin(); it != words.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}

    std::sort(numbers.begin(), numbers.end());

    // print check values for array<int>, numbers
   	typedef std::array<int, 3>::iterator arr_int_it;
	for (arr_int_it it = numbers.begin(); it != numbers.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}

  	std::list<int> values;
  	// http://stackoverflow.com/questions/19907677/whats-the-difference-between-iterator-and-back-insert-iterator, https://pkisensee.wordpress.com/2011/06/02/efficient-stl-insertion-tip-of-the-month/
  	// copy from source using back_insert_iterator, assuming destination is a container supporting push_back
	std::copy(numbers.begin(), numbers.end(), std::back_inserter(values));

	// http://stackoverflow.com/questions/8017215/whats-the-difference-between-list-sort-and-stdsort
	// std::list::sort has a one-argument form, with the first argument being the comparison function
	// can't use std::sort to sort std::list, because std::sort requires iterators to be random access, and std::list iterators are only bidirectional
  	values.sort();

    // print check values for list<int>, values
   	typedef std::list<int>::iterator list_int_it;
	for (list_int_it it = values.begin(); it != values.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}

	// Create a std::map where the keys are std::string and the values are int
    // Use a for loop to go through std::string vector, create a std::pair of each string in the vector and its position index, insert each std::pair into the map

	std::map<std::string, int> mymap;

    // move values for vector<string> words to map
    std::pair <std::string, int> foo;
	for (vec_str_it it = words.begin(); it != words.end(); it++)
	{
		// http://stackoverflow.com/questions/2152986/effective-way-to-get-the-index-of-an-iterator
		// std::distance(words.begin(), it) to get index of iterator
		foo = std::make_pair (*it, std::distance(words.begin(), it) ); // create a pair of string and int declared as foo
		std::cout << (*it) << " " << std::distance(words.begin(), it) << std::endl;

		std::map<std::string,int>::iterator it_map = mymap.begin();
  		mymap.insert (it_map, std::pair<std::string,int>(*it, std::distance(words.begin(), it)) );  // max efficiency inserting
	}

	// Use a range-based (for each) loop over the map to print out the key and value for each pair in the map
	typedef std::map<std::string,int>::iterator map_str_int_it;
	for (map_str_int_it it = mymap.begin(); it != mymap.end(); it++)
	{
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	}

return 0;
}

