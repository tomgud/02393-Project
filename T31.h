// note that your header files must be protected against multiple inclusion using the definition of a special identifier
// note that you also need the #endif at the end of the file
 
#ifndef ____T31____
#define ____T31____

#include "game.h"
#include "field.h"

class T31: public Wall // if you implement a Floor tile, replace "Wall" with "Floor"
{
public:
  T31(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground  pg);
  virtual fieldtype getFieldType();
  // you need to declare here all (virtual) functions that change with respect to parent class
  // see example in testfield.h and testfield.cpp
};


#endif
