#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>

#define PRINT(a) std::cout << a << std::endl;

void findLoop(std::vector<std::string>& loop, std::vector<std::string> pipes, int startX, int startY);
void takeAStep(int positions[], std::vector<std::string> pipes, bool direction);
int countDirtInsideLoop(std::vector<std::string> loop);

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
    std::vector<std::string> pipes;

    if (myfile.is_open())
    {
        int sX = -1;
        int sY = -1;
        int lineIndex = 0;
        while (getline(myfile, line))
        {
            if (lineIndex == 0)
            {
                pipes.push_back(std::string(line.length() + 2, '.'));
                lineIndex++;
            }

            if (not line.empty())
                pipes.push_back("." + line + ".");

            int sIndex = line.find('S', 0);
            if (sIndex != std::string::npos)
            {
                sX = sIndex + 1; // Since border of "ground"
                sY = lineIndex;
            }

            lineIndex++;
        }
        pipes.push_back(std::string(line.length() + 2, '.'));

        std::vector<std::string> loop = pipes;
        findLoop(loop, pipes, sX, sY);
        sum += countDirtInsideLoop(loop);
    }

    PRINT(sum);

    myfile.close();

    return 0;
}

void findLoop(std::vector<std::string>& loop, std::vector<std::string> pipes, int startX, int startY)
{
    // for (int i = 0; i < pipes.size(); i++)
    // {
    //     PRINT(pipes[i]);
    // }

    // South-West dir (prevPos, currentPos)
    int leftLap[4] = {startX, startY, startX, startY};
    takeAStep(leftLap, pipes, false);
    // Nort-East dir (prevPos, currentPos)
    int rightLap[4] = {startX, startY, startX, startY};
    takeAStep(rightLap, pipes, true);

    // mark first loop pipe
    loop[leftLap[1]][leftLap[0]] = 'x';

    int stepsTaken = 1;
    
    while (leftLap[2] != rightLap[2] || leftLap[3] != rightLap[3])
    {
        loop[leftLap[3]][leftLap[2]] = 'x';
        loop[rightLap[3]][rightLap[2]] = 'x';
        takeAStep(leftLap, pipes, false);
        takeAStep(rightLap, pipes, true);
        // PRINT(leftLap[2]);
        // PRINT(rightLap[2]);
        // PRINT(leftLap[3]);
        // PRINT(rightLap[3]);
        // PRINT(std::to_string(leftLap[2] != rightLap[2] && leftLap[3] != rightLap[3]));
        stepsTaken++;
        PRINT("Steps taken: " + std::to_string(stepsTaken));
        std::cout << "Positions: (" << leftLap[2] << ", " << leftLap[3] << ");(" << rightLap[2] << ", " << rightLap[3] << ")";
    }
    loop[leftLap[3]][leftLap[2]] = 'x';
}

void takeAStep(int positions[], std::vector<std::string> pipes, bool direction)
{
    int& prevX = positions[0];
    int& prevY = positions[1];
    int& currX = positions[2];
    int& currY = positions[3];

    #define NORTH() std::string("|7F").find(pipes[currY - 1][currX    ], 0) != std::string::npos
    #define EAST() std::string("-J7").find( pipes[currY    ][currX + 1], 0) != std::string::npos
    #define SOUTH() std::string("|LJ").find(pipes[currY + 1][currX    ], 0) != std::string::npos
    #define WEST() std::string("-LF").find( pipes[currY    ][currX - 1], 0) != std::string::npos

    #define PREV_NOT_NORTH() not(currX == prevX && currY - 1 == prevY)
    #define PREV_NOT_EAST() not(currX + 1 == prevX && currY == prevY)
    #define PREV_NOT_SOUTH() not(currX == prevX && currY + 1 == prevY)
    #define PREV_NOT_WEST() not(currX - 1 == prevX && currY == prevY)

    // First step
    if (prevX == currX && prevY == currY)
    {
        if (direction)
        {
            if (NORTH())
            {
                currY--;
            }
            else if (EAST())
            {
                currX++;
            }
        }
        else
        {
            // North
            if (SOUTH())
            {
                currY++;
            }
            else if (WEST())
            {
                currX--;
            }
        }
    }
    // Other steps
    else
    {
        int tmpPrevX = currX;
        int tmpPrevY = currY;
        char currChar = pipes[currY][currX];
        bool checkNorth = false;
        bool checkEast = false;
        bool checkSouth = false;
        bool checkWest = false;

        if (currChar == '7')
        {
            checkWest = true;
            checkSouth = true;
        }
        else if (currChar == '|')
        {
            checkNorth = true;
            checkSouth = true;
        }
        else if (currChar == 'J')
        {
            checkWest = true;
            checkNorth = true;
        }
        else if (currChar == '-')
        {
            checkWest = true;
            checkEast = true;
        }
        else if (currChar == 'L')
        {
            checkNorth = true;
            checkEast = true;
        }
        else if (currChar == 'F')
        {
            checkEast = true;
            checkSouth = true;
        }


        if (checkNorth && NORTH() && PREV_NOT_NORTH())
        {
            currY--;
        }
        else if (checkEast && EAST() && PREV_NOT_EAST())
        {
            currX++;
        }
        else if (checkSouth && SOUTH() && PREV_NOT_SOUTH())
        {
            currY++;
        }
        else if (checkWest && WEST() && PREV_NOT_WEST())
        {
            currX--;
        }

        prevX = tmpPrevX;
        prevY = tmpPrevY;
    }

    // std::string msg = (direction ? "        " : "");
    // PRINT(msg + ":" + std::to_string(positions[2]) + ":" + std::to_string(positions[3]));
}

int countDirtInsideLoop(std::vector<std::string> loop)
{
    for (int i = 0; i < loop.size(); i++)
    {
        PRINT(loop[i]);
    }
    int tilesWithinLoop = 0;
    for (int i = 0; i < loop.size(); i++)
    {
        for (int j = 0; j < loop[0].size(); j++)
        {
            char currChar = loop[i][j];
            if (currChar == '.')
            {
                int minLoopCount = 999;
                int loopCount = 0;

                // Check vertically
                for (int k = 0; k < loop.size(); k++)
                {
                    if (k == i || k == loop.size() - 1)
                    {
                        minLoopCount = std::min(minLoopCount, loopCount);
                        loopCount = 0;
                    }
                    else if (loop[k][j] == 'x')
                    {
                        loopCount++;
                    }
                }
                
                // Check horizontally
                for (int k = 0; k < loop[0].size(); k++)
                {
                    if (k == j || k == loop[0].size() - 1)
                    {
                        minLoopCount = std::min(minLoopCount, loopCount);
                        loopCount = 0;
                    }
                    else if (loop[i][k] == 'x')
                    {
                        loopCount++;
                    }
                }

                if (minLoopCount % 2 == 1)
                {
                    tilesWithinLoop++;
                }
            }
        }
    }
    return tilesWithinLoop;
}