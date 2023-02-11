#include <stdio.h>

#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <ctime>
#include "particle.hpp"
#include "preformance.hpp"
#include "debughelp.hpp"
#include <stdio.h>
#include<tuple>
#include <vector>
#include <random>
#include <chrono>

struct connections
    {
        double dist;
        double attraction;
        int id;
    };

struct particle_details
{
    

    //int color[3];
    double size;
    double damp;
    //sh::Color color(0, 0, 255);
    vector<connections> connection;
};

int main()
{
    
    vector<particle_details> particle_detail;
    
    particle_detail[0].size = 5;
    particle_detail[0].connection[0];
    
    particle_detail[0].connection[0].id = 0;
    particle_detail[0].connection[0].dist = 10;
    particle_detail[0].connection[0].attraction = 0.001;
}
