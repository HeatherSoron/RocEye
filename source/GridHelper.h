//this file provides utilities that help with grid calculations
//e.g., rounding things to the grid cell size

#ifndef GRID_HELPER_H
#define GRID_HELPER_H

#include <Ogre.h>

class GridHelper
{
public:
	static Ogre::Vector3 roundToGrid(const Ogre::Vector3 vec);
	static Ogre::Real roundToGrid(const Ogre::Real num);
	
	static const int GRID_SIZE = 50;
};

#endif
