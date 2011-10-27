#ifndef ___PULSE__FIELD_H
#define ___PULSE__FIELD_H

#include <irrlicht.h>
#include "driverChoice.h"
#include <iostream>
#include <fstream>
#include <matrix4.h>
#include "field.h"

using namespace irr;
using namespace std;
using core::vector3df;

class PulseField : public Floor {
	protected:
		f32 timeActive = 1.5;
}
#endif