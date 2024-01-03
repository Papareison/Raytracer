#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "light.h"

void ppm_write(char* filename, unsigned char *ppmdata, int vres, int hres){
    FILE *fp;
    fp = fopen("test1.ppm", "w");

    fprintf(fp, "P6 %d %d %d\n",  vres, hres, 255);
   
    // Args: ppmdata array, size of each pixel (3 rgb ints), total pixels, file pointer
    fwrite(ppmdata, 3, vres * hres, fp);
   
    fclose(fp);
}