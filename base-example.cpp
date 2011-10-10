#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <matrix4.h>
#include <time.h>

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


int _RAND_SEED = 12313;
int rand_int(int lower, int higher) {
	srand(time(NULL) + _RAND_SEED++);
	int val = (rand() % higher) + lower;
	return val;

}

struct mapCell {
	int texture_id;
	bool isWall;
	bool isStone;
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

  const int dimx=20;   // the playground will have 20 x 13 fields
  const int dimy=13;
  const f32 fieldsize=8.f;  // each field is a square or a cube of side length 8 units 
  const f32 halffieldsize=fieldsize/2;
  const f32 spheresize = 2.f;  // sphere has radius 2 units

  const f32 offsetx=fieldsize*dimx/2; // offset of the playground's center from (0,0,0)
  const f32 offsety=fieldsize*dimy/2;

  const f32 minborderx = spheresize+fieldsize; // borders of the field (for collision detection)
  const f32 maxborderx = fieldsize*(dimx-1)-spheresize;
  const f32 minbordery = spheresize+fieldsize;  
  const f32 maxbordery = fieldsize*(dimy-1)-spheresize;
	

	// Loading a texture to put on the squares
	io::path texturepath="../enigma-1.01/data/gfx48/";
	video::ITexture* ballTextures[] = {
		driver->getTexture(texturepath + "fg-blackball.png"),
		driver->getTexture(texturepath + "fg-whiteball.png"),
	};
	int ballTextures_Length = sizeof(ballTextures) / sizeof(ballTextures[0]);
	video::ITexture* blockTextures[] = {
		driver->getTexture(texturepath + "expl.png"),
		driver->getTexture(texturepath + "fl-acwhite.png"),
		driver->getTexture(texturepath + "fl-black.png"),
		driver->getTexture(texturepath + "fl-darkgray.png"),
		driver->getTexture(texturepath + "fl-ice.png"),
		driver->getTexture(texturepath + "fl-inverse.png"),
		driver->getTexture(texturepath + "fl-lightgray.png"),
		driver->getTexture(texturepath + "fl-rock.png"),
		driver->getTexture(texturepath + "fl-rock2.png"),
	};
    int blockTextures_Length = sizeof(blockTextures) / sizeof(blockTextures[0]);

   	// Creating theMap
	mapCell theMap[dimx][dimy];
	mapCell curCell;
	for (int i = 0; i < dimx; ++i) {
		for (int j =0; j < dimy; ++j) {
			
			curCell.isWall = (i==0 || i==dimx-1 || j==0 || j==dimy-1);
			curCell.isStone = rand_int(0,1);
			if (curCell.isWall) {
				curCell.texture_id = 2;
			} else {
				curCell.texture_id = rand_int(0, blockTextures_Length);
			}
			theMap[i][j] = curCell;
		}
	}
	
  // drawing one block for each field
  for(int i=0; i<dimx; i++){
    for(int j=0; j<dimy; j++){
      scene::ISceneNode *block = smgr->addCubeSceneNode(fieldsize);

      // For starters, all inner stones of the playground are "floor", only the outermost stones
      // form a sourrounding wall. Thus the vertical position of each stone is determined by 
      // whether it is an outer stone or not. 
      f32 vpos = (theMap[i][j].isWall || theMap[i][j].isStone) ? fieldsize : 0.f;

      block->setPosition(core::vector3df(fieldsize*j+halffieldsize,vpos,fieldsize*i+halffieldsize));
      block->setMaterialTexture(0, blockTextures[theMap[i][j].texture_id]); // put the texture on
      block->setMaterialFlag(video::EMF_LIGHTING, false);
    }
  }


  // the sphere (in previous version called "node")
  scene::ISceneNode * sphere = smgr->addSphereSceneNode(spheresize,32);
  sphere->setPosition(core::vector3df(offsety,spheresize+fieldsize*.5f,offsetx));
  sphere->setMaterialFlag(video::EMF_LIGHTING, false);
  sphere->setMaterialTexture(0, ballTextures[rand_int(0, ballTextures_Length)]); // put a black texture on the sphere



  scene::ICameraSceneNode* camera=smgr->addCameraSceneNode(NULL,core::vector3df(offsety+50.f,100.f,offsetx),
							        core::vector3df(offsety,0.f,offsetx));
  // to change the camera position use: 
  //    camera->setPosition(core::vector3df(...));
  // see docmentation of  ICameraSceneNode  for more (like setting target, rotation, aspect)


  device->getCursorControl()->setVisible(false);
  
  u32 then = device->getTimer()->getTime();

  core::vector3df velocity(30.f,0.f,10.f);

  const f32 friction=.2f;

  // remember current mouse position
  core::position2di RefPosition=receiver.Position;

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
      velocity.X += mousemove.Y;
      velocity.Z += mousemove.X;
      // remember current mouse position
      RefPosition=receiver.Position;

      // Measure the time that has passed since last drawing 
      const u32 now = device->getTimer()->getTime();
      const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
      then = now;

      // friction
      velocity.X *=1-(friction*frameDeltaTime);
      velocity.Z *=1-(friction*frameDeltaTime);

      // detect collision with wall and change speed accordingly
      core::vector3df spherePosition = sphere->getPosition();
      if (velocity.X<0){
	if (spherePosition.X<minbordery){
	  velocity.X = -velocity.X;
	}
      }
      else{
	if (spherePosition.X>maxbordery){
	  velocity.X = -velocity.X;
	}
      }
      
      if (velocity.Z<0){
	if (spherePosition.Z<minborderx){
	  velocity.Z = -velocity.Z;
	}
      }
      else{
	if (spherePosition.Z>maxborderx){
	  velocity.Z = -velocity.Z;
	}
      }


      // Update position
      spherePosition.X += velocity.X*frameDeltaTime;
      spherePosition.Z += velocity.Z*frameDeltaTime;
      sphere->setPosition(spherePosition);
     
      // Draw the picture anew
      driver->beginScene(true, true, video::SColor(255,113,113,133));
      smgr->drawAll();
      driver->endScene();
    }
  device->drop();
  return 0;
}
















