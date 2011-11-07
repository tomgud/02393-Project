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
	this->isActive = true;
	this->timePassed = 0.0;
	this->texIndexIncrement = 2;
	this->texIndex = 0;
	this->isCenterField = true;
	
	// Texture stuff
	block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") );
};


void T31::introduceTo(Field &f)
{
	// Should add this field to friendFields vector.
	int place = sizeof(this->friendFields)/sizeof(Field) - 1;
	this->friendFields[place] = &f;
}


void T31::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)
{
	// Might not need this. 
	// We should call this function in parent field.
	Floor::sphereOverlap(s, xoverlap, yoverlap);
}


void T31::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime)
{
	Floor::handleSphere(s, mousemove, frameDeltaTime);
	
	// Need to keep on counting.
	timeProgress(frameDeltaTime);
	if (isActive)
	{
		vector3df here = vector3df(getx()*fieldsize, 0, gety()*fieldsize);
		vector3df zero = here + s.getVelocity();
		//s.setPosition(here);
		//s.setVelocity(zero);
		
		vector3df p = s.getPosition();
		vector3df v = s.getVelocity();
		s.setPosition(p);
		s.setVelocity(v);
		
		
	}
	this->changeTexture();
}

void T31::changeTexture()
{
	if ( this->texIndex < 50 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") ); 
	}
	else if ( this->texIndex < 100 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor1.bmp") ); 
	}
	else if ( this->texIndex < 150 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor2.bmp") ); 
	}
	else if ( this->texIndex < 200 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor3.bmp") ); 
	}
	else if ( this->texIndex < 250 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor4.bmp") ); 
	}
	else if ( this->texIndex < 300 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor5.bmp") ); 
	}
	else if ( this->texIndex < 350 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor6.bmp") ); 
	}
	else if ( this->texIndex < 400 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor7.bmp") ); 
	}
	else if ( this->texIndex < 450 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor8.bmp") ); 
	}
	else if ( this->texIndex < 500 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor9.bmp") ); 
	}
	else if ( this->texIndex < 550 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor10.bmp") ); 
	}
	else if ( this->texIndex < 600 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor11.bmp") ); 
	}
	else if ( this->texIndex < 650 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor12.bmp") ); 
	}
	else if ( this->texIndex < 700 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor13.bmp") ); 
	}
	else if ( this->texIndex < 750 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor14.bmp") ); 
	}
	else if ( this->texIndex < 800 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor15.bmp") ); 
	}
	else if ( this->texIndex < 850 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor16.bmp") ); 
	}
	else if ( this->texIndex < 900 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor17.bmp") ); 
	}
	else if ( this->texIndex < 950 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor18.bmp") ); 
	}
	else if ( this->texIndex < 1000 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor19.bmp") ); 
	}
	else if ( this->texIndex < 1050 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor20.bmp") ); 
	}
	else {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") ); 
		this->texIndex = 0;
	}
}

void T31::timeProgress(f32 frameDeltaTime)
{
	if (timePassed > timeActive)
	{
		// Time to switch the pulse off.
		isActive = !isActive;
		timePassed = 0.0;
	} 
	else
	{
		timePassed += frameDeltaTime;
	}
	
	if (isActive)
	{
		// Need to check every friend field
		// if ball is in that field.
		// If we are active, then we apply force.
	}
	// else we do nothing
}

// when the sphere enters, change the texture to the alternate one
void T31::sphereEnter(Sphere &s)
{
	//block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor9.bmp") );
}

// change back when the sphere leaves.
void T31::sphereExit(Sphere &s)
{
	block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") );
	this->texIndex = 0;
}

fieldtype T31::getFieldType()
{ 
	return tT31; 
}