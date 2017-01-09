#include "Game.h"

void Game::loadSettings(Settings *settings)
{
	firstPlayer = settings->firstPlayer;
	secondPlayer = settings->secondPlayer;
	std::vector<Entity *> *entities = settings->entities;
	onMove = firstPlayer;
	for (auto it = entities->begin(); it != entities->end();) {
		if ((*it)->isUnit()) { //add units
			Unit *u = (Unit*)(*it);
			if (!map->addUnit(u)) {
				it = entities->erase(it);
				delete u;
				continue;
			}
		}
		else if ((*it)->isStaticEntity()) { //add static entities
			StaticEntity *se = (StaticEntity*)(*it);
			if (!map->addStaticEntity(se)) {
				it = entities->erase(it);
				delete se;
				continue;
			}
		}
		++it;
	}
}

Map *Game::getMap() const
{
	return map;
}

Player * Game::getPlayer(int player) const
{
	if (player == 0) {
		return onMove;
	}
	else if (player == 1) {
		return firstPlayer;
	}
	else if (player == 2) {
		return secondPlayer;
	}
	return nullptr;
}

Unit * Game::getSelectedUnit()
{
	if (selectedUnit == NULL) {
		this->selectedUnit = onMove->selectNextUnit();
	}
	return selectedUnit;
}

void Game::tick()
{
	if (!paused && !isEnd()) {
		if (changePlayer) {
			changePlayer = false;
			onMove = onMove == firstPlayer ? secondPlayer : firstPlayer;
		}
		if (selectNextUnit) {
			selectNextUnit = false;
			this->selectedUnit = onMove->selectNextUnit();
		}
	}
}


std::vector<int> Game::moveSelectedUnit(int x, int y)
{
	std::vector<int> path;
	if (!paused && !isEnd()) {
		if (map->isEmpty(x, y)) {
			path = map->getPathFromTo(selectedUnit->getX(), selectedUnit->getY(), x, y);
			if ((int)path.size() / 2 <= selectedUnit->getSpeed() && !path.empty()) {
				map->moveUnit(x, y, selectedUnit);
				changePlayer = true;
				selectNextUnit = true;
			}
			else {
				path.clear();
			}
		}
	}
	return path;
}

bool Game::attackUnitAt(int x, int y)
{
	if (!paused && !isEnd()) {
		Unit *unit = (Unit*)map->getMapArray()[x][y];
		if (selectedUnit->attackUnit(unit)) {
			changePlayer = true;
			selectNextUnit = true;
			return true;
		}
	}
	return false;
}

bool Game::healSelectedUnit()
{
	if (!paused && !isEnd() && selectedUnit->heal()) {
		changePlayer = true;
		selectNextUnit = true;
		return true;
	}
	return false;
}

void Game::pause()
{
	paused = true;
}

void Game::unpause()
{
	paused = false;
}

bool Game::isPaused()
{
	return paused;
}

bool Game::canSelectedUnitAttackAt(int x, int y)
{
	return selectedUnit->canAttackAt(x, y);
}

bool Game::isEnemyPlayer(int x, int y)
{
	return map->isEnemyPlayer(onMove, x, y);
}

bool Game::isSelectedUnit(int x, int y)
{
	return selectedUnit->getX() == x && selectedUnit->getY() == y;
}

bool Game::die(int x, int y)
{
	Unit *unit = map->getUnit(x, y);
	if (unit->isDead()) {
		map->removeUnit(x, y);
		Player *opponent = onMove == firstPlayer ? secondPlayer : firstPlayer;
		opponent->removeUnit(unit);
		delete unit;
		changePlayer = true;
		selectNextUnit = true;
		return true;
	}
	return false;
}


bool Game::isBoxAvailable(int x, int y)
{
	int pathLength = (int)map->getPathFromTo(selectedUnit->getX(), selectedUnit->getY(), x, y).size();
	return
		(map->isEmpty(x, y) //empty box
			&& pathLength <= selectedUnit->getSpeed() * 2 //not too far
			&& pathLength > 0) //path exists
		|| (isSelectedUnit(x, y) //is selected (heal)
			&& onMove->getUnits()->size() > 1) //and the player have more minions
		|| (isEnemyPlayer(x, y) //is enemy
			&& canSelectedUnitAttackAt(x, y)); //and can attack
}

bool Game::isEnd()
{
	Player *player = onMove == firstPlayer ? secondPlayer : firstPlayer;
	if (player->getUnits()->empty()) {
		return true;
	}
	return false;
}

Game::Game(int mapWidth, int mapHeight)
{
	this->map = new Map(mapWidth, mapHeight);
	this->changePlayer = false;
	this->selectNextUnit = false;
	this->paused = false;
}

Game::~Game()
{
	delete map;
	delete firstPlayer;
	delete secondPlayer;
}
