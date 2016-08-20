#include <iostream>
#include <fstream>


namespace cs6771 {
	void order3(int *a, int *b, int *c) {
		if (*a < *c) {
			int t = *a;
			*a = *c;
			*c = t;
		}
		if (*a < *b) {
			int t = *a;
			*a = *b;
			*b = t;
		}
		if (*b < *c) {
			int t = *b;
			*b = *c;
			*c = t;
		}
	}
}


int main(int args, char* argv[])
{
    int i1, i2, i3;

    std::cout << "Enter three integers: " << std::flush;

    std::cin >> i1 >> i2 >> i3;

    std::cout << "Input: " << i1 << " " << i2 << " " << i3 << std::endl;

    cs6771::order3(&i1,&i2,&i3);

    std::cout << "Output: " << i1 << " " << i2 << " " << i3 << std::endl;

    std::ofstream result("tmp.txt");

    result << i1 << " " << i2 << " " << i3 << std::endl;
}
