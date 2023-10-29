#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <memory>
#include <cstdlib>
#include <limits>

//Using statements
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Functions
inline double degree_to_radian(double degrees)
{
    return degrees * pi/180.0;
}

//Random number generation
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0); //Generate random number from [0,1)
}

inline double random_double(double min, double max)
{
    return min + (max-min)*random_double(); //Generate ramdom number with parameters
}

//Used header file 
#include "vec3.h"
#include "ray.h"
#include "interval.h"

#endif 