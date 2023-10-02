#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

class interval
{
    public:
        double min, max;
        const double infinity = std::numeric_limits<double>::infinity(); 

        interval() : min(+infinity), max(-infinity) {}
        interval(double _min, double _max) : min(_min) , max(_max) {} 

        bool contains(double x) const
        {
            return min <= x && x <= max;
        }
        bool surrounds(double x) const
        {
            return min < x && x < max;
        }
        double clamp(double x) const
        {
            if(x < min) return min;
            if(x > max) return max;
            return x;
        }
        // static const interval empty, universe;
};

// const static interval empty (+infinity, -infinity);
// const static interval universe (-infinity, +infinity);

#endif