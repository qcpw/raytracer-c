#include "vec.h"
#include "object.h"

class plane : public object{
 public:
  Vec norm, v;
  
  plane(Vec N, Vec v);
  int intersect(Vec , Vec , double&);
  Vec normal(point surfacePoint);
};
