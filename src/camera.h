#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"

#include <iostream>

class camera
{
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int samples_per_pixel = 10;
        
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
                    for(int sample=0; sample < samples_per_pixel; sample++)
                    {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, world);
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

        void initialize()
        {
            image_height = static_cast<int>(image_width/aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            centre = point3(0,0,0);

            //Determinig the viewpoint dimensions
            auto focal_length = 1.0;
            auto viewpoint_height = 2.0;
            auto viewpoint_width = viewpoint_height * (static_cast<double>(image_width) / image_height);

            //Calculate the vector along horizontal and vertical of the viewpoint
            auto viewpoint_u = vec3(viewpoint_width,0,0);
            auto viewpoint_v = vec3(0,-viewpoint_height,0);

            //Calculate the horizontal and vertical delta values
            pixel_delta_u = viewpoint_u / image_width;
            pixel_delta_v = viewpoint_v / image_height;

            //Calculate the location of the upper left part and the pixel00
            auto viewpoint_upper_left = centre - vec3(0,0,focal_length) - viewpoint_u/2 - viewpoint_v/2;
            pixel00_loc = viewpoint_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        ray get_ray(int i, int j) const
        {
            //Ray with random sampling
            auto pixel_centre = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto pixel_sample = pixel_centre + pixel_sample_square();

            auto ray_origin = centre;
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

        color ray_color(const ray& r, const hittable& world)
        {
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec))
            {
                return 0.5 * (rec.normal + color(1,1,1));
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5,0.7,1.0); //Background color for the image using Linear Interpolation
        }
};

#endif