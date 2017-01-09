#pragma once
#include "Animation.h"
#include "MovingEntity.h"

/*
represents animation of rotating entity
*/
class RotateAnimation : public Animation
{
private:
	/*
	entity of this animations, casted to MovingEntity type
	*/
	MovingEntity *mentity;
	/*
	angle to rotate to
	*/
	float toAngle;
	/*
	true if the rotation is clockwise
	*/
	bool clockwise;
	/*
	size of on step, in radians
	*/
	float stepSize;
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
	constructor, speed is in milliseconds needed to do full rotation, angle is in radians
	*/
	RotateAnimation(MovingEntity *entity, float toAngle, bool clockwise, int speed, int fps);
};

