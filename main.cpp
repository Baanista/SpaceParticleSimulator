
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
#include <thread>
using namespace std;

int max_particle_types = 100;
int selected_id = 0;
int worldsize[2] = {10, 6};
int chunk_size = 100;
vector<particles> allp;
vector<Cell> allcells;
vector<Cell> *allcells_adr = &allcells;
vector<particle_detail> particle_details;
vector<particles> *allp_adr = &allp;


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

// void threadedupdate(int anount_of_thread)
// {

// }

particle_detail add_particle_detail(int size, int outline_size, double damp, int inside_r, int inside_b, int inside_g, int outside_r, int outside_b, int outside_g)
{
    particle_detail output_details;
    output_details.size =size;
    output_details.outline_size =outline_size;
    output_details.damp = damp;
    output_details.inside_r = inside_r;
    output_details.inside_b = inside_b;
    output_details.inside_g = inside_g;
    output_details.outside_r = outside_r;
    output_details.outside_b = outside_b;
    output_details.outside_g = outside_g;

    connection zero_connection;
    zero_connection.attraction = 0;
    zero_connection.distance = 0;
    
    for (int i = 0; i < max_particle_types; i++)
    {
        output_details.connections.push_back(zero_connection);
    }

    return(output_details);
}

void gameterminal()
{
    string command;

    while (command != "end")
    {
        cout << ">";
        cin >> command;
        if (command == "id")
        {
            cout << "id: ";
            cin >> selected_id;
        }
        else if (command == "num_types")
        {
            cout << particle_details.size() << endl;
        }
        else if (command == "edit")
        {
            
            string edit_commands;
            int edit_id = selected_id;
            int connection_id;
            while (edit_commands != "end")
            {
            cout << "e>";
            if (edit_commands == "id")
            {
                cin >> edit_id;
            }
            if (edit_commands == "size")
            {
                cout << particle_details[edit_id].size;
                cin >> particle_details[edit_id].size;
                cout << particle_details[edit_id].size;
            }
            if (edit_commands == "outline_size")
            {
                cin >> particle_details[edit_id].outline_size;
            }
            if (edit_commands == "outline_size")
            {
                cin >> particle_details[edit_id].outline_size;
            }
            if (edit_commands == "damp")
            {
                cin >> particle_details[edit_id].damp;
            }
            if (edit_commands == "inside_r")
            {
                cin >> particle_details[edit_id].inside_r;
            }
                
            
            if (edit_commands == "inside_b")
            {
                cin >> particle_details[edit_id].inside_b;
            };
            if (edit_commands == "inside_g")
            {
                cin >> particle_details[edit_id].inside_g;
            }
            if (edit_commands == "outside_r")
            {
                cin >> particle_details[edit_id].outside_r;
            }
            if (edit_commands == "outside_b")
            {
                cin >> particle_details[edit_id].outside_b;
            }
            if (edit_commands == "outside_g")
            {
                cin >> particle_details[edit_id].outside_g;
            }
            if (edit_commands == "connections")
            {
                cout << "id connection you are editing:";
                cin >> connection_id;
                cout << "Distance:";
                cin >> particle_details[edit_id].connections[connection_id].distance;
                cout << "Attraction:";
                cin >> particle_details[edit_id].connections[connection_id].attraction;
            }
            
                cin >> edit_commands;
            }
        }
        else if (command == "add")
        {   
            int size;
            int outline_size;
            double damp;
            int inside_r;
            int inside_b;
            int inside_g;
            int outside_r;
            int outside_b;
            int outside_g;
            cout << "size: ";
            cin >> size;
            cout << "outline_size: ";
            cin >> outline_size;
            cout << "damp: ";
            cin >> damp;
            cout << "inside_r: ";
            cin >> inside_r;
            cout << "inside_b: ";
            cin >> inside_b;
            cout << "inside_g: ";
            cin >> inside_g;
            cout << "outside_r: ";
            cin >> outside_r;
            cout << "outside_b: ";
            cin >> outside_b;
            cout << "outside_g: ";
            cin >> outside_g;
            particle_detail tempdetails = add_particle_detail(size, outline_size, damp, inside_r, inside_b, inside_g,outside_r, outside_b, outside_g);
        }
    }
}  

void onethread(int dt, int check, vector<particles> *particlesi, vector<int> neerby)
{
    cout << "test";
    //allp[i].update(dt, i, allp_adr, map[cx][cy]);
    allp[check].update(dt, check, particlesi, neerby);
}
// void onethread()
// {
//     cout << "test";
// }


int main()
{
    particle_detail tempdetails = add_particle_detail(10, 0, .99, 255, 255, 255, 255, 0, 0);
    tempdetails.connections[0].attraction = -.01;
    tempdetails.connections[0].distance = 25;
    tempdetails.connections[1].attraction = -.1;
    tempdetails.connections[1].distance = 40;
    particle_details.push_back(tempdetails);
    
    tempdetails = add_particle_detail(5, 0, .99, 255, 255, 0, 255, 255, 255);
    tempdetails.connections[1].attraction = -.02;
    tempdetails.connections[1].distance = 40;
    tempdetails.connections[0].attraction = .01;
    tempdetails.connections[0].distance = 20;
    particle_details.push_back(tempdetails);
    tempdetails = add_particle_detail(3, 0, 1, 0, 255, 0, 0, 0, 255);
    tempdetails.connections[2].attraction = .001;
    tempdetails.connections[2].distance = 20;
    particle_details.push_back(tempdetails);
    tempdetails = add_particle_detail(3, 0, 1, 0, 255, 0, 0, 0, 255);
    particle_details.push_back(tempdetails);
    // particle_details[0].size = 5;
    // particle_details[0].r = 255;
    // particle_details[0].b = 255;
    // particle_details[0].g = 255;
    // particle_detail[0].connection[0];
    
    // particle_detail[0].connection[0].id = 0;
    // particle_detail[0].connection[0].dist = 10;
    // particle_detail[0].connection[0].attraction = 0.001;    
    Cell tempcell;
    tempcell.size = 1000;
    tempcell.max_size = 7;
    tempcell.outline_size = 2;
    tempcell.inside_r = 0;
    tempcell.inside_b = 0;
    tempcell.inside_g = 0;

    tempcell.outside_r = 255;
    tempcell.outside_b = 255;
    tempcell.outside_g = 255;

    tempcell.x = 100;
    tempcell.y= 100;
    tempcell.mutation_rate = .1;
    // particle_detail[0].connection[0].id = 0;
    // particle_detail[0].connection[0].dist = 10;
    // particle_detail[0].connection[0].attraction = 0.001;    
    tempcell.energy = 100;

    allcells.push_back(tempcell);

    vector<vector<vector<int> > > map(worldsize[0], vector<vector<int> >(worldsize[1]));
    vector<vector<vector<int> > > dmap(worldsize[0], vector<vector<int> >(worldsize[1]));

    vector<vector<vector<int> > > cell_map(worldsize[0], vector<vector<int> >(worldsize[1]));
    vector<vector<vector<int> > > cell_dmap(worldsize[0], vector<vector<int> >(worldsize[1]));

    int randomthing = random_in_range(0, 10);
    cout << randomthing << endl;
    vector<vector<double> > dgmap = defalt_gmap();
    vector<vector<double> > gmap = dgmap;
    vector<vector<vector<double> > > dvelmap = vel_gmap();
    vector<vector<vector<double> > > velmap = velocityfeild(gmap, worldsize, chunk_size, dvelmap);;

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Space Particles");
    window.setVisible(true);

    

    //text.setFont(sf::Font:);
    // sf::Text text;

    // // select the font
    // sf::Font font;
    // font.loadFromFile("arial.ttf");
    // text.setFont(font); // font is a sf::Font

    // // set the string to display
    // text.setString("../example_font.ttf");

    // // set the character size
    // text.setCharacterSize(100); // in pixels, not points!

    // // set the color
    // text.setFillColor(sf::Color::Blue);

    // // set the text style
    // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // text.setPosition(100, 100); 

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
    double funidamp = .9999;
    double unidamp = 1;
    // vector<thread> threads;
    // vector<thread> dthreads;
    thread terminal(gameterminal);
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
                        allp[allp.size() - 1].x = (particle_details[selected_id].size * 2) * i + position.x;
                        allp[allp.size() - 1].y = (particle_details[selected_id].size * 2) * a + position.y;
                        //allp[allp.size() - 1].damp = unidamp;
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
                allp[allp.size() - 1].id = selected_id;
                allp[allp.size() - 1].vx = 5;
        }}
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Tab)
            {
                cout << "hello" << endl;
                gameterminal();
            }
        }
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                allp.push_back(particles());
                allp[allp.size() - 1].x = -1;
                allp[allp.size() - 1].y = -1;

            }
        }
        
        map = dmap;
        cell_map = dmap;
        //velmap = dvelmap;
        //unidamp = pow(funidamp, (dt/20));
        //threads = dthreads;
        dt = 1;
        
        for (int i = 0; i < allp.size(); i++)
        {

            int id = allp[i].id;
            sf::CircleShape shape(particle_details[id].size);
            shape.setOutlineThickness(particle_details[id].outline_size);
            shape.setFillColor(sf::Color(particle_details[id].inside_r, particle_details[id].inside_g, particle_details[id].inside_b));
            shape.setOutlineColor(sf::Color(particle_details[id].outside_r, particle_details[id].outside_g, particle_details[id].outside_b));
            shape.setPosition(allp[i].x - particle_details[id].size, allp[i].y- particle_details[id].size);
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
            
            //cout << vxm << vym <<endl;
            allp[i].vx += vxm;
            
            allp[i].vy += vym;
            //allp[i].vy += .008;
            // cout << gmap[cx][cy] << endl;
            // cout << gmap[cx][cy] << endl;
            //cout << i << '|' << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;
            

        }
        vector<thread> threads;
        map = change_map(map);
        //cout << threads.size() << endl;
        //cout << "hello" << endl;
        //map = change_map(map);
        //velmap = velocityfeild(gmap, worldsize, chunk_size, dvelmap);
        for (int i = 0; i < allp.size(); i++)
        {
            cx = allp[i].x/chunk_size;
            cy = allp[i].y/chunk_size;
            //printvecint(map[cx][cy]); 
            
            //allp[i].update(dt, i, allp_adr, map[cx][cy]);

            threads.emplace_back([&allp, i, dt, &allp_adr, &map]() {
                int cx = allp[i].x / chunk_size;
                int cy = allp[i].y / chunk_size;
                allp[i].update(dt, i, allp_adr, map[cx][cy]);
                });

            //onethread(i, dt, allp_adr, map[cx][cy]);
            //onethread();
            if (false)
            {
            for (int a = 0; a < allp.size(); a++)
            {
                allp[i].addgravvelocity(allp[a].x, allp[a].y, - particle_details[allp[a].id].size * .0001);
            }}
            // cout << i << '|' << velmap[cx][cy][0] << ';' << velmap[cx][cy][1] << endl;

            
            // vxm = velmap[cx][cy][0];
            // vym = velmap[cx][cy][1];


            //th.join();
        }
        //allp.size() - 1 <<endl;
        for (auto& thread : threads) 
        {
        thread.join();
        }   

        cell_map = change_map(cell_map);
        //cout << &allp << end;
        for (int i = 0; i < allcells.size(); i++)
        {
            //allcells


            sf::CircleShape shape(allcells[i].size);

            shape.setOutlineThickness(allcells[i].outline_size);
            shape.setFillColor(sf::Color(allcells[i].inside_r, allcells[i].inside_g, allcells[i].inside_b));
            shape.setOutlineColor(sf::Color(allcells[i].outside_r, allcells[i].outside_g, allcells[i].outside_b));
            shape.setPosition(allcells[i].x - allcells[i].size, allcells[i].y- allcells[i].size);
            window.draw(shape);
            
            cx = allcells[i].x/chunk_size;
            cy = allcells[i].y/chunk_size;

            cell_map[cx][cy].push_back(i);
            
        }

        for (int i = 0; i < allcells.size(); i++)
        {
            cx = allcells[i].x/chunk_size;
            cy = allcells[i].y/chunk_size;
            //void cell_update(int dt, int check, vector<particles> *particlesi, vector<particles> *cellsi, vector<int> particle_neerby, vector<int> cell_neerby)
            //cout << "here" << endl;
            //printvecint(map[cx][cy]);

            //cout << allcells_adr << endl;
            allcells[i].cell_update(dt, i, allp_adr, allcells_adr, map[cx][cy], cell_map[cx][cy]);
            if (allcells[i].size > allcells[i].max_size)
            {
                allcells[i].energy *= .45;
                Cell next_cell = allcells[i];
                next_cell = next_cell.reproduce(next_cell);
                next_cell.check_border();
                allcells.push_back(next_cell);
            }

        }
        vector<Cell> temp_temp_allcells;
        vector<Cell> temp_allcells = allcells;
        allcells = temp_temp_allcells;

        //cout << temp_allcells.size() << endl;
        for (int i = 0; i < temp_allcells.size(); i++)
        {
            if (allcells[i].dead == false)
            {
                allcells.push_back(temp_allcells[i]);
            }
        }
        //window.draw(text);
        if (held)
        {
            allp.push_back(particles());
            allp[allp.size() - 1].x = position.x;
            allp[allp.size() - 1].y = position.y;
            //allp[allp.size() - 1].damp = unidamp;
            allp[allp.size() - 1].id = selected_id;
            
        }

        //(vector<vector<double> > gmap, int worldsize[2], int chunk_size, vector<vector<vector<double> > > defalt)
        
        //cout << velmap[0][0][1] << cout << ','; cout << velmap[0][0][1] << endl;
        
        window.display();
        vector<vector<vector<int> > > map = chunk();
        //cout << map[1][1][0] << endl;
        //out << map[1][1][0] << endl;
        //break;
        position = sf::Mouse::getPosition(window);
        
        
        gmap = dgmap;
        end = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        
        // printf("fps: ");
        // cout << dt << endl;
        // printf("id: ");
        // cout << selected_id << endl;
        // //cout <<  allp.size() << endl;
        // dt = 1;
        //dt = dt * .1;
        
    }
    cin.get();
    return 0;
}    