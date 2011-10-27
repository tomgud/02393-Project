#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
using namespace irr;
using namespace std;
using core::vector3df;
#include "game.h"
#include "field.h"


//------------------------------------
// Field!
//------------------------------------

Field::Field(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y)
{
	this->smgr=smgr;
	this->driver=driver;
	this->x=x;
	this->y=y;
}
int Field::getx(){ return x; }
int Field::gety(){ return y; }

vector3df cubePosition(int x, int y, bool isWall)
{
	f32 vpos = isWall ? fieldsize : 0.f;
	return core::vector3df(fieldsize*y+halffieldsize,vpos,fieldsize*x+halffieldsize);
};


//------------------------------------
// Wall!
//------------------------------------

Wall::Wall(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y) : Field(smgr,driver,x,y)
{
	// instances of Wall may use a different texture or even several of them. 
	this->texture=driver->getTexture(texturepath+"st-blue-sand.png");
	
	block = smgr->addCubeSceneNode(fieldsize);
	block->setMaterialTexture(0,texture); 
	block->setPosition(cubePosition(x,y,true));
	block->setMaterialFlag(video::EMF_LIGHTING, false);
}

bool Wall::reflects(){ return true; }
void Wall::sphereEnter(Sphere &s){ /*do nothing */  }
void Wall::sphereExit(Sphere &s){ /* do nothing */  }

void Wall::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime)
{
	// for standard walls this method should not be called, as long as the collision detection 
	// works perfectly, as this can only occur if the center of the ball is within the field's limits.
	// So at least let's report that:
	cerr << "Bug: sphere has managed to enter a solid wall.\n";
	s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
};

Wall::Wall(scene::ISceneManager* smgr,
	video::IVideoDriver* driver,
	int x, int y) 
    : Field(smgr,driver,x,y)   
      // calling constructor of parent class
  {
   

    // instances of Wall may use a different texture or even several of them. 
    this->texture=driver->getTexture(texturepath+"st-blue-sand.png");

    block = smgr->addCubeSceneNode(fieldsize);
    block->setMaterialTexture(0,texture); 
    block->setPosition(cubePosition(x,y,true));
    block->setMaterialFlag(video::EMF_LIGHTING, false);
  }

 bool Wall::reflects(){ return true; }
 void Wall::sphereEnter(Sphere &s){
    // do nothing
  }
 void Wall::sphereExit(Sphere &s){
    // do nothing
  }

 void Wall::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime){
    // for standard walls this method should not be called, as long as the collision detection 
    // works perfectly, as this can only occur if the center of the ball is within the field's limits.
    // So at least let's report that:
    cerr << "Bug: sphere has managed to enter a solid wall.\n";

    s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
  };

 void Wall::timeProgress(f32 frameDeltaTime){
    // do nothing
};

 void Wall::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap){
    // standard collision detection

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
 fieldtype Wall::getFieldType(){ return tWall; }


Floor::Floor(scene::ISceneManager* smgr,
	video::IVideoDriver* driver,
	int x, int y) 
    : Field(smgr,driver,x,y) // calling constructor of parent class
  {
    texture=driver->getTexture(texturepath+"fl-acblack.png");
    block = smgr->addCubeSceneNode(fieldsize);
    block->setMaterialTexture(0,texture); 
    block->setPosition(cubePosition(x,y,false));
    block->setMaterialFlag(video::EMF_LIGHTING, false);
  }
bool Floor::reflects(){ return false; }
   void Floor::sphereEnter(Sphere &s){
    // do nothing
}
   void Floor::sphereExit(Sphere &s){
    // do nothing
  }

   void Floor::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime){
    s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
  };

   void Floor::timeProgress(f32 frameDeltaTime){
    // do nothing
  };

   void Floor::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap){
    // do nothing
  }
   fieldtype Floor::getFieldType(){ return tFloor; }

LightFloor::LightFloor(scene::ISceneManager* smgr,
	video::IVideoDriver* driver,
	     int x, int y) 
    : Floor(smgr,driver,x,y) // calling constructor of parent class
  {
    alt_texture=driver->getTexture(texturepath+"fl-plank.png");
    timeSpentHere=0.f;
  }
   void LightFloor::sphereEnter(Sphere &s){
    block->setMaterialTexture(0,alt_texture); 
  }
   void LightFloor::sphereExit(Sphere &s){
    block->setMaterialTexture(0,texture);
  }
   void LightFloor::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime){
    timeSpentHere+=frameDeltaTime;
    if (timeSpentHere>3.f){
      block->setVisible(false);
      vector3df p=s.getPosition();
      vector3df v=s.getVelocity();
      v.X=v.Z=0.f;
      v.Y-=.3f; // falling;
      p+=v;
      s.setPosition(p);
      s.setVelocity(v);
    }
    else{
      s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
    }
  };
   fieldtype LightFloor::getFieldType(){ return tLightFloor; }
void Wall::timeProgress(f32 frameDeltaTime){ /* do nothing */ };

void Wall::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)
{
	// standard collision detection
	vector3df p=s.getPosition();
	vector3df v=s.getVelocity();
	if (xoverlap!=0) 
	{ 
		v.Z= -v.Z; 
		p.Z += 2*xoverlap; 
	}
	if (yoverlap!=0)
	{
		v.X= -v.X; 
		p.X += 2*yoverlap; 
	}
	s.setPosition(p);
	s.setVelocity(v);
}

fieldtype Wall::getFieldType(){ return tWall; }



//------------------------------------
// Pulse wall!
//------------------------------------


PulseWall::PulseWall(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y) : Field(smgr,driver,x,y) // calling constructor of parent class
{
	
}






//------------------------------------
// Floor!
//------------------------------------

Floor::Floor(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y) : Field(smgr,driver,x,y) // calling constructor of parent class
{
	texture=driver->getTexture(texturepath+"fl-acblack.png");
	block = smgr->addCubeSceneNode(fieldsize);
	block->setMaterialTexture(0,texture); 
	block->setPosition(cubePosition(x,y,false));
	block->setMaterialFlag(video::EMF_LIGHTING, false);
}

bool Floor::reflects(){ return false; }

void Floor::sphereEnter(Sphere &s){ /* do nothing */ }
void Floor::sphereExit(Sphere &s){ /* do nothing */ }

void Floor::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime)
{
	s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
};

void Floor::timeProgress(f32 frameDeltaTime){ /* do nothing */ };
void Floor::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap){ /* do nothing */ }
fieldtype Floor::getFieldType(){ return tFloor; }


//------------------------------------
// LightFloor!
//------------------------------------

LightFloor::LightFloor(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y) : Floor(smgr,driver,x,y) // calling constructor of parent class
{
	alt_texture=driver->getTexture(texturepath+"fl-plank.png");
	timeSpentHere=0.f;
}

void LightFloor::sphereEnter(Sphere &s) 
{
	block->setMaterialTexture(0,alt_texture); 
}

void LightFloor::sphereExit(Sphere &s)
{
	block->setMaterialTexture(0,texture);
}

void LightFloor::handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime)
{
	timeSpentHere+=frameDeltaTime;
	if (timeSpentHere>3.f)
	{
		block->setVisible(false);
		vector3df p=s.getPosition();
		vector3df v=s.getVelocity();
		v.X=v.Z=0.f;
		v.Y-=.3f; // falling;
		p+=v;
		s.setPosition(p);
		s.setVelocity(v);
	}
	else
	{
		s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
	}
};

fieldtype LightFloor::getFieldType(){ 
	return tLightFloor; 
}
