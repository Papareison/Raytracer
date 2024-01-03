#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "ray.h"

typedef struct sphere{
    vector center;
    double r;
    color color;
}sphere;

// Last argument is the address of the parameter of the vector line (ray) that intersects the sphere, returns 1 on success. Assumes not normalized direction vector.
int sphere_intersect(sphere *sphere, ray *ray, double *solution);