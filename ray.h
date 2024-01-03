#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

typedef struct ray{
    vector origin;
    vector direction;
}ray;

typedef struct color{
    double r;
    double g;
    double b;
}color;

typedef struct light{
    vector origin;
    color color;
}light;


