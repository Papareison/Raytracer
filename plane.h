#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "ray.h"

// Plane is defined as: ax + by + cz = D. a,b,c make up the normal vector.
typedef struct plane{
    vector normal;
    double D;
}plane;

typedef struct plane_intersect{
   vector point;
   double lambda; // Line intersect parameter
   int flag; 
}plane_intersect;

plane_intersect check_plane_intersect(ray *ray, plane *plane);