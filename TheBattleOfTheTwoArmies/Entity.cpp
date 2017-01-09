#include "Entity.h"
#include <iostream>


float Entity::getBitmapX() const
{
	return bitmapX;
}

float Entity::getBitmapY() const
{
	return bitmapY;
}

int Entity::getX() const
{
	return x;
}

int Entity::getY() const
{
	return y;
}

int Entity::getHeight()
{
	return 1;
}

int Entity::getWidth()
{
	return 1;
}

bool Entity::isUnit()
{
	return false;
}

bool Entity::isStaticEntity()
{
	return false;
}

bool Entity::isMovingEntity()
{
	return false;
}

void Entity::flipLeft()
{
	flip = true;
}

void Entity::flipRight()
{
	flip = false;
}

bool Entity::isFlippedLeft()
{
	return flip;
}

void Entity::moveBitmapTo(float x, float y)
{
	this->bitmapX = x;
	this->bitmapY = y;
}

void Entity::moveTo(int x, int y)
{
	this->x = x;
	this->y = y;
}

ALLEGRO_BITMAP *Entity::getBitmap()
{
	return bitmap;
}

Entity::Entity(std::string imageFile, int x, int y, float bitmapX, float bitmapY, bool flip)
{
	this->imageFile = imageFile;
	this->bitmap = al_load_bitmap(this->imageFile.c_str());
	this->x = x;
	this->y = y;
	this->bitmapX = bitmapX;
	this->bitmapY = bitmapY;
	this->flip = flip;
}


Entity::~Entity()
{
	al_destroy_bitmap(bitmap);
}
