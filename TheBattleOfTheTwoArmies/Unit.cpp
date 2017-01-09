#include "Unit.h"



void Unit::setNewAttack()
{
	int healthPercent = health / maxHealth;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<float> dist(healthPercent, 1.2);
	float p = dist(eng);
	p = p < 0.5 ? 0.5 : p;
	attack = maxAttack * p;
}

bool Unit::isUnit()
{
	return true;
}

int Unit::getAttack() const
{
	return attack;
}

int Unit::getHealth() const
{
	return health;
}

int Unit::getMaxHealth() const
{
	return maxHealth;
}

bool Unit::isDead()
{
	return health <= 0;
}

void Unit::wound(int no)
{
	int diff = health - no;
	if (diff < 0) {
		no += diff;
	}
	health -= no;
	setNewAttack();
}

bool Unit::heal()
{
	if (player->getUnits()->size() > 1) { //cannot heal if last unit
		std::mt19937 eng(time(0));
		std::uniform_int_distribution<int> dist(6, 14);
		int heal = dist(eng);
		int end = health + heal;
		if (end > maxHealth) {
			health = maxHealth;
		}
		else {
			health += heal;
		}
		setNewAttack();
		return true;
	}
	return false;
}

bool Unit::attackUnit(Unit * unit)
{
	int attack = canAttackAt(unit->getX(), unit->getY());
	if (attack > 0) {
		unit->wound(attack);
		return true;
	}
	return false;
}

Player * Unit::getPlayer() const
{
	return player;
}

int Unit::getSpeed() const
{
	return speed;
}

std::string Unit::getAttackBitmapFile()
{
	return attackBitmapFile;
}

Unit::Unit(int attack, int maxHealth, Player *player, std::string imageFile, int speed, std::string attackBitmapFile, int x, int y, float bitmapX, float bitmapY) : Entity(imageFile, x, y, bitmapX, bitmapY)
{
	this->maxAttack = attack;
	this->maxHealth = maxHealth;
	this->health = maxHealth;
	this->player = player;
	this->speed = speed;
	this->player->addUnit(this);
	this->attackBitmapFile = attackBitmapFile;
	setNewAttack();
}
