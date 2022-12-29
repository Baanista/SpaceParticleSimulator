#ifndef preformance_HPP
#define preformance_HPP
#include <stdio.h>
#include <iostream>
#include<tuple>
#include <vector>
#include "particle.hpp"
using namespace std;
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time

int random_in_range(int lower_bound, int upper_bound) {
    // Seed the random number generator with the current time
    srand(time(nullptr));

    // Generate a random number between lower_bound and upper_bound, inclusive
    int random_number = lower_bound + std::rand() % (upper_bound - lower_bound + 1);

    return random_number;
}


pair<double, double> addgravvelocityfeild(double x, double y, double ox, double oy, double attraction, int chunk_size)
{
    
    double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

    //cout << dist << endl;
            
    double div = attraction / dist;

    double vx = ((x - ox) * div);
    double vy = ((y - oy) * div);
    cout << vx;
    cout << ',';
    cout << vy;
    cout << endl;

    return make_pair(vx, vy);
}

vector<vector<vector<double> > > velocityfeild(vector<vector<double> > gmap, int worldsize[2], int chunk_size, vector<vector<vector<double> > > defalt)
{
    vector<vector<vector<double> > > out = defalt;
    pair<double, double> temp;
    double half = chunk_size * .5;
    
    for (int x = 0; x < gmap.size(); x++)
    {
        for (int y = 0; y < gmap.size(); y++)
            {
                
                for (int i = 0; i < gmap.size(); i++)
                {
                    for (int a = 0; a < gmap.size(); a++)
                    {
                        pair<double, double> temp = addgravvelocityfeild((x * 2) + half, (y *2) +half, i, a, gmap[i][a]* -.001, chunk_size);
                        out[x][y][0] += temp.first;
                        out[x][y][1] += temp.second;
                    }
                }
            }
    }

    return out;
}


#endif
