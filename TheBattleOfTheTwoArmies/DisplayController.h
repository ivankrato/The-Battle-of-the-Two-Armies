#pragma once
#include "Game.h"
#include "Entity.h"
#include "Settings.h"
#include "MovingEntity.h"
#include "MoveAnimation.h"
#include "RotateAnimation.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <iostream>
#include <future>

/*
Allegro graphics logic
*/
class DisplayController
{
private:
	/*
	Game object, game logic
	*/
	Game *game;
	/*
	width of the display
	*/
	int displayWidth;
	/*
	height of the display
	*/
	int displayHeight;
	/*
	maximum frames per second of the display
	*/
	int fps;
	/*
	allegro display
	*/
	ALLEGRO_DISPLAY *display;
	/*
	allegro display event queue
	*/
	ALLEGRO_EVENT_QUEUE *event_queue;
	/*
	allegro timer
	*/
	ALLEGRO_TIMER *timer;
	/*
	if true, display will be redraw on the next tick
	*/
	bool redraw;
	/*
	if true, the game will exit after finishing all animations
	*/
	bool exit;
	/*
	vector containing all the entities in the game
	*/
	std::vector<Entity*> *entities;
	/*
	vector containing all the animations in the game
	*/
	std::vector<Animation*> *animations;
	/*
	width of one box
	*/
	float boxWidth;
	/*
	height of one box
	*/
	float boxHeight;
	/*
	X coordinate of the highlighted box (the one the mouse is over)
	*/
	int highlightedBoxX;
	/*
	Y coordinate of the highlighted box (the one the mouse is over)
	*/
	int highlightedBoxY;
	/*
	margin of the map (top, right, bottom, left)
	*/
	int mapMargin[4];
	/*
	width of the box border
	*/
	float mapLineWidth;
	/*
	bitmap containing the map - background, unit, entities, boxes
	*/
	ALLEGRO_BITMAP *mapBitmap;
	/*
	bitmap containing one tile of the map background
	*/
	ALLEGRO_BITMAP *mapTileBitmap;
	/*
	bitmap containing one tile of the display background
	*/
	ALLEGRO_BITMAP *displayTileBitmap;
	/*
	small (16) font, Vera
	*/
	ALLEGRO_FONT *font;
	/*
	big (36) font, Vera
	*/
	ALLEGRO_FONT *fontBig;

	/*
	loads all entities graphics from the settings (parameter) to the map
	*/
	void loadEntities(Settings *settings);
	/*
	redraws whole display
	*/
	void redrawDisplay();
	/*
	draws the map on the display
	*/
	void drawMap();
	/*
	draws one entity (parameter) to the map, if fitInBox is true, the entity will be resize to fit one box
	*/
	void drawEntityBitmap(Entity *entity, bool fitInBox = true);
	/*
	draws highlighted box (the one the mouse is over)
	*/
	void drawHighlightedBox();
	/*
	draws info about the selected unit (attack, hp, player)
	*/
	void drawSelectedInfo();
	/*
	initializes bitmap coordinates of one entity (parameter)
	*/
	void initEntityBitmapCoords(Entity *entity);
	/*
	returns logic X coordinate based on bitmap X coordinate, -1 if fail
	*/
	int getMapXFromBitmapX(float bitmapX);
	/*
	returns logic Y coordinate based on bitmap Y coordinate, -1 if fail
	*/
	int getMapYFromBitmapY(float bitmapY);
	/*
	moves selected unit from one place to other (logic coordinates, parameter) and creates move animation
	*/
	void moveSelectedUnit(int x, int y);
	/*
	attacks unit (logic coordinates, parameter) and creates attack animation
	*/
	void attackUnit(int x, int y);
	/*
	heals the selected unit
	*/
	void healUnit();
	/*
	calls the tick function in all animations, deletes the animations if needed
	*/
	void animate();
	/*
	returns entity on logic coordinates (parameter), nullptr if fail
	*/
	Entity *getEntity(int x, int y);

public:
	/*
	constructor, needs the name of the settings file in parameter
	*/
	DisplayController(std::string settingsFile);
	/*
	starts the game cycle
	*/
	void start();
	/*
	destructor, clears allocated memory
	*/
	~DisplayController();
};

