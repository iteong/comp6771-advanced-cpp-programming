#include <iostream>
#include <fstream>
#include <cstdio>

// Note: usually good practice to include your own header files after
// the standard ones.

#include "cs6771.h"

int main(int args, char* argv[])
{
    int i1, i2, i3;
    unsigned int ui1, ui2, ui3;
    std::ofstream outputs;
    std::ifstream inputs;

    std::cout << "Enter three integers: " << std::flush;
    std::cin >> i1 >> i2 >> i3;

    cs6771::order3(&i1,&i2,&i3);

    // Open/create
    //outputs.open("tmp.txt");

    // Note: Could also explicitly open in truncation mode
    outputs.open("tmp.txt", std::ofstream::trunc);

    outputs << i1 << " " << i2 << " " << i3 << std::endl;
    outputs.close();


    inputs.open("tmp.txt");
    inputs >> ui1 >> ui2 >> ui3;
    inputs.close();

    cs6771::order3(ui1,ui2,ui3);

    std::cout << "Output: " << ui1 << " " << ui2 << " " << ui3 << std::endl;

    // To be good we remove the file
    std::remove("tmp.txt");
}
