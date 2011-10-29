#include "game.h"

// Here are some useful functions to compute the position on the
// playground from the 3d-position of the sphere, as well as computing
// overlaps with other fields.

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

void error(string message){
  cerr << message;
  exit(-1);
}

/////////////////////////

// Standard sphere constructor
Sphere::Sphere(ISceneManager* smgr,
	 IVideoDriver* driver,
	 vector3df p){ 
    position=p; 
    this->smgr=smgr;
    this->driver=driver;
    sphere = smgr->addSphereSceneNode(spheresize,32);
    sphere->setPosition(p);
    sphere->setMaterialFlag(video::EMF_LIGHTING
			    , false);
    sphere->setMaterialTexture(0,driver->getTexture(texturepath+"fl-abyss.png")); 
    // put a black texture on the sphere
    
    altSphereProgress=0; // an alternate progress handler: initially none
};

vector3df Sphere::getPosition(){ return position; }

// when setting the sphere's position, immediately update the position
// of the corresponding ISceneNode
void Sphere::setPosition(vector3df p){ position=p; sphere->setPosition(p); }

vector3df Sphere::getVelocity(){ return velocity; }
void Sphere::setVelocity(vector3df v){ velocity=v; }


void Sphere::standardSphereProgress(position2di mousemove, f32 frameDeltaTime, f32 friction){
  /* This method is usually called by the Field the sphere is
     currently on when time progresses by frameDeltaTime (and that
     Field does not have a specific influence on the sphere. The
     standard behavior is that the speed gets modified by the
     mousemovement and by the friction, and then the sphere just moves
     into the direction of the speed-vector for time frameDeltaTime.
  */

  // A field can take global control over the sphere by installing an
  // alternate handler (see installAlternateSphereProgress). If such a
  // handler is installed, we just pass everything to that handler.
  if (altSphereProgress){
    altSphereProgress(*this,mousemove,frameDeltaTime,friction);
  }else{
    // Otherwise, standard behavior:

    // Acceleration
    velocity.X += mousemove.Y;
    velocity.Z += mousemove.X;
    
    // Friction
    velocity.X *=1-(friction*frameDeltaTime);
    velocity.Z *=1-(friction*frameDeltaTime);
          
    // Update position (note we use the functions getPosition and setPosition!
    vector3df spherePosition = getPosition();
    spherePosition.X += velocity.X*frameDeltaTime;
    spherePosition.Z += velocity.Z*frameDeltaTime;
    setPosition(spherePosition);
  } 
};

// When a field wants global control over a sphere it can install an
// alternate progress handler; see LightFloor (in testfield.h/cpp) for
// an example of how to use this feature. Note that the argument of
// this method is itself a function f.
void Sphere::installAlternateSphereProgress(void (* f)(Sphere &,position2di,f32,f32)){
  altSphereProgress=f;
};

// To remove the alternate handler and continue with the standard
// handler, on can call this function. 
void Sphere::uninstallAlternateSphereProgress(){
  altSphereProgress=0;
};

