/// The main header file of the game; it declares central constants and the Sphere class 

#ifndef  ___GAME_H
#define  ___GAME_H

#include <irrlicht.h>
#include <iostream>
using namespace irr;
using namespace std;
using core::vector3df;
using scene::ISceneManager;
using scene::ISceneNode;
using video::IVideoDriver;
using video::ITexture;
using core::position2di;

////// Constants
#define dimx 20   // the playground will have 20 x 13 fields
#define dimy 13
#define fieldsize 8.f  // each field is a square or a cube of side length 8 units 
#define halffieldsize fieldsize/2
#define spheresize 2.f  // sphere has radius 2 units

#define offsetx fieldsize*dimx/2 // offset of the playground's center from (0,0,0)
#define offsety fieldsize*dimy/2

#define minborderx spheresize+fieldsize // borders of the field (for collision detection)
#define maxborderx fieldsize*(dimx-1)-spheresize
#define minbordery spheresize+fieldsize  
#define maxbordery fieldsize*(dimy-1)-spheresize

extern io::path texturepath;

int getFieldx(vector3df position);
int getFieldy(vector3df position);
  
f32 getOverlapx(vector3df position, int fx);
f32 getOverlapy(vector3df position, int fy);

void error(string msg);

class Sphere{
 public:
  // typdef (void *)(Sphere &,position2di,f32,f32) sphereProgressHandler; 

private:
  vector3df position,velocity;
  ISceneManager* smgr;
  IVideoDriver* driver;
  ISceneNode * sphere;
  void (*altSphereProgress)(Sphere &,position2di,f32,f32);
public:
  Sphere(ISceneManager* smgr,
	 IVideoDriver* driver,
	 vector3df p=vector3df(offsety,spheresize+fieldsize*.5f,offsetx));

  vector3df getPosition();
  void setPosition(vector3df p);
  vector3df getVelocity();
  void setVelocity(vector3df v);

  /* this method is typically used when a (Floor) field has control
   over the sphere and does not want to do anything special; this
   function changes the velocity according to given mousemovement and
   friction, and then lets the sphere move according to velocity for
   the given timeperiod.  This standard behavior can be overwritten by
   installing alternate handlers (see last two methods below).
  */
  void standardSphereProgress(position2di mousemove, f32 frameDeltaTime, f32 friction);

  // Install an alternate handler for the progress; see LightWall (in testfield.cpp/.h) for an example
  void installAlternateSphereProgress(void (* f)(Sphere &,position2di,f32,f32));

  // Remove an installed alternate handler and go back to standard handling
  void uninstallAlternateSphereProgress();
};  

#endif
