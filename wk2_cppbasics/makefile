# compiler type
CC=g++-6
# standard of C++
STD=-std=c++14
# error, warning and optimisation level
CFLAGS=-Wall -Werror -O2 -o

%.exe : %.cpp
	${CC} ${STD} S{CFLAGS} $@ $<

all: $(basename $(wildcard *.cpp))
