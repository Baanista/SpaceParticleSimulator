#ifndef particle_HPP
#define particle_HPP
#include <cmath>
//#include "jsoncpp-master/include/json/json.h"
extern int worldsize[2];
extern int chunk_size;
#include <iostream>
using namespace std;

//this is the class for a defalt particle
class particles
{
    public:
        //position
        double x;
        double y;

        //velocities
        double vx;
        double vy;

        //damp is the loss of velocity due to friction
        double damp;

        //connections is equal to connections from main [id]
        //connections{id, distance, atraction}
        int id;
        

        particles() {

            void move(double ox, double oy, int attraction);

        }
        void update()
        {

            

            x += vx;
            y += vy;

            vx *= damp;
            vy *= damp;

            if (x < 0) {
                x = 1;
                vx *= -1;
            } else if (x > chunk_size*worldsize[0]) {
                x = chunk_size*worldsize[0] -1;
                vx *= -1;
            } else if (y < 0) {
                y = 1;
                vy *= -1;
            } else if (y > chunk_size*worldsize[1]) {
                y = chunk_size*worldsize[1] - 1;
                vy *= -1;
            }
        }
        
        void addgravvelocity(double ox, double oy, double attraction)
        {

            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            //cout << dist << endl;
            
            double div = attraction / dist;

            vx += ((x - ox) * div);
            vy += ((y - oy) * div);

            
        }

        //changes velocity
        void addvelocity(double ox, double oy, double attraction)
        {
            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            //cout << dist << endl;
            
            double div = dist / attraction;

            vx += ((x - ox) / div);
            vy += ((y - oy) / div);
        }

        //this function moves the particle to a location in one step depending on the attraction value
        void move(double ox, double oy, double attraction)
        {

            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            //cout << dist << endl;

            x += ((x - ox) / ((dist / attraction)));
            y += ((y - oy) / ((dist / attraction)));
        }

};






#endif