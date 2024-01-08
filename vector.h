#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector{
    double x;
    double y;
    double z;
}vector;

vector add_vec(vector *v1, vector *v2);
vector subtract_vec(vector *v1, vector *v2);
vector scale_vec(vector *v, double scalar);
double dotP(vector *v1, vector *v2);
double magnitude_vec(vector *v);

