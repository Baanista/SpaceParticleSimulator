#ifndef preformance_HPP
#define preformance_HPP
#include <stdio.h>
#include <iostream>
#include<tuple>
#include <vector>

extern int worldsize[2];
extern int chunk_size;
extern particles allp[30];

//this puts all particles on a chunk map to boost preformance
std::vector<std::vector<std::vector<int>>> chunk()
{
    std::vector<std::vector<std::vector<int>>> map(worldsize[0], std::vector<std::vector<int>>(worldsize[0]));;
    
    int cx;
    int cy;
    int len;
    for (int i = 0; i < numbers.size(allp); i++)
    {
        cx = allp[i].x / chunk_size;
        cy = allp[i].y / chunk_size;
        
        //len = sizeof(map[cx][cy]) / sizeof(map[cx][cy]);
        map[cx][cy].push_back(i);
    }


    return(map);

}



#endif
