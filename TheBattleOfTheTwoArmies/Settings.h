#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Player.h"
#include "Entity.h"
#include "MeleeUnit.h"
#include "RangedUnit.h"
#include "StaticEntity.h"
#include <algorithm>

/*
represents game settings, parsed from file
*/
struct Settings
{
	/*
	display width
	*/
	int displayWidth;
	/*
	display height
	*/
	int displayHeight;
	/*
	maximal frames pre second
	*/
	int fps;
	/*
	first player object
	*/
	Player *firstPlayer;
	/*
	second player object
	*/
	Player *secondPlayer;
	/*
	logic map width
	*/
	int mapWidth;
	/*
	logic map height
	*/
	int mapHeight;
	/*
	respresents settings of an unit, it is used later in the settings file
	*/
	struct UnitSettings {
		int attack;
		int hp;
		std::string bitmap;
		int speed;
		std::string attackBitmap;
		int efRange;
	};
	/*
	respresents settings of a static entity, it is used later in the settings file
	*/
	struct EntitySettings {
		std::string bitmap;
		int width;
		int height;
	};
	/*
	map, key is the name of the unit settings, value is the unit settings object
	*/
	std::map<std::string, UnitSettings> unitSettings;
	/*
	map, key is the name of the static entity settings, value is the static entity settings object
	*/
	std::map<std::string, EntitySettings> entitySettings;
	/*
	vector of all entities on the map
	*/
	std::vector<Entity*> *entities;

	/*
	parse the settings from file (parameter)
	*/
	void load(std::string file);
	/*
	constructor
	*/
	Settings();
};

