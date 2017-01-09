#pragma once
#include "Entity.h"

/*
animation interface
*/
class Animation
{
protected:
	/*
	number of steps neede to complete this animation
	*/
	int noOfSteps;
	/*
	number of current step the animation is on
	*/
	int step;
	/*
	speed of one animation, depends on the type
	*/
	int speed;
	/*
	max fps the game runs in
	*/
	int fps;
	/*
	entity to animate
	*/
	Entity *entity;
	bool finished;
	/*
	next animation to run after this
	*/
	Animation *nextAnimation;

	/*
	initializes the animation's variables, we need to initialize the animation before it starts, not on construction
	*/
	void virtual init() = 0;
public:
	/*
	one tick of the animation
	*/
	bool virtual tick() = 0;
	/*
	true, if there is a next animation
	*/
	bool hasNext();
	/*
	returns the next animation, nullptr on fail
	*/
	Animation *getNextAnimation();
	/*
	returns the entity in this animation
	*/
	Entity* getEntity();
	/*
	sets the next animation
	*/
	void setNextAnimation(Animation *animation);
	/*
	constructor
	*/
	Animation(Entity *entity, int speed, int fps, Animation *nextAnimation = nullptr);
};

