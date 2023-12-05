#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
            // Do stuff...
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}