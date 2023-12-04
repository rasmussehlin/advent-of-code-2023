#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void getPointsOfCard(string line);
vector<int> nrOfCards;
vector<int> numberOfWins;
int currentLineIndex = -1;

int main()
{
    // Code goes here
    ifstream myfile;
    myfile.open("input");
    string line;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            currentLineIndex++;
            if (currentLineIndex == nrOfCards.size())
            {
                nrOfCards.push_back(1);
            }

            for (int i = 0; i < nrOfCards[currentLineIndex]; i++)
            {
                getPointsOfCard(line);
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < nrOfCards.size(); i++)
    {
        sum += nrOfCards[i];
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

void getPointsOfCard(string line)
{
    if (currentLineIndex == numberOfWins.size())
    {
        if (line.compare("") == 0)
        {
            return;
        }

        int colon = line.find(':');
        int splitpoint = line.find('|');
        string winningNumbers = line.substr(colon + 1, splitpoint - colon - 1);
        string scratchedNumbers = line.substr(splitpoint + 1, line.length() - splitpoint - 1);
        cout << line.substr(line.find(' '), colon - line.find(' ')) << '\n';
        cout << winningNumbers << '\n';
        cout << scratchedNumbers << '\n';

        int index = 1;
        while (line[index] == ' ') { index++; }
        int uBound = scratchedNumbers.find(' ', index);

        int nrOfWins = 0;
        while (index < scratchedNumbers.length())
        {
            int wIndex = 1;
            while (winningNumbers[wIndex] == ' ') { wIndex++; }
            int wUBound = winningNumbers.find(' ', 1);

            while (wIndex < winningNumbers.length())
            {
                string scratchedNumber = scratchedNumbers.substr(index, uBound - index);
                string winningNumber = winningNumbers.substr(wIndex, wUBound - wIndex);
                if (scratchedNumber.compare(winningNumber) == 0)
                {
                    nrOfWins++;
                }
                wIndex = wUBound;
                while (winningNumbers[wIndex] == ' ') { wIndex++; }
                wUBound = winningNumbers.find(' ', wIndex);
            }
            index = uBound;
            while (scratchedNumbers[index] == ' ') { index++; }
            uBound = scratchedNumbers.find(' ', index);
        }

        numberOfWins.push_back(nrOfWins);
    }

    for (int i = 1; i <= numberOfWins[currentLineIndex]; i++)
    {
        if (currentLineIndex + i == nrOfCards.size())
        {
            nrOfCards.push_back(2);
        }
        else
        {
            nrOfCards[currentLineIndex + i]++;
        }
    }
}