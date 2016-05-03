#include "sphere.h"
#include "math.h"
#include "raytrace.h"
#include <iostream>
using namespace std;


// #ifndef _SAFEDIV_
// #define _SAFEDIV_
// int sign(double x)
// {
//   return (x == 0 ? 0 : (x < 0 ? -1 : 1));
// }

// double fdiv(double a, double b)
// {
//   if (b == 0)
//   {
//     if (a == 0) return 0;
//     else return LARGE_VAL * sign(a);
//   }
//   else
//   {
//     if (a == 0) return 0;
//     else
//     {
//       if ((a + b) == a) return LARGE_VAL * sign(a) * sign(b);
//       else return a / b;
//     }
//   }
// }
// #endif /*SAFEDIV*/

// double object::min(double a, double b){
//   return (a>=b)?b:a;
// }

// double object::max(double a, double b){
//   return (a>=b)?a:b;
// }
// void object::setColor(double r, double g, double b){
//   //set the values between 0 and 1
//   color.x = r;
//   color.y = g;
//   color.z = b;
//   color.normalize();
// }

// Vec object::getColor(){
//   return color;
// }
// double object::getDiffuse(){
//   return diffuse;
// }
// double object::getSpecular(){
//   return specular;
// }
// double object::getAmbient(){
//   return ambient;
// }
// void object::setDiffuse(double d){
//   if(d > 1) diffuse = 1.0;
//   else if(d<0) diffuse = 0.0;
//   else diffuse = d;
// }
// void object::setSpecular(double s){
//     if(s > 1) specular = 1.0;
//   else if(s<0) specular = 0.0;
//   else specular = s;
// }
// void object::setAmbient(double a){
//     if(a > 1) specular = 1.0;
//   else if(a<0) specular = 0.0;
//   else specular = a;
// }

Vec sphere::normal(Vec surfacePoint){
  Vec output;
  output = surfacePoint - center;
  output.normalize();
  return output;
}

int sphere::intersect( point origin, Vec dir, double& t){
  //if direction is not already normalized, normalize it
  if(dir.len() != 1) dir.normalize();

  Vec v = origin - center;

  //dot(a,b) = size(a) * size(b) * cos(theta)
  //so this should always = 1 * 1 * 1 = 1
  double a = dot( dir, dir);
  // b is 2 times the angle between the ray and the viewer
  double b = 2.0 * dot(dir, v);
  //size of v - radius squared
  double c = dot(v, v) - (radius*radius);
  double t1, t2;
  double discriminant = (b*b) - (4.0*a*c);
  //if(discriminant > 0) cout<<discriminant<<endl;
  //if(discriminant > 0 && discriminant < .00001) discriminant = 0;
  if(discriminant < 0){
    return 0; // no intersection
  } else if(discriminant == 0){
    //check to see if the denominator is 0. If so, approximate. (this should never happen anyway. if so, something is wrong)
    if(a != 0){
      t1 = (-b / (2.0*a));
      return 2;
    } else {
      t1 = (-b/.001);
      return -1;
    }
  } else if(discriminant > 0){
    //if(a == 0) a = .001;
    double sq = sqrt(discriminant);
    t1 = fdiv((-b + sq),(2.0*a));
    t2 = fdiv((-b - sq),(2.0*a));

    // t1 = ((-b + sq)/(2*a));
    // t2 = ((-b - sq)/(2*a));
    //t1 = (-b + sq)/(2.0);
    //t2 = (-b - sq)/(2.0);
    if(t1 != t1 || t2!= t2)
      return -2;
    if( t1 > 0 && t2 > 0){
      t = min(t1, t2);
      return 2;
    } else if(t1 < 0 && t2 < 0){
      //if(t1 == t1 && t2 == t2){
	t = max(t1, t2);
	return -2;
	//}
    } else {
      return -1; //inside the sphere, so don't show anything
    }
  }
}
