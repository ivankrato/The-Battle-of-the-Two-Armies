#include "RangedUnit.h"



int RangedUnit::canAttackAt(int x, int y)
{
	int diffX = abs(this->getX() - x);
	int diffY = abs(this->getY() - y);
	int range = sqrt(diffX*diffX + diffY*diffY);
	int diff = range - efRange;
	if (diff <= 0) { //successful attack
		return attack;
	}
	else if (diff > 0) { //long attack
		int wound = attack - 3 * diff;
		if (wound <= 0) {
			return 0;
		}
		else {
			return wound;
		}
	}
	else { //too long, miss
		return 0;
	}
}

bool RangedUnit::isRanged()
{
	return true;
}

RangedUnit::RangedUnit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int efRange, int x, int y, float bitmapX, float bitmapY) : Unit(attack, maxHealth, player, imageFile, speed, attackBitmapFile, x, y, bitmapX, bitmapY)
{
	this->efRange = efRange;
}
