#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record
{
    public:
        point3 p;
        vec3 normal;
        double t;
};

class hittable
{
    virtual bool hit(const ray& r, double rayt_min, double rayt_max, hit_record& rec) const = 0;

    public:
        virtual ~hittable() = default;
};

#endif