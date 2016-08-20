
CC=g++       # Use g++
#CC=clang++   # Use clang

#OPTS=-std=c++11 -Wall -O0

# Note: this option disables all return value optimisation
OPTS=-std=c++11 -Wall -O0 -fno-elide-constructors

main: main.cpp car
	$(CC) $(OPTS) -o main main.cpp car.o

car: car.hpp car.cpp
	$(CC) $(OPTS) -c -o car.o car.cpp

clean:
	rm -f *.o *~ main a.out

