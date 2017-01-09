#include "Map.h"



std::vector<Map::Node*> Map::getNextNodes(Node * node)
{
	std::vector<Node*> nextNodes;
	int x = node->x;
	int y = node->y;
	if (x + 1 < mapWidth && nodeArray[x + 1][y] != NULL) { //right
		nextNodes.push_back(nodeArray[x + 1][y]);
	}
	if (x - 1 >= 0 && nodeArray[x - 1][y] != NULL) { //left
		nextNodes.push_back(nodeArray[x - 1][y]);
	}
	if (y + 1 < mapHeight && nodeArray[x][y + 1] != NULL) { //down
		nextNodes.push_back(nodeArray[x][y + 1]);
	}
	if (y - 1 >= 0 && nodeArray[x][y - 1] != NULL) { //up
		nextNodes.push_back(nodeArray[x][y - 1]);
	}
	std::random_shuffle(nextNodes.begin(), nextNodes.end());
	return nextNodes;
}

Entity*** Map::getMapArray()
{
	return mapArray;
}

int Map::getMapWidth() const
{
	return mapWidth;
}

int Map::getMapHeight() const
{
	return mapHeight;
}

std::vector<int> Map::getPathFromTo(int fromX, int fromY, int toX, int toY)
{
	//initialize nodeArray
	this->nodeArray = new Node**[mapWidth];
	for (int i = 0; i < mapWidth; i++) {
		nodeArray[i] = new Node*[mapHeight];
		for (int j = 0; j < mapHeight; j++) {
			if (mapArray[i][j] == NULL) {
				nodeArray[i][j] = new Node(i, j);
			}
			else {
				nodeArray[i][j] = NULL;
			}
		}
	}
	nodeArray[fromX][fromY] = new Node(fromX, fromY);
	//BFS
	std::vector<int> path;
	std::queue<Node*> q;
	Node *current = nodeArray[fromX][fromY];
	q.push(current);
	visitedNodes.push_back(current);
	while (!q.empty()) {
		current = q.front();
		q.pop();
		if (current->x == toX && current->y == toY) {
			break;
		}
		else {
			for (Node* node : getNextNodes(current)) {
				if (std::find(visitedNodes.begin(), visitedNodes.end(), node) == visitedNodes.end()) {
					q.push(node);
					visitedNodes.push_back(node);
					prevNodes.insert(std::pair<Node*, Node*>(node, current));
				}
			}
		}
	}
	//delete nodeArray
	for (int i = 0; i < mapWidth; i++) {
		delete[] nodeArray[i];
	}
	delete[] nodeArray;
	if (current->x != toX || current->y != toY) { //path not found
		return path;
	}

	//create path (x, y, x, y, x, y, ...)
	for (Node *node = current; prevNodes.find(node) != prevNodes.end(); node = prevNodes[node]) {
		path.push_back(node->y);
		path.push_back(node->x);
	}
	std::reverse(path.begin(), path.end());

	return path;
}

bool Map::addUnit(int x, int y, Unit *unit)
{
	unit->moveTo(x, y);
	return addUnit(unit);
}

bool Map::addStaticEntity(int x, int y, StaticEntity * staticEntity)
{
	staticEntity->moveTo(x, y);
	return addStaticEntity(staticEntity);
}

bool Map::addUnit(Unit * unit)
{
	int x = unit->getX();
	int y = unit->getY();
	if (isEmpty(x, y)) {
		mapArray[x][y] = unit;
		if (x >= mapWidth / 2) {
			unit->flipLeft();
		}
		return true;
	}
	return false;
}

bool Map::addStaticEntity(StaticEntity * staticEntity)
{
	int x = staticEntity->getX();
	int y = staticEntity->getY();
	for (int i = 0; i < staticEntity->getWidth(); i++) {
		for (int j = 0; j < staticEntity->getHeight(); j++) {
			if (x + i < mapWidth && y + j < mapHeight) {
				if (!isEmpty(x + i, y + j)) {
					return false;
				}
			}
		}
	}
	for (int i = 0; i < staticEntity->getWidth(); i++) {
		for (int j = 0; j < staticEntity->getHeight(); j++) {
			if (x + i < mapWidth && y + j < mapHeight) {
				mapArray[x + i][y + j] = staticEntity;
			}
		}
	}
	return true;
}

void Map::moveUnit(int x, int y, Unit * unit)
{
	mapArray[unit->getX()][unit->getY()] = NULL;
	mapArray[x][y] = unit;
	unit->moveTo(x, y);
}

void Map::removeUnit(int x, int y)
{
	mapArray[x][y] = NULL;
}

Unit * Map::getUnit(int x, int y)
{
	return (Unit*)mapArray[x][y];
}

bool Map::isEnemyPlayer(Player * player, int x, int y)
{
	if (!isEmpty(x, y) && mapArray[x][y]->isUnit()) {
		Unit *unit = (Unit*)mapArray[x][y];
		return unit->getPlayer() != player;
	}
	return false;
}

bool Map::isFriendlyPlayer(Player * player, int x, int y)
{
	if (!isEmpty(x, y)) {
		Unit *unit = (Unit*)mapArray[x][y];
		return unit->getPlayer() == player;
	}
	return false;
}

bool Map::isEmpty(int x, int y)
{
	return mapArray[x][y] == NULL;
}

Map::Map(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->mapArray = new Entity**[mapWidth];
	for (int i = 0; i < mapWidth; i++) {
		mapArray[i] = new Entity*[mapHeight];
		for (int j = 0; j < mapHeight; j++) {
			mapArray[i][j] = NULL;
		}
	}
}


Map::~Map()
{
	for (int i = 0; i < mapWidth; i++) {
		delete[] mapArray[i];
	}
	delete[] mapArray;
}

Map::Node::Node(int x, int y)
{
	this->x = x;
	this->y = y;
}
