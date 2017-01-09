#pragma once
#include "Unit.h"
#include <iostream>

/*
represents melee unit, inherits from Unit
*/
class MeleeUnit : public Unit
{
public:
	/*
	overrides the virtual method, returns the attack damage, if the unit on the coordinates (parameter) is in melee range, 0 if fail
	*/
	int canAttackAt(int x, int y);
	/*
	overrides the virtual method, returns false
	*/
	bool isRanged();
	/*
	constructor
	*/
	MeleeUnit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int x = 0, int y = 0, float bitmapX = 0, float bitmapY = 0);
};

