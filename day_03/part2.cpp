#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int getGearRatiosFromLine(vector<string> lines, int i);
int getGearsRatio(vector<string> lines, int y, int x);

int main()
{
    ifstream myfile;
    vector<string> lines;
    string line;
    myfile.open("input");

    int gearRatios = 0;
    lines.push_back(string(142, '.')); // to not have to deal with boundary checking

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.compare("") != 0)
            {
                lines.push_back("." + line + ".");
            }
        }

        lines.push_back(string(142, '.')); // boundary checking fix

        for (int i = 1; i < int(lines.size()) - 1; i++)
        {
            gearRatios += getGearRatiosFromLine(lines, i);
        }
    }

    cout << gearRatios;
    cout << '\n';

    myfile.close();

    return 0;
}

int getGearRatiosFromLine(vector<string> lines, int i)
{
    string currLine = lines[i];
    int sumGearRatios = 0;

    for (int j = 1; j < currLine.length() - 1; j++)
    {
        char symbol = currLine[j];
        if (symbol == '*')
        {
            sumGearRatios += getGearsRatio(lines, i, j);
        }
    }

    cout << "Sum of Line " << i << " :" << sumGearRatios << '\n';
    return sumGearRatios;
}

int getGearsRatio(vector<string> lines, int y, int x)
{
    vector<string> mask(3, "_______");
    mask[1][3] = '*'; // for printing
    int gearRatio = 1;
    int numberCount = 0;

    auto getFullNumber = [&](int j, int i)
    {
        string currentLine = lines[y + j];
        string number(1, currentLine[x + i]);
        bool alreadyCounted = false;
        bool leftDone = false;
        bool rightDone = false;
        int offset = 1;

        auto checkOffset = [&](int offset_param) {
            char tmpChar = currentLine[x + i + offset_param];
            if (isdigit(tmpChar))
            {
                number = offset_param < 0 ? tmpChar + number : number + tmpChar;
                mask[j + 1][(i + 1) + 2 + offset_param] = 'x';
            }
            else
            {
                if (offset_param < 0) { leftDone = true; } else { rightDone = true; }
            }
        };

        while (not leftDone || not rightDone)
        {
            if ((not leftDone && mask[j + 1][(i + 1) + 2 - offset] == 'x') ||
                (not rightDone && mask[j + 1][(i + 1) + 2 + offset] == 'x'))
            {
                alreadyCounted = true;
                break;
            }

            if (not leftDone) { checkOffset(-offset); }
            if (not rightDone) { checkOffset(offset); }
            offset++;
        }

        if (not alreadyCounted) { numberCount++; }

        return stoi(number);
    };

    // Look around gear
    for (int j = -1; j < 2; j++)
    {
        for (int i = -1; i < 2; i++)
        {
            if (isdigit(lines[y + j][x + i]) && mask[j + 1][i + 1 + 2] != 'x')
            {
                mask[j + 1][i + 1 + 2] = 'x';
                int fullNumber = getFullNumber(j, i);
                gearRatio *= fullNumber;
            }
        }
    }
    
    // Print mask
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << mask[i][j];
        }
        cout << '\n';
    }
    cout << "Gear ratio: " << gearRatio << ", numberCount: " << numberCount << '\n';
    return numberCount == 2 ? gearRatio : 0;
}