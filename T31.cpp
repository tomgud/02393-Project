// Skeleton of implementation file for groups

#include "game.h"
#include "field.h"
#include "T31.h"

//////////////////////////////
// PulseField. 
// Authors: 
// Tomas Gudmundsson
// Elvar Orn Unnthorsson
//////////////////////////////
T31::T31(ISceneManager* smgr, IVideoDriver* driver, int x, int y, playground pg) : Wall(smgr,driver,x,y,pg)
{
	cerr << "Creating a T31 field" << endl;

};

fieldtype T31::getFieldType(){ 
  return tT31; 
}