
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glutapp.h"
#include "view.h"
#include "math.h"
using namespace std;

//#define ImageHeight 600
//#define ImageWidth 800
GLubyte Image[ImageHeight][ImageWidth][3];

static GLdouble zoomFactor = 1.0;
static GLint height;

AppState* App = new AppState;


//App->background_color.x = 0; App->background_color.y = 0; App->background_color.z = 0;



void makeCheckImage(void)
{
   int i, j;
   //App->objects[0] = new sphere();
//App->objects[1] = new sphere();

  Vec centerOfScene, eye, upVector, f0,f1, f2, f3, proj0, proj1, proj2, proj3;
  Vec screenSize;
  Vec recordingSurfaceSize;
  float depth;

  //this is the middle of the "world" in which the objects exist
  centerOfScene.set(0,0,4);

  //this is the eye of the viewer (or the camera)
  eye.set(0,0,-14);

  //this determines the angle of the camera
  upVector.set(0,1,0);  

  //calculate the coordinates of the point (0,0,-1) in the camera's frame of reference
  //f = look(centerOfScene, eye, upVector, Vec(0,0,5));

depth = dist(centerOfScene, eye);

 cout<<"depth is:"<<depth<<endl;

 f0 = look(centerOfScene, eye, upVector, Vec(-8,-6,depth)); //bottom left
 f1 = look(centerOfScene, eye, upVector, Vec(8,-6,depth)); //top left
 f2 = look(centerOfScene, eye, upVector, Vec(-8,6,depth));//bottom right
 f3 = look(centerOfScene, eye, upVector, Vec(8,6,depth));//top right


 //f0.set(-8, -6, depth);
 //f1.set(8, -6, depth);
 //f2.set(-8, 6, depth);
 //f3.set(8, 6, depth);

  screenSize.set(800.0, 600.0, 0);
  recordingSurfaceSize.set(160.0, 120.0, 0);
  
  

  proj0 = project(f0, screenSize, recordingSurfaceSize, depth);
  proj1 = project(f1, screenSize, recordingSurfaceSize, depth);
  proj2 = project(f2, screenSize, recordingSurfaceSize, depth);
  proj3 = project(f3, screenSize, recordingSurfaceSize, depth);

  

  Vec xSize(min(proj0.x, proj1.x), max(proj2.x, proj3.x));
  Vec ySize(min(proj0.y, proj2.y), max(proj1.y, proj3.y));

  //cout<<xSize<<"\t"<<ySize<<endl;

  //xSize.set(proj3.y, proj2.y);
  //ySize.set(proj0.x, );

  //cout<<"proj0:"<<proj0<<endl<<"proj2:"<<proj2<<endl;
  //cout<<"proj1:"<<proj1<<endl<<"proj3:"<<proj3<<endl;

  //cout<<"xSize:"<<xSize<<endl;
  //cout<<"ySize:"<<ySize<<endl;

  // App->num_objects = 2;

          
  // App->objects[0].radius = 2;
  // App->objects[0].center.set( 0, 5, .9);
  // App->objects[0].setColor(1, 0, 0);
  // App->objects[0].setDiffuse(.1);
  //App->objects[0].setSpecular(1);

  //App->background_color.set(0, 0, 0);


  //App->light_source_color.set(1.0f, 1.0f, 1.0f);
  //App->lightpos.set(0, -10, -20);
  //App->viewpos = eye; //x and y stretch, z zooms
  //App->viewpos.set(0,0,-20);

  int* pointColor[3];
  pointColor[0] = new int[SCREENW*SCREENH];
  pointColor[1] = new int[SCREENW*SCREENH];
  pointColor[2] = new int[SCREENW*SCREENH];

  renderScreen(xSize, ySize, eye, depth, pointColor );

  //testTrace(SCREENW, SCREENH);




  // testTrace(ImageWidth, ImageHeight);
   for (i = 0; i < ImageHeight; i++) {
      for (j = 0; j < ImageWidth; j++) {
	//c = ((((i&0x8)==0)^((j&0x8))==0))*255;
	Image[i][j][0] = (GLubyte) (App->screen[i][j].x );
	Image[i][j][1] = (GLubyte) (App->screen[i][j].y );
	Image[i][j][2] = (GLubyte) (App->screen[i][j].z );
	//cout<<App->screen[i][j]<<endl;

		
	//Image[i][j][0] = (GLubyte) (pointColor[0][i*j]);
	//Image[i][j][1] = (GLubyte) (pointColor[1][i*j]);
        //Image[i][j][2] = (GLubyte) (pointColor[2][i*j]);


      }
   }
}

void init(void)
{    
  //glClearColor (0.0, 0.0, 0.0, 0.0);
   //glShadeModel(GL_FLAT);
   makeCheckImage();
   //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0, 0);
  //glDrawPixels(ImageWidth, ImageHeight, GL_RGB, GL_UNSIGNED_BYTE, Image);
  glDrawPixels(ImageWidth, ImageHeight, GL_RGB, GL_UNSIGNED_BYTE, Image);
  glFlush();
  glutSwapBuffers();
}


void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void motion(int x, int y)
{
   static GLint screeny;
   
   screeny = height - (GLint) y;
   glRasterPos2i (x, screeny);
   glPixelZoom (zoomFactor, zoomFactor);
   glCopyPixels (0, 0, ImageWidth, ImageHeight, GL_COLOR);
   glPixelZoom (1.0, 1.0);
   glFlush ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'r':
      case 'R':
         zoomFactor = 1.0;
         glutPostRedisplay();
         printf ("zoomFactor reset to 1.0\n");

         break;
      case 'z':
         zoomFactor += 0.5;
         if (zoomFactor >= 3.0) 
            zoomFactor = 3.0;
         printf ("zoomFactor is now %4.1f\n", zoomFactor);
         break;
      case 'Z':
         zoomFactor -= 0.5;
         if (zoomFactor <= 0.5) 
            zoomFactor = 0.5;
         printf ("zoomFactor is now %4.1f\n", zoomFactor);
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(ImageWidth, ImageHeight);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("RayTrace");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMotionFunc(motion);
   glutMainLoop();
   return 0; 
}






