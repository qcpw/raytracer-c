#include <math.h>
#include <iostream>
#include "glutapp.h"
#include "raytrace.h"
using namespace std;

//q must be correct
//norm appears to be correct
//l also appears to be correct, but changing it to the left or right makes the reflections become strange
//look in functions that use l

#define no_intersection 0
#define light_source 1
typedef Vec color;
typedef Vec point;


//added from new ray
double normalLight(Vec normal, Vec surfaceToLight){
  double output;
  //cout<<surfaceToLight<<endl;
  //do some checks. These may be redundant, but they save me headaches
  if(normal.len() != 1) normal.normalize();
  if(surfaceToLight.len() != 1) surfaceToLight.normalize();
  //calculate the angle
  output = dot(normal , surfaceToLight);

  return output;
}

Vec new_reflection(Vec normal, Vec surfaceToLight){
  Vec output;
  //this function does checking to see if vectors are normalized, so additional checking is unneccessary
  double angle = normalLight(normal, surfaceToLight);
  double twiceTheAngle = angle * 2.0 * 3.141592653589793238462643383279502884197169399375106;
  
  output = normal * twiceTheAngle;
  output = output - surfaceToLight;
  return output;
}

Vec phongModel(Vec normal, Vec surfaceToLight, Vec viewerDirection, double ambient, double diffuse, double specular, Vec color){
  int shininess = App->shininess;
  Vec output;
  if(viewerDirection.len() != 1) viewerDirection.normalize();


  Vec reflectionDirection = new_reflection(normal, surfaceToLight);
  double dir = dot(reflectionDirection, viewerDirection);

  //reflectionDirection = dot(reflectionDirection, viewerDirection);
  double lightAngle = normalLight(normal, surfaceToLight);
  
  if(dir<0)dir = 0.0;
  if(lightAngle < 0) lightAngle = 0.0;

  //if(lightAngle < 0) lightAngle *= -1;
  //if(lightAngle < 0) lightAngle = dir + 2.0 * 3.141592653589793238462643383279502884197169399375106;

  dir = pow(dir, shininess);
  // this assumes the light has equal specular, ambient, and diffuse properties with value 1
  //red
  output.x = (App->light_source_color.x * ambient * color.x) + (App->light_source_color.x * diffuse * lightAngle * color.x) + (App->light_source_color.x * dir * specular * color.x );
  //green
  output.y = (App->light_source_color.y * ambient * color.y) + (App->light_source_color.y * diffuse * lightAngle * color.y) + (App->light_source_color.y * dir * specular * color.y );
  //blue
  output.z = (App->light_source_color.z * ambient * color.z) + (App->light_source_color.z * diffuse * lightAngle * color.z) + (App->light_source_color.z * dir * specular * color.z );

  return output;
}

color trace(point p, Vec d, int step){
  int max = 10;// max number of recursions of the function
  
    color local, reflected, transmitted;
    point q(0, 0, 0);
    int status = -999;
    double t_value = -999;
    double closest = 10000; //set this to a big number, so that we can find the closest sphere to the camera at the point, and draw it
    int closest_sphere = -999;
    int closest_status = -999;
    Vec l;
    bool shadow = false; //keep track of whether a point is in shadow or not

    if(step>max) return( App->background_color );
  
    
    for ( int s = 0; s < App->num_objects; s++ )
      {
	status = 0;
	status = App->objects[s]->intersect(p, d, t_value);
	Vec tempq = p + (d*t_value);
	double distance = dist(tempq, p);
	if(status >= 2 && abs(distance) <= abs(closest)){
	  //closest = t_value;
	  closest = distance;
	  closest_status = status;
	  closest_sphere = s;
	  q = tempq;
	  //cout<<s<<endl;
	}
      }
  
    //l.x = App->lightpos.x - q.x;
    //  l.y = App->lightpos.y - q.y;
    //  l.z = App->lightpos.z - q.z;

    l = App->lightpos - q;

      //send out a feeler ray and see if it hits anything
      for ( int s = 0; s < App->num_objects; s++ )
      {
	status = 0;
	if(s != closest_sphere){
	  status = (App->objects[s])->intersect(q, l, t_value);
	  if(status == 2){
	    shadow = true;
	    break;
	  }
	} 
	
      }

      //debug
      if(App->noShadow)
	shadow = false;
      //end_debug


    //    cout<<q<<endl;
//q = intersect(p, d, center, r, status);
    //if(*status == 2) cout<<"status = "<<*status<<endl;
    color debug(0, 0, 0);
    //if(*status != 2) return debug;
    //if(*status == light_source) return (App->light_source_color);
    if(closest_status < 2){
      return (App->background_color);
    }
    //if(*status == no_intersection) return(App->background_color);
    


    //Vec norm = normal(q, App->objects[closest_sphere].center);
   Vec norm = App->objects[closest_sphere]->normal(q);
    Vec v;
    v = App->viewpos - q;

    if(l.len() != 1) l.normalize();
    if(v.len() != 1) v.normalize();

    Vec refl;

    //tran = transmit(q, n); //calculate transmission

    refl = new_reflection(norm, l); //calculate reflection direction

// local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse, App->objects[closest_sphere]->specular, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);

    if( App->noShadow){
      // local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse, App->objects[closest_sphere]->specular, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);

    	if(step == 0) local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse, App->objects[closest_sphere]->specular, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);
    	else local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse,App->objects[closest_sphere]->specular * .5, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);
    } else {

      if(!shadow){
    	if(step == 0) local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse, App->objects[closest_sphere]->specular, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);
    	else local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse,App->objects[closest_sphere]->specular * .5, App->objects[closest_sphere]->color);//phong(q, norm, l, v, refl, mat, light);
      } else {
    	local = phongModel(norm, l, v, App->objects[closest_sphere]->ambient, App->objects[closest_sphere]->diffuse, App->objects[closest_sphere]->specular, App->objects[closest_sphere]->color*.1);
    	//local.set(0,0,0);
    	//local.set(1,1,1);
      }
    }

    //PROBLEM!
    //refl is not correct, but new_reflection is correct.

    if(shadow || !App->reflections) reflected = Vec(0,0,0); 
    else
      /*if(shadow)*/ reflected = trace(q, refl, step + 1) * App->objects[closest_sphere]->getSpecular(); 
   
   
    //transmitted = trace(q, tran, step+1);//this is for transparent objects. Add it later
    
      

    //if( local.y > 255 || local.y <= 0) cout<<"local = "<<local.x<<" "<< local.y<< " "<< local.z<< " for point:"<<q.x<<", "<<q.y<<", "<<q.z<<endl;
    //reflected = 0;
    transmitted = 0;
    //cout<<"reflected ="<<reflected.x<<" "<<reflected.y<<" "<<reflected.z<<endl;
     color ret = (local + reflected + transmitted);
     //ret.normalize();
    return ret;
}
/*
bool realNumber(double n){
  return( n == n && n<=DBL_MAX && n>= DBL_MIN);
}
double minPositive(double a, double b){
  if(a<=0 && b>0){
    return b;
  } else if (a>0 && b<=0){
    return a;
  } else if(a>0 && b>0){
    //return min(a, b)
    return (a<=b)?a:b;
    }*/



/*color newTrace(point origin, Vec direction, int step){
  if (step > 1) return 0;

  int* status = new int();
  //keep track of what the status is. This is redundant, but I used it to check that the status was not overwritten
  int sphereStatus;
  int sp;
  double t_value;
  point ret;

  double light2[3][4];
  double mat2[3][4];
  light2[0][0] = 1; light2[0][1] = 1; light2[0][2] = 1;
     light2[1][0] = 1; light2[1][1] = 1; light2[1][2] = 1;
     light2[2][0] = 1; light2[2][1] = 1; light2[2][2] = 1;

     mat2[0][0] = 1; mat2[0][1] = 0; mat2[0][2] = 1;
     mat2[1][0] = 1; mat2[1][1] = 1; mat2[1][2] = 1;
     mat2[2][0] = 1; mat2[2][1] = 1; mat2[2][2] = 1;
    


  for ( int s = 0; s < 2; s++ )
    {
      sphereStatus = App->objects[s].intersect(origin, direction, t_value);
      ret.x = origin.x + t_value * direction.x;
      ret.y = origin.y + t_value * direction.y;
      ret.z = origin.z + t_value * direction.z;

      //ret = intersect(origin, direction, App->objects[s].center, App->objects[s].radius, status   );
      sp = s;
      //sphereStatus = *status;
      //if(*status != 0) cout<<*status<<endl;
      
      //result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive REMOVE
    }
  //if(ret.x !=0) cout<<ret.x<<", "<<ret.y<<", "<<ret.z<<endl;
  if(sphereStatus == 0){
    return 0;
  }
  if(sphereStatus == 1){
    return color(1, 1, 1);
  }
  
  
  //Vec ray = origin + direction * 1000.0f;
		
  //for ( int l = 0; l < 2; l++ )
  //{
  //sphere* sp_current = App->objects[l];
  //if (sp->light) 
  //{
  //Primitive* light = p;
  // calculate diffuse shading
  

if(*status == light_source) return (App->light_source_color);
    if(*status == no_intersection) return(App->background_color);
    delete(status);


    Vec norm = normal(ret, App->objects[sp].center);
    //cout<<"norm is:"<<endl;
    //cout<<norm<<endl;
    Vec l, v;
    norm.normalize();

    l.x = App->lightpos.x - ret.x;
    l.y = App->lightpos.y - ret.y;
    l.z = App->lightpos.z - ret.z;

    v.x = App->viewpos.x - ret.x;
    v.y = App->viewpos.y - ret.y;
    v.z = App->viewpos.z - ret.z;
    l.normalize();
    v.normalize();

    //cout<<ret<<endl;

    //cout<<" l = "<<l.x<<", "<<l.y<<", "<<l.z<<" v = "<<v.x<<", "<<v.y<<", "<<v.z<<endl;
    Vec refl = reflect(ret, norm, l); //direction a perfectly reflected ray would go
    //cout<<App->objects[sp].mat[0][2]<<endl;
  
    //color local = Ipx(l, norm, refl, v, App->objects[sp].mat, App->light);
    color local = Ipx(l, norm, refl, v, mat2, light2, shadow);
  
  //cout<<"local color:"<<local.x<<" "<<local.y<<" "<<local.z<<endl;
  color reflected(0, 0, 0);
  color refracted(0, 0, 0);

  color retColor = (local + reflected + refracted);
  retColor.normalize();
  return retColor;
  
}
*/
