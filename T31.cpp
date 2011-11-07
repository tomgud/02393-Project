// Skeleton of implementation file for groups

#include "game.h"
#include "field.h"
#include "T31.h"
#include <vector>

//////////////////////////////
// PulseField. 
// Authors: 
// Tomas Gudmundsson
// Elvar Orn Unnthorsson
//////////////////////////////
T31::T31(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground pg) : Floor(smgr,driver,x,y,pg)
{
	texture=driver->getTexture(texturepath+"particlewhite.bmp");	
	block->setMaterialTexture(0,texture); 
	this->isActive = true;
	this->timePassed = 0.0;
};

void T31::introduceTo(Field &f) {
	// Should add this field to friendFields vector.
	int place = sizeof(this->friendFields)/sizeof(Field) -1;
	this->friendFields[place] = &f;
	
}


void T31::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap) {
	// Might not need this. 
	// We should call this function in parent field.
	Floor::sphereOverlap(s, xoverlap, yoverlap);
}

void T31::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime) {
	Floor::handleSphere(s, mousemove, frameDeltaTime);
	// Need to keep on counting.
	timeProgress(frameDeltaTime);
	if (isActive) {
		vector3df here = vector3df(getx()*fieldsize, 0, gety()*fieldsize);
		vector3df zero = vector3df(0,0,0);
		s.setPosition(here);
		s.setVelocity(zero);
	}
}

void T31::timeProgress(f32 frameDeltaTime) {
	if (timePassed > timeActive) {
		// Time to switch the pulse off.
		isActive = !isActive;
		timePassed = 0.0;
	} else {
		timePassed += frameDeltaTime;
	}
}

fieldtype T31::getFieldType(){ 
  return tT31; 
}