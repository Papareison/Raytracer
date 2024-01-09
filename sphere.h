#include "plane.h"

typedef struct sphere{
    vector center;
    double r;
    color sphere_color;
}sphere;

// Last argument is the address of the parameter of the vector line (ray) that intersects the sphere, returns 1 on success. Assumes not normalized direction vector
// Also changes the value of the final argument to the solution (The ray-sphere intersection parameter)
int sphere_intersect(sphere *sphere, ray *ray, double *final_solution);