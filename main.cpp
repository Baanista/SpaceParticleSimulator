
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <iostream>
using namespace std;
#include "particle.hpp"
#include "preformance.hpp"
#include <stdio.h>
#include<tuple>
#include <vector>

int worldsize[2] = {10, 6};
int chunk_size = 100;

//std::vector<std::vector<std::vector<int>>> connections;
int main()
{

    cout << "hello" << endl;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Space Particles");
    window.setVisible(true);
    sf::CircleShape shape(10.0);
    shape.setFillColor(sf::Color::Green);

    sf::Vector2i position = sf::Mouse::getPosition(window);

    //particles test(10, 10);
    //auto pr;

    int worldsize[2] = {10, 6};
    int chunk_size = 100;
    particles allp[30];

    allp[0].x = 100.0;
    allp[0].y = 100.0;
    allp[0].damp = 1;
    allp[0].id = 0;

    double connections[10][10][10][2];
    connections[0][0][0][0] = 100.0;
    connections[0][0][0][1] = -.0001;

    allp[0].move(1, 1, 10);
    

    //cout << allp[0].x << allp[0].y << endl;
    int temp[3] = {1, 2, 3};
    //cout << len(temp) << endl;
    shape.setPosition(allp[0].x, allp[0].y);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {


            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //cout << x << endl;
        shape.setPosition(allp[0].x, allp[0].y);
        window.clear();
        window.draw(shape);
        window.display();
        //allp[0].addvelocity(position.x, position.y, -.0001);
        allp[0].update();
        //cout << 'particle pos: ';
        //cout << allp[0].x << endl;
        //cout << ',' << endl;
        //cout << allp[0].y << endl;
        //cout << ' ' << endl;
        //cout << 'test' << endl;
        position = sf::Mouse::getPosition(window);
        //window.setSize(sf::Vector2u(window.getSize()))
        

        //cout << 'mpos: ';
        //cout << position.x << ', ' << position.y << endl;


    }

    return 0;
}