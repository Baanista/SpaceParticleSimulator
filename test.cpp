#include <iostream>
#include <chrono>
#include <ctime>   
#include "preformance.hpp"
#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>
#include "particle.hpp"
using namespace std;
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time
#include "debughelp.hpp"

//vector<int> printintvec

int main()
{
    vector<vector<vector<int> > > map(3, vector<vector<int> >(3));
    int i = 0;
    for (int x = 0; x < map.size(); x++)
    {
        for (int y = 0; y < map[0].size(); y++)
        {
            map[x][y].push_back(i);

            i ++;
            map[x][y].push_back(i);

            i ++;
        }
    }
    i = 0;
    for (int x = 0; x < map.size(); x++)
    {
        for (int y = 0; y < map[0].size(); y++)
        {
            cout << i << ':';
            printvecint(map[x][y]);
            i++;
        }
    }
    map =  change_map(map);

    i = 0;
    for (int x = 0; x < map.size(); x++)
    {
        for (int y = 0; y < map[0].size(); y++)
        {
            cout << i << ':';
            printvecint(map[x][y]);
            i++;
        }
    }
}