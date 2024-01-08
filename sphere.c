#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "sphere.h"

int sphere_intersect(sphere *sphere, ray *ray, double *final_solution){
    double solution1, solution2;
    int flag = 0;
    vector temp;
    
    // Solution is quadratic. These 3 variables are calculated before the final for legibility
    temp = subtract_vec(&ray->origin, &sphere->center);
    double dp = dotP(&ray->direction, &temp);
    double direction_v_squared = dotP(&ray->direction, &ray->direction);
    temp = subtract_vec(&ray->origin, &sphere->center);
    double square = pow(magnitude_vec(&temp), 2) - pow(sphere->r, 2);

    double discriminant = pow(dp, 2) - direction_v_squared * square;

    if (discriminant >= 0){
        solution1 = (-dp + sqrt(discriminant)) / direction_v_squared;
        solution2 = (-dp - sqrt(discriminant)) / direction_v_squared;
        if (solution1 > 0 && solution2 > 0){ // Chain of ifs and else ifs is used to determine the smallest positive solution (parameter) of the two
            if (solution1 < solution2){
                *final_solution = solution1;
                flag = 1;
            }
            else{
                *final_solution = solution2;
                flag = 1;
            }
        }
        else if (solution1 > 0){
            *final_solution = solution1;
            flag = 1;
        }
        else if (solution2 > 0){
            *final_solution = solution2;
            flag = 1;
        }
    }
    return flag;
}