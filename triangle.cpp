#include "triangle.h"


triangle::triangle(Vec a, Vec b, Vec c, bool pnts): v(a), point0(a), point1(b), point2(c), ccw(pnts) {
  if(ccw)
    norm = cross((point1 - point0), (point2 - point0));
  else
    norm = cross((point1 - point0), (point2 - point0)) * -1;
}

Vec triangle::normal(point surfacePoint){
  return norm;
}

int triangle::intersect(Vec origin, Vec dir, double& t){
  double denominator = dot(norm, dir);
  if(denominator == 0) return 0;
  t = fdiv(dot((v - origin), norm),denominator);
  //t = ((dot(normal, v) + c)/denominator);
  if(t<=0) return 0;
  Vec x = origin + (dir * t);
  Vec c1, c2, c3;
  double d1, d2, d3;

  c1 = cross((point1-point0),(x-point0));
  c2 = cross((point2-point1), (x - point1));
  c3 = cross((point0-point2), (x - point2));

  //check for the ccw case
  d1 = dot(c1, norm);
  d2 = dot(c2, norm);
  d3 = dot(c3, norm);

  //check for the cw case
  double d4, d5, d6;
  d4 = dot(c1, norm * -1);
  d5 = dot(c2, norm * -1);
  d6 = dot(c3, norm * -1);
  
  if((d1>=0 && d2>=0 && d3>=0))
    return 2;
  if(d4>=0 && d5>=0 && d6>=0){
    return 2;
  }

  /*
  if(!ccw && d1 < 0 && d2 < 0 && d3 < 0){
    return 2;
  } else if (ccw && d1 >= 0 && d2 >= 0 && d3 >=0){
    return 2;
    }*/
  else return 0;


}
