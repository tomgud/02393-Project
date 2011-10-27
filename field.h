#ifndef ___FIELD_H
#define  ___FIELD_H


#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
using namespace irr;
using namespace std;
using core::vector3df;
#include "game.h"

typedef enum fieldtype { 
  tWall, tFloor, tLightFloor 
  // all the types of fields that are defined in the game 
  // (except Field itself which is purely virtual)
};


class Field
{
	protected:
		scene::ISceneManager* smgr;
		video::IVideoDriver* driver; 
		int x,y; // field on the map
		scene::ISceneNode * block;
	  	vector3df position;
	public:
		Field(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y);
		virtual int getx();
		virtual int gety();
		virtual bool reflects()=0; 
		virtual void sphereEnter(Sphere &s)=0;
		virtual void sphereExit(Sphere &s)=0;
		virtual void handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime)=0;
		virtual void timeProgress(f32 frameDeltaTime)=0;
		virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap)=0;
		virtual fieldtype getFieldType()=0;
};


core::vector3df cubePosition(int x, int y, bool isWall);
#define stdfriction .2f


class Wall : public Field
{
	protected:
		video::ITexture *texture;
	public:
		Wall (scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y);
		virtual bool reflects();
		virtual void sphereEnter(Sphere &s);
		virtual void sphereExit(Sphere &s);
		virtual void handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime);
		virtual void timeProgress(f32 frameDeltaTime);
		virtual void sphereOverlap(Sphere &s, f32 xoverlap, f32 yoverlap);
		virtual fieldtype getFieldType();
};


class LightFloor: public Wall
{
	protected:
		video::ITexture *alt_texture;
		f32 timeSpentHere;
	public:
		LightFloor(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y) ;
		virtual void sphereEnter(Sphere &s);
		virtual void sphereExit(Sphere &s);
		virtual void handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime);
		virtual fieldtype getFieldType();
};


class PulseWall: public Wall
{
	protected:
	  video::ITexture *texture;
	
	public:
		PulseWall(scene::ISceneManager* smgr,video::IVideoDriver* driver, int x, int y);
};


class LightFloor: public Floor
{
	protected:
		video::ITexture *alt_texture;
		f32 timeSpentHere;
	public:
		LightFloor(scene::ISceneManager* smgr, video::IVideoDriver* driver, int x, int y);
		virtual void sphereEnter(Sphere &s);
		virtual void sphereExit(Sphere &s);
		virtual void handleSphere(Sphere &s, core::position2di mousemove, f32 frameDeltaTime);
		virtual fieldtype getFieldType();
};


class 
#endif
