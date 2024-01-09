#include "plane.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define EPSILON 0.000001

#define EPSILON 0.000001

plane_intersect check_plane_intersect(ray *ray, plane *plane){
    
    plane_intersect check;
    vector temp;

    // Compute the denominator of the parameter for intersection equation
    double denominator = dotP(&ray->direction, &plane->normal);

    // If the denominator is close to zero, the ray is parallel to the plane
    if (fabs(denominator) > EPSILON){

        // Compute the numerator
        double numerator = dotP(&plane->normal, &ray->origin) + plane->D;

        // Compute the final equation
        double parameter = numerator / denominator;

        // If paramter is positive, the intersection point is in front of the ray
        if (parameter >= 0){
            check.flag = 1;
            temp = scale_vec(&ray->direction, parameter);
            check.point = add_vec(&ray->origin, &temp);
            check.lambda = parameter;
        }
        else{

            check.flag = 0;
        }
    }
    else{
        check.flag = 0;
    }
    return check;
}