#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace AoCUtil
{
    /**
     * @brief "Private" functions declarations.
     */
    namespace
    {
        int getNextIndex(char searchFor, std::string inString, int currentIndex);
        int getNextIndexDifferentThan(char searchFor, std::string inString, int currentIndex);
    }

    /**
     * @brief Split a string into a vector array.
     * 
     * @param delimmiter the character to split at (gets removed)
     * @param toSplit the string to split
     * @param consecutiveAsOne count consecutive delimmiters as one
     * @return vector<string> an array containing the substrings of `toSplit`
     */
    std::vector<std::string> split(char delimmiter, std::string toSplit, bool consecutiveAsOne)
    {
        std::vector<std::string> result;
        int currentIndex = 0;
        int nextIndex;
        nextIndex = toSplit.find(delimmiter, currentIndex);

        while (currentIndex < toSplit.length())
        {
            result.push_back(toSplit.substr(currentIndex, nextIndex - currentIndex));
            
            if (consecutiveAsOne)
            {
                currentIndex = getNextIndexDifferentThan(delimmiter, toSplit, nextIndex);
            }
            else
            {
                currentIndex = nextIndex + 1;
            }

            nextIndex = toSplit.find(delimmiter, currentIndex);
            if (nextIndex == std::string::npos)
            {
                nextIndex = toSplit.length();
            }
        }
        return result;
    }

    /**
     * @brief Remove alla occurences of char in string. Returns a new string.
     * 
     * @param toRemove char to be removed
     * @param inString string to remove from
     * @return string resulting new string
     */
    std::string removeAll(char toRemove, std::string inString)
    {
        // Thanks: https://stackoverflow.com/a/20326454
        std::string result;
        result.reserve(inString.length());
        
        for (int i = 0; i < inString.length(); i++)
        {
            if (inString[i] != toRemove)
            {
                result += inString[i];
            }
        }

        return result;
    }

    /**
     * @brief "Private" functions
     */
    namespace
    {
        /**
         * @brief Get the next index in `inString` which is not `searchFor`
         * 
         * @param searchFor the char to ignore
         * @param inString the string in which to search
         * @param currentIndex index to search from (inclusive)
         * @return int the next index which isn't `searchFor`
         */
        int getNextIndexDifferentThan(char searchFor, std::string inString, int currentIndex)
        {
            int nextIndex = inString.find(searchFor, currentIndex);

            if (nextIndex == std::string::npos)
            {
                nextIndex = currentIndex;
            }

            while (inString[nextIndex] == searchFor && nextIndex < inString.length())
            {
                nextIndex++;
            }

            return nextIndex;
        }
    }
}