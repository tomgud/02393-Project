#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <matrix4.h>
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

using namespace irr;
using namespace std;

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
  video::E_DRIVER_TYPE driverType=video::EDT_OPENGL; 
  if (driverType==video::EDT_COUNT) return 1;
  MyEventReceiver receiver;  
  IrrlichtDevice* device = createDevice(driverType,
					core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
  if (device == 0) return 1; 
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();

  scene::ISceneNode * node = smgr->addSphereSceneNode(2.f,32);
  if (node)
    {
      node->setPosition(core::vector3df(0,5.f,0));
      node->setMaterialFlag(video::EMF_LIGHTING
      			    , false);
    }

  for(f32 i=-64.f; i<=64.f; i+=2.f){
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(-64.f,5.f,i));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(64.f,5.f,i));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(i,5.f,-64.f));
    smgr->addCubeSceneNode(2.f)->setPosition(core::vector3df(i,5.f,64.f));
  }
  const f32 minborder = -58.f;  
  const f32 maxborder = 58.f;

  smgr->addCameraSceneNode(NULL,core::vector3df(0.f,100.f,0.f),core::vector3df(0.f,0.f,0.f));
  //  smgr->addCameraSceneNodeFPS();

  device->getCursorControl()->setVisible(false);
  
  u32 then = device->getTimer()->getTime();

  int movex=1;
  int movey=1;
  int pause=1;
  core::vector3df velocity(30.f,0.f,10.f);


  f32 friction=.2f;

  // remember current mouse position
  core::position2di RefPosition=receiver.Position;

  while(device->run())
    {
      /*
      if(receiver.IsKeyDown(irr::KEY_KEY_Q)) exit(0);
      if(receiver.IsKeyDown(irr::KEY_KEY_Z)){
	movey=1;
	movex=0;
      }
      if(receiver.IsKeyDown(irr::KEY_KEY_X)){
	movey=0;
	movex=1;
      }
      */

      // Adapt speed by the difference in mouse position
      velocity.X -= (receiver.Position.Y-RefPosition.Y);
      velocity.Z -= (receiver.Position.X-RefPosition.X);
      // remember current mouse position
      RefPosition=receiver.Position;

      // Measure the time that has passed since last drawing 
      const u32 now = device->getTimer()->getTime();
      const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
      then = now;

      // detect collision with wall and change speed accordingly
      core::vector3df nodePosition = node->getPosition();
      if (velocity.X<0){
	if (nodePosition.X<minborder){
	  velocity.X = -velocity.X;
	}
      }
      else{
	if (nodePosition.X>maxborder){
	  velocity.X = -velocity.X;
	}
      }
      
      if (velocity.Z<0){
	if (nodePosition.Z<minborder){
	  velocity.Z = -velocity.Z;
	}
      }
      else{
	if (nodePosition.Z>maxborder){
	  velocity.Z = -velocity.Z;
	}
      }


      // Update position
      nodePosition.X += velocity.X*frameDeltaTime;
      nodePosition.Z += velocity.Z*frameDeltaTime;
      node->setPosition(nodePosition);
     
      // Draw the picture anew
      driver->beginScene(true, true, video::SColor(255,113,113,133));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
  return 0;
}
















