#pragma once
#include "Entity.h"
#include <random>

/*
represents player's unit, inherits from Entity
*/
class Unit : public Entity
{
protected:
	/*
	current attack
	*/
	int attack;
	/*
	maximal attack
	*/
	int maxAttack;
	/*
	current health
	*/
	int health;
	/*
	maximal health
	*/
	int maxHealth;
	/*
	the longest path the unit can go
	*/
	int speed;
	/*
	player the unit belongs to
	*/
	Player *player;
	/*
	image file of the attack (shot or melee weapon)
	*/
	std::string attackBitmapFile;

	/*
	sets the new attack, it's based on randomness (Mersenne twister engine) and on current health percentage
	*/
	void setNewAttack();
public:
	/*
	overrides the virtual method, returns true
	*/
	bool isUnit();
	/*
	returns current attack
	*/
	int getAttack() const;
	/*
	returns current health
	*/
	int getHealth() const;
	/*
	returns maximal health
	*/
	int getMaxHealth() const;
	/*
	returns true if the unit's health is <= 0
	*/
	bool isDead();
	/*
	virtual method, must be overridden, shoudl return true, if the child is ranged
	*/
	virtual bool isRanged() = 0;
	/*
	wound the unit, substracts number (parameter) from health, health can't be < 0
	*/
	void wound(int no);
	/*
	heals the unit somewhere from +6 to +12, adds to health, return true, if the heal was successful (healed unit is not the last player's unit)
	*/
	bool heal();
	/*
	virtual method, must be overridden, shoud return the attack damage if the unit on the coordinates (parameter) is attackable (in range), 0 if fail
	*/
	virtual int canAttackAt(int x, int y) = 0;
	/*
	attacks the unit in (parameter)
	*/
	virtual bool attackUnit(Unit *unit);
	/*
	returns the player this unit belongs to
	*/
	Player *getPlayer() const;
	/*
	returns the speed (walk range) of the unit
	*/
	int getSpeed() const;
	/*
	returns the name of the image file
	*/
	std::string getAttackBitmapFile();
	/*
	constructor
	*/
	Unit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int x = 0, int y = 0, float bitmapX = 0, float bitmapY = 0);
};

