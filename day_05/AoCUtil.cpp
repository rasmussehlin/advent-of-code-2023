#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(char delimmiter, string toSplit)
{
    vector<string> result;
    int currentIndex = 0;
    int nextIndex = toSplit.find(delimmiter, currentIndex);
    while (currentIndex < toSplit.length())
    {
        result.push_back(toSplit.substr(currentIndex, nextIndex - currentIndex));
        currentIndex = nextIndex + 1;
        nextIndex = toSplit.find(delimmiter, currentIndex);
        if (nextIndex == string::npos)
        {
            nextIndex = toSplit.length();
        }
    }
    return result;
}