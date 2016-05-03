#include <vector>
#include "math.h"
#include "glutapp.h"
#include "vec.h"
#include "model.h"



void addTo(std::vector<Vec>& data, double x, double y, double z){
  data.push_back(Vec(x, y, z));  
}


//construct the model out of regular auto-triangles
int drawTriModel(std::vector<Vec>& vertices, std::vector<Vec>& colors, double diffuse, double specular, double ambient, int size){
  //draw the first triangle
  
  //debug
  // cout<<"makes it this far"<<endl;
  //
  // vertices[0] = Vec(0,0,0);
  // vertices[1] = Vec(-1,1,0);
  // vertices[2] = Vec(-1,0,0);
  //end_debug

  //cout<<vertices[0]<<endl;
  //cout<<vertices[1]<<endl;

  
  // App->objects.push_back((triangle*) new triangle(vertices[0], vertices[1], vertices[2], true));
  // App->objects.back()->setColor(colors[0].x, colors[0].y, colors[0].z);
  // App->objects.back()->setDiffuse(diffuse);
  // App->objects.back()->setSpecular(specular);
  // App->objects.back()->setAmbient(ambient);

  //debug
  // App->objects.back()->setColor(1, 0, 1);
  // App->objects.back()->setDiffuse(1);
  // App->objects.back()->setSpecular(1);
  // App->objects.back()->setAmbient(1);
  //end_debug

  //cout<<"makes it this far"<<endl;
  int ret = 0;
  //draw the rest of the triangles in strips (use the previous 2 vertices and the present one to define a triangle)
  for (int i = 0; i < size * 3; i+=3)
    {
      App->objects.push_back((triangle*) new triangle(vertices[i], vertices[i+1], vertices[i+2], true));
      //App->objects.back()->setColor(colors[i].x, colors[i].y, colors[i].z);
      App->objects.back()->setColor(colors[0].x, colors[0].y, colors[0].z);
      App->objects.back()->setDiffuse(diffuse);
      App->objects.back()->setSpecular(specular);
      App->objects.back()->setAmbient(ambient);    


      //debug
      // App->objects.back()->setColor(1, 0, 1);
      // App->objects.back()->setDiffuse(1);
      // App->objects.back()->setSpecular(1);
      // App->objects.back()->setAmbient(1);
      //end_debug

      ret++;
    }
  return ret;
}

//construct the model out of manual triangles
int drawTriModel(std::vector<Vec>& vertices, std::vector<Vec>& normals, std::vector<Vec>& colors,double diffuse, double specular, double ambient, int size){
  
}

int draw_model ( const Model &m, float d, float s, float a, bool smooth){
  float mcolor[]= {1.0f, 1.0f, 1.0f, 1.0f};
  std::vector<Vec> colors;// = new std::vector<Vec>();
  std::vector<Vec> vertices;// = new std::vector<Vec>();
  std::vector<Vec> normals;// = new std::vector<Vec>();
  //float specReflection[]= {1.0f, 1.0f, 0.8f, 1.0f};
  //float diffuseReflection[] = {0.3f, 0.3f, 0.3f, 1.0f};
  
  for(int i = 0; i<m.fsize; i++){
    double a1, a2, a3, b1, b2, b3, c1, c2, c3;
    double v1[3], v2[3], cross[3], draw[3], magnitude;
    if( smooth){
      a1 = m.V[m.F[i].va].x; a2 = m.V[m.F[i].va].y; a3 = m.V[m.F[i].va].z;
      b1 = m.V[m.F[i].vb].x; b2 = m.V[m.F[i].vb].y; b3 = m.V[m.F[i].vb].z;
      c1 = m.V[m.F[i].vc].x; c2 = m.V[m.F[i].vc].y; c3 = m.V[m.F[i].vc].z;
      v1[0] = b1-a1; v1[1] = b2-a2; v1[2] = b3-a3;
      v2[0] = c1-a1; v2[1] = c2-a2; v2[2] = c3-a3;
      cross[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
      cross[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
      cross[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
      magnitude = (sqrt((cross[0]*cross[0])+(cross[1]*cross[1])+(cross[2]*cross[2])));
      //glIsEnabled( GL_NORMALIZE );
      cross[0] = cross[0]/magnitude;
      cross[1] = cross[1]/magnitude;
      cross[2] = cross[2]/magnitude;
    }
	
	
	
    //N: when actually creating the triangle objects, create first one with 3 verts, then
    //   use the prev. 2 verts for each new vert.
    // // glBegin( GL_TRIANGLE_STRIP );
		
    //get the colors
    mcolor[0]=m.F[i].r/255.0; mcolor[1]=m.F[i].g/255.0; mcolor[2]=m.F[i].b/255.0;
		
    //printf("mcolor: %f, %f, %f\n", mcolor[0], mcolor[1], mcolor[2]);
		
    //set the material properties
    // DONE
    // N: only set the color. take the others as input to the func
    addTo(colors, mcolor[0], mcolor[1], mcolor[2]);

    // // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mcolor);
    // // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specReflection);
    // // glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseReflection);
    // // glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 30);
		
    //N: change smooth to correct z value

    // DONE
    // N: change glNormal3d to a function that stores these properties in an array of vecs
    // N: similar with glVertex
    if(smooth){
      
      addTo(normals, m.N[m.F[i].na].x, m.N[m.F[i].na].y, m.N[m.F[i].na].z);
      addTo(vertices, m.V[m.F[i].va].x, m.V[m.F[i].va].y, m.V[m.F[i].va].z);
      addTo(normals, m.N[m.F[i].nb].x, m.N[m.F[i].nb].y, m.N[m.F[i].nb].z);
      addTo(vertices, m.V[m.F[i].vb].x, m.V[m.F[i].vb].y, m.V[m.F[i].vb].z);
      addTo(normals, m.N[m.F[i].nc].x, m.N[m.F[i].nc].y, m.N[m.F[i].nc].z);
      addTo(vertices, m.V[m.F[i].vc].x, m.V[m.F[i].vc].y, m.V[m.F[i].vc].z );
    } else {

      //addTo(&normals, cross[0], cross[1], cross[2]);

      //debug
      //addTo(vertices, 0,0,0);
      //addTo(vertices, -1,1,0);
      //addTo(vertices, -1,0,0);
      //cout<<vertices.back()<<endl;
      //end_debug


	addTo(vertices, m.V[m.F[i].va].z, m.V[m.F[i].va].y, m.V[m.F[i].va].x);
	addTo(vertices, m.V[m.F[i].vb].z, m.V[m.F[i].vb].y, m.V[m.F[i].vb].x);
	addTo(vertices, m.V[m.F[i].vc].z, m.V[m.F[i].vc].y, m.V[m.F[i].vc].x);

	
	//addTo(vertices, m.V[m.F[i].vb].z, m.V[m.F[i].vb].y, m.V[m.F[i].vb].x);
	//addTo(vertices, m.V[m.F[i].vc].z, m.V[m.F[i].vc].y, m.V[m.F[i].vc].x);
      
      
      
	// App->objects.push_back((triangle*) new triangle(m.V[m.F[i].va],m.V[m.F[i].vb],m.V[m.F[i].vc], true) );
	
    }
		
		

		
		
		
		
		
		
		

  }//end for loop


  int ret;
  //for all faces, create the triangles with appropriate shading techniques
  if(smooth){
    drawTriModel(vertices, normals, colors, d, s, a, m.fsize);
  } else {
    ret = drawTriModel(vertices, colors, d, s, a, m.fsize); 
    //ret = m.fsize;
  }

  return ret;
}






