#CC=g++-4.9
CC=g++       # Use g++
#CC=clang++   # Use clang

# Note: by default clang will use libstdc++
OPTS=-std=c++11 -Wall -O3
#OPTS=-std=c++14 -Wall

# For clang using the LLVM standard libraries
#OPTS=-std=c++11 -stdlib=libc++

main: thread_basics

thread_basics: thread_basics.cpp
	$(CC) $(OPTS) -o thread_basics thread_basics.cpp -pthread

clean:
	rm -f *.o *~ a.out thread_basics

