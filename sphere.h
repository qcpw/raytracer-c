#include "vec.h"
#include "object.h"
typedef Vec point;

class sphere : public object{
 public:
  double radius;
  Vec center;
  double mat[3][4];
  Vec normal(point surfacePoint);
  int intersect(point, Vec, double&);
};
