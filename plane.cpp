#include "plane.h"

#ifndef _SAFEDIV_
#define _SAFEDIV_

// signum function
int sign(double x)
{
  return (x == 0 ? 0 : (x < 0 ? -1 : 1));
}

// returns a / b (0 / 0 = 0, overflow = LARGE_VAL with correct sign)
double fdiv(double a, double b)
{
  if (b == 0)
  {
    if (a == 0) return 0;
    else return LARGE_VAL * sign(a);
  }
  else
  {
    if (a == 0) return 0;
    else
    {
      if ((a + b) == a) return LARGE_VAL * sign(a) * sign(b);
      else return a / b;
    }
  }
}
#endif /* _SAFEDIV_*/

plane::plane(Vec N, Vec p): norm(N), v(p) {}

Vec plane::normal(point surfacePoint){
  return norm;
}

int plane::intersect(Vec origin, Vec dir, double& t){
  double denominator = dot(norm, dir);
  if(denominator == 0) return 0;
  t = fdiv(dot((v - origin), norm),denominator);
  //t = ((dot(normal, v) + c)/denominator);
  if(t<=0) return 0;
  else return 2;

  /*
	float d = dot( normal, dir );
	if (d != 0)
	{
		double dist = -(dot( normal, origin ) + value) / d;
		if (dist > 0)
		{
		  //set an arbitrary distance limit
			if (dist < 100) 
			{
				t = dist;
				return 2;
			}
		}
	}
	return 0;*/
}
