#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
#include <chrono>
#include <thread>

using namespace std;

struct hand
{
    string cards;
    int bet;
    int lineIndex;
};
// returns ​true if the first argument is less than (i.e. is ordered before) the second. // cpp reference
bool handCompare(const hand &a, const hand &b);
bool cardsCompare(const string &a, const string &b);
int getHandsRank(const hand &h);

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

    vector<hand> hands;
    int lineIndex = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.length() > 2)
            {
                vector<string> splitLine = AoCUtil::split(' ', line, true);
                // cout << splitLine[0] << splitLine[1];
                // if (splitLine[0].compare("") == 0)
                // {
                //     cout << "hopp";
                // }

                hand tmpHand;
                tmpHand.cards = splitLine[0];
                tmpHand.bet = stoi(splitLine[1]);
                tmpHand.lineIndex = lineIndex;
                lineIndex++;
                hands.push_back(tmpHand);
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
        
        std::sort(hands.begin(), hands.end(), handCompare);

        for (int i = 0; i < hands.size(); i++)
        {
            sum += (i + 1) * hands[i].bet;
        }
    }

    cout << sum;
    cout << '\n';

    myfile.close();

    return 0;
}

bool handCompare(const hand &a, const hand &b)
{
    if (a.cards.compare("") == 0)
    {
        cout << "WRONG";
    }
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

bool cardsCompare(const string &a, const string &b)
{
    if (a.length() != b.length())
    {
        throw std::invalid_argument("Cards `a` and `b` aren't the same length.");
    }

    string rank = "23456789TJQKA";

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

int getHandsRank(const hand &h)
{
    string cards = h.cards;
    std::sort(cards.begin(), cards.end());
    string uniques = "";
    int maxCount = 0;
    int currCount = 1;
    for (int i = 0; i < cards.length(); i++)
    {
        if (uniques.find(cards[i]) == string::npos)
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
            throw std::invalid_argument("uniques.length() was \"" + to_string(uniques.length()) + "\", invalid arguments.");
    }
}