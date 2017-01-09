#include "StaticEntity.h"



StaticEntity::StaticEntity(std::string imageFile, int width, int height, int x, int y, float bitmapX, float bitmapY) : Entity(imageFile, x, y, bitmapX, bitmapY)
{
	this->width = width;
	this->height = height;
}


bool StaticEntity::isStaticEntity()
{
	return true;
}

int StaticEntity::getWidth()
{
	return width;
}

int StaticEntity::getHeight()
{
	return height;
}
