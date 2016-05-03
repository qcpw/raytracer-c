#include "view.h"

int main(void){
  float center[3] = {0, -5, 0};
  float eye[3] = {0,0,0};
  float upVector[3] = {0,1,0};
  float* f;
  f
  f = look(center, eye, upVector, center);
  cout<<f[0]<<f[1]<<f[2]<<endl;
  return 0;
}