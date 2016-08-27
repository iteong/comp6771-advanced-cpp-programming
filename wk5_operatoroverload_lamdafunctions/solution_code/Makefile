
CC=g++       # Use g++
#CC=clang++   # Use clang

OPTS=-std=c++11 -Wall -O0

main: main.cpp book
	$(CC) $(OPTS) -o main main.cpp book.o

book: book.hpp book.cpp
	$(CC) $(OPTS) -c -o book.o book.cpp

clean:
	rm -f *.o *~ main a.out

