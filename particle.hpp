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
// extern struct particle_details;
// extern vector<particle_details> particle_detail;
extern int worldsize[2];
extern int chunk_size;
double walldamp = .1;



struct connection
    {
        int distance;
        double attraction;
    };
struct particle_detail
{
    int size;
    int outline_size;
    double damp;

    int inside_r;
    int inside_g;
    int inside_b;

    int outside_r;
    int outside_g;
    int outside_b;
    
    
    vector<connection>  connections;
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
       // double damp;

        //connections is equal to connections from main [id]
        //connections{id, distance, atraction}
        int id;
        
        
        particles() {

            void move(double ox, double oy, int attraction);

        }

        void test()
        {
            cout << "test" << endl;
        }
        
        double roughdistance(double ix, double iy)
        {
            double dx = abs(x - ix);
            double dy = abs(x - ix);

            double dist = .5 * (dx + dy + max(dx, dy));
            return(dist);
        }
        
        void update(int dt, int check, vector<particles> *particlesi, vector<int> neerby)
        {

            

            x += vx;// * dt;
            y += vy;// * dt;
            

            // vx *= damper;
            // vy *= damper;
            //cout << particle_details[id].damp << endl;
            vx *= particle_details[id].damp;
            vy *= particle_details[id].damp;

            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            particles p;
            double dist;
            double dx;
            double dy;
            double attractiontemp;
            double power;
            // printf("speed:");
            // cout << sqrt(vx*vx + vy*vy) << endl;
            for (int i = 0; i < neerby.size(); i++)
            
            {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                

                
                

                //dist = roughdistance(p.x, p.y);
                dist = sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );

                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);
                //cout << particle_details[id].connections[p.id].size();

                    //cout << particle_details[id].connections[p.id][0].attraction;
                neeraddvelocity(p.x, p.y, particle_details[id].connections[p.id].attraction, particle_details[id].connections[p.id].distance, dist);


            
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
                    
                    
                    tvx = vx;
                    tvy = vy;
                    circle_collision_result(dist, p.x, p.y, p.vx, p.vy, particle_details[p.id].size, particle_details[id].size);
                    particlesi->at(a).circle_collision_result(dist, x, y, tvx, tvy, particle_details[id].size, particle_details[p.id].size);

                    move(p.x, p.y, dist, attractiontemp);
                    particlesi->at(a).move(x, y, dist, attractiontemp);

                    particlesi->at(a).check_border();
                    // tvx = vx;
                    // tvy = vy;
                    // //cout << tvy / ((tvy + p.vy) *2) << endl;
                    // if (tvx + p.vx != 0)
                    // {
                    // vx *= tvx / ((tvx + p.vx) *2);
                    // p.vx *= p.vx / ((tvx + p.vx) *2);
                    // }
                    // if (tvy + p.vy != 0)
                    // {
                        
                    // vy *= tvy / ((tvy + p.vy) *2);
                    // p.vy *= p.vy / ((tvy + p.vy) *2);
                    // }
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
                vx *= -walldamp;
                //x += vx * 2;
                //vx *= 0;
            }
            if (x > (chunk_size * worldsize[0]) - 1) {
                x = chunk_size*worldsize[0] - 1;
                vx *= -walldamp;
                //x += vx * 2;
                //vx *= 0;
            }
            if (y <= 0) {
                y = 1;
                vy *= -walldamp;
               // vy *= 0;
                
            }
            if (y >= (chunk_size * worldsize[1]) - 1) {
                y = chunk_size * worldsize[1] -1;
                vy *= -walldamp;
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

        void circle_collision_result(double distance, double ox, double oy, double other_velocityx, double other_velocityy, double other_mass, double our_size)
        {
            
            double mass = our_size;

            // calculate the unit normal and tangential vectors
            double unx = (ox - x) / distance;
            double uny = (oy - y) / distance;
            double utx = -uny;
            double uty = unx;

            // calculate the scalar normal and tangential velocities
            double v1n = vx * unx + vy * uny;
            double v1t = vx * utx + vy * uty;
            double v2n = other_velocityx * unx + other_velocityy * uny;
            double v2t = other_velocityx * utx + other_velocityy * uty;

            // calculate the new scalar normal velocities
            double v1n_new = (v1n * (mass - other_mass) + 2 * other_mass * v2n) / (mass + other_mass);
            double v2n_new = (v2n * (other_mass - mass) + 2 * mass * v1n) / (mass + other_mass);

            // calculate the new vector velocities
            double v1x_new = v1n_new * unx + v1t * utx;
            double v1y_new = v1n_new * uny + v1t * uty;
            double v2x_new = v2n_new * unx + v2t * utx;
            double v2y_new = v2n_new * uny + v2t * uty;
            

            // assign the new velocities to the global variables
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

class Phermon: public particles{
    public:
        int id = 2;
    
        int inside_r;
        int inside_g;
        int inside_b;

        int outside_r;
        int outside_g;
        int outside_b;
        int duration;


        // Phermon()


};
class Cell: public particles{
    public:
        double energy;
        double id = 0;

        double max_size;
        double size;
        double outline_size;

        int inside_r;
        int inside_g;
        int inside_b;

        int outside_r;
        int outside_g;
        int outside_b;

        float mutation_rate;
        int lifetime = 0;

        int collisions = 0;
        bool dead = false;
        
        void Particle_Update(int dt, int check, vector<particles> *particlesi, vector<int> neerby)
        {

            

            x += vx;// * dt;
            y += vy;// * dt;
            

            // vx *= damper;
            // vy *= damper;
            //cout << particle_details[id].damp << endl;
            vx *= particle_details[id].damp;
            vy *= particle_details[id].damp;

            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            particles p;
            double dist;
            double dx;
            double dy;
            double attractiontemp;
            double power;
            // printf("speed:");
            // cout << sqrt(vx*vx + vy*vy) << endl;
            for (int i = 0; i < neerby.size(); i++)
            {
                
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                

                
                

                //dist = roughdistance(p.x, p.y);
                dist = sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );

                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);
                //cout << particle_details[id].connections[p.id].size();

                    //cout << particle_details[id].connections[p.id][0].attraction;
                neeraddvelocity(p.x, p.y, particle_details[id].connections[p.id].attraction, particle_details[id].connections[p.id].distance, dist);


            
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
                    
                    
                    tvx = vx;
                    tvy = vy;
                    
                    circle_collision_result(dist, p.x, p.y, p.vx, p.vy, particle_details[p.id].size, size);
                    
                    particlesi->at(a).circle_collision_result(dist, x, y, tvx, tvy, size, particle_details[p.id].size);
                    

                    move(p.x, p.y, dist, attractiontemp);
                    particlesi->at(a).move(x, y, dist, attractiontemp);

                    particlesi->at(a).check_border();
                    // tvx = vx;
                    // tvy = vy;
                    // //cout << tvy / ((tvy + p.vy) *2) << endl;
                    // if (tvx + p.vx != 0)
                    // {
                    // vx *= tvx / ((tvx + p.vx) *2);
                    // p.vx *= p.vx / ((tvx + p.vx) *2);
                    // }
                    // if (tvy + p.vy != 0)
                    // {
                        
                    // vy *= tvy / ((tvy + p.vy) *2);
                    // p.vy *= p.vy / ((tvy + p.vy) *2);
                    // }
                }


                    
            }}
        



            //x += vx;
            //y += vy;      
            //cout << 'd';
            //cout << x << ',' << y << endl;
            check_border();
        }

        void Cell_Update(int dt, int check, vector<Cell> *particlesi, vector<int> neerby)
        {

            

            x += vx;// * dt;
            y += vy;// * dt;
            

            // vx *= damper;
            // vy *= damper;
            //cout << particle_details[id].damp << endl;
            vx *= particle_details[id].damp;
            vy *= particle_details[id].damp;

            int cx = x / chunk_size;
            int cy = y / chunk_size;
            int a;
            Cell p;
            double dist;
            double dx;
            double dy;
            double attractiontemp;
            double power;
            // printf("speed:");
            // cout << sqrt(vx*vx + vy*vy) << endl;
            for (int i = 0; i < neerby.size(); i++)
            {
                
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                

                
                

                //dist = roughdistance(p.x, p.y);
                dist = sqrt( (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) );

                dx = x - p.x;
                dy = y - p.y;
                dist = sqrt(dx*dx + dy*dy);
                //cout << particle_details[id].connections[p.id].size();

                    //cout << particle_details[id].connections[p.id][0].attraction;

                //old:
                neeraddvelocity(p.x, p.y, particle_details[id].connections[p.id].attraction, particle_details[id].connections[p.id].distance * .25 * size, dist);
                //new:
                //neeraddvelocity(p.x, p.y, particle_details[id].connections[p.id].attraction, size + 5, dist);

            
            }

            double bounce_force;
            double tvx;
            double tvy;
            double temp_size =  size;
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
                if (dist <= size + p.size && dist != 0)
                {
                    
                    //cout << '8008' << endl;
                    // power = 1 / sqrt(vx*vx + vy*vy);
                    // //cout << vx << ',' << vy << endl;
                    // addvelocity(p.x, p.y, power * .5);
                    // p.addvelocity(x, y, power * .5);
                    
                    attractiontemp = ((size + p.size) - dist) * .5;
                    
                    
                    tvx = vx;
                    tvy = vy;
                    collisions ++;
                    circle_collision_result(dist, p.x, p.y, p.vx, p.vy, p.size, size);
                    p.collisions ++;
                    particlesi->at(a).circle_collision_result(dist, x, y, tvx, tvy, size, p.size);
                    

                    move(p.x, p.y, dist, attractiontemp);
                    particlesi->at(a).move(x, y, dist, attractiontemp);

                    particlesi->at(a).check_border();
                    if (p.size*2 < temp_size)
                    {
                        cout << "eaten" << endl;
                        energy += p.energy * .5;
                        p.energy = 0;
                        p.size = 0;
                        p.dead = true;
                    }
                    if (temp_size*2 < p.size)
                    {
                        
                        cout << "eaten" << endl;
                        p.energy += energy * .5;
                        energy = 0;
                        size = 0;
                        dead = true;
                    }

                    // tvx = vx;
                    // tvy = vy;
                    // //cout << tvy / ((tvy + p.vy) *2) << endl;
                    // if (tvx + p.vx != 0)
                    // {
                    // vx *= tvx / ((tvx + p.vx) *2);
                    // p.vx *= p.vx / ((tvx + p.vx) *2);
                    // }
                    // if (tvy + p.vy != 0)
                    // {
                        
                    // vy *= tvy / ((tvy + p.vy) *2);
                    // p.vy *= p.vy / ((tvy + p.vy) *2);
                    // }
                }


                    
            }}
        



            //x += vx;
            //y += vy;      
            //cout << 'd';
            //cout << x << ',' << y << endl;
            check_border();
        }
        void check_near(int dt, int check, vector<particles> *particlesi, vector<int> neerby)
        {
            particles p;
            int a;
            for (int i = 0; i < neerby.size(); i++)
            {
                a = neerby[i];
                //a = i;  
                //cout << a << endl;
                p = particlesi->at(a);
                double dist = sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));

                if (dist < 20)
                {
                    cout << "near" << endl;
                }
            }
            
        }

		void rotation_pherome_detection()
		{
		
		
		}
        void cell_update(int dt, int check, vector<particles> *particlesi, vector<Cell> *cellsi, vector<int> particle_neerby, vector<int> cell_neerby)
        {

            
            Particle_Update(dt, check, particlesi, particle_neerby);
            Cell_Update(dt, check, cellsi, cell_neerby);
            energy += .002 * dt;
            if (random_in_range(0, 1) == 0)
            {
                energy += .008 * dt;
            }
            energy -= size * .02;
            size = sqrt(energy);

            lifetime += 1 * dt;

            if (lifetime > 20000 * max_size)
            {
                dead = true;
            }
            else if(collisions > 2000 * size)
            {
                dead = true;
            }
            else if(energy < max_size * .25)
            {
                cout << "consumed" << endl;
                dead = true;
            }
        }

        Cell reproduce(Cell Input_Cell)
        {
            Cell outputcell = Input_Cell;
            
            
            //cout << "rbgf" << outputcell.inside_r << ", " << outputcell.inside_g << ", " << outputcell.inside_b << endl;
            if (randomFloat() < mutation_rate)
            {
                cout << "mut" << endl;
                int mut_amount = 50;
                outputcell.inside_r += random_in_range(-mut_amount, mut_amount);
                
                outputcell.inside_g += random_in_range(-mut_amount, mut_amount);

                outputcell.inside_b += random_in_range(-mut_amount, mut_amount);

                //cout << "rbgi" << outputcell.inside_r << ", " << outputcell.inside_g << ", " << outputcell.inside_b << endl;
                outputcell.max_size += random_in_range(-2, 2);
                if (outputcell.max_size < 3)
                {
                    outputcell.max_size  = 3;
                }

  

                
            }
            
            outputcell.x += random_in_range(-1, 1) * outputcell.size * 2;
            outputcell.y += random_in_range(-1, 1) * outputcell.size * 2;
            if (outputcell.inside_r > 255)
                {
                    outputcell.inside_r = 255;
                }
                if (outputcell.inside_r < 0)
                {
                    outputcell.inside_r = 0;
                }
                if (outputcell.inside_g > 255)
                {
                    outputcell.inside_g = 255;
                }
                if (outputcell.inside_g < 0)
                {
                    outputcell.inside_g = 0;
                }

                if (outputcell.inside_b > 255)
                {
                    outputcell.inside_b = 255;
                }
                if (outputcell.inside_b < 0)
                {
                    outputcell.inside_b = 0;
                }
            //cout << "rbg" << outputcell.inside_r << ", " << outputcell.inside_g << ", " << outputcell.inside_b << endl;
            outputcell.lifetime = 0;
            outputcell.dead = false;
            outputcell.collisions = 0;
            return(outputcell);
        }


};



#endif