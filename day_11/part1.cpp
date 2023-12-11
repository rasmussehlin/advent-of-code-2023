#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>

#define PRINT(a) std::cout << a << std::endl;

void expandColumns(std::vector<std::string>& lines);

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

    std::vector<std::string> lines;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (not line.empty())
            {
                lines.push_back(line);
                if (line.find('#') == std::string::npos)
                {
                    lines.push_back(std::string(line.length(), '.'));
                }
                PRINT(line);
            }
        }

        PRINT("");
        expandColumns(lines);

        for (int i = 0; i < lines.size(); i++)
        {
            PRINT(lines[i]);
        }

        // calculate distances

        // Create a map of all pairs (coordinate to coordinate)

        // deltaX + deltaY = min(paths)
        
        
    }

    PRINT(sum);

    myfile.close();

    return 0;
}

void expandColumns(std::vector<std::string>& lines)
{
    // Expand columns
    for (int i = 0; i < lines[0].length(); i++)
    {
        bool columnIsEmpty = true;
        bool checkedAll = false;
        for (int j = 0; j < lines.size(); j++)
        {
            if (columnIsEmpty && checkedAll)
            {
                lines[j].insert(i, ".");
            }
            else
            {
                if (lines[j][i] == '#')
                {
                    columnIsEmpty = false;
                    break;
                }

                if (columnIsEmpty && j == lines.size() - 1)
                {
                    j = -1;
                    i++;
                    checkedAll = true;
                }
            } 
        }
    }
}