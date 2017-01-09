#pragma once
#include "Entity.h"
#include "Animation.h"

/*
represents animation of moving entity
*/
class MoveAnimation : public Animation
{
private:
	/*
	bitmap X coordinate where to move
	*/
	float toX;
	/*
	bitmap Y coordinate where to move
	*/
	float toY;
	/*
	step size on the X axis
	*/
	float stepSizeX;
	/*
	step size on the Y axis
	*/
	float stepSizeY;
	/*
	initializes the animation's variables, we need to initialize the animation before it starts, not on construction
	*/
	void init();
public:
	/*
	one tick of the animation
	*/
	bool tick();
	/*
	constructor, speed (parameter) is in pixels per second
	*/
	MoveAnimation(Entity *entity, float toX, float toY, int speed, int fps, MoveAnimation *nextAnimation = nullptr);
};

