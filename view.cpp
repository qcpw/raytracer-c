#include "glutapp.h"
#include "view.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
//#include "../vec.h"
#include "raytrace.h"
#include "triModel.cpp"
#include <vector>
#include <iostream>
using namespace std;

typedef Vec color;
typedef Vec point;
      
void drawModel(int numTriangles, double input[], bool ccw, int count){
  for(int i = 0; i<numTriangles*15; i+=9){
    App->objects.push_back((triangle*) new triangle(Vec(input[i],input[i+1], input[i+2]), Vec(input[i+3], input[i+4], input[i+5]), Vec(input[i+6],-input[i+7],input[i+8]), ccw));

    App->objects[count]->setColor(1, 0, 1);
    App->objects[count]->setDiffuse(1);
    App->objects[count]->setSpecular(0);
    App->objects[count]->setAmbient(1);
    count++;
  }
}

//works    
Vec look(Vec lookAt, Vec lookFrom, Vec upVector, Vec point){
  Vec zAxis, yAxis, xAxis, output;
  
  zAxis = lookAt - lookFrom;
  zAxis.normalize();
  
  xAxis = cross( upVector, zAxis);
  xAxis.normalize();

  yAxis = cross(zAxis, xAxis);
  yAxis.normalize();

  output.x = dot(point, xAxis);
  output.y = dot(point, yAxis);
  output.z = dot(point, zAxis);

  return output;
}
  
Vec project(Vec inputCoordinates, Vec screenSize, Vec recordingSurfaceSize, float depth){
  /*float* output;
  output = (float*) malloc(sizeof(float)*2);*/

  Vec output;
  output.x = (inputCoordinates.x * screenSize.x)/(inputCoordinates.z*recordingSurfaceSize.x)*depth;
  output.y = (inputCoordinates.y * screenSize.y)/(inputCoordinates.z*recordingSurfaceSize.y)*depth;

  /* output[0] = (inputCoordinates[0] * screenSize[0])/(inputCoordinates[2]*recordingSurfaceSize[0])*(depth);
  output[1] = (inputCoordinates[1] * screenSize[1])/(inputCoordinates[2]*recordingSurfaceSize[1])*(depth);*/
  return output;
}

void setScene(int scene){
  if(scene == 1){
    
    App->reflections = false;
    App->num_objects = 3;
    App->shininess = 10;

    Vec planePoint(0,0,-5);
    Vec planeNormal(0,0,1);
    planeNormal.normalize();

    App->objects.push_back((plane*) new plane(planeNormal, planePoint));
    App->objects.push_back((sphere*) new sphere());
    App->objects.push_back((sphere*) new sphere());
    
    ((sphere*)App->objects[1])->radius = 1;
    ((sphere*)App->objects[1])->center.set( 1.4, 1.5, 0);
    App->objects[1]->setColor(0, 0, 1);
    App->objects[1]->setDiffuse(1);
    App->objects[1]->setSpecular(1);
    App->objects[1]->setAmbient(0);

    ((sphere*)App->objects[2])->radius = 1;
    ((sphere*)App->objects[2])->center.set( -1.4, .5, 4);
    App->objects[2]->setColor(1, .2, 1);
    App->objects[2]->setDiffuse(1);
    App->objects[2]->setSpecular(1);
    App->objects[2]->setAmbient(1);

    App->objects[0]->setColor(1, 1, 1);
    App->objects[0]->setDiffuse(1);
    App->objects[0]->setSpecular(1);
    App->objects[0]->setAmbient(.3);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    App->lightpos.set(-3,0,20);
    //App->lightpos.set(0,0,20);
    //App->lightpos = App->viewpos;
  }
 if(scene == 2){
    
    App->num_objects = 2;
    App->objects.push_back((sphere*) new sphere());
    App->objects.push_back((sphere*) new sphere());
          
    ((sphere*)App->objects[0])->radius = 1;
    ((sphere*)App->objects[0])->center.set( .6, .5, 0);
    App->objects[0]->setColor(0, 0, 1);
    App->objects[0]->setDiffuse(.6);
    App->objects[0]->setSpecular(.3);
    App->objects[0]->setAmbient(1);

    ((sphere*)App->objects[1])->radius = 1;
    ((sphere*)App->objects[1])->center.set( -1.4, .5, 4);
    App->objects[1]->setColor(1, .2, 1);
    App->objects[1]->setDiffuse(1);
    App->objects[1]->setSpecular(1);
    App->objects[1]->setAmbient(0);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    App->lightpos.set(0,0,4);
  }

 if(scene == 3){
    
    App->num_objects = 2;
    App->objects.push_back((sphere*) new sphere());
    App->objects.push_back((sphere*) new sphere());
    App->objects.push_back((plane*) new plane(Vec(0,0,1), Vec(0,0,-20)));
    ((sphere*)App->objects[0])->radius = 1;
    ((sphere*)App->objects[0])->center.set( -.6, .5, 0);
    App->objects[0]->setColor(0, 0, 1);
    App->objects[0]->setDiffuse(.1);
    App->objects[0]->setSpecular(.5);
    App->objects[0]->setAmbient(0);

    ((sphere*)App->objects[1])->radius = 1;
    ((sphere*)App->objects[1])->center.set( 1.4, .5, -4);
    App->objects[1]->setColor(1, .2, 1);
    App->objects[1]->setDiffuse(.5);
    App->objects[1]->setSpecular(1);
    App->objects[1]->setAmbient(0);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    App->viewpos.set(0,-5,14);
    App->lightpos = App->viewpos;
  }

if(scene == 4){
    
    App->num_objects = 7;
    App->noShadow = true;

    //App->objects.push_back((plane*) new plane(Vec(0,1,0),Vec(0,-1,0)));
    Vec planePoint(0,0,-15);
    Vec planeNormal(0,0,1);
    Vec planePointB(0,-4,0);
    Vec planeNormalB(0,1,0);
    Vec planePointC(4,0,0);
    Vec planeNormalC(-1,0,0);
    Vec planePointD(-4,0,0);
    Vec planeNormalD(1,0,0);
    Vec planeNormalE(0,-1,0);
    Vec planePointE(0, 4, 0);
    Vec planeNormalF(0,0,-1);
    Vec planePointF(0,0,15);

    planeNormal.normalize();
    planeNormalB.normalize();
    planeNormalC.normalize();
    planeNormalD.normalize();
    planeNormalE.normalize();
    planeNormalF.normalize();

    App->objects.push_back((plane*) new plane(planeNormal,planePoint));
    App->objects.push_back((plane*) new plane(planeNormalB,planePointB));
    App->objects.push_back((plane*) new plane(planeNormalC,planePointC));
    App->objects.push_back((plane*) new plane(planeNormalD,planePointD));
    App->objects.push_back((plane*) new plane(planeNormalE,planePointE));
    App->objects.push_back((plane*) new plane(planeNormalF,planePointF));
    App->objects.push_back((sphere*) new sphere());          

    App->objects[0]->setColor(0, 0, 1);
    App->objects[0]->setDiffuse(1);
    App->objects[0]->setSpecular(.3);
    App->objects[0]->setAmbient(.1);

    App->objects[1]->setColor(0, 1, 0);
    App->objects[1]->setDiffuse(1);
    App->objects[1]->setSpecular(.3);
    App->objects[1]->setAmbient(.1);

    App->objects[2]->setColor(1, 0, 0);
    App->objects[2]->setDiffuse(1);
    App->objects[2]->setSpecular(.3);
    App->objects[2]->setAmbient(0);

    App->objects[3]->setColor(1, 0, 1);
    App->objects[3]->setDiffuse(1);
    App->objects[3]->setSpecular(.3);
    App->objects[3]->setAmbient(0);

    App->objects[4]->setColor(1, 1, 0);
    App->objects[4]->setDiffuse(1);
    App->objects[4]->setSpecular(.3);
    App->objects[4]->setAmbient(.1);

    //((sphere*)App->objects[4])->radius = 1;
    //((sphere*)App->objects[4])->center.set( -.6, .5, 0);

    App->objects[5]->setColor(0, 0, 1);
    App->objects[5]->setDiffuse(1);
    App->objects[5]->setSpecular(.3);
    App->objects[5]->setAmbient(0);


    ((sphere*)App->objects[6])->radius = 1;
    //((sphere*)App->objects[6])->center.set( -.6, .5, 0);
    ((sphere*)App->objects[6])->center.set( 0, 0, 0);
    App->objects[6]->setColor(1, 1, 1);
    App->objects[6]->setDiffuse(1);
    App->objects[6]->setSpecular(0);
    App->objects[6]->setAmbient(.6);

    

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    
    //App->viewpos.set(0,0,14);
    //App->lightpos = App->viewpos;
    
    App->lightpos.set(3, 0, 0);
  }

if(scene == 5){
  //App->noShadow = true;
    App->num_objects = 3;
   
    //App->objects.push_back((plane*) new plane(Vec(0,1,0),Vec(0,-1,0)));
    Vec planePoint(0,0,-4);
    Vec planeNormal(0,0,1);
    Vec planePointB(1000,0,0);
    Vec planeNormalB(1,0,0);
    planeNormal.normalize();
    planeNormalB.normalize();

    App->objects.push_back((plane*) new plane(planeNormal,planePoint));
    App->objects.push_back((sphere*) new sphere());          
    //App->objects.push_back((triangle*) new triangle(Vec(0,3,0), Vec(1,3,0), Vec(1, 1, 0), true));

    double model[] = { -2,0,0, 0,4,0, 2,0,0,
		       0,4,0, 2,0,0, 5,0,-4
		        };

    drawModel(2, model, true, 2);
    // App->objects.push_back((triangle*) new triangle(Vec(-2,0,-2), Vec(0,3,0), Vec(1, 3, 0), true));
    // App->objects.push_back((triangle*) new triangle(Vec(-2,0,-2), Vec(-3,1,-2), Vec(-1.2, .2, -2), true));
    

    App->objects[0]->setColor(0, 0, 1);
    App->objects[0]->setDiffuse(.3);
    App->objects[0]->setSpecular(1);
    App->objects[0]->setAmbient(0);
    cout << "The value of App->objects[0]->getAmbient() is:"<< App->objects[0]->getAmbient() <<endl;

    // App->objects[2]->setColor(0, 1, 0);
    // App->objects[2]->setDiffuse(0);
    // App->objects[2]->setSpecular(1);
    // App->objects[2]->setAmbient(1);


    ((sphere*)App->objects[1])->radius = 1;
    ((sphere*)App->objects[1])->center.set( .6, .5, 0);
    App->objects[1]->setColor(1, 0, 0);
    App->objects[1]->setDiffuse(1);
    App->objects[1]->setSpecular(1);
    App->objects[1]->setAmbient(1);

    // App->objects[3]->setColor(1, 0, 0);
    // App->objects[3]->setDiffuse(1);
    // App->objects[3]->setSpecular(.2);
    // App->objects[3]->setAmbient(.7);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    
    //App->viewpos.set(0,0,14);
    App->lightpos = App->viewpos;
    
    App->lightpos.set(3, 0, 0);
    //App->lightpos.set(-3,0,4);
  }
    
if(scene == 6){
    
  App->noShadow = true;
    App->num_objects = 4;

    App->objects.push_back((sphere*) new sphere());
    Vec norm(0,-1,0);
    Vec pnt(0,-8,0);
    App->objects.push_back((plane*) new plane(norm, pnt));
    App->objects.push_back((sphere*) new sphere());
    App->objects.push_back((sphere*) new sphere());
    ((sphere*)App->objects[0])->radius = 1;
    ((sphere*)App->objects[0])->center.set( 0, 2, 0);
    App->objects[0]->setColor(0, 0, 1);
    App->objects[0]->setDiffuse(1);
    App->objects[0]->setSpecular(1);
    App->objects[0]->setAmbient(0);

    App->objects[1]->setColor(.1, .1, .1);
    App->objects[1]->setDiffuse(1);
    App->objects[1]->setSpecular(1);
    App->objects[1]->setAmbient(1);

((sphere*)App->objects[2])->radius = 1;
    ((sphere*)App->objects[2])->center.set( 2, 2, 0);
    App->objects[2]->setColor(1, 0, 0);
    App->objects[2]->setDiffuse(1);
    App->objects[2]->setSpecular(0);
    App->objects[2]->setAmbient(0);


((sphere*)App->objects[3])->radius = 1;
    ((sphere*)App->objects[3])->center.set( -2, 4.5, 0);
    App->objects[3]->setColor(0, 1, 0);
    App->objects[3]->setDiffuse(1);
    App->objects[3]->setSpecular(0);
    App->objects[3]->setAmbient(0);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    //App->lightpos.set(0,20,0);
    App->lightpos = App->viewpos;
  }


if(scene == 7){
    
     
    App->num_objects = 2;
   
    //App->objects.push_back((plane*) new plane(Vec(0,1,0),Vec(0,-1,0)));
    Vec planePoint(0,0,-4);
    Vec planeNormal(0,0,1);

    double model[] = { -2,0,0, 0,4,0, 2,0,0,
		       0,4,0, 2,0,0, 5,0,-4
		        };

    drawModel(2, model, true, 0);

    // planeNormal.normalize();

    //points specified in cw order, so ccw argument is set to false
    
     // App->objects.push_back((triangle*) new triangle( Vec(-2,-4,0), Vec(0,4,0), Vec(2,-4,-1), false));
    
//  App->objects.push_back((triangle*) new triangle(planeNormal,planePoint, Vec(2,-4,0), Vec(2,4,0), Vec(6,-4,-1), false));

//     App->objects.push_back((triangle*) new triangle(planeNormal,planePoint, Vec(0,4,0), Vec(2,-4,-1), Vec(2,4,0), true));

// App->objects.push_back((triangle*) new triangle(planeNormal,planePoint, Vec(2,-4,0), Vec(2,4,0), Vec(6,-4,-1), false));

    // App->objects[0]->setColor(0, 0, 1);
    // App->objects[0]->setDiffuse(.3);
    // App->objects[0]->setSpecular(0);
    // App->objects[0]->setAmbient(.1);

    // App->objects[1]->setColor(1, 0, 0);
    // App->objects[1]->setDiffuse(1);
    // App->objects[1]->setSpecular(0);
    // App->objects[1]->setAmbient(.4);


    // App->objects[2]->setColor(0, 1, 0);
    // App->objects[2]->setDiffuse(.3);
    // App->objects[2]->setSpecular(0);
    // App->objects[2]->setAmbient(1);

    // App->objects[3]->setColor(0, 0, 1);
    // App->objects[3]->setDiffuse(.3);
    // App->objects[3]->setSpecular(0);
    // App->objects[3]->setAmbient(1);

    // cout<<App->objects[3]->getSpecular()<<endl;
    // cout<<App->objects[0]->getSpecular()<<endl;


    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    
    //App->viewpos.set(0,0,14);
    App->lightpos = App->viewpos;
    
    //App->lightpos.set(10, 2, 0);
  }

if(scene == 8){
  App->noShadow = true;
  App->reflections = true;

  float diffuse = 1;
  float specular = 0;
  float ambient = 1;

  

  App->num_objects = draw_model ( *App->model[0], diffuse, specular, ambient, false);
  App->num_objects += 2;

  // App->objects.push_back((sphere*) new sphere());
  // ((sphere*)App->objects.back())->radius = 1;
  // ((sphere*)App->objects.back())->center.set( -2, 4.5, 0);
  // App->objects.back()->setColor(1,1,1);
  // App->objects.back()->setDiffuse(1);
  // App->objects.back()->setAmbient(1);
  // App->objects.back()->setSpecular(1);

  Vec norm(0,0,1);
  Vec pnt(0,0,30);
  App->objects.push_back((plane*) new plane(norm, pnt));
  App->objects.back()->setColor(0,0,1);
  App->objects.back()->setDiffuse(1);
  App->objects.back()->setAmbient(1);
  App->objects.back()->setSpecular(1);

  norm.set(1,0,0);
  pnt.set(-8,0,0);
  App->objects.push_back((plane*) new plane(norm, pnt));
  App->objects.back()->setColor(1,0,0);
  App->objects.back()->setDiffuse(1);
  App->objects.back()->setAmbient(.3);
  App->objects.back()->setSpecular(0);

    App->background_color.set(0, 0, 0);
    App->light_source_color.set(1.0f, 1.0f, 1.0f);
    
    //App->viewpos.set(0,0,-14);
    App->lightpos = App->viewpos;
    
    App->lightpos.set(10, 2, 0);
  }


}


void renderScreen(Vec xSize, Vec ySize, Vec eye, float depth, int* pointColor[3] ){
  Vec result;

  // interpolate over the projected size of the screen
  float delta_y = (ySize.y - ySize.x)/(double)SCREENH;
  float delta_x = (xSize.y - xSize.x)/(double)SCREENW;

  //debug
  //cout<<"deltas:"<<delta_x<<" "<<delta_y<<endl;
  //end_debug

	Model* m1 = new Model();
	App->model[0] = m1;
	m1->load("rlowerarm.m");



  //set the first point with which to choose a direction
  float viewX, viewY = ySize.x;
  Vec view, direction;

  //set the default to use reflections
  App->reflections = true;

  // set the default to use shadows
  App->noShadow = false;

  //set the default shininess to be 20
  App->shininess = 20;

  //set the view position to be the same as that used for transforms
  App->viewpos = eye;

 //choose a pre-defined scene
 // 1 is two spheres on the same plane, but at different positions. Demonstrates reflection
 // 2 is the same as 1, but with a different light position
 // 3 is a reverse view of 1. Demonstrates reflection 
 // 4 is a box with a sphere in it
 // 5 is a demonstration of shadows with a plane, a triangle, and a sphere
 // 6 is a test
 // 7 is a test
 // presentation: 1, 3, 4, 5
 setScene(8);

 //go across the entire virtual screen (recording surface) of the camera, tracing
 //     rays in the appropriate direction
  int x, y;
  for( y = 0; y<SCREENH ; y++){
    viewX = xSize.x;
    for( x = 0; x<SCREENW; x++){
        
      //set the point on the screen that a ray will pass through
      view.x = viewX; view.y = viewY; view.z = depth;
        
      //get the direction vector and normalize
      direction.set(viewX, viewY, 0);
      direction = direction - App->viewpos;
      direction.normalize();
  
      //do the ray trace for the ray in the given direction. Start at step 0
      result = trace(App->viewpos, direction, 0);
      //result = trace(eye, direction, 0);

      //debug
      //if(y == 0 && x == 0) cout<< "x starts at "<< viewX << endl<<"y starts at "<<viewY<<endl;
      //end_debug

      color scr;
      scr.x = (result.x*255);
      scr.y = (result.y*255);
      scr.z = (result.z*255);
      if(scr.x > 255) scr.x = 255;
      if(scr.y > 255) scr.y = 255;
      if(scr.z > 255) scr.z = 255;

      App->screen[y][x].x += scr.x; App->screen[y][x].y += scr.y; App->screen[y][x].z += scr.z;
      //increment the x positon of the target location on the virtual screen
      viewX += delta_x;
    }
    //increment the y position of the target location on the virtual screen
    viewY += delta_y;
  }
        
}

