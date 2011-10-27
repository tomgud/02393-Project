#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
using namespace irr;
using namespace std;
using core::vector3df;

#include "field.h"
#include "game.h"

class MyEventReceiver : public IEventReceiver
{
public:
  core::position2di Position;
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
	switch(event.MouseInput.Event)
	  {
	  case EMIE_MOUSE_MOVED:
	    Position.X = event.MouseInput.X;
	    Position.Y = event.MouseInput.Y;
	    break;
	    
	  default:
	    break;
	  }
      }    
    return false;
  }
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  MyEventReceiver()
  {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  } 
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


int main()
{
  // Initialization of Device, Video Driver and Scene Manager
  video::E_DRIVER_TYPE driverType=video::EDT_OPENGL; 
  MyEventReceiver receiver;  
  IrrlichtDevice* device = createDevice(driverType,
					core::dimension2d<u32>(960, 720), 16, false, false, false, &receiver);
  if (device == 0) return 1; 
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  // Building the scene.


  // open level file
  ifstream infile;
  infile.open("base-example.app/Contents/Resources/field.lvl");
  if (infile.fail()) { cerr << "Could not open level file\n"; return -1; }
  string line;
  infile >> line;
  if (line!="Enigma-3D") { cerr << "Illegal Level file" << line << "\n"; return -1; } 

  Field* playground[dimx][dimy];

  // drawing one block for each field
  for(int j=0; j<dimy; j++){
    for(int i=0; i<dimx; i++){
      // determine filed type
      int fieldtype;
      infile >> fieldtype;
      switch(fieldtype){
      case 0: 
	playground[i][j]=new LightFloor(smgr,driver,i,j);
	break;
      case 1:
	playground[i][j]=new Wall(smgr,driver,i,j);
	break;
      default:
	cerr << "Illegal field type in level file: " << fieldtype << endl;
	return -1;
      }
      //      playground[i][j]=new Field(smgr,driver,i,j,texture[fieldtype],fieldtype>0);
    } 
  }
  infile.close();

  Sphere *sphere=new Sphere(smgr,driver);

  scene::ICameraSceneNode* camera=smgr->addCameraSceneNode(NULL,core::vector3df(offsety+50.f,100.f,offsetx),
							        core::vector3df(offsety,0.f,offsetx));
  // to change the camera position use: 
  //    camera->setPosition(core::vector3df(...));
  // see docmentation of  ICameraSceneNode  for more (like setting target, rotation, aspect)


  device->getCursorControl()->setVisible(false);
  
  u32 then = device->getTimer()->getTime();


  // remember current mouse position
  core::position2di RefPosition=receiver.Position;

  int fieldx=getFieldx(sphere->getPosition());
  int fieldy=getFieldy(sphere->getPosition());

  playground[fieldx][fieldy]->sphereEnter(*sphere);

  while(device->run())
    {
      if(receiver.IsKeyDown(irr::KEY_KEY_Q)) exit(0); // quit game on key Q
      
      // Adapt speed by the difference in mouse position
      core::position2di mousemove;
      mousemove.X=(receiver.Position.X-RefPosition.X);
      mousemove.Y=(receiver.Position.Y-RefPosition.Y);
      // eliminating too rapid movements of the mouse
      if (fabs(mousemove.X)>10) mousemove.X=0;
      if (fabs(mousemove.Y)>10) mousemove.Y=0;
      // remember current mouse position
      RefPosition=receiver.Position;

      // Measure the time that has passed since last drawing 
      const u32 now = device->getTimer()->getTime();
      const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
      then = now;

      // Let the current field handle the time difference; this may change position and velocity      // of the sphere
      playground[fieldx][fieldy]->handleSphere(*sphere,mousemove,frameDeltaTime);
      // all other fields get told that time has passed:
      for(int j=0; j<dimy; j++)
	for(int i=0; i<dimx; i++)
	  if (i!=fieldx && j!=fieldy) 
	    playground[i][j]->timeProgress(frameDeltaTime);

      // detect collision with wall and change speed accordingly
      core::vector3df spherePosition = sphere->getPosition();

      int new_fieldx=getFieldx(spherePosition);
      int new_fieldy=getFieldy(spherePosition);

      f32 xoE=getOverlapx(spherePosition,new_fieldx+1);
      f32 xoW=getOverlapx(spherePosition,new_fieldx-1);
      f32 yoN=getOverlapy(spherePosition,new_fieldy+1);
      f32 yoS=getOverlapy(spherePosition,new_fieldy-1);
      
      if (xoE) playground[new_fieldx+1][new_fieldy]->sphereOverlap(*sphere,xoE,0.f);
      if (xoW) playground[new_fieldx-1][new_fieldy]->sphereOverlap(*sphere,xoW,0.f);
      if (yoN) playground[new_fieldx][new_fieldy+1]->sphereOverlap(*sphere,0.f,yoN);
      if (yoS) playground[new_fieldx][new_fieldy-1]->sphereOverlap(*sphere,0.f,yoS);
      
      /*
      if (spherePosition==sphere->getPosition()){ 
	// there was no collision with E,W,N, or S, check for overlaps with diagonal fields
	if (xoE && yoN) playground[new_fieldx+1][new_fieldy+1]->sphereOverlap(*sphere,xoE/4,yoN/4);
	if (xoE && yoS) playground[new_fieldx+1][new_fieldy-1]->sphereOverlap(*sphere,xoE/4,yoS/4);
	if (xoW && yoN) playground[new_fieldx-1][new_fieldy+1]->sphereOverlap(*sphere,xoW/4,yoN/4);
	if (xoW && yoS) playground[new_fieldx-1][new_fieldy-1]->sphereOverlap(*sphere,xoW/4,yoS/4);
	}*/

      if (new_fieldx!=fieldx || new_fieldy!=fieldy){
	// changed field
	playground[fieldx][fieldy]->sphereExit(*sphere);
	fieldx=new_fieldx;
	fieldy=new_fieldy;
	playground[fieldx][fieldy]->sphereEnter(*sphere);
      }

      // Draw the picture anew
      driver->beginScene(true, true, video::SColor(255,113,113,133));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
  return 0;
}
















