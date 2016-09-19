#CC=g++-4.9
CC=g++       # Use g++
#CC=clang++   # Use clang

# Note: by default clang will use libstdc++
OPTS=-std=c++11 -Wall
#OPTS=-std=c++14 -Wall

# For clang using the LLVM standard libraries
#OPTS=-std=c++11 -stdlib=libc++

main: extraSmart variadicPrint

extraSmart: extraSmart.cpp
	$(CC) $(OPTS) -o es extraSmart.cpp

variadicPrint: variadicPrint.cpp
	$(CC) $(OPTS) -o vp variadicPrint.cpp

clean:
	rm -f *.o *~ es vp a.out

