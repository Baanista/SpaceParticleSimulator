#ifndef particle_HPP
#define particle_HPP
#include <cmath>
//#include "jsoncpp-master/include/json/json.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <vector>
#include <cstdio>
#include <random>
//#include <bits/stdc++.h>
#include "preformance.hpp"

class Nuron
{
    public:
        double w1;
        double w2;
        int Pass_Down[3];
        double input;

        void activate()
        {
            double output = input * w1 + w2;

            if (0 < output)
            {
                output = 0;
            }
            

            return(output);
        }

        void Mutate(double change_amount_weight, int change_amount_Pass_Down)
        {
            w1 += Positive_and_Negative_randomFloat() * change_amount_weight;
            w2 += Positive_and_Negative_randomFloat() * change_amount_weight;
            Pass_Down[0] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);
            Pass_Down[1] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);
            Pass_Down[2] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);
        }
}

class Cell_Responce_Mechanism()
{
    public:
        vector<Nuron> Nurons;

        void update()
        {
            double next_Pass_Down;
            for (int i = 0; i < Nurons.size(); i++)
            {
                next_Pass_Down = Nurons[i].activate();
            }
        }
}
#endif