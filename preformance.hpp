#ifndef preformance_HPP
#define preformance_HPP
#include <stdio.h>
#include <iostream>
#include<tuple>
#include <vector>
#include "particle.hpp"
using namespace std;
#include <cstdlib>  // for rand and srand
#include <ctime>    // for time

int random_in_range(int lower_bound, int upper_bound) {
    // Seed the random number generator with the current time
    srand(time(nullptr));

    // Generate a random number between lower_bound and upper_bound, inclusive
    int random_number = lower_bound + std::rand() % (upper_bound - lower_bound + 1);

    return random_number;
}




#endif
