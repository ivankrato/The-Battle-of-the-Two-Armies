#include "MovingEntity.h"



float MovingEntity::getAngle()
{
	return angle;
}

bool MovingEntity::isMovingEntity()
{
	return true;
}

void MovingEntity::rotate(float angle, bool clockwise)
{
	if (clockwise) {
		this->angle += angle;
	}
	else {
		this->angle -= angle;
	}
}

void MovingEntity::rotateTo(float angle)
{
	this->angle = angle;
}

MovingEntity::MovingEntity(std::string imageFile, float fromX, float fromY, float toX, float toY, float angle) : Entity(imageFile, 0, 0, fromX, fromY)
{
	if (angle == -1) { //angle calculation, some trigonometry here
		struct vector {
			float x;
			float y;

			vector(float x, float y) {
				this->x = x;
				this->y = y;
			}
		} v(toX - fromX, toY - fromY);
		angle = acos(v.x / sqrt(v.x*v.x + v.y*v.y));
		if (v.y < 0) {
			angle = 0 - angle;
		}
	}
	this->angle = angle;
}