#include <iostream>
#include "view.h"
using namespace std;


/*
int main(void){
  Vec centerOfScene, eye, upVector, f0,f1, f2, f3, proj0, proj1, proj2, proj3;
  Vec screenSize;
  Vec recordingSurfaceSize;
  float depth;

  //this is the middle of the "world" in which the objects exist
  centerOfScene.set(0,0,5);

  //this is the eye of the viewer (or the camera)
  eye.set(0,0,0);

  //this determines the angle of the camera
  upVector.set(0,1,0);  

  //calculate the coordinates of the point (0,0,-1) in the camera's frame of reference
  //f = look(centerOfScene, eye, upVector, Vec(0,0,5));

  f0 = look(centerOfScene, eye, upVector, Vec(-4,-3,5)); //bottom left
  f1 = look(centerOfScene, eye, upVector, Vec(4,-3,5)); //top left
  f2 = look(centerOfScene, eye, upVector, Vec(-4,3,5));//bottom right
  f3 = look(centerOfScene, eye, upVector, Vec(4,3,5));//top right

  screenSize.set(800.0, 600.0, 0);
  recordingSurfaceSize.set(800.0, 600.0, 0);
  depth = dist(centerOfScene, eye);

  proj0 = project(f0, screenSize, recordingSurfaceSize, depth);
  proj1 = project(f1, screenSize, recordingSurfaceSize, depth);
  proj2 = project(f2, screenSize, recordingSurfaceSize, depth);
  proj3 = project(f3, screenSize, recordingSurfaceSize, depth);

  

  Vec xSize(min(proj0.x, proj1.x), max(proj2.x, proj3.x));
  Vec ySize(min(proj0.y, proj2.y), max(proj1.y, proj3.y));

  //xSize.set(proj3.y, proj2.y);
  //ySize.set(proj0.x, );

  //cout<<"proj0:"<<proj0<<endl<<"proj2:"<<proj2<<endl;
  //cout<<"proj1:"<<proj1<<endl<<"proj3:"<<proj3<<endl;

  //cout<<"xSize:"<<xSize<<endl;
  //cout<<"ySize:"<<ySize<<endl;

  int* pointColor[3];
  pointColor[0] = new int[SCREENW*SCREENH];
  pointColor[1] = new int[SCREENW*SCREENH];
  pointColor[2] = new int[SCREENW*SCREENH];

  renderScreen(xSize, ySize, eye, depth, pointColor );

  // cout<<"camera coordinates of bottom left corner:"<<endl;
  // cout<<f0<<endl<<endl;
  // cout<<"projected coordinates"<<endl;
  // cout<<"bottom left:"<<proj0<<endl;
  // cout<<"top right:"<<proj3<<endl;
  return 0;
}
*/
