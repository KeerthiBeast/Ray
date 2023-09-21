#ifndef RTWEEKEND_H
#define RTWEEKEND_H

//Used header file 
#include "vec3.h"
#include "ray.h"
#include "interval.h"

#include <cmath>
#include <memory>
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

#endif 