#include "rtweekend.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"

int main()
{
    hittable_list world;

    auto material_ground = make_shared<lambetarian>(color(0.8, 0.8, 0.0));
    auto material_centre = make_shared<lambetarian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_centre));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 10;
    cam.max_depth = 50;

    cam.render(world);
}