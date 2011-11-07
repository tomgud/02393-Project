// note that your header files must be protected against multiple inclusion using the definition of a special identifier
// note that you also need the #endif at the end of the file
 
#ifndef ____T31____
#define ____T31____

#include "game.h"
#include "field.h"
#include <vector>

using namespace std;
const static int friendFieldSize = 16;

class T31: public Floor // if you implement a Floor tile, replace "Wall" with "Floor"
{
	protected:
		const static f32 timeActive = 2.0;
		const static f32 force = 5.0;
		Field* friendFields[friendFieldSize];
		bool isActive;
		bool isCenterField;
		f32 timePassed;
		int texIndexIncrement;
		int texIndex;
		void changeTexture();
		
	
	public:
		T31(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground  pg);
		virtual fieldtype getFieldType();
		virtual void introduceTo(Field &f);
		virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap);
		virtual void handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime);
		virtual void timeProgress(f32 frameDeltaTime);
		virtual void sphereEnter(Sphere &s);
		virtual void sphereExit(Sphere &s);
		bool switchCenterField(bool val);
};


#endif
