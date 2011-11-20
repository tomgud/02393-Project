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
	T31* friendField = (T31*) &f;
	friendField->switchCenterField(false);
}

void T31::switchCenterField(bool val) {
	this->isCenterField = val;
	if (!val) {
		this->texture = driver->getTexture(texturepath+"fl-acblack.png");
		block->setMaterialTexture(0,texture);
	}
}

void T31::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)
{
	// Might not need this. 
	// We should call this function in parent field.
	if (isActive && this->isCenterField )
	{
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
}


void T31::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime)
{
	vector3df vel = s.getVelocity();
	vector3df pos = s.getPosition();
	
	// Need to keep on counting.
	timeProgress(frameDeltaTime);
	if (isActive && !this->isCenterField)
	{
		float adjustment = 10;
		vel.X *= 1-(adjustment*frameDeltaTime);
		vel.Z *= 1-(adjustment*frameDeltaTime);
		s.setVelocity( vel );
		
		pos.X += vel.X*frameDeltaTime;
	    pos.Z += vel.Z*frameDeltaTime;
		s.setPosition( pos );
	}
	else 
	{
		Floor::handleSphere(s, mousemove, frameDeltaTime);
	}
}

void T31::changeTexture()
{
	if (!this->isCenterField)
		return;
	
	if ( this->texIndex < 50 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") ); 
	}
	else if ( this->texIndex < 100 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor4.bmp") ); 
	}
	else if ( this->texIndex < 150 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor7.bmp") ); 
	}
	else if ( this->texIndex < 200 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor10.bmp") ); 
	}
	else if ( this->texIndex < 250 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor13.bmp") ); 
	}
	else if ( this->texIndex < 300 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor16.bmp") ); 
	}
	else if ( this->texIndex < 350 ) {
		block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor19.bmp") ); 
	}
}

void T31::timeProgress(f32 frameDeltaTime)
{
	if (timePassed > timeActive)
	{
		// Time to switch the pulse off.
		isActive = !isActive;
		timePassed = 0.0;
		
		if (this->isCenterField)
			block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") );
		this->texIndex = 0;
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
		this->texIndex += 1;
		this->changeTexture();
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
	//block->setMaterialTexture(0, driver->getTexture(texturepath + "pulsecolor0.bmp") );
	this->texIndex = 0;
}

fieldtype T31::getFieldType()
{ 
	return tT31; 
}