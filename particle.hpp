#ifndef particle_HPP
#define particle_HPP
#include <cmath>
//#include "jsoncpp-master/include/json/json.h"
#include <cmath>
#include <iostream>
using namespace std;
#include <vector>
#include <cstdio>
// extern struct particle_details;
// extern vector<particle_details> particle_detail;
extern int worldsize[2];
extern int chunk_size;


struct connection
    {
        int distance;
        double attraction;
    };
struct particle_detail
{
    int size;
    int outline_size;

    int inside_r;
    int inside_g;
    int inside_b;

    int outside_r;
    int outside_g;
    int outside_b;
    
    
    vector<connection> connections;
};
extern vector<particle_detail> particle_details;
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
        
        double roughdistance(double ix, double iy)
        {
            double dx = abs(x - ix);
            double dy = abs(x - ix);

            double dist = .5 * (dx + dy + max(dx, dy));
            return(dist);
        }
        
        void update(int dt, int check, vector<particles> *particlesi, vector<int> neerby, double damper)
        {

            

            x += vx * dt;
            y += vy * dt;

            vx *= damper;
            vy *= damper;


            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            particles p;
            double dist;
            double dx;
            double dy;
            double attractiontemp;
            double power;
            for (int i = 0; i < neerby.size(); i++)
            
            {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                

                
                

                //dist = roughdistance(p.x, p.y);
                dist = sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );
                //neeraddvelocity(p.x, p.y, -.001 * dt, 60, dist);
                /*
                for (int z = 0; z < particle_detailid.connection.size(); z++)
                {
                    neeraddvelocity(p.x, p.y, particle_detail[p.id].connections[z].attraction * dt, 10, dist);
                }*/
                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);
                
                
                neeraddvelocity(p.x, p.y, particle_details[id].connections[p.id].attraction, particle_details[id].connections[p.id].distance, dist);
                //neeraddvelocity(p.x, p.y, .0008 * dt, particle_details[id].size*2, dist);
                
                //neeraddvelocity(p.x, p.y, -.002 * dt, 15, dist);
                //neeraddvelocity(p.x, p.y, -.002 * dt, 15, dist);
                // if (dist <= 10)
                // {
                // attractiontemp = (5 - dist) * .5;
                // power = sqrt(vx*vx + vy*vy) * .5;
                // //neeraddvelocity(p.x, p.y, power, 10, dist);
                
                // move(p.x, p.y, dist, 10);
                // p.move(x, y, dist, 10);
                
                // // vx *= -1 * p.vx;
                // // vy *= -1 * p.vy;
                
                // }
                // for (int a = 0; i < 4; a++)
                // {
                //     if (dist <= 10)
                //     {
                //     attractiontemp = (10 - dist) * .5;
                //     move(p.x, p.y, dist, attractiontemp);
                //     //p.move(x, y, dist, attractiontemp);
                //     }
                // }
                
                //addgravvelocity(p.x, p.y, -.00001 * dt);
            
            }
            double bounce_force;
            double tvx;
            double tvy;
            for (int j = 0; j < 8; j++){
            for (int i = 0; i < neerby.size(); i++)
                {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);
                int (particles::*Pmove)(double, double, double, double);
                if (dist <= particle_details[id].size + particle_details[p.id].size && dist != 0)
                {
                    
                    //cout << '8008' << endl;
                    // power = 1 / sqrt(vx*vx + vy*vy);
                    // //cout << vx << ',' << vy << endl;
                    // addvelocity(p.x, p.y, power * .5);
                    // p.addvelocity(x, y, power * .5);
                    attractiontemp = ((particle_details[id].size + particle_details[p.id].size) - dist) * .5;
                    


                    circle_collision_result(dist, p.x, p.y, p.vx, p.vy, particle_details[p.id].size);
                    particlesi->at(a).circle_collision_result(dist, x, y, vx, vy, particle_details[id].size);

                    move(p.x, p.y, dist, attractiontemp);
                    particlesi->at(a).move(x, y, dist, attractiontemp);

                    particlesi->at(a).check_border();


                }


                    
            }}
        



            //x += vx;
            //y += vy;      
            //cout << 'd';
            //cout << x << ',' << y << endl;
            check_border();
        }
        void check_border()
        {
                                    if (x < 0) {
                x = 1;
                vx *= -1;
                //x += vx * 2;
                //vx *= 0;
            }
            if (x > (chunk_size * worldsize[0]) - 1) {
                x = chunk_size*worldsize[0] - 1;
                vx *= -1;
                //x += vx * 2;
                //vx *= 0;
            }
            if (y <= 0) {
                y = 1;
                vy *= -1;
               // vy *= 0;
                
            }
            if (y >= (chunk_size * worldsize[1]) - 1) {
                y = chunk_size * worldsize[1] -1;
                vy *= -1;
                //vy *= 0;
                
                  
            }
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
        void circle_collision_result(double distance, double ox, double oy, double other_velocityx, double other_velocityy, double other_mass)
            {
                // Get this particle's mass and velocity
                double mass = particle_details[id].size;

                // Calculate the unit normal vector and unit tangent vector
                double nx = (ox - x) / distance;
                double ny = (oy - y) / distance;
                double tx = -ny;
                double ty = nx;

                // Calculate the dot product of the velocity and the unit normal and tangent vectors
                double v1n = vx * nx + vy * ny;
                double v1t = vx * tx + vy * ty;
                double v2n = other_velocityx * nx + other_velocityy * ny;
                double v2t = other_velocityx * tx + other_velocityy * ty;

                // Calculate the new normal velocities after the collision
                double v1n_new = (v1n * (mass - other_mass) + 2 * other_mass * v2n) / (mass + other_mass);

                // Convert the scalar normal and tangent velocities back to vector form
                double v1n_newx = v1n_new * nx;
                double v1n_newy = v1n_new * ny;
                double v1t_newx = v1t * tx;
                double v1t_newy = v1t * ty;



                // Calculate the new velocities after the collision
                double v1x_new = v1n_newx + v1t_newx;
                double v1y_new = v1n_newy + v1t_newy;


                // Set the new velocities for both particles
                vx = v1x_new;
                vy = v1y_new;
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
        void neeraddvelocity(double ox, double oy, double attraction, double distance, double distl)
        {
            
            if (distl <= distance)
            {
                addvelocity(ox, oy, attraction);
                //vx += ovx * .001;
                //vy += ovy * .001;
                //addvelocity(ox, oy, -(1.5/(distl+.5))-(attraction/(distl-distance-.5)));
                
            }
        }
        void neeraddvelocitygrav(double ox, double oy, double attraction, double distance, double distl)
        {
            
            if (distl <= distance)
            {
                addgravvelocity(ox, oy, attraction);
                //vx += ovx * .001;
                //vy += ovy * .001;
                //addvelocity(ox, oy, -(1.5/(distl+.5))-(attraction/(distl-distance-.5)));
                
            }
        }
        //this function moves the particle to a location in one step depending on the attraction value
        void move(double ox, double oy, double dist, double attraction)
        {
            //printf("what");
            if (!(dist == 0))
            {
            x += ((x - ox) / ((dist / attraction)));
            y += ((y - oy) / ((dist / attraction)));
            }
        }
        #include <cmath>




};






#endif