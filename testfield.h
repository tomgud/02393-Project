///////////// Some examples of fields by Sebastian Moedersheim

// note that your header files must be protected against multiple inclusion using the definition of a special identifier
// note that you also need the #endif at the end of the file
 
#ifndef ____TESTFIELD____
#define ____TESTFIELD____

#include "game.h"
#include "field.h"

// Declaring one example of a Wall, called TestWall.

class TestWall: public Wall
{
	protected:
		// To demonstrate the "introduceTo" feature, we have here a pointer to another
		// field of type TestWall. (Explained in comments where it is used)
		TestWall *related;
		
	public:
		TestWall(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground  pg) ;
		
		// since the parent class Wall defines all the virtual methods of
		// Field, we only need to declare those that we are going to change:
		virtual fieldtype getFieldType();
		virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap);
		virtual void introduceTo(Field &f);
};


// Declaring one example of a Floor, called LightFloor
class LightFloor: public Floor
{
	protected:
		// this one contains a second texture (for when the sphere is on this floor)
		ITexture *alt_texture;
		
		// a counter for the time that the sphere was on this floor
		f32 timeSpentHere;
		
		// a flag whether the sphere is in free fall mode
		bool falling;
	
	public:
		LightFloor(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground pg) ;
		
		// again just declaring those methods that are going to change with respect to parent class:
		virtual void sphereEnter(Sphere &s);
		virtual void sphereExit(Sphere &s);
		virtual void handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime);
		virtual fieldtype getFieldType();
};

#endif
