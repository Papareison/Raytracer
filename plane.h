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

// Check intersect of plane with a specific ray, vector line parameter for intersect is included in the returned struct
plane_intersect check_plane_intersect(ray *ray, plane *plane);