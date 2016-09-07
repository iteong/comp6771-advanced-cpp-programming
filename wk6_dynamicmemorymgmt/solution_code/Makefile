CC=g++-4.9    
#CC=g++       # Use g++
#CC=clang++   # Use clang

# Note: by default clang will use libstdc++
OPTS=-std=c++11 -Wall
#OPTS=-std=c++14 -Wall

# For clang using the LLVM standard libraries
#OPTS=-std=c++11 -stdlib=libc++

main: school.cpp school
	$(CC) $(OPTS) -o main main.cpp school.o

school: school.hpp school.cpp
	$(CC) $(OPTS) -c -o school.o school.cpp

clean:
	rm -f *.o *~ main a.out

