// Declaration of the main game class Field, and its children Wall and Field

#ifndef ___FIELD_H
#define  ___FIELD_H
#include "game.h"

// Every type of Field gets its unique identifier
typedef int fieldtype;
#define tWall       90 // by Sebastian Moedersheim
#define tTestWall   91 // by Sebastian Moedersheim
#define tFloor      92 // by Sebastian Moedersheim
#define tLightFloor 93 // by Sebastian Moedersheim
#define tT01 1
#define tT02 2
#define tT03 3
#define tT04 4
#define tT05 5
#define tT06 6
#define tT07 7
#define tT08 8
#define tT09 9
#define tT10 10
#define tT11 11
#define tT12 12
#define tT13 13
#define tT14 14
#define tT15 15
#define tT16 16
#define tT17 17
#define tT18 18
#define tT19 19
#define tT20 20
#define tT21 21
#define tT22 22
#define tT23 23
#define tT24 24
#define tT25 25
#define tT26 26
#define tT27 27
#define tT28 28
#define tT29 29
#define tT30 30
#define tT31 31
#define tT32 32
#define tT33 33
#define tT34 34
#define tT35 35
#define tT36 36
#define tT37 37
#define tT38 38
#define tT39 39
#define tT40 40

// A function that computes the 3d-position from the field index (x,y) and depending whether it is a wall or not
vector3df cubePosition(int x, int y, bool isWall);

// The standard floor tile will have the following friction factor:
#define stdfriction .2f

////////////////////////////////////////////

class Field{
public:
  // declaring a type "playground", i.e. a two-dimensional array (of size dimx and dimy) of pointers to Fields. 
  // note that the second dimension of the vector needs to be specified in with a fixed size
  typedef Field* (*playground)[dimy];

protected:
  ISceneManager* smgr;
  IVideoDriver* driver;
  int x,y;            // field on the map
  ISceneNode * block; // the visual irrLicht object representing the wall
  vector3df position; // its position
  playground pg;      // the entire playground
public:

  // constructor
  Field(ISceneManager* smgr,
	IVideoDriver* driver,
	int x, int y, playground pg);

  // inquiry functions for the position
  virtual int getx();
  virtual int gety();
 
  // whether a field will push back the ball or not
  virtual bool reflects()=0; 

  // whether a field is a wall type
  virtual bool isWall()=0;

  // notification that the center of the sphere s is within the limits of the field
  virtual void sphereEnter(Sphere &s)=0;

  // notification that the center of the sphere s has left the limits of the field
  // this only happens after a sphereEnter event has occurred first. 
  virtual void sphereExit(Sphere &s)=0;

  /* The field is in charge of the progress of the sphere s for some time time frameDeltaTime
     and that the mouse has been moved by the amount specified in mousemove in this time. 
     Usually, one should then call the "standardSphereProgress" method of the sphere.
     This method will only occur after sphereEnter has occurred and before a corresponding 
     sphereExit has occurred.  */
  virtual void handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime)=0;

  // Notification that the amount frameDeltaTime has passed; this is relevant if the Field
  // has some time-dependent behavior (such as blinking).
  virtual void timeProgress(f32 frameDeltaTime)=0;
  
  // Notification that the sphere overlaps with the limits of the field by the specified amount. 
  // Usually, Floor tiles will ignore this event, and Wall tiles will reflect the sphere. 
  virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)=0;

  // Return the unique field type 
  virtual fieldtype getFieldType()=0;
  
  // This function will be called if the level file contains any specifications which fields
  // should be introduced to one another. 
  virtual void introduceTo(Field &f){};
};

/////////////////////////////////////////////////

// class Wall is derived from class Field; all methods have the same meaning as in the parent class

class Wall : public Field{
protected:
  // All Walls have a standard texture 
  ITexture *texture;
public:
  Wall (ISceneManager* smgr,
	IVideoDriver* driver,
	int x, int y, playground pg);
  virtual bool reflects();
  virtual bool isWall(){ return true; }
  virtual void sphereEnter(Sphere &s);
  virtual void sphereExit(Sphere &s);

  virtual void handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime);
  virtual void timeProgress(f32 frameDeltaTime);

  virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap);
  virtual fieldtype getFieldType();
};

///////////////////////////////////////////////

// similarly the derived class Floor:

class Floor: public Field{
protected:
  ITexture *texture;
public:
  Floor(ISceneManager* smgr,
	IVideoDriver* driver,
	int x, int y, playground pg);
  virtual bool reflects();
  virtual bool isWall(){ return false; }
  virtual void sphereEnter(Sphere &s);
  virtual void sphereExit(Sphere &s);

  virtual void handleSphere(Sphere &s, position2di mousemove, f32 frameDeltaTime);

  virtual void timeProgress(f32 frameDeltaTime);

  virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap);
  virtual fieldtype getFieldType();

  virtual void alternateSphereProgress(position2di mousemove, f32 frameDeltaTime, f32 friction){};
};


#endif
