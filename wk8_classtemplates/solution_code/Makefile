#CC=g++-4.9
CC=g++       # Use g++
#CC=clang++   # Use clang

# Note: by default clang will use libstdc++
OPTS=-std=c++11 -Wall
#OPTS=-std=c++14 -Wall

# For clang using the LLVM standard libraries
#OPTS=-std=c++11 -stdlib=libc++

main: week8

week8: week8.cpp Library.hpp
	$(CC) $(OPTS) -o week8 week8.cpp

clean:
	rm -f *.o *~ week8 a.out

