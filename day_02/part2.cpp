#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int nrOfRedCubes = 12;
int nrOfGreenCubes = 13;
int nrOfBlueCubes = 14;

int getIdIfSuccessfulGame(string line);

int main()
{
    // Code goes here
    ifstream myfile;
    myfile.open("input");
    string line;
    int sum = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            sum += getIdIfSuccessfulGame(line);
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

int getIdIfSuccessfulGame(string line)
{
    int colonIndex = line.find(':');
    int spaceIndex = line.find(' ');
    string gameId = line.substr(5, colonIndex - spaceIndex - 1);
    int gameIdNr = stoi(gameId);
    bool gameIsPossible = true;
    
    int position = colonIndex + 1;
    int nextSemicolon = line.length();
    int maxRed = 0;
    int maxGreen = 0;
    int maxBlue = 0;
    while (position < line.length())
    {
        if (position < line.length())
        {
            nextSemicolon = line.find(';', position);
            if (nextSemicolon == string::npos)
            {
                nextSemicolon = line.length() - 1;
            }
        }

        int setPosition = position + 1;
        while (setPosition < nextSemicolon) 
        {
            int nextComma = line.find(',', setPosition);
            if (nextComma == string::npos)
            {
                nextComma = nextSemicolon;
            } 
            int nextSpace = line.find(' ', setPosition);
            int nr = stoi(line.substr(setPosition, nextSpace - setPosition));

            char colorChar = line[nextSpace + 1];
            switch (colorChar)
            {
                case 'r':
                    if (nr > maxRed)
                    {
                        maxRed = nr;
                    }
                    break;
                case 'g':
                    if (nr > maxGreen)
                    {
                        maxGreen = nr;
                    }
                    break;
                case 'b':
                    if (nr > maxBlue)
                    {
                        maxBlue = nr;
                    }
                    break;
            }

            setPosition = nextComma + 2;
        }

        position = nextSemicolon + 1;
    }

    int powerOfGame = maxRed * maxGreen * maxBlue;
    cout << ("Power of Game " + gameId + " is " + to_string(powerOfGame) + " (" + to_string(maxBlue) + " red, " + to_string(maxGreen) + " green, " + to_string(maxBlue) + " blue)") + '\n';

    return powerOfGame;
}