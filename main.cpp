
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <iostream>
#include <ctime>
#include "particle.hpp"
#include "preformance.hpp"
#include <stdio.h>
#include<tuple>
#include <vector>
#include <random>
#include <chrono>
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

vector<vector<int> > defalt_gmap()
{
    vector<vector<int> > vec(worldsize[0], vector<int>(worldsize[1]));
    for (int j = 0; j < worldsize[0]; j++) {
      std::fill(vec[j].begin(), vec[j].end(), 0);
    }
    return vec;
}
vector<vector<vector<int> > > vel_gmap()
{
    //vector<vector<vector<int> > > vec(worldsize[0], vector<vector<int> >(worldsize[1], vector<int>(2)));
    std::vector<std::vector<std::vector<int> > > vec(worldsize[0], std::vector<std::vector<int> >(worldsize[1], std::vector<int>(2)));

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
    int randomthing = random_in_range(0, 10);
    cout << randomthing << endl;
    vector<vector<int> > dgmap = defalt_gmap();
    vector<vector<int> > gmap = dgmap;
    vector<vector<vector<int> > > dvelmap = vel_gmap();
    vector<vector<vector<int> > > velmap;

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Space Particles");
    window.setVisible(true);
    sf::CircleShape shape(1.0);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2i position = sf::Mouse::getPosition(window);
    

    //particles test(10, 10);
    //auto pr;

    
    //vector<vector<vector<int> > > map = chunk();
    vector<particles> allp;  
    
    for (int i = 0; i < 200; i++)
    {
        for (int a = 0; a < 120; a++)
        {
        allp.push_back(particles());
        allp[allp.size() - 1].x = i * 5;
        allp[allp.size() - 1].y = a * 5;
        allp[allp.size() - 1].damp = 1;
        allp[allp.size() - 1].id = 0;
        //cout << allp[i].x << endl;
        }
    }

    
    
    //cout << len(temp) << endl;
    
    vector<vector<vector<int> > > map;
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    double dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    int cx;
    int cy;
    while (window.isOpen())
    {   
        start = std::chrono::system_clock::now();
        sf::Event event;
        window.clear();
        while (window.pollEvent(event))
        {


            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        
        for (int i = 0; i < allp.size(); i++)
        {
            shape.setPosition(allp[i].x, allp[i].y);
            window.draw(shape);
            //allp.
            //allp[i].addgravvelocity(501, 300, -.00005 * dt);
            //allp[i].addgravvelocity(500, 300, -.00005 * dt);
            allp[i].update();
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            gmap[cx][cy] += 1;
        }

        //(vector<vector<double> > gmap, int worldsize[2], int chunk_size, vector<vector<vector<double> > > defalt)
        velmap = velocityfeild(gmap, worldsize, chunk_size, dvelmap);
        //cout << velmap[0][0][0]; cout << ','; cout << velmap[0][0][1] << endl;

        window.display();
        vector<vector<vector<int> > > map = chunk();
        //cout << map[1][1][0] << endl;
        //out << map[1][1][0] << endl;
    
        position = sf::Mouse::getPosition(window);
    
        gmap = dgmap;
        end = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        //cout << dt << endl;

    }

    return 0;
}