#include "vec.h"
#include <iostream>
using namespace std;

typedef Vec point;
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define LARGE_VAL 1e10

class object{

public:
  
  double min(double a, double b);
  double max(double a, double b);
  double diffuse;
  double specular;
  double ambient;
  Vec color;
  void setColor(double, double, double);
  Vec getColor();
  double getDiffuse();
  double getSpecular();
  double getAmbient();
  void setDiffuse(double);
  void setSpecular(double);
  void setAmbient(double);
  virtual Vec normal(point surfacePoint)=0;

  virtual int intersect(point, Vec, double&)=0;

  

};

int sign(double x);
double fdiv(double a, double b);

#endif /* _OBJECT_H_ */
