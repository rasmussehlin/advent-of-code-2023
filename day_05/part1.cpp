#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Needs to be exactly one argument. Exiting...\n";
        return 0;
    }

    // Code goes here
    ifstream myfile;
    myfile.open(argv[1]);
    string line;
    int sum = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<string> asd = split(' ', line);
            for (int i = 0; i < asd.size(); i++)
            {
                cout << asd[i] << '\n';
            }
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}