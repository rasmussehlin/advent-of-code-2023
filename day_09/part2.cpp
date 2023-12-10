#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>

#define PRINT(a) std::cout << a << std::endl;

int extrapolateHistory(std::string line);

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
            sum += extrapolateHistory(line);
        }
    }

    PRINT(sum);
    PRINT('\n');

    myfile.close();

    return 0;
}

int extrapolateHistory(std::string line)
{
    std::vector<int> values;
    std::vector<std::string> stringValues = AoCUtil::split(' ', line, true);
    std::vector<std::string> stringValuesReversed;
    for (int i = stringValues.size() - 1; i >= 0; i--)
    {
        stringValuesReversed.push_back(stringValues[i]);
    }

    for (int i = 0; i < stringValuesReversed.size(); i++)
    {
        values.push_back(stoull(stringValuesReversed[i]));
    }

    int layers = 1;
    bool allZeroes = false;
    while (not allZeroes)
    {
        allZeroes = true;
        for (int i = 0; i < values.size() - layers; i++)
        {
            values[i] = values[i] - values[i + 1];
            // std::cout << values[i] << " ";
            if (values[i] != 0)
            {
                allZeroes = false;
            }
        }
        layers++;
    }

    int extrapolation = values[values.size() - layers - 1];
    /* Skip layer with only zeroes. */
    for (int i = layers; i > 0; i--)
    {
        extrapolation = values[values.size() - i] - extrapolation;
    }

    return extrapolation;
}