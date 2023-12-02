#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getNumbers(string line);

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
    int nr = 0;
    int ascii_0 = 48;
    int val;
    int last;
    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]))
        {
            val = int(line[i]);
            last = val;
            // Handle the first occurence of a number
            if (nr == 0)
            {
                nr += val - ascii_0;
                nr *= 10;
            }
        }
    }

    // Handle the last occurence
    nr += last - ascii_0;

    // cout << nr;
    // cout << '\n';
    return nr;
}