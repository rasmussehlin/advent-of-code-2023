#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>
#include <boost/integer/common_factor.hpp>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Needs to be exactly one argument. Exiting...\n";
        return 0;
    }

    // Code goes here
    std::ifstream myfile;
    myfile.open(argv[1]);
    std::string line;
    int sum = 0;

    std::string instructions;
    std::vector<std::vector<std::string>> stringNodes;
    std::vector<std::vector<int>> nodes;
    std::vector<int> startingPositions;

    if (myfile.is_open())
    {
        getline(myfile, line);
        instructions = line;
        getline(myfile, line); // consume one line

        while (getline(myfile, line))
        {
            if (not line.empty())
            {
                stringNodes.push_back(std::vector<std::string>(3, ""));
                stringNodes[stringNodes.size() - 1][0] = line.substr(0, 3);
                stringNodes[stringNodes.size() - 1][1] = line.substr(7, 3);
                stringNodes[stringNodes.size() - 1][2] = line.substr(12, 3);
            }
        }

        nodes = std::vector<std::vector<int>>(stringNodes.size(), std::vector<int>(3, -1));

        // Reformat to a tree structure (kind of)
        for (int i = 0; i < stringNodes.size(); i++)
        {
            if (stringNodes[i][0][2] == 'A')
            {
                startingPositions.push_back(i);
            }
            nodes[i][0] = i;
            std::string left = stringNodes[i][1];
            std::string right = stringNodes[i][2];
            bool foundLeft = false;
            bool foundRight = false;
            for (int j = 0; j < stringNodes.size(); j++)
            {
                if (not foundLeft && stringNodes[j][0].compare(left) == 0)
                {
                    nodes[i][1] = j;
                    foundLeft = true;
                }
                
                if (not foundRight && stringNodes[j][0].compare(right) == 0)
                {
                    nodes[i][2] = j;
                    foundRight = true;
                }

                if (foundLeft && foundRight)
                {
                    break;
                }
            }
            
        }

        // Take steps
        int instructionIndex = 0;
        bool foundZZZ = false;
        boost::int64_t stepsTaken = 0;

        std::vector<boost::uint64_t> cycles = std::vector<boost::uint64_t>(startingPositions.size(), -1);
        int cyclesFound = 0;

        while (cyclesFound < cycles.size())
        {
            if (instructionIndex == instructions.length())
            {
                instructionIndex = 0;
            }

            char instruction = instructions[instructionIndex];
            for (int i = 0; i < startingPositions.size(); i++)
            {
                startingPositions[i] = instruction == 'L' ? nodes[startingPositions[i]][1] : nodes[startingPositions[i]][2];
            }

            stepsTaken++;
            instructionIndex++;

            // Find first time reaching "**z" for each starting position
            for (int i = 0; i < startingPositions.size(); i++)
            {
                if (stringNodes[startingPositions[i]][0][2] == 'Z' && cycles[i] == -1)
                {
                    cycles[i] = stepsTaken;
                    cyclesFound++;
                }
            }
        }

        // Calculate LCM
        boost::uint64_t result = boost::integer::lcm(cycles[0], cycles[1]);
        for (int i = 2; i < cycles.size(); i++)
        {
            result = boost::integer::lcm(result, cycles[i]);
        }

        std::cout << "Steps needed to take: " << result << std::endl;
    }

    myfile.close();

    return 0;
}