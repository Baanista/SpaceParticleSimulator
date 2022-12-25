
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <iostream>
using namespace std;
#include "particle.hpp"
#include "preformance.hpp"
#include <stdio.h>
#include<tuple>
#include <vector>
#include <random>

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


//std::vector<std::vector<std::vector<int>>> connections;
int main()
{

    
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Space Particles");
    window.setVisible(true);
    sf::CircleShape shape(10.0);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2i position = sf::Mouse::getPosition(window);
    

    //particles test(10, 10);
    //auto pr;

    
    
    vector<particles> allp;
    cout << "hello" << endl;
    
    for (int i = 0; i < 1000; i++)
    {
        allp.push_back(particles());
        allp[i].x = i;
        allp[i].y = 2;
        allp[i].damp = 1;
        allp[i].id = 0;
        
    }

    
    
    //cout << len(temp) << endl;
    shape.setPosition(allp[0].x, allp[0].y);
    vector<vector<vector<int> > > map;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {


            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        for (int i = 0; i < allp.size(); i++)
        {
        shape.setPosition(allp[i].x, allp[i].y);
        window.draw(shape);
        //allp[i].addvelocity(position.x, position.y, -.0005);
        allp[i].addvelocity(500, 300, -.0001);
        allp[i].update();
        }
        window.display();
        map = chunk();

        //out << map[1][1][0] << endl;
    
        position = sf::Mouse::getPosition(window);
        //window.setSize(sf::Vector2u(window.getSize()))
        


    }

    return 0;
}