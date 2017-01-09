#pragma once
#include "Map.h"
#include "Entity.h"
#include "Settings.h"
#include "MeleeUnit.h"
#include "RangedUnit.h"
#include "Player.h"
#include <vector>

/*
game logic
*/
class Game
{
private:
	/*
	map object, contains entities
	*/
	Map *map;
	/*
	player, who is on the move
	*/
	Player *onMove;
	/*
	first player
	*/
	Player *firstPlayer;
	/*
	second player
	*/
	Player *secondPlayer;
	/*
	selected unit (on the move)
	*/
	Unit *selectedUnit;
	/*
	if true, the player will be change next tick
	*/
	bool changePlayer;
	/*
	if true, next unit will be selected next tick
	*/
	bool selectNextUnit;
	/*
	if true, players can't do anything
	*/
	bool paused;
public:
	/*
	loads settings from settings object
	*/
	void loadSettings(Settings *settings);
	/*
	returns the map object
	*/
	Map *getMap() const;
	/*
	if the (parameter) is 0, return player on move, else return first (1) or second (2) player
	*/
	Player *getPlayer(int player) const;
	/*
	returns selected unit (on move)
	*/
	Unit *getSelectedUnit();
	/*
	called every tick of the game
	*/
	void tick();
	/*
	returns vector of integers with a path, x and y are rotating (x, y, x, y, ...) or empty vector if cant move or none path found
	*/
	std::vector<int> moveSelectedUnit(int x, int y);
	/*
	selected unit attacks unit on coordinates (parameter), return true if the attack was successful
	*/
	bool attackUnitAt(int x, int y);
	/*
	heals selected unit, returns true if the heal was successful
	*/
	bool healSelectedUnit();
	/*
	pauses the game
	*/
	void pause();
	/*
	unpauses the game
	*/
	void unpause();
	/*
	returns true if the game is paused
	*/
	bool isPaused();
	/*
	returns true, if the selected unit can attack unit at coordinates (parameter)
	*/
	bool canSelectedUnitAttackAt(int x, int y);
	/*
	returns true, if the unit on coordinates (parameter) is an enemy
	*/
	bool isEnemyPlayer(int x, int y);
	/*
	returns true, if the unit on coordinates (parameter) is selected
	*/
	bool isSelectedUnit(int x, int y);
	/*
	returns true, if the unit on coordinates (parameter) is dead, also deletes that unit from memory
	*/
	bool die(int x, int y);
	/*
	returns true, if the box on coordinates (parameter) is available - selected unit can move there
	*/
	bool isBoxAvailable(int x, int y);
	/*
	returns true, if the game has ended
	*/
	bool isEnd();
	/*
	constructor with logic map width and logic map height
	*/
	Game(int mapWidth, int mapHeight);
	/*
	destructor, clears allocated memory
	*/
	~Game();
};

