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
    color light_color;
}light;

// Writes the rgb values from the arg called ppmdata to a ppm file
void ppm_write(char *filename, unsigned char *ppmdata, int vres, int hres);
