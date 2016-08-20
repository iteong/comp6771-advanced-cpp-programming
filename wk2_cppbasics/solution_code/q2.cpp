#include <iostream>
#include <fstream>


namespace cs6771 {
	void order3(unsigned int& a, unsigned int& b, unsigned int& c) {
		if (a > c) {
			int t = a;
			a = c;
			c = t;
		}
		if (b > c) {
			int t = b;
			b = c;
			c = t;
		}
		if (a > b) {
			int t = a;
			a = b;
			b = t;
		}
	}
}


int main(int args, char* argv[])
{
    unsigned int ui1, ui2, ui3;

    std::ifstream inputs("tmp.txt");

    inputs >> ui1 >> ui2 >> ui3;

    std::cout << "Input: " << ui1 << " " << ui2 << " " << ui3 << std::endl;

    cs6771::order3(ui1,ui2,ui3);

    std::cout << "Output: " << ui1 << " " << ui2 << " " << ui3 << std::endl;

}
