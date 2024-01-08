#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

vector add_vec(vector *v1, vector *v2){
    vector v3;
    v3.x = v1->x + v2->x;
    v3.y = v1->y + v2->y;
    v3.z = v1->z + v2->z;
    return v3;
}

vector subtract_vec(vector *v1, vector *v2){
    vector v3;
    v3.x = v1->x - v2->x;
    v3.y = v1->y - v2->y;
    v3.z = v1->z - v2->z;
    return v3;
}

vector scale_vec(vector *v, double scalar){
    vector vs;
    vs.x = scalar * v->x;
    vs.y = scalar * v->y;
    vs.z = scalar * v->z;
    return vs;
}

double magnitude_vec(vector *v){
    double magnitude = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    return magnitude; 
}

double dotP(vector *v1, vector *v2){
    double product = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
    return product;
}
