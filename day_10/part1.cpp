#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>

#define PRINT(a) std::cout << a << std::endl;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        PRINT("Needs to be exactly one argument. Exiting...\n");
        return 0;
    }

    // Code goes here
    std::ifstream myfile;
    myfile.open(argv[1]);
    std::string line;
    int sum = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // Do stuff...
        }
    }

    PRINT(sum);
    PRINT('\n');

    myfile.close();

    return 0;
}