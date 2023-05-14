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

<<<<<<< HEAD
        void Mutate(double change_amount_weight, int change_amount_Pass_Down, int biggest_element, float turn_2_int_chance)
=======
        void Mutate(double change_amount_weight, int change_amount_Pass_Down, int biggest_element)
>>>>>>> 0212e9cd089fed41578e4726f1e856d08efe29c6
        {
            w1 += Positive_and_Negative_randomFloat() * change_amount_weight;
            w2 += Positive_and_Negative_randomFloat() * change_amount_weight;

            if (randomFloat < turn_2_int_chance){w1 = round(w1);}
            if (randomFloat < turn_2_int_chance){w1 = round(w2);}

            Pass_Down[0] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);
            Pass_Down[1] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);
            Pass_Down[2] += random_in_range(-change_amount_Pass_Down, change_amount_Pass_Down);

<<<<<<< HEAD
            if (Pass_Down[0] < 0){Pass_Down[0] = 0;}if (Pass_Down[0] > biggest_element){{Pass_Down[0] = biggest_element - 1;}}

            if (Pass_Down[1] < 0){Pass_Down[1] = 0;}if (Pass_Down[1] > biggest_element){{Pass_Down[1] = biggest_element - 1;}}
        
            if (Pass_Down[2] < 0){Pass_Down[2] = 0;}if (Pass_Down[2] >= biggest_element){{Pass_Down[0] = biggest_element - 1;}}
=======
            if (Pass_Down[0] < 0){Pass_Down[0] = 0}if (Pass_Down[0] > biggest_element){{Pass_Down[0] = biggest_element - 1}}

            if (Pass_Down[1] < 0){Pass_Down[1] = 0}if (Pass_Down[1] > biggest_element){{Pass_Down[1] = biggest_element - 1}}
        
            if (Pass_Down[2] < 0){Pass_Down[2] = 0}if (Pass_Down[2] >= biggest_element){{Pass_Down[0] = biggest_element - 1}}
>>>>>>> 0212e9cd089fed41578e4726f1e856d08efe29c6
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
                Nurons.input = next_Pass_Down
                
<<<<<<< HEAD
            }
        }

        void mutate(int lowest_bar, int higest_bar, float replication_chance)
        {
            for (int i = 0; i < Nurons.size(); i++)
            {
                if (Nurons.size)
                if (randomFloat < replication_chance)
                {
                    Nurons.push_back();
                }
                Nurons()
=======
>>>>>>> 0212e9cd089fed41578e4726f1e856d08efe29c6
            }
        }
}
#endif