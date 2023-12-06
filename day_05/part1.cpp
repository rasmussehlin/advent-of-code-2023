#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <boost/cstdint.hpp>
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
        getline(myfile, line);
        vector<string> seeds = AoCUtil::split(' ', line, true);
        seeds.erase(seeds.begin());
        getline(myfile, line);

        struct santaMap
        {
            boost::uint64_t destRangeStart;
            boost::uint64_t srcRangeStart;
            boost::uint64_t rangeLength;
        };
        vector<vector<santaMap>> maps;

        while (getline(myfile, line))
        {
            if (line.length() > 1 && isdigit(line[0]))
            {
                vector<string> tmp = AoCUtil::split(' ', line, true);
                santaMap tmpMap;
                tmpMap.destRangeStart = stoull(tmp[0]);
                tmpMap.srcRangeStart = stoull(tmp[1]);
                tmpMap.rangeLength = stoull(tmp[2]);
                maps[maps.size() - 1].push_back(tmpMap);
            }
            else if (line.length() > 1 && isalpha(line[0]))
            {
                maps.push_back(vector<santaMap>());
            }
        }

        for (int i = 0; i < seeds.size(); i++)
        {
            boost::uint64_t seed = stoull(seeds[i]);
            int mapTypeIndex = 0;
            while (mapTypeIndex < maps.size())
            {
                vector<santaMap> tmpMap = maps[mapTypeIndex];
                for (int i = 0; i < tmpMap.size(); i++)
                {
                    
                }
                
            }
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}