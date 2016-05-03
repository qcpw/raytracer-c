/*=================================================
 * glutapp3d 1.0
 * CSE170 - Introduction to Computer Graphics
 * UC Merced, M. Kallmann 
 *=================================================*/

// Ensure the header file is included only once in multi-file projects
// Pragma once is a non-standard but widely supported preprocessor directive
# pragma once

// Include GLUT (OpenGL Graphics Utility Library) header files.
// In Windows we include our own included GLUT header file, but
// in Linux, the GLUT header file should be already installed.
#if defined WIN32
#include <glut/glut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "utils.h"
//#include "vec.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "model.h"
#include <vector>
#define	ImageWidth 800
#define	ImageHeight 600

// The application state is stored in the AppState structure defined
// below. A single instance of this structure is initialized in
// glutapp.cpp and is accessible by pointer App. This will allow
// your application data to be visible by all source files including
// this header file and this will be very usefull when your project
// grows and becomes multi-file project.
struct AppState
 { double fovy;
   bool   viewaxis, uselist;
   double rotx, roty, listid;
   double n,r,g,b;
   double time;
   Vec background_color;
   Vec light_source_color;
   Vec lightpos, viewpos;
   double attenuation;
   Vec screen[ImageHeight][ImageWidth];
   //sphere objects[];
   vector<object*> objects;
   double light[3][4];
   int num_objects;
   bool noShadow;
    double shininess;
    bool reflections;
   Model* model[3];
   int numModels;
 };
extern AppState* App; // Pointer to the single instance

// The following functions are callbacks that GLUT will call to
// run your application. They are passed to GLUT in glutdemo.cpp.
// See in glut.h additional callbacks to interface your program with GLUT.
// For extensive documentation, just google GLUT and OpenGL
void appKeyboardFunc ( unsigned char key, int x, int y );
void appKeyboardFunc ( int key, int x, int y );
void appDrawScene ();
void appResizeWindow ( int w, int h );

