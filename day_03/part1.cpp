#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int getSumOfAdjacentPartNumbers(vector<string> lines, int i);

int main()
{
    // Code goes here
    ifstream myfile;
    myfile.open("input");
    string line;
    int sum = 0;
    vector<string> lines;
    lines.push_back(string(142, '.'));
    cout << "Let's go" << '\n';
    if (myfile.is_open())
    {
        cout << "File is open" << '\n';
        while (getline(myfile, line))
        {
            if (line.compare("") != 0)
            {
                lines.push_back("." + line + ".");
            }
        }

        lines.push_back(string(142, '.'));

        cout << "lines size: " << int(lines.size()) << '\n';

        int upperBound = int(lines.size());
        for (int i = 1; i < upperBound - 1; i++)
        {
            // cout << lines[i];
            // cout << '\n';
            sum += getSumOfAdjacentPartNumbers(lines, i);
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

int getSumOfAdjacentPartNumbers(vector<string> lines, int i)
{
    string currLine = lines[i];
    int currLineBound = currLine.length();
    int sumOfLine = 0;
    bool prevSymbolIsDigit = false;
    bool numberIsAdjacentToSymbol = false;
    char tmpSymbol = '.';
    string currentNumber = "";
    auto updateAdjacentToSymbol = [&](char tmpSym) { numberIsAdjacentToSymbol = tmpSym != '.' && !isdigit(tmpSym) ? true : numberIsAdjacentToSymbol; };

    cout.width(3);
    cout.fill('0');
    cout << right << (i + 1);
    cout << ": .";

    for (int j = 1; j < currLineBound - 1; j++)
    {
        char symbol = currLine[j];
        if (isdigit(symbol))
        {
            if (numberIsAdjacentToSymbol)
            {
                cout << symbol;
            }
            else
            {
                if (!prevSymbolIsDigit) // set during previous symbol's check
                {
                    // One step behind
                    tmpSymbol = lines[i - 1][j - 1];
                    updateAdjacentToSymbol(tmpSymbol);
                    tmpSymbol = lines[i + 0][j - 1];
                    updateAdjacentToSymbol(tmpSymbol);
                    tmpSymbol = lines[i + 1][j - 1];
                    updateAdjacentToSymbol(tmpSymbol);
                }
                // Directly above and below
                tmpSymbol = lines[i - 1][j + 0];
                updateAdjacentToSymbol(tmpSymbol);
                tmpSymbol = lines[i + 1][j + 0];
                updateAdjacentToSymbol(tmpSymbol);

                // One step forward
                tmpSymbol = lines[i - 1][j + 1];
                updateAdjacentToSymbol(tmpSymbol);
                tmpSymbol = lines[i + 0][j + 1];
                updateAdjacentToSymbol(tmpSymbol);
                tmpSymbol = lines[i + 1][j + 1];
                updateAdjacentToSymbol(tmpSymbol);

                if (numberIsAdjacentToSymbol)
                {
                    cout << symbol;
                }
                else
                {
                    cout << 'x';
                }
            }

            currentNumber += symbol;
            prevSymbolIsDigit = true;
        }
        else
        {
            cout << symbol;
            if (prevSymbolIsDigit && numberIsAdjacentToSymbol)
            {
                sumOfLine += stoi(currentNumber);
            }
            currentNumber = "";
            prevSymbolIsDigit = false;
            numberIsAdjacentToSymbol = false;
        }
    }

    if (prevSymbolIsDigit && numberIsAdjacentToSymbol)
    {
        sumOfLine += stoi(currentNumber);
    }

    cout << '.' << " sum: " << sumOfLine << '\n';

    return sumOfLine;
}