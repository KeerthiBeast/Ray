#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hittable.h"

class sphere : public hittable
{
    private:
        point3 centre;
        double radius;
        shared_ptr<material> mat;

    public:
        sphere(point3 _centre, double _radius, shared_ptr<material> _mat) : centre(_centre), radius(_radius), mat(_mat) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override
        {
            vec3 oc = r.origin() - centre;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if(discriminant < 0) return false;

            //Finding the nearest root in the acceptable range
            auto sqrtd = sqrt(discriminant);
            auto root = (-half_b - sqrtd) / a;
            if(!ray_t.surrounds(root))
            {
                root = (-half_b + sqrtd) / a; 
                if(!ray_t.surrounds(root)) return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - centre) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }

};

#endif 