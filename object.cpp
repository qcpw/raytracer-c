#include "object.h"
#include "math.h"


#define LARGE_VAL 1e10

double object::min(double a, double b){
  return (a>=b)?b:a;
}

double object::max(double a, double b){
  return (a>=b)?a:b;
}

void object::setColor(double r, double g, double b){
  //set the values between 0 and 1
  color.x = r;
  color.y = g;
  color.z = b;
  color.normalize();
}

Vec object::getColor(){
  return color;
}
double object::getDiffuse(){
  return diffuse;
}
double object::getSpecular(){
  return specular;
}
double object::getAmbient(){
  return ambient;
}
void object::setDiffuse(double d){
  if(d > 1) diffuse = 1.0;
  else if(d<0) diffuse = 0.0;
  else diffuse = d;
}
void object::setSpecular(double s){
  if(s > 1) {specular = 1.0;/*cout<<"s was:"<<s<<endl;*/}
  else if(s<0) {specular = 0.0; /*cout<<"s was:"<<s<<endl;*/}
  else {specular = s; /*cout<<"s was:"<<s<<endl;*/}
}
void object::setAmbient(double a){
    if(a > 1) ambient = 1.0;
  else if(a<0) ambient = 0.0;
  else ambient  = a;
}
