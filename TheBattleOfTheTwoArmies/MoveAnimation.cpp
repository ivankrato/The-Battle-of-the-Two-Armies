#include "MoveAnimation.h"

void MoveAnimation::init()
{
	float fromX = entity->getBitmapX();
	float fromY = entity->getBitmapY();
	float distance = sqrt((toX - fromX)*(toX - fromX) + (toY - fromY)*(toY - fromY));
	this->noOfSteps = (distance * fps) / speed;
	this->stepSizeX = (toX - fromX) / float(noOfSteps);
	this->stepSizeY = (toY - fromY) / float(noOfSteps);
}

bool MoveAnimation::tick()
{
	//reset at start (for next animations), the start point can be different
	if (step == 0) {
		init();
	}
	float x = entity->getBitmapX() + stepSizeX;
	float y = entity->getBitmapY() + stepSizeY;
	entity->moveBitmapTo(x, y);
	step++;
	finished = step == noOfSteps;
	if (finished) {
		entity->moveBitmapTo(toX, toY);
	}
	return finished;
}

MoveAnimation::MoveAnimation(Entity * entity, float toX, float toY, int speed, int fps, MoveAnimation *nextAnimation) : Animation(entity, speed, fps, nextAnimation)
{
	this->toX = toX;
	this->toY = toY;
	float distance = 0;
	this->stepSizeX = 0;
	this->stepSizeY = 0;
}
