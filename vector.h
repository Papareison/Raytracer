#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vector{
    double x;
    double y;
    double z;
}vector;

// Adds 2 vectors
vector add_vec(vector *v1, vector *v2);

// Subtracts v2 from v1 => v1 - v2
vector subtract_vec(vector *v1, vector *v2);

// Scalar multiplications by the 2nd argument
vector scale_vec(vector *v, double scalar);

// Returns the dot product of both vectors
double dotP(vector *v1, vector *v2);

// Returns the magnitude of the provided vector
double magnitude_vec(vector *v);

