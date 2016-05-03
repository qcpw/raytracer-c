#include "vec.h"
#include "object.h"

class triangle : public object{
 public:
  Vec norm, v;
  bool ccw;
  triangle(Vec, Vec, Vec, bool);
  int intersect(Vec , Vec , double&);
  Vec normal(point surfacePoint);
  Vec point0, point1, point2;
};
