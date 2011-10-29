#include "game.h"
#include "field.h"

// Implementation of all the functions that are declared in field.h

vector3df cubePosition(int x, int y, bool isWall){
  f32 vpos = isWall ? fieldsize : 0.f;
  return vector3df(fieldsize*y+halffieldsize,vpos,fieldsize*x+halffieldsize);
};

// Constructor of class Field
Field::Field(ISceneManager* smgr,
	IVideoDriver* driver,
	     int x, int y, playground pg)
{
  this->smgr=smgr;
  this->driver=driver;
  this->x=x;
  this->y=y;
  this->pg=pg;
}

// inquiry functions
int Field::getx(){ return x; }
int Field::gety(){ return y; }

// Constructor of class Wall
Wall::Wall(ISceneManager* smgr,
	   IVideoDriver* driver,
	   int x, int y, playground pg) 
  : Field(smgr,driver,x,y,pg)   
    // calling constructor of parent class
{
  // instances of Wall may use a different texture or even several of them. 
  this->texture=driver->getTexture(texturepath+"st-blue-sand.png");

  // build a block and paint it with texture
  block = smgr->addCubeSceneNode(fieldsize);
  block->setMaterialTexture(0,texture); 
  block->setPosition(cubePosition(x,y,true));
  block->setMaterialFlag(video::EMF_LIGHTING, false);
}

// Walls are by default reflecting (i.e. pushing the sphere back)
bool Wall::reflects(){ return true; }

void Wall::sphereEnter(Sphere &s){
  // do nothing
}
void Wall::sphereExit(Sphere &s){
  // do nothing
}

// The handleSphere method should only be called when the sphere has
// entered a field, which should actually not happen for a solid wall.
// However, our collision detection is not perfect and it happens. 
// We then just print out a message and play as if it was a Floor---using 
// the standardSphereProgress method of the sphere.
void Wall::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime){
  cerr << "Bug: sphere has managed to enter a solid wall.\n";
  s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
};

void Wall::timeProgress(f32 frameDeltaTime){
  // do nothing
};

// Overlap of the sphere with this Wall: here happens the standard
// collision detection---reflecting the sphere by two times the amount
// of the overlap
void Wall::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap){
  vector3df p=s.getPosition();
  vector3df v=s.getVelocity();
  if (xoverlap!=0){ 
    v.Z= -v.Z; 
    p.Z += 2*xoverlap; 
  }
  if (yoverlap!=0){
    v.X= -v.X; 
    p.X += 2*yoverlap; 
  }
  s.setPosition(p);
  s.setVelocity(v);
}

// the field type of the parent class is just tWall
fieldtype Wall::getFieldType(){ return tWall; }

//////////////////////////////

// constructor of Floor
Floor::Floor(ISceneManager* smgr,
	     IVideoDriver* driver,
	     int x, int y, playground pg) 
  : Field(smgr,driver,x,y,pg) // calling constructor of parent class
{
  texture=driver->getTexture(texturepath+"fl-acblack.png");
  block = smgr->addCubeSceneNode(fieldsize);
  block->setMaterialTexture(0,texture); 
  block->setPosition(cubePosition(x,y,false));
  block->setMaterialFlag(video::EMF_LIGHTING, false);
}

// Floors are by default not reflecting the Sphere
bool Floor::reflects(){ return false; }

void Floor::sphereEnter(Sphere &s){
  // do nothing
}
void Floor::sphereExit(Sphere &s){
  // do nothing
}

// this is called when the sphere is on this Floor for the amount frameDeltaTime
// usually, one should just use the standardSphereProgress method of the sphere.
void Floor::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime){
  s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
};

void Floor::timeProgress(f32 frameDeltaTime){
  // do nothing
};

void Floor::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap){
  // do nothing
}
fieldtype Floor::getFieldType(){ return tFloor; }


