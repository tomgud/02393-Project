// Implementation of the example Wall and example Floor

#include "game.h"
#include "field.h"
#include "testfield.h"

//////////////////////////////

TestWall::TestWall(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground pg) 
: Wall(smgr,driver,x,y,pg) // calling constructor of parent class
{
	// use a different texture than parent class:
	texture=driver->getTexture(texturepath+"st-rock3_cracked.png");
	block->setMaterialTexture(0,texture);
	
	// A pointer to a related object which is initially 0 (i.e. no related object).
	related=0;
};


void TestWall::introduceTo(Field &f)
{
	/* 
	Example to how to build up relationships between fields. 
	The field.lvl file contains the line
	introduce 14 2 to 1 7
	which means that main routine is going to call
	playground[14][2]->introduceTo(playground[1][7]);

	We assume that such calls only occur for fieldtypes that "know
	how to talk to each other" (i.e. being programmed by the same
	team). In the example, let's say it can only happen between
	objects of type TestWall. And we first check this:
	*/
	if (f.getFieldType()!=tTestWall) error("TestWall introduced to Non-TestWall!!\n");
	
	// Now we know that f is an object of type TestWall (i.e. a more
	// specific type than Field). We do a pointer conversion, so we can
	// store it in the variable "related" (which is of type
	// TestWall*). So this field can later communicate to the related Field.
	related=(TestWall *) &f;
}

void TestWall::sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)
{
	/* 
	This function is called when the sphere touches/overlaps with the
	borders of this TestWall. Normally we do just collision detection
	(as in the parent class Wall), but here wo do something additional:

	We make an example of using the playground (which is a parameter
	of the constructor for all Fields). Here we check whether any of
	the adjacent Fields is also of type TestWall; if so, we make it
	invisible. For that we first need a pointer conversion from
	Field *) to the more specific (TestWall *) -- because Field does
	not have a member variable "block" that we want to access.
	*/
	if (x>0 && pg[x-1][y]->getFieldType()==tTestWall)
		((TestWall *)pg[x-1][y])->block->setVisible(false);
	if (y>0 && pg[x][y-1]->getFieldType()==tTestWall)
		((TestWall *)pg[x][y-1])->block->setVisible(false);
	if (x<dimx-1 && pg[x+1][y]->getFieldType()==tTestWall)
		((TestWall *)pg[x+1][y])->block->setVisible(false);
	if (y<dimy-1 && pg[x][y+1]->getFieldType()==tTestWall)
		((TestWall *)pg[x][y+1])->block->setVisible(false);

	/* 
	Another example: if the introduceTo function above had been
	called for this field, i.e. if the pointer "related" is not 0,
	then we set that related field to be visible again. 
	*/
	
	if (related)
		related->block->setVisible(true);
	
	// standard collision detection (a copy of the code parent class)
	// Tomas: Actually just call the parent function since it is 
	// very bad practice to copy / pasting code. (i.e. what if you
	// want to change the code, you have to change it in many placse etc)
	// Tomas: (this worked)
	Wall::sphereOverlap(s, xoverlap, yoverlap);
}

fieldtype TestWall::getFieldType()
{ 
	return tTestWall; 
}



/////////////////////////////////

/// Example of a special kind of Floor
LightFloor::LightFloor(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground pg)
: Floor(smgr,driver,x,y,pg) // calling constructor of parent class
{
	// use a different standard texture than parent class:
	texture=driver->getTexture(texturepath+"fl-bridgex-closed.png");
	block->setMaterialTexture(0,texture); 
	
	// use a alternative texture (for when the sphere is on this Floor).
	alt_texture = driver->getTexture(texturepath+"fl-plank.png");
	timeSpentHere=0.f; // see below
	falling=false;     // see below
}

// when the sphere enters, change the texture to the alternate one
void LightFloor::sphereEnter(Sphere &s)
{
	block->setMaterialTexture(0,alt_texture); 
}

// change back when the sphere leaves.
void LightFloor::sphereExit(Sphere &s)
{
	block->setMaterialTexture(0,texture);
}


/* 
	Example for the feature to install a special "handler" for the sphere (that is independent 
	of the Floor the sphere is on). Then we first have to declare a function that has just the 
	same input arguments as the following one (and no output):  
*/

void fallingSphere(Sphere & s,position2di mousemove,f32 frameDeltaTime,f32 friction)
{
	// This handler would accelerate the sphere downwards, ignoring all
	// mouse movements or speed in horizontal directions:
	vector3df p=s.getPosition();
	vector3df v=s.getVelocity();
	v.X=v.Z=0.f;
	v.Y-=1.f*frameDeltaTime; // falling;
	p+=v;
	s.setPosition(p);
	s.setVelocity(v);
}  

// This method gets called whenever the sphere is on the floor for frameDeltaTime
void LightFloor::handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime)
{
	// We count the total time that the sphere has been on this field:
	timeSpentHere+=frameDeltaTime;
	
	// If we have spent more than 3.0 time units here, then the floor is
	// removed and the sphere falls downwards. The falling flag is used
	// so that we won't start falling more than once.
	if (!falling && timeSpentHere>3.f)
	{
		falling =true;
		// removing the floor by making it invisble:
		block->setVisible(false);
		
		// Installing the "fallingSphere" handler we have defined
		// above. The sphere will no longer behave according to the
		// standardSphereProgress-method (of class sphere) but do what the
		// fallingSphere handler tells it to. Note that we here give the
		// entire "fallingSphere" function as an argument (!) to the
		// installAlternateSphereProgress method.
		s.installAlternateSphereProgress(fallingSphere);
	}
	
	// We always call the standardSphereProgress -- even after the 3.f
	// seconds, because that will invoke either the standard progress or
	// the alternative handler once it is installed.
	s.standardSphereProgress(mousemove, frameDeltaTime, stdfriction);
};

fieldtype LightFloor::getFieldType()
{
	return tLightFloor;
}

