#ifndef gameterminal_HPP
#define gameterminal_HPP
#include <cmath>
#include "particle.hpp"
//#include "jsoncpp-master/include/json/json.h"
#include <string>
#include <iostream>
using namespace std;
#include <vector>

extern vector<particles> allp;
extern vector<particle_detail> particle_details;
extern int selected_id;

void gameterminal()
{
    cout << "debug" << endl;
    string command = "stuff";
    int number;
    while (command != "end")
    {
        cout << "type your command:" << endl;
        cin >> command;
        if (command == "switch")
        {
            cout << "What ID do you want to switch to?" << endl;
            //cout << selected_id << endl;
            cin >> number;
            //cout << selected_id << endl;
        }
    }
}


#endif