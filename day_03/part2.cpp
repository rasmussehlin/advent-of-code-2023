#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;
using namespace std;

// int128_t getGearRatiosFromLine(vector<string> lines, int i);
int getGearRatiosFromLine(vector<string> lines, int i);
int getGearsRatio(vector<string> lines, int y, int x);

int main()
{
    // Code goes here
    ifstream myfile;
    myfile.open("input");
    string line;
    int gearRatios = 0;
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
    int sumGearRatios = 0;
    string currLine = lines[i];
    int currLineBound = currLine.length();

    // cout.width(3);
    // cout.fill('0');
    // cout << right << (i + 1);
    // cout << ": .";

    for (int j = 1; j < currLineBound - 1; j++)
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
    mask[1][3] = '*';
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
        if (y + j == 133) {
            cout << "133\n";
        }
        auto checkOffset = [&](int offset_param) {
            char tmpChar = currentLine[x + i + offset_param];
            // cout << "Looking at char at " << (i + offset_param) << ": " << tmpChar;
            // cout.width(10);
            // cout.fill(' ');
            if (isdigit(tmpChar))
            {
                number = offset_param < 0 ? tmpChar + number : number + tmpChar;
                mask[j + 1][(i + 1) + 2 + offset_param] = 'x';
            }
            else
            {
                if (offset_param < 0)
                {
                    leftDone = true;
                }
                else
                {
                    rightDone = true;
                }
            }
        };

        while (offset < 3 && (not leftDone || not rightDone))
        {
            if ((not leftDone && mask[j + 1][(i + 1) + 2 - offset] == 'x') ||
                (not rightDone && mask[j + 1][(i + 1) + 2 + offset] == 'x'))
            {
                alreadyCounted = true;
                break;
            }

            if (not leftDone) { checkOffset(-offset); /* cout << right << number << "L\n"; */}
            if (not rightDone) { checkOffset(offset); /* cout << right << number << "R\n"; */}
            offset++;
        }
        // cout << "getFullNumber done: " << number << '\n';

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
                // cout << "Fullnumber: " << fullNumber << '\n';
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
    cout << '\n';
    cout << "Gear ratio: " << gearRatio << ", numberCount: " << numberCount << '\n';
    return numberCount == 2 ? gearRatio : 0;
}