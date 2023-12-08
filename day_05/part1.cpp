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
        int mapsSize = 0;
        int mapsSantamapSize = 0;

        while (getline(myfile, line))
        {
            if (line.length() > 1 && isdigit(line[0]))
            {
                vector<string> tmp = AoCUtil::split(' ', line, true);

                maps[mapsSize - 1].push_back(santaMap());
                mapsSantamapSize++;
                santaMap &tmpMap = maps[mapsSize - 1][mapsSantamapSize - 1];
                tmpMap.destRangeStart = stoull(tmp[0]);
                tmpMap.srcRangeStart = stoull(tmp[1]);
                tmpMap.rangeLength = stoull(tmp[2]);
            }
            else if (line.length() > 1 && isalpha(line[0]))
            {
                maps.push_back(vector<santaMap>());
                mapsSize++;
                mapsSantamapSize = 0;
            }
        }

        // Convert seeds to integers
        vector<boost::uint64_t> transformedSeeds;
        for (int i = 0; i < seeds.size(); i++)
        {
            transformedSeeds.push_back(stoull(seeds[i]));
        }

        // Translate seeds to location
        for (int i = 0; i < seeds.size(); i++)
        {
            int mapTypeIndex = 0;
            bool transformedSeedChanged = false;
            // Go through all maptypes and transform step by step
            while (mapTypeIndex < maps.size())
            {
                vector<santaMap> tmpMap = maps[mapTypeIndex];
                
                // Find the one map for this maptype that fits
                for (int j = 0; j < tmpMap.size(); j++)
                {
                    if (transformedSeeds[i] >= tmpMap[j].srcRangeStart && 
                        transformedSeeds[i] < tmpMap[j].srcRangeStart + tmpMap[j].rangeLength)
                    {
                        transformedSeeds[i] = tmpMap[j].destRangeStart + transformedSeeds[i] - tmpMap[j].srcRangeStart;
                        break;
                    }
                }

                mapTypeIndex++;
            }
        }

        std::cout << to_string(*min_element(transformedSeeds.begin(), transformedSeeds.end())) << std::endl;
    }

    myfile.close();

    return 0;
}