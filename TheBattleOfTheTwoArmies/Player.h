#pragma once
#include <string>
#include <vector>
#include <allegro5\allegro.h>

/*
to prevent circular dependencies
*/
class Unit;

/*
respresents one player
*/
class Player
{
private:
	/*
	name
	*/
	std::string name;
	/*
	player's units
	*/
	std::vector<Unit*> *units;
	/*
	players color, red part (0-255)
	*/
	char colorRed;
	/*
	players color, green part (0-255)
	*/
	char colorGreen;
	/*
	players color, blue part (0-255)
	*/
	char colorBlue;
	/*
	index of last selected unit (which was on move)
	*/
	int lastSelectedUnitIndex;
public:
	/*
	adds unit to this player
	*/
	void addUnit(Unit *unit);
	/*
	remove unit from this player
	*/
	void removeUnit(Unit *unit);
	/*
	return true, if the unit belongs to this player
	*/
	bool isMyUnit(Unit *unit);
	/*
	returns the name
	*/
	std::string getName();
	/*
	returns the allegro color of this player
	*/
	ALLEGRO_COLOR getColor();
	/*
	returns the vector of player's units
	*/
	std::vector<Unit*> *getUnits();
	/*
	returns the next unit which should be selected and increment lastSelectedUnitIndex by 1
	*/
	Unit *selectNextUnit();
	/*
	constructor
	*/
	Player(std::string name, char red = 0, char green = 0, char blue = 0);
	~Player();
};

