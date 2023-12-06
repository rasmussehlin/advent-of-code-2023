#include <iostream>
#include <fstream>
#include <string>
#include "../AoCUtil.cpp"
using namespace std;

void calculateBounds(int raceIndex, int totalTime, int minimumDistance, vector<vector<int>>& bounds);

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
    int product = 1;

    if (myfile.is_open())
    {
        getline(myfile, line);
        vector<string> times = AoCUtil::split(' ', line, true);
        times.erase(times.begin());
        getline(myfile, line);
        vector<string> distances = AoCUtil::split(' ', line, true);
        distances.erase(distances.begin());

        int races = times.size();
        vector<vector<int>> bounds(races, vector<int>(2,0));
        for (int i = 0; i < races; i++)
        {
            int raceTime = stoi(times[i]);
            int raceDistance = stoi(distances[i]);
            calculateBounds(i, raceTime, raceDistance, bounds);
        }

        for (int i = 0; i < bounds.size(); i++)
        {
            cout << "Race " << i << " bounds: " << bounds[i][0] << ":" << bounds[i][1] << " (" << (bounds[i][1] + 1 - bounds[i][0]) << ")\n";
            product = product * (bounds[i][1] + 1 - bounds[i][0]);
        }
    }

    cout << product;
    cout << '\n';

    myfile.close();

    return 0;
}

void calculateBounds(int raceIndex, int totalTime, int minimumDistance, vector<vector<int>>& bounds)
{
    int tempDistance;
    for (int i = 1; i < totalTime; i++)
    {
        // distance = timeLeft * speed
        // timeLeft = totalTime - timePassed
        // speed = timePassed
        // timePassed = totalTime - timeLeft

        // distance = (totalTime - timePassed) * (totalTime - timeLeft)
        // distance = (totalTime - timePassed) * (totalTime - (totalTime - timePassed))
        // distance = (totalTime - timePassed) * timePassed
        // distance = totalTime * timePassed - timePassed^2
        tempDistance = totalTime * i - i * i;
        tempDistance = (totalTime - i) * i;

        if (tempDistance > minimumDistance && bounds[raceIndex][0] == 0)
        {
            bounds[raceIndex][0] = i;
        }
        else if (bounds[raceIndex][0] != 0 && tempDistance <= minimumDistance)
        {
            bounds[raceIndex][1] = i - 1;
            break;
        }
    }   
}