#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getNumbers(string line);
string numberTexts[9] =
    {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"};
int nrTxtIndex[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

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
            sum += getNumbers(line);
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

int getNumbers(string line)
{
    // stega igenom varje "char" i line

    // håll koll på hur långt varje ord har kommit i uppräknande

    // om ordets index är lika långt som ordet så är det vad som var först

    // om det är en siffra så är det klart

    // För att hitta sista siffran
    // Gå baklänges. om siffra, klar.
    // Räkna baklänges bara. :)

    for (int i = 0; i < 9; i++)
    {
        nrTxtIndex[i] = 0;
    }
    

    // Hitta första siffran
    int numTextArraySize = sizeof(numberTexts) / sizeof(numberTexts[0]);
    bool foundFirst = false;
    int totSum = 0;
    int ascii_0 = 48;

    for (int i = 0; i < line.length() && !foundFirst; i++)
    {
        if (isdigit(line[i]))
        {
            totSum = (int(line[i]) - ascii_0) * 10;
            break;
        }

        for (int j = 0; j < numTextArraySize; j++)
        {
            char currChar = numberTexts[j][nrTxtIndex[j]];
            char currLineChar = line[i];
            if (currChar == currLineChar)
            {
                nrTxtIndex[j]++;
            }
            else
            {
                nrTxtIndex[j] = 0;
                if (numberTexts[j][nrTxtIndex[j]] == currLineChar)
                {
                    nrTxtIndex[j]++;
                }
            }

            if (nrTxtIndex[j] == numberTexts[j].length())
            {
                totSum = (j + 1) * 10; // one = 0, two = 1, ...
                foundFirst = true;
                break;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        nrTxtIndex[i] = numberTexts[i].length() - 1;
    }

    // find last
    bool foundLast = false;
    for (int i = line.length() - 1; i >= 0 && !foundLast; i--)
    {
        if (isdigit(line[i]))
        {
            totSum += int(line[i]) - ascii_0;
            break;
        }

        for (int j = 0; j < numTextArraySize; j++)
        {
            char currChar = numberTexts[j][nrTxtIndex[j]];
            char currLineChar = line[i];
            if (currChar == currLineChar)
            {
                nrTxtIndex[j]--;
            }
            else
            {
                nrTxtIndex[j] = numberTexts[j].length() - 1;
                if (numberTexts[j][nrTxtIndex[j]] == currLineChar)
                {
                    nrTxtIndex[j]--;
                }
            }

            if (nrTxtIndex[j] == -1)
            {
                totSum += j + 1;
                foundLast = true;
                break;
            }
        }
    }

    cout << line;
    cout << '\n';
    cout << totSum;
    cout << '\n';
    return totSum;
}