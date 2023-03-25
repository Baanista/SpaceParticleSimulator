
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <ctime>
#include "particle.hpp"
#include "preformance.hpp"
#include "debughelp.hpp"
#include "gameterminal.hpp"
#include <stdio.h>
#include<tuple>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
using namespace std;


int worldsize[2] = {10, 6};
int chunk_size = 100;
vector<particles> allp;



vector<vector<vector<int> > > chunk()
{
    vector<vector<vector<int> > > map(worldsize[0], vector<vector<int> >(worldsize[1]));
    
    register int cx;
    register int cy;
    
    for (int i = 0; i < allp.size(); i++)
    {
        cx = allp[i].x / chunk_size;
        cy = allp[i].y / chunk_size;
        
        //len = sizeof(map[cx][cy]) / sizeof(map[cx][cy]);
        map[cx][cy].push_back(i);
    }


    return(map);

}

vector<vector<double> > defalt_gmap()
{
    vector<vector<double> > vec(worldsize[0], vector<double>(worldsize[1]));
    for (int j = 0; j < worldsize[0]; j++) {
      std::fill(vec[j].begin(), vec[j].end(), 0.0);
    }
    return vec;
}



vector<vector<vector<double> > > vel_gmap()
{
    //vector<vector<vector<int> > > vec(worldsize[0], vector<vector<int> >(worldsize[1], vector<int>(2)));
    std::vector<std::vector<std::vector<double> > > vec(worldsize[0], std::vector<std::vector<double> >(worldsize[1], std::vector<double>(2)));

    for (int x = 0; x < worldsize[0]; x++)
    {
        for (int y = 0; y < worldsize[1]; y++)
        {
            for (int i = 0; i < 2; i++)
            {
                vec[x][y][i] = 0;
            }
        }
    }
    return vec;
}

vector<particle_detail> particle_details;
int main()
{
    particle_detail tempdetails;
    tempdetails.size =5;
    tempdetails.outline_size =0;
    tempdetails.inside_r = 255;
    tempdetails.inside_b = 255;
    tempdetails.inside_g = 255;
    tempdetails.outside_r = 255;
    tempdetails.outside_b = 0;
    tempdetails.outside_g = 0;
    connection tempconection;
    tempconection.attraction = -.01;
    tempconection.distance = 0;
    tempdetails.connections.push_back(tempconection);
    tempconection.attraction = -.002;
    tempconection.distance = 20;
    tempdetails.connections.push_back(tempconection);
    

    particle_details.push_back(tempdetails);
    
    tempdetails.size =5;
    tempdetails.outline_size = 2;
    tempdetails.inside_r = 255;
    tempdetails.inside_b = 0;
    tempdetails.inside_g = 255;
    tempdetails.outside_r = 0;
    tempdetails.outside_b = 255;
    tempdetails.outside_g = 0;
    
    tempconection.attraction = .1;
    tempconection.distance = 0;
    tempdetails.connections.push_back(tempconection);
    
    
    tempconection.attraction = -.002;
    tempconection.distance = 20;
    tempdetails.connections.push_back(tempconection);
    
    particle_details.push_back(tempdetails);
    // particle_details[0].size = 5;
    // particle_details[0].r = 255;
    // particle_details[0].b = 255;
    // particle_details[0].g = 255;
    // particle_detail[0].connection[0];
    
    // particle_detail[0].connection[0].id = 0;
    // particle_detail[0].connection[0].dist = 10;
    // particle_detail[0].connection[0].attraction = 0.001;    
    
    

    vector<vector<vector<int> > > map(worldsize[0], vector<vector<int> >(worldsize[1]));
    vector<vector<vector<int> > > dmap(worldsize[0], vector<vector<int> >(worldsize[1]));

    int randomthing = random_in_range(0, 10);
    cout << randomthing << endl;
    vector<vector<double> > dgmap = defalt_gmap();
    vector<vector<double> > gmap = dgmap;
    vector<vector<vector<double> > > dvelmap = vel_gmap();
    vector<vector<vector<double> > > velmap = velocityfeild(gmap, worldsize, chunk_size, dvelmap);;

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Space Particles");
    window.setVisible(true);

    
    
    

    sf::Vector2i position = sf::Mouse::getPosition(window);
    
    

    //particles test(10, 10);
    //auto pr;

    
    //vector<vector<vector<int> > > map = chunk();
    vector<particles> allp;  
    
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    int cx;
    int cy;
    double vxm;
    double vym;
    bool held = false;
    //char v = 'v';
    vector<particles> *allp_adr = &allp;
    //vector<particle_details> *pd = &particle_detail;
    double funidamp = 1;
    double unidamp = .1;
    int selected_id = 0;
    
    while (window.isOpen())
    {    
        start = std::chrono::system_clock::now();
        sf::Event event;
        window.clear();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                held = true;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                held = false;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::S)
            {
                for (int i = 0; i < 10; i++)
                {
                    for (int a = 0; a < 10; a++)
                    {
                        allp.push_back(particles());
                        allp[allp.size() - 1].x = 10 * i + position.x;
                        allp[allp.size() - 1].y = 10 * a + position.y;
                        allp[allp.size() - 1].damp = unidamp;
                        allp[allp.size() - 1].id = selected_id;
                        //allp[allp.size() - 1].vx = .5;

                        gmap[allp[i].x/chunk_size][allp[i].y/chunk_size] += 1.0;
        //cout << allp[i].x << endl;
        }
    }
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::O)
            {
                allp.push_back(particles());
                allp[allp.size() - 1].x = position.x;
                allp[allp.size() - 1].y = position.y;
                allp[allp.size() - 1].damp = unidamp;
                allp[allp.size() - 1].id = 0;
                allp[allp.size() - 1].vx = 1;
        }}
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Tab)
            {
                cout << "hello" << endl;
                gameterminal();
            }
        }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        map = dmap;
        map = change_map(map);
        velmap = dvelmap;
        unidamp = pow(funidamp, (dt/20));
        for (int i = 0; i < allp.size(); i++)
        {

            int id = allp[i].id;
            sf::CircleShape shape(particle_details[id].size);
            shape.setOutlineThickness(particle_details[id].outline_size);
            shape.setFillColor(sf::Color(particle_details[id].inside_r, particle_details[id].inside_g, particle_details[id].inside_b));
            shape.setOutlineColor(sf::Color(particle_details[id].outside_r, particle_details[id].outside_g, particle_details[id].outside_b));
            shape.setPosition(allp[i].x, allp[i].y);
            window.draw(shape);

            //window.draw(shape);
               
            //allp[i].addgravvelocity(501, 300, -.00005 * dt);
            //allp[i].addgravvelocity(500, 300, -.00005 * dt);
            
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            
            map[cx][cy].push_back(i);
            //cout << i << endl;
            //printvecint(map[cx][cy]);
            gmap[cx][cy] += 100.0;
            //cout << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;
            vxm = velmap[cx][cy][0];
            vym = velmap[cx][cy][1];
            //cout << vxm << vym <<endl;
            //allp[i].vx += (vxm * dt);
            
            //allp[i].vy += (vym * dt);
            allp[i].vy += .008;
            //cout << gmap[cx][cy] << endl;
            //cout << gmap[cx][cy] << endl;
            //cout << i << '|' << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;
            

        }

        map = change_map(map);

        for (int i = 0; i < allp.size(); i++)
        {
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            //printvecint(map[cx][cy]); 
            allp[i].update(dt, i, allp_adr, map[cx][cy], unidamp);
        }

        //cout << allp.size() - 1 <<endl;

        //cout << &allp << end;
        
        
        if (held)
        {
            allp.push_back(particles());
            allp[allp.size() - 1].x = position.x;
            allp[allp.size() - 1].y = position.y;
            allp[allp.size() - 1].damp = unidamp;
            allp[allp.size() - 1].id = selected_id;
            
        }
        //(vector<vector<double> > gmap, int worldsize[2], int chunk_size, vector<vector<vector<double> > > defalt)
        
        //cout << velmap[0][0][1] << cout << ','; cout << velmap[0][0][1] << endl;
        velmap = velocityfeild(gmap, worldsize, chunk_size, dvelmap);
        window.display();
        vector<vector<vector<int> > > map = chunk();
        //cout << map[1][1][0] << endl;
        //out << map[1][1][0] << endl;
        //break;
        position = sf::Mouse::getPosition(window);
        
        
        gmap = dgmap;
        end = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        printf("fps: ");
        cout << 1000/dt << endl;
        //cout <<  allp.size() << endl;
        dt = 1;
        //dt = 1/dt * 20;
    }

    return 0;
}   