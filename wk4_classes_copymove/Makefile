
CC=g++       # Use g++
#CC=clang++   # Use clang

#OPTS=-std=c++11 -Wall -O0

# Note: this option disables all return value optimisation
OPTS=-std=c++11 -Wall -O0 -fno-elide-constructors

Car: Car.hpp Car.cpp
	$(CC) $(OPTS) -c -o Car.o Car.cpp

clean:
	rm -f *.o *~ main a.out

