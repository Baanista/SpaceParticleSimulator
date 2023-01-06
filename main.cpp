
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
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
using namespace std;


int worldsize[2] = {13, 8};
int chunk_size = 75;
vector<particles> allp;



struct particle_details
{
    struct connections
    {
        double dist;
        double attraction;
        int id;
    };

    int color[3];
    double size;
    double damp;
    vector<connections> connection;
};

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

//std::vector<std::vector<std::vector<int>>> connections;
int main()
{
    /*
    vector<particle_details> particle_details;
    
    particle_details[0].size = 5;
    //particle_details[0].connection.push_back(connections);
    particle_details[0].connection[0].id = 0;
    particle_details[0].connection[0].dist = 10;
    particle_details[0].connection[0].attraction = 0.001;*/
    
    

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
    
    /*for (int i = 0; i < 250; i++)
    {
        for (int a = 0; a < 150; a++)
        {
        allp.push_back(particles());
        allp[allp.size() - 1].x = i*4;
        allp[allp.size() - 1].y = a*4;
        allp[allp.size() - 1].damp = 1;
        allp[allp.size() - 1].id = 0;

        gmap[allp[i].x/chunk_size][allp[i].y/chunk_size] += 1.0;
        //cout << allp[i].x << endl;
        }
    }*/

    
    
    //cout << len(temp) << endl;
    
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
    double unidamp = .95;
    
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
                for (int i = 0; i < 5; i++)
                {
                    for (int a = 0; a < 5; a++)
                    {
                        allp.push_back(particles());
                        allp[allp.size() - 1].x = 10 * i + position.x;
                        allp[allp.size() - 1].y = 10 * a + position.y;
                        allp[allp.size() - 1].damp = unidamp;
                        allp[allp.size() - 1].id = 0;

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
        }}
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        map = dmap;
        //map = change_map(map);
        for (int i = 0; i < allp.size(); i++)
        {

            sf::CircleShape shape(1);
            shape.setFillColor(sf::Color::Red);
            shape.setPosition(allp[i].x, allp[i].y);
            window.draw(shape);
            //allp[i].addgravvelocity(501, 300, -.00005 * dt);
            //allp[i].addgravvelocity(500, 300, -.00005 * dt);
            
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            
            map[cx][cy].push_back(i);
            //cout << i << endl;
            //printvecint(map[cx][cy]);
            gmap[cx][cy] += 10.0;
            //cout << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;
            vxm = velmap[cx][cy][0];
            vym = velmap[cx][cy][1];
            //allp[i].vx += (vxm * dt);
            //allp[i].vy += (vym * dt);
            allp[i].vy += .002 * dt;
            
            //cout << gmap[cx][cy] << endl;
            //cout << i << '|' << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;
            

        }

        map = change_map(map);

        for (int i = 0; i < allp.size(); i++)
        {
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            //printvecint(map[cx][cy]); 
            allp[i].update(dt, i, allp_adr, map[cx][cy]);
        }

        //cout << allp.size() - 1 <<endl;

        //cout << &allp << end;
        
        
        if (held)
        {
            allp.push_back(particles());
            allp[allp.size() - 1].x = position.x;
            allp[allp.size() - 1].y = position.y;
            allp[allp.size() - 1].damp = unidamp;
            allp[allp.size() - 1].id = 0;
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
        //velmap = dvelmap;
        
        gmap = dgmap;
        end = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        cout << (1 / dt) * 1000 << endl;

    }

    return 0;
}