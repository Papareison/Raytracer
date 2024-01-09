#include "light.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

color plane_lighting(light *light, ray *ray, plane_intersect *plane_intersect)
{
    color RGB;
    const double parameter = plane_intersect->lambda;

    const double ambient_value = 0.1;
    RGB.r = ambient_value;
    RGB.g = ambient_value;
    RGB.b = ambient_value;

    vector viewpoint = ray->direction;

    vector scaled_view = scale_vec(&viewpoint, parameter);
    vector line = add_vec(&ray->origin, &scaled_view);

    vector N = subtract_vec(&line, &plane_intersect->point);

    // Normalize the normal vector
    double inv_mag = 1 / magnitude_vec(&N);
    N = scale_vec(&N, inv_mag);

    vector L = subtract_vec(&light->origin, &line);

    double L_mag = magnitude_vec(&L);

    // constants for attenuated lighting
    const double c1 = 0.002;
    const double c2 = 0.0002;
    const double c3 = 0.2;

    // attenuated lighting, calculated and added to rgb
    double atten = 1.0 / ((c1 * (L_mag * L_mag)) + (c2 * L_mag) + c3);
    if (atten < 0.1)
    {
        atten = 0.1;
    }
    RGB.r += atten;
    RGB.g += atten;
    RGB.b += atten;

    return RGB;
}
color sphere_lighting(light *light, ray *ray, sphere *sph, double *param)
{

    double parameter = *param; // Parameter of ray vector line needed for intersection between sphere and ray
    double temp_invmag;        // Used to hold inverse reciprocal vector magnitudes temporarily
    vector temp;               // Used for vectors only needed in 1 calc and not used further
    color RGB;                 // Pixel color for specific ray
    RGB.r = 0;
    RGB.g = 0;
    RGB.b = 0;

    // add ambient lighting value to rgb
    double amb = 0.1;
    RGB.r += amb;
    RGB.g += amb;
    RGB.b += amb;

    // viewpoint vector V
    vector V = ray->direction;

    // normalize V
    temp_invmag = 1 / magnitude_vec(&V);
    V = scale_vec(&V, temp_invmag);

    // vectors for normal, N
    temp = scale_vec(&V, parameter);
    vector norm_origin = add_vec(&ray->origin, &temp);

    /*normalized vector N (difference
    of sphere center and norm origin)*/
    vector N = subtract_vec(&norm_origin, &sph->center);

    // normalize N
    temp_invmag = 1 / magnitude_vec(&N);
    N = scale_vec(&N, temp_invmag);

    // vector for light L
    temp = subtract_vec(&light->origin, &norm_origin);
    vector L = scale_vec(&temp, 1 / parameter);

    // DIFFUSE
    double cos_dif = dotP(&L, &N);
    if (cos_dif > 0)
    {
        RGB.r += cos_dif * light->light_color.r * (sph->sphere_color.r);
        RGB.g += cos_dif * light->light_color.g * (sph->sphere_color.g);
        RGB.b += cos_dif * light->light_color.b * (sph->sphere_color.b);
    }

    /* equation for R = L - 2 * (N dot L) * N
    R is the vector between N and V
    broken down into working components via temp variables */
    temp = (scale_vec(&N, (2 * dotP(&L, &N))));
    vector R = subtract_vec(&L, &temp);
    temp_invmag = 1 / magnitude_vec(&R);
    R = scale_vec(&R, temp_invmag);

    // SPECULAR
    double cos_spec = dotP(&R, &V);
    double n = 40 / cos_spec;
    if ((cos_spec > 0) && (cos_dif > 0))
    {
        RGB.r += pow(cos_spec, n);
        RGB.g += pow(cos_spec, n);
        RGB.b += pow(cos_spec, n);
    }

    return RGB;
}
