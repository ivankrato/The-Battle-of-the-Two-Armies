#include "Unit.h"
#include "StaticEntity.h"
#include <map>
#include <queue>
#include <iostream>
#pragma once

/*
represents the map
*/
class Map
{
private:
	/*
	represents one node in a graph, for finding path (BFS)
	*/
	struct Node
	{
		int x;
		int y;
		Node(int x, int y);
	};
	/*
	two dimensional array of nodes, for finding path (BFS)
	*/
	Node*** nodeArray;
	/*
	two dimensional array of entities, represents the map
	*/
	Entity*** mapArray;
	/*
	logic width of the map
	*/
	int mapWidth;
	/*
	logic height of the map
	*/
	int mapHeight;
	/*
	vector of the nodes which are connected to the node (parameter), for finding path (BFS)
	*/
	std::vector<Node *> getNextNodes(Node *node);
	/*
	map of previous nodes (key is a node, value is a node which was visited before), for finding path (BFS)
	*/
	std::map<Node*, Node*> prevNodes;
	/*
	vector of visited nodes, for finding path (BFS)
	*/
	std::vector<Node*> visitedNodes;
public:
	/*
	returns the map array
	*/
	Entity*** getMapArray();
	/*
	returns the logic map width
	*/
	int getMapWidth() const;
	/*
	returns the logic map height
	*/
	int getMapHeight() const;
	/*
	returns vector of integers with a path, x and y are rotating (x, y, x, y, ...), breadth-first search (BFS) is used here
	algorithm found on StackOverflow in Java, rewritten for C++
	(http://stackoverflow.com/questions/1579399/shortest-path-fewest-nodes-for-unweighted-graph)
	*/
	std::vector<int> getPathFromTo(int fromX, int fromY, int toX, int toY);
	/*
	adds the unit (parameter) to the map to coordinates (parameter), return true if successful
	*/
	bool addUnit(int x, int y, Unit *unit);
	/*
	adds the static entity (parameter) to the map to coordinates (parameter), return true if successful
	*/
	bool addStaticEntity(int x, int y, StaticEntity *staticEntity);
	/*
	adds the unit (parameter) to the map to coordinates from the unit object, return true if successful
	*/
	bool addUnit(Unit *unit);
	/*
	adds the static entity (parameter) to the map to coordinates from the static entity object, return true if successful
	*/
	bool addStaticEntity(StaticEntity *staticEntity);
	/*
	moves the unit (parameter) to coordinates (parameter)
	*/
	void moveUnit(int x, int y, Unit *unit);
	/*
	removes the unit on coordinates (parameter) from the map
	*/
	void removeUnit(int x, int y);
	/*
	returns the unit on coordinates (parameter)
	*/
	Unit *getUnit(int x, int y);
	/*
	returns true, if the unit on coordinates (parameter) is player's (coordinates) enemy
	*/
	bool isEnemyPlayer(Player *player, int x, int y);
	/*
	returns true, if the unit on coordinates (parameter) is player's (coordinates) friend
	*/
	bool isFriendlyPlayer(Player *player, int x, int y);
	/*
	returns true, if the box on coordinates (parameter) is empty
	*/
	bool isEmpty(int x, int y);
	/*
	constructor
	*/
	Map(int mapWidth, int mapHeight);
	~Map();
};

