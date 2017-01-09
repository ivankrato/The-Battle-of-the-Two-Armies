#include "MeleeUnit.h"



int MeleeUnit::canAttackAt(int x, int y)
{
	int diffX = abs(this->getX() - x);
	int diffY = abs(this->getY() - y);
	if (diffY <= 1 && diffX <= 1) {
		return attack;
	}
	return 0;
}

bool MeleeUnit::isRanged()
{
	return false;
}

MeleeUnit::MeleeUnit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int x, int y, float bitmapX, float bitmapY) : Unit(attack, maxHealth, player, imageFile, speed, attackBitmapFile, x, y, bitmapX, bitmapY)
{
}
