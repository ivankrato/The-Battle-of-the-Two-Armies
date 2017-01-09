#include "RotateAnimation.h"



void RotateAnimation::init()
{
	float fromAngle = mentity->getAngle();
	float diff = abs(toAngle - fromAngle);
	noOfSteps = (diff * 1000 * fps) / speed;
	stepSize = diff / float(noOfSteps);
}

bool RotateAnimation::tick()
{
	//reset at start (for next animations), the start point can be different
	if (step == 0) {
		init();
	}
	mentity->rotate(stepSize, clockwise);
	step++;
	finished = step == noOfSteps;
	if (finished) {
		mentity->rotateTo(toAngle);
	}
	return finished;
}

RotateAnimation::RotateAnimation(MovingEntity *entity, float toAngle, bool likeClock, int speed, int fps) : Animation(entity, speed, fps)
{
	this->mentity = entity;
	this->toAngle = toAngle;
	this->clockwise = likeClock;
}