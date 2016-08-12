main: q1 q2 q3

q1: q1.cpp
	g++ -o q1 q1.cpp

q2: q2.cpp
	g++ -o q2 q2.cpp


cs6771: cs6771.cpp cs6771.h
	g++ -c -o cs6771.o cs6771.cpp

q3: q3.cpp cs6771
	g++ -o q3 q3.cpp cs6771.o

clean:
	rm -f *.o *~ q1 q2 q3

