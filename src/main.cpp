#include "vec3.h"
#include "ray.h"
#include "color.h"

#include <iostream>

color ray_color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5,0.7,1.0); //Background color for the image using Linear Interpolation
}

int main()
{
    //Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    //Calculating image height and ensuring it is atleast 1
    int image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //Camera
    auto focal_length = 1.0;
    auto viewpoint_height = 2.0;
    auto viewpoint_width = viewpoint_height * (static_cast<double>(image_width)/image_height);
    auto camera_centre = point3(0,0,0);

    //Calculate the vectors across the horizontal and vertical edges of the viewpoint 
    auto viewpoint_u = vec3(viewpoint_width, 0, 0);
    auto viewpoint_v = vec3(0, -viewpoint_height, 0);

    //Calculate the horizontal and vertical delta distance between two pixels in the viewpoint 
    auto pixel_delta_u = viewpoint_u/image_width;
    auto pixel_delta_v = viewpoint_v/image_height;

    //Calculate the location of the upper left edge of the viewpoint
    auto viewpoint_upper_left = camera_centre - vec3(0,0,focal_length) - viewpoint_u/2 - viewpoint_v/2;
    auto pixel00_loc = viewpoint_upper_left + 0.5*(pixel_delta_u+pixel_delta_v);

    std::cout<<"P3\n"<<image_width<<' '<<image_height<<"\n255\n";

    for(int j=0; j<image_height; j++)
    {
        std::clog<<"\rScanlines remaining: "<<(image_height-j)<<' '<<std::flush;
        for(int i=0; i<image_width; i++)
        {
            auto pixel_centre = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto ray_direction = pixel_centre-camera_centre;
            ray r(camera_centre, ray_direction);

            color pixel_color = ray_color(r); 
            write_color(std::cout, pixel_color);
        }
    }
    std::clog<<"\rDone.         \n";
}