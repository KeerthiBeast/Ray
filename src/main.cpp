#include "vec3.h"
#include "ray.h"
#include "color.h"

#include <iostream>

double hit_sphere(const point3& centre, double radius, const ray& r)
{
    vec3 oc = r.origin()-centre;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0){
        return -1.0;
    }
    else{
        return (-half_b - sqrt(discriminant)) / (a);
    }
}

color ray_color(const ray& r)
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if(t>0.0){
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
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
    auto focal_length = 1.0; //Camera z axis
    auto viewpoint_height = 2.0;
    auto viewpoint_width = viewpoint_height * (static_cast<double>(image_width)/image_height);
    auto camera_centre = point3(0,0,0); //Camera in positive x and y and negative z

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

    //Printing out the image
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