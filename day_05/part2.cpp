#include <iostream>
#include <fstream>
#include <string>
#include <map>
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

    struct santaMap
    {
        boost::uint64_t destRangeStart;
        boost::uint64_t srcRangeStart;
        boost::uint64_t rangeLength;
    };

    if (myfile.is_open())
    {
        // Get seeds
        getline(myfile, line);
        vector<string> seedStrings = AoCUtil::split(' ', line, true);
        seedStrings.erase(seedStrings.begin());
        vector<boost::uint64_t> seeds;
        for (int i = 0; i < 4; i += 2)
        {
            int seedInterval = stoull(seedStrings[i + 1]);
            for (int j = 0; j < seedInterval; j++)
            {
                seeds.push_back(stoull(seedStrings[i]) + j);
            }
        }

        getline(myfile, line);

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

        std::map<boost::uint64_t, boost::uint64_t> seedToLocation;
        // Translate seeds to locations
        std::cout << "Going through " << seeds.size() << " seeds." << std::endl;
        for (int i = 0; i < seeds.size(); i++)
        {
            if (i % 50000 == 0)
            {
                std::cout << "Seed nr " << i << "/" << seeds.size() << std::endl;
            }

            if (seedToLocation.count(seeds[i]) != 0)
            {
                seeds[i] = seedToLocation[seeds[i]];
                continue;
            }

            int mapTypeIndex = 0;
            boost::uint64_t startSeed = seeds[i];
            bool transformedSeedChanged = false;
            // Go through all maptypes and transform step by step
            while (mapTypeIndex < maps.size())
            {
                vector<santaMap> tmpMap = maps[mapTypeIndex];
                
                // Find the one map for this maptype that fits
                for (int j = 0; j < tmpMap.size(); j++)
                {
                    if (seeds[i] >= tmpMap[j].srcRangeStart && 
                        seeds[i] < tmpMap[j].srcRangeStart + tmpMap[j].rangeLength)
                    {
                        seeds[i] = tmpMap[j].destRangeStart + seeds[i] - tmpMap[j].srcRangeStart;
                        break;
                    }
                }

                mapTypeIndex++;
            }

            seedToLocation[startSeed] = seeds[i];
        }

        std::cout << to_string(*min_element(seeds.begin(), seeds.end())) << std::endl;
    }

    myfile.close();

    return 0;
}