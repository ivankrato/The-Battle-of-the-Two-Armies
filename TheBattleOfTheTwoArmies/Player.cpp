#include "Player.h"
#include <iostream>



void Player::addUnit(Unit * unit)
{
	units->push_back(unit);
}

void Player::removeUnit(Unit * unit)
{
	std::vector<Unit *>::iterator it = std::find(units->begin(), units->end(), unit);
	units->erase(it);
}

bool Player::isMyUnit(Unit *unit)
{
	for (Unit *u : *units) {
		if (u == unit) {
			return true;
		}
	}
	return false;
}

std::string Player::getName()
{
	return name;
}

ALLEGRO_COLOR Player::getColor()
{
	return al_map_rgba(colorRed, colorGreen, colorBlue, 100);
}

std::vector<Unit*>* Player::getUnits()
{
	return units;
}

Unit * Player::selectNextUnit()
{
	lastSelectedUnitIndex++;
	lastSelectedUnitIndex %= units->size();
	return (*units)[lastSelectedUnitIndex];
}

Player::Player(std::string name, char colorRed, char colorGreen, char colorBlue)
{
	this->units = new std::vector<Unit*>();
	this->name = name;
	this->colorRed = colorRed;
	this->colorGreen = colorGreen;
	this->colorBlue = colorBlue;
	this->lastSelectedUnitIndex = -1;
}

Player::~Player()
{
	delete units;
}
