#pragma once
#include "Entity.h"

/*
represents any moving or rotating object on the map, deleted after it's movement
*/
class MovingEntity : public Entity
{
private:
	/*
	rotation angle of this object, in radians
	*/
	float angle;
public:
	/*
	return angle in radians
	*/
	float getAngle();
	/*
	overrides the virtual method, returns true
	*/
	bool isMovingEntity();
	/*
	changes the angle, if clockwise (parameter) is true, the angle is change to += angle (parameter), else -= angle (parameter), in radians
	*/
	void rotate(float angle, bool clockwise);
	/*
	changes the angle to the angle (parameter), in radians
	*/
	void rotateTo(float angle);
	/*
	constructor, if the angle is -1, it's calculated to point to the toX and toY coordinates (i.e. flying arrow)
	*/
	MovingEntity(std::string imageFile, float fromX, float fromY, float toX, float toY, float angle = -1);
};

