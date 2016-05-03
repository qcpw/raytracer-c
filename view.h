#include "vec.h"
#define SCREENW 800
#define SCREENH 600


float* cross( const float v1[3], const float v2[3]);
    
Vec look(Vec lookAt,Vec lookFrom,Vec upVector,Vec point);
  
Vec project(Vec inputCoordinates, Vec screenSize, Vec recordingSurfaceSize, float depth);
 
void renderScreen(Vec xSize, Vec ySize, Vec eye, float depth, int* pointColor[3] );

void createView(const float lookAt[3], const float lookFrom[3], const float upVector[3], const float recordingSurfaceSize[2], int* pointColor[3]);

void testTrace(int j, int i);




