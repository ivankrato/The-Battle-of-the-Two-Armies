#pragma once
#include <string>
#include "allegro5\allegro.h"
#include "Player.h"

/*
represents any object on the map
*/
class Entity
{
protected:
	/*
	name of the image file
	*/
	std::string imageFile;
	/*
	allegro bitmapy, based on the image
	*/
	ALLEGRO_BITMAP *bitmap;
	/*
	bitmap X coordinate
	*/
	float bitmapX;
	/*
	bitmap Y coordinate
	*/
	float bitmapY;
	/*
	logic X coordinate
	*/
	int x;
	/*
	logic Y coordinate
	*/
	int y;
	/*
	if the graphics should be flipped from right to left
	*/
	bool flip;
public:
	/*
	return the bitmap
	*/
	ALLEGRO_BITMAP *getBitmap();
	/*
	returns bitmap X coordinate
	*/
	float getBitmapX() const;
	/*
	returns bitmap Y coordinate
	*/
	float getBitmapY() const;
	/*
	returns logic X coordinate
	*/
	int getX() const;
	/*
	returns logic X coordinate
	*/
	int getY() const;
	/*
	returns height of the bitmap
	*/
	virtual int getHeight();
	/*
	returns width of the bitmap
	*/
	virtual int getWidth();
	/*
	returns true, if the entity is Unit, virtual
	*/
	virtual bool isUnit();
	/*
	return true, if the entity is StaticEntity
	*/
	virtual bool isStaticEntity();
	/*
	returns true, if the entity is MovingEntity
	*/
	virtual bool isMovingEntity();
	/*
	sets to flip variable to true
	*/
	void flipLeft();
	/*
	sets to flip variable to false
	*/
	void flipRight();
	/*
	return the flip variable
	*/
	bool isFlippedLeft();
	/*
	changes the bitmap coordinates to (parameter)
	*/
	void moveBitmapTo(float x, float y);
	/*
	changes the logic coordinates to (parameter)
	*/
	void moveTo(int x, int y);
	/*
	constructor
	*/
	Entity(std::string imageFile, int x = 0, int y = 0, float bitmapX = 0, float bitmapY = 0, bool flip = false);
	/*
	destructor, clears allocated memory
	*/
	~Entity();
};

