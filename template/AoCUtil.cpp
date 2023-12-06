#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace AoCUtil
{
    /**
     * @brief Split a string into a vector array.
     * 
     * @param delimmiter the character to split at (gets removed)
     * @param toSplit the string to split
     * @param consecutiveAsOne count consecutive delimmiters as one
     * @return vector<string> an array containing the substrings of `toSplit`
     */
    vector<std::string> split(char delimmiter, string toSplit, bool consecutiveAsOne)
    {
        vector<string> result;
        int currentIndex = 0;
        int nextIndex;
        if (consecutiveAsOne)
        {
             nextIndex = getNextIndexDifferentThan(delimmiter, toSplit, currentIndex);
        }
        else
        {
            nextIndex = toSplit.find(delimmiter, currentIndex);
        }

        while (currentIndex < toSplit.length())
        {
            result.push_back(toSplit.substr(currentIndex, nextIndex - currentIndex));
            currentIndex = nextIndex + 1;
            if (consecutiveAsOne)
            {
                nextIndex = getNextIndexDifferentThan(delimmiter, toSplit, currentIndex);
            }
            else 
            {
                nextIndex = toSplit.find(delimmiter, currentIndex);
            }
            if (nextIndex == string::npos)
            {
                nextIndex = toSplit.length();
            }
        }
        return result;
    }

    /**
     * @brief "Private" functions
     */
    namespace {
        /**
         * @brief Get the next index in `inString` which is not `searchFor`
         * 
         * @param searchFor the char to ignore
         * @param inString the string in which to search
         * @param currentIndex index to search from (inclusive)
         * @return int the next index which isn't `searchFor`
         */
        int getNextIndexDifferentThan(char searchFor, string inString, int currentIndex)
        {
            int nextIndex = inString.find(searchFor, currentIndex);

            while (inString[nextIndex] == searchFor && nextIndex < inString.length())
            {
                nextIndex++;
            }

            return nextIndex;
        }
    }
};