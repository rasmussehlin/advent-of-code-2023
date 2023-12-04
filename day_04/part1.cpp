#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getPointsOfCard(string line);

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
            sum += getPointsOfCard(line);
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

int getPointsOfCard(string line)
{
    if (line.compare("") == 0)
    {
        return 0;
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

    int numberOfWins = 0;
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
                numberOfWins++;
            }
            wIndex = wUBound;
            while (winningNumbers[wIndex] == ' ') { wIndex++; }
            wUBound = winningNumbers.find(' ', wIndex);
        }
        index = uBound;
        while (scratchedNumbers[index] == ' ') { index++; }
        uBound = scratchedNumbers.find(' ', index);
    }

    int result = numberOfWins > 0 ? 1 : 0;
    for (int i = 0; i < numberOfWins - 1; i++)
    {
        result = result << 1;
    }

    return result;
}