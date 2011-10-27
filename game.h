#ifndef  ___GAME_H
#define  ___GAME_H


#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
using namespace irr;
using namespace std;
using core::vector3df;


////// Constants
const int dimx=20;   // the playground will have 20 x 13 fields
const int dimy=13;
const f32 fieldsize=8.f;  // each field is a square or a cube of side length 8 units 
const f32 halffieldsize=fieldsize/2;
const f32 spheresize = 2.f;  // sphere has radius 2 units

const f32 offsetx=fieldsize*dimx/2; // offset of the playground's center from (0,0,0)
const f32 offsety=fieldsize*dimy/2;

const f32 minborderx = spheresize+fieldsize; // borders of the field (for collision detection)
const f32 maxborderx = fieldsize*(dimx-1)-spheresize;
const f32 minbordery = spheresize+fieldsize;  
const f32 maxbordery = fieldsize*(dimy-1)-spheresize;

const io::path texturepath="base-example.app/Contents/Resources/";

int getFieldx(vector3df position);
int getFieldy(vector3df position);
  
f32 getOverlapx(vector3df position, int fx);
f32 getOverlapy(vector3df position, int fy);
class Sphere{
private:
  vector3df position,velocity;
  scene::ISceneManager* smgr;
  video::IVideoDriver* driver;
  scene::ISceneNode * sphere;
public:
  Sphere(scene::ISceneManager* smgr,
	 video::IVideoDriver* driver,
	 vector3df p=core::vector3df(offsety,spheresize+fieldsize*.5f,offsetx));

  vector3df getPosition();
  void setPosition(vector3df p);
  vector3df getVelocity();
  void setVelocity(vector3df v);

  void standardSphereProgress(core::position2di mousemove, f32 frameDeltaTime, f32 friction);
};  

#endif
