#pragma once
#include "Unit.h"
#include <iostream>

/*
represents ranged Unit, inherits from Unit
*/
class RangedUnit : public Unit
{
	/*
	effective range, the unit can attack even further, but do less damage (based on attack)
	*/
	int efRange;
public:
	/*
	returns the attack damage of the attack, full damage if the unit is in effective range, else less, 0 if fail
	*/
	int canAttackAt(int x, int y);
	/*
	overrides the virtual method, returns true
	*/
	bool isRanged();
	/*
	constructor
	*/
	RangedUnit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int efRange, int x = 0, int y = 0, float bitmapX = 0, float bitmapY = 0);
};

