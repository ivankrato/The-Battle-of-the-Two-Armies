#pragma once
#include "Entity.h"

/*
represents any not moving object on the map
*/
class StaticEntity : public Entity
{
private:
	/*
	logic height of the entity
	*/
	int height;
	/*
	logic width of the entity
	*/
	int width;
public:
	/*
	overrides the virtual method, returns true
	*/
	bool isStaticEntity();
	/*
	returns logic width
	*/
	int getWidth();
	/*
	returns logic height
	*/
	int getHeight();
	/*
	constructor
	*/
	StaticEntity(std::string imageFile, int width = 1, int height = 1,  int x = 0, int y = 0, float bitmapX = 0, float bitmapY = 0);
};

