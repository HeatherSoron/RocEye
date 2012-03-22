#include "GridHelper.h"

Ogre::Vector3 GridHelper::roundToGrid(const Ogre::Vector3 vec)
{
	return Ogre::Vector3(roundToGrid(vec.x), roundToGrid(vec.y), roundToGrid(vec.z));
}

Ogre::Real GridHelper::roundToGrid(const Ogre::Real num)
{
	int roundedNum = static_cast<int>(num / GRID_SIZE) * GRID_SIZE;
	if (num >= 0 && num - roundedNum >= GRID_SIZE / 2)
	{
		roundedNum += GRID_SIZE;
	}
	else if (num <= 0 && roundedNum - num >= GRID_SIZE / 2)
	{
		roundedNum -= GRID_SIZE;
	}
	return roundedNum;
}
