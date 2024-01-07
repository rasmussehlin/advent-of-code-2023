#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

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

#define PRINT(a) std::cout << a << std::endl;

struct Hand
{
    Hand(std::string cards, int bet, int lineIndex)
    {
        this->cards = cards;
        this->bet = bet;
        this->lineIndex = lineIndex;
    };
    std::string cards;
    int bet;
    int lineIndex;
};
// returns ​true if the first argument is less than (i.e. is ordered before) the second. // cpp reference
bool handCompare(const Hand &a, const Hand &b);
bool cardsCompare(const std::string &a, const std::string &b);
int getHandsRank(const Hand &h);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Needs to be exactly one argument. Exiting...\n";
        return 0;
    }

    // Code goes here
    std::ifstream myfile;
    myfile.open(argv[1]);
    std::string line;
    int sum = 0;

    std::vector<Hand> hands;
    int lineIndex = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.length() > 2)
            {
                std::vector<std::string> splitLine = split(' ', line, true);
                hands.push_back(Hand(splitLine[0], stoi(splitLine[1]), lineIndex));
                lineIndex++;
                PRINT(lineIndex);
            }
            if (lineIndex == 1000)
            {
                PRINT("DUDE");
            }
        }

        // for (int i = 0; i < hands.size(); i++)
        // {
        //     if (hands[i].lineIndex == 0)
        //     {
        //         cout << "found it";
        //     }
        // }

        // for (int i = 0; i < hands.size(); i++)
        // {
        //     cout << hands[i].cards << ':' << hands[i].lineIndex << '\n';
        //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // }
        
        for (int i = 0; i < hands.size(); i++)
        {
            if (hands[i].cards.empty())
            {
                PRINT("Is empty");
            }
        }

        std::sort(hands.begin(), hands.end(), handCompare);

        for (int i = 0; i < hands.size(); i++)
        {
            sum += (i + 1) * hands[i].bet;
        }
    }

    std::cout << sum;
    std::cout << '\n';

    myfile.close();

    return 0;
}

bool handCompare(const Hand &a, const Hand &b)
{
    int aType = getHandsRank(a);
    int bType = getHandsRank(b);

    if (aType < bType)
    {
        return true;
    }
    else if (bType < aType)
    {
        return false;
    }
    else
    {
        return cardsCompare(a.cards, b.cards);
    }
}

bool cardsCompare(const std::string &a, const std::string &b)
{
    if (a.length() != b.length())
    {
        return false;
        // throw std::invalid_argument("Cards a and b aren't the same length.");
    }

    std::string rank = "23456789TJQKA";

    for (int i = 0; i < a.length(); i++)
    {
        int aIndex = rank.find(a[i]);
        int bIndex = rank.find(b[i]);

        if (aIndex < bIndex)
        {
            return true;
        }
        else if (bIndex < aIndex)
        {
            return false;
        }
    }

    // they are the same
    return true;
}

int getHandsRank(const Hand &h) 
{
    std::string cards = h.cards;
    std::sort(cards.begin(), cards.end());
    std::string uniques = "";
    int maxCount = 0;
    int currCount = 1;
    for (int i = 0; i < cards.length(); i++)
    {
        if (uniques.find(cards[i]) == std::string::npos)
        {
            uniques += cards[i];
            if (currCount > maxCount)
            {
                maxCount = currCount;
            }
            currCount = 1;
        }
        else
        {
            currCount++;
        }
    }

    // check last one
    if (currCount > maxCount)
    {
        maxCount = currCount;
    }

    switch (uniques.length())
    {
    case 1:
        return 6;
    case 2:
        return (maxCount == 4) ? 5 : 4;
    case 3:
        return (maxCount == 3) ? 3 : 2;
    case 4:
        return 1;
    case 5:
        return 0;
    default:
        return -1;
        // throw std::invalid_argument("uniques.length() was \"" + to_string(uniques.length()) + "\", invalid arguments.");
    }
}
