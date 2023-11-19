#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "material.h"

#include <iostream>

class camera
{
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90; //Vectical view angle
        point3 lookfrom = point3(0,0,-1); //Point camera is looking from
        point3 lookat = point3(0,0,0); //Point camera is looking at
        vec3 vup = vec3(0,1,0); //Camera-related up direction

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable& world)
        {
            initialize();

            std::cout<< "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int j=0; j<image_height; ++j)
            {
                std::clog<<"\rScanlines remaining: "<<(image_height-j)<<' '<<std::flush;
                for(int i=0; i<image_width; ++i)
                {
                    color pixel_color(0,0,0);
                    for(int sample=0; sample < samples_per_pixel; ++sample)
                    {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel);
                }
            }
            std::clog<< "\rDone                 \n";
        }

    private:
        int image_height;   //Rendered image height
        point3 centre;      //Center of the camera
        point3 pixel00_loc; //Pixel 00 position
        vec3 pixel_delta_u; //Delta of horizontal pixels
        vec3 pixel_delta_v; //Delta of vertical pixels
        vec3 u,v,w; //Camera frame basis vectors
        vec3 defocus_disk_u; //Defocus disk horizontal radius
        vec3 defocus_disk_v; //Vertical radius

        void initialize()
        {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            centre = lookfrom;

            //Determinig the viewpoint dimensions
            auto theta = degrees_to_radian(vfov);
            auto h = tan(theta/2);
            auto viewpoint_height = 2 * h * focus_dist;
            auto viewpoint_width = viewpoint_height * (static_cast<double>(image_width) / image_height);

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            //Calculate the vector along horizontal and vertical of the viewpoint
            auto viewpoint_u = viewpoint_width * u;
            auto viewpoint_v = viewpoint_height * -v;

            //Calculate the horizontal and vertical delta values
            pixel_delta_u = viewpoint_u / image_width;
            pixel_delta_v = viewpoint_v / image_height;

            //Calculate the location of the upper left part and the pixel00
            auto viewpoint_upper_left = centre - (focus_dist * w) - viewpoint_u/2 - viewpoint_v/2;
            pixel00_loc = viewpoint_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            auto defocus_radius = focus_dist * tan(degrees_to_radian(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

        ray get_ray(int i, int j) const
        {
            //Ray with random sampling
            auto pixel_centre = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto pixel_sample = pixel_centre + pixel_sample_square();

            auto ray_origin = (defocus_angle <= 0) ? centre : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const
        {
            //Return a random point in the square surrounding the pixel with the origin of pixel as centre
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }

        point3 defocus_disk_sample() const
        {
            auto p = random_in_unit_disk();
            return centre + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }

        color ray_color(const ray& r, int depth, const hittable& world)
        {
            if(depth <= 0)
            {
                return color(0,0,0);
            }
            hit_record rec;
            if(world.hit(r, interval(0.001, infinity), rec))
            {
                ray scattered;
                color attenuation;
                if(rec.mat->scatter(r, rec, attenuation, scattered))
                {
                    return attenuation * ray_color(scattered, depth-1, world);
                }
                return color(0,0,0);
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.9*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5,0.7,1.0); //Background color for the image using Linear Interpolation
        }
};

#endif