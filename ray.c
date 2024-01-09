#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "light.h"

void makeppm(char *file, unsigned char *ppmdata, int wd, int ht){

    FILE *fp;
    fp = fopen("test1.ppm", "w");

    fprintf(fp, "P6 %d %d %d\n", wd, ht, 255);

    // Args: ppmdata array, size of each pixel (3 rgb ints), total pixels, file pointer
    fwrite(ppmdata, 3, wd * ht, fp);

    fclose(fp);
}

enum ppmoffset{
    r,
    g,
    b
}ppmoffset;

int main(){

    ray ray;

    // Resolution
    int horizontal_res = 640;
    int vertical_res = 480;

    sphere *spheres;
    int num_of_spheres = 2;
    spheres = (sphere *)malloc(sizeof(sphere) * num_of_spheres);

    spheres[0].center.x = 0.5;
    spheres[0].center.y = 0.8;
    spheres[0].center.z = 4.0;
    spheres[0].r = 0.5;
    spheres[0].sphere_color.r = 0.3;
    spheres[0].sphere_color.g = 0.0;
    spheres[0].sphere_color.b = 0.0;

    spheres[1].center.x = -0.5;
    spheres[1].center.y = 0.15;
    spheres[1].center.z = 4.2;
    spheres[1].r = 0.6;
    spheres[1].sphere_color.r = 0.0;
    spheres[1].sphere_color.g = 0.3;
    spheres[1].sphere_color.b = 0.0;


    plane plane;
    plane.normal.x = 0.0;
    plane.normal.y = 1.0;
    plane.normal.z = 0.0;
    plane.D = -1.0;

    light light;
    light.origin.x = 5.0;
    light.origin.y = 10.0;
    light.origin.z = -2.0;
    light.light_color.r = 1.0;
    light.light_color.g = 1.0;
    light.light_color.b = 1.0;

    unsigned char ppmdata[3 * horizontal_res * vertical_res];

    double parameter;
    int i;
    int closest_i = -1;
    int x,y;
    for (y = 0; y < vertical_res; y++){
        for (x = 0; x < horizontal_res; x++){


            ray.origin.x = 0;
            ray.origin.y = 0;
            ray.origin.z = 0;

            ray.direction.x = -0.67 + x / (float)vertical_res;
            ray.direction.y = 0.5 - y / (float)vertical_res;
            ray.direction.z = 1.0;

            // Background color in case of no intersections
            color rgb;
            rgb.r = 0.5;
            rgb.g = 0.5;
            rgb.b = 0.5;

            parameter = 20000;

            plane_intersect plnx = check_plane_intersect(&ray, &plane);

            // Flooring is necessary, typecasting rounds towards zero, flooring towards -INF
            if (plnx.flag){
                if ((int)floor(plnx.point.x) + (int)floor(plnx.point.y) + (int)floor(plnx.point.z) & 1){
                    rgb.r = 0;
                    rgb.g = 0;
                    rgb.b = 0;
                }
                else{
                    rgb.r = 1.0;
                    rgb.g = 1.0;
                    rgb.b = 1.0;
                }
                color RGB_P = plane_lighting(&light, &ray, &plnx);
                rgb.r *= RGB_P.r;
                rgb.g *= RGB_P.g;
                rgb.b *= RGB_P.b;
            }
            
            for (i = 0; i < num_of_spheres; i++){
                closest_i = -1;
                if (sphere_intersect(&spheres[i], &ray, &parameter)){
                    closest_i = i;
                }
                // Greater than zero is necessary
                if (closest_i >= 0){
                    color RGB_S = sphere_lighting(&light, &ray, &spheres[closest_i], &parameter);
                    rgb.r = spheres[closest_i].sphere_color.r + RGB_S.r;
                    rgb.g = spheres[closest_i].sphere_color.g + RGB_S.g;
                    rgb.b = spheres[closest_i].sphere_color.b + RGB_S.b;
                }
            }
            if (rgb.r > 1.0)
                rgb.r = 1.0;
            if (rgb.g > 1.0)
                rgb.g = 1.0;
            if (rgb.b > 1.0)
                rgb.b = 1.0;

            ppmdata[(x + y * horizontal_res) * 3 + r] = (unsigned char)(rgb.r * 255.0);
            ppmdata[(x + y * horizontal_res) * 3 + g] = (unsigned char)(rgb.g * 255.0);
            ppmdata[(x + y * horizontal_res) * 3 + b] = (unsigned char)(rgb.b * 255.0);
        }
    }
    makeppm("test1.ppm", ppmdata, horizontal_res, vertical_res);
    free(spheres);
}