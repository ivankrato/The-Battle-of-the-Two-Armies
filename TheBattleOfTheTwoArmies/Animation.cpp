#include "Animation.h"


bool Animation::hasNext()
{
	return nextAnimation != nullptr;
}

Animation *Animation::getNextAnimation()
{
	return nextAnimation;
}

Entity * Animation::getEntity()
{
	return entity;
}

void Animation::setNextAnimation(Animation * animation)
{
	nextAnimation = animation;
}

Animation::Animation(Entity *entity, int speed, int fps, Animation *nextAnimation)
{
	this->entity = entity;
	this->speed = speed;
	this->fps = fps;
	this->nextAnimation = nextAnimation;
	this->finished = false;
	this->step = 0;
	this->noOfSteps = 0;
}
