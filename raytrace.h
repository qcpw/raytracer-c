#include "vec.h"
#define no_intersection 0
#define light_source 1
typedef Vec color;
typedef Vec point;

double dot_product (Vec , Vec);
Vec intersect(point p, Vec v, point center, double r, int* status);
double Iax( double al_color, double asc, double ds_color);
double Idx(double att, double l_color, double ds, double ds_color);
double Isx(double att, double l_color, double ss, double ss_color);
color phong(Vec q, Vec n, Vec l, Vec v, Vec r, double mat[3][4], double light[3][4]);
Vec normal(point q, point sphere_center);
Vec reflect(point q, Vec n, Vec l);
color trace(Vec p, Vec d, int step, Vec center, double r, double energy, double light[3][4], double mat[3][4]);
color trace(Vec p, Vec d, int step);
color newTrace(point, Vec, int);

