#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
#include "game.h"

using namespace irr;
using namespace std;
using core::vector3df;


int getFieldx(vector3df position){
  int x = position.Z/fieldsize;
  if (x<0) x=0;
  if (x>=dimx) x=dimx-1;
  return x;
} 
int getFieldy(vector3df position){
  int y = position.X/fieldsize;
  if (y<0) y=0;
  if (y>=dimx) y=dimy-1;
  return y;
}
  
f32 getOverlapx(vector3df position, int fx){
  f32 diffx = position.Z - (fieldsize*fx);
  if (diffx<spheresize+fieldsize && diffx>-spheresize){
    if (diffx<=0) return -(diffx+spheresize);
    else return -(diffx-spheresize-fieldsize);
  }
  return 0.f;
}
f32 getOverlapy(vector3df position, int fy){
  f32 diffy = position.X - (fieldsize*fy);
  if (diffy<spheresize+fieldsize && diffy>-spheresize){
    if (diffy<=0) return -(diffy+spheresize);
    else return -(diffy-spheresize-fieldsize);
  }
  return 0.f;
}


Sphere::Sphere(scene::ISceneManager* smgr,
	 video::IVideoDriver* driver,
	 vector3df p){ 
    position=p; 
    this->smgr=smgr;
    this->driver=driver;
    sphere = smgr->addSphereSceneNode(spheresize,32);
    sphere->setPosition(p);
    sphere->setMaterialFlag(video::EMF_LIGHTING
			    , false);
    sphere->setMaterialTexture(0,driver->getTexture(texturepath+"fl-abyss.png")); // put a black texture on the sphere
};

vector3df Sphere::getPosition(){ return position; }
void Sphere::setPosition(vector3df p){ position=p; sphere->setPosition(p); }
vector3df Sphere::getVelocity(){ return velocity; }
void Sphere::setVelocity(vector3df v){ velocity=v; }

void Sphere::standardSphereProgress(core::position2di mousemove, f32 frameDeltaTime, f32 friction){
    // Acceleration
    velocity.X += mousemove.Y;
    velocity.Z += mousemove.X;
    
    // Friction
    velocity.X *=1-(friction*frameDeltaTime);
    velocity.Z *=1-(friction*frameDeltaTime);
          
    // Update position (note we use the functions getPosition and setPosition!
    core::vector3df spherePosition = getPosition();
    spherePosition.X += velocity.X*frameDeltaTime;
    spherePosition.Z += velocity.Z*frameDeltaTime;
    setPosition(spherePosition);
};
