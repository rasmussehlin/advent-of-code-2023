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
    cout << gameId + "\n";
    int gameIdNr = stoi(gameId);
    bool gameIsPossible = true;
    
    int position = colonIndex + 1;
    int nextSemicolon = line.length();
    while (position < line.length())
    {
        int red = 0;
        int green = 0;
        int blue = 0;

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
                    red += nr;
                    break;
                case 'g':
                    green += nr;
                    break;
                case 'b':
                    blue += nr;
                    break;
            }

            setPosition = nextComma + 2;
        }

        if (red > nrOfRedCubes || green > nrOfGreenCubes || blue > nrOfBlueCubes)
        {
            gameIsPossible = false;
            break;
        }

        position = nextSemicolon + 1;
    }

    cout << (gameIsPossible ? "" : "Game " + gameId + " is NOT possible.");

    return gameIsPossible ? gameIdNr : 0;
}