#include "sphere.h"

// Lighting of plane per ray
color plane_lighting(light *light, ray *ray, plane_intersect *plane_intersect);

// Lighting of sphere per ray
color sphere_lighting(light *light, ray *ray, sphere *sph, double *param);