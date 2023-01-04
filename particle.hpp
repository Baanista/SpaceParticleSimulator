#ifndef particle_HPP
#define particle_HPP
#include <cmath>
//#include "jsoncpp-master/include/json/json.h"
extern int worldsize[2];
extern int chunk_size;
#include <iostream>
using namespace std;
#include <vector>

//this is the class for a defalt particle
class particles
{
    public:
        //position
        double x;
        double y;

        //velocities
        double vx = 0;
        double vy = 0;

        //damp is the loss of velocity due to friction
        double damp;

        //connections is equal to connections from main [id]
        //connections{id, distance, atraction}
        int id;
        

        particles() {

            void move(double ox, double oy, int attraction);

        }
        void update(int dt, int check, vector<particles> *particlesi, vector<int> neerby)
        {

            

            x += vx;
            y += vy;

            vx *= damp;
            vy *= damp;

            if (x < 0) {
                x = 1;
                vx *= -1;
                //x += vx * 2;
            }
            if (x > (chunk_size * worldsize[0]) - 1) {
                x = chunk_size*worldsize[0] - 1;
                vx *= -1;
                //x += vx * 2;
            }
            if (y <= 0) {
                y = 1;
                vy *= -1;
                
            }
            if (y >= (chunk_size * worldsize[1]) - 1) {
                y = chunk_size * worldsize[1] -1;
                vy *= -1;
                
                  
            }
            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            particles p;
            /*
            for (int i = 0; i < neerby.size(); i++)
            {
                //a = map[cx][cy][i];
                a = neerby[i];
                cout << a << ',';
            }
            cout << endl;*/
            for (int i = 0; i < neerby.size(); i++)
            {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                neeraddvelocity(p.x, p.y, -.00005 * dt, 30);
                neeraddvelocity(p.x, p.y, .002 * dt, 10);
            }

            //x += vx;
            //y += vy;
            //cout << 'd';
            //cout << x << ',' << y << endl;
        }
        
        void addgravvelocity(double ox, double oy, double attraction)
        {

            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            //cout << dist << endl;
            if (!(dist == 0))
            {
            double div = attraction / dist;

            vx += ((x - ox) * div);
            vy += ((y - oy) * div);
            }
            
        }

        //changes velocity
        void addvelocity(double ox, double oy, double attraction)
        {
            double dist = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));

            
            if (!(dist == 0))
            {
            double div = dist / attraction;

            vx += ((x - ox) / div);
            vy += ((y - oy) / div);
            }
        }
        void neeraddvelocity(double ox, double oy, double attraction, double distance)
        {
            double distl = sqrt((x - ox)*(x - ox) + (y - oy)*(y - oy));
            if (distl <= distance)
            {
                addvelocity(ox, oy, attraction);
            }
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