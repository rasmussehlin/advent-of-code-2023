#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>

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
    int startNodeIndex = -1;

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

        for (int i = 0; i < stringNodes.size(); i++)
        {
            if (stringNodes[i][0].compare("AAA") == 0)
            {
                startNodeIndex = i;
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

        int instructionIndex = 0;
        bool foundZZZ = false;
        int currentNode = startNodeIndex;
        int stepsTaken = 0;
        while (not foundZZZ)
        {
            std::string current = stringNodes[currentNode][0];

            if (instructionIndex == instructions.length())
            {
                instructionIndex = 0;
            }

            char instruction = instructions[instructionIndex];
            currentNode = instructions[instructionIndex] == 'L' ? nodes[currentNode][1] : nodes[currentNode][2];
            stepsTaken++;
            instructionIndex++;

            if (stringNodes[currentNode][0].compare("ZZZ") == 0)
            {
                foundZZZ = true;
            }
        }

        std::cout << "Steps taken: " << stepsTaken << '\n';
    }

    myfile.close();

    return 0;
}