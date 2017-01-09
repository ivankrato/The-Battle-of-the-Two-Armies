#include "DisplayController.h"

void DisplayController::loadEntities(Settings *settings)
{
	for (Entity* e : *entities) {
		initEntityBitmapCoords(e);
	}
}

void DisplayController::redrawDisplay()
{
	animate();
	//background
	al_clear_to_color(al_map_rgb(255, 255, 255));
	for (float bitmapX = 0; bitmapX < displayWidth; bitmapX += al_get_bitmap_width(displayTileBitmap)) {
		float bitmapY;
		for (bitmapY = 0; bitmapY < displayHeight; bitmapY += al_get_bitmap_height(displayTileBitmap)) {
			al_draw_bitmap(displayTileBitmap, bitmapX, bitmapY, 0);
		}
	}
	//map+boxes, entities, highligted box, info
	drawMap();
	for (Entity* e : *entities) {
		bool fit = true;
		if (e->isMovingEntity()) {
			fit = false;
		}
		drawEntityBitmap(e, fit);
	}
	drawHighlightedBox();
	drawSelectedInfo();
	al_draw_bitmap(mapBitmap, mapMargin[0], mapMargin[3], 0);
	al_flip_display();
}

void DisplayController::drawMap()
{
	al_set_target_bitmap(mapBitmap);
	//background
	al_clear_to_color(al_map_rgb(0, 255, 0));
	for (float bitmapX = 0; bitmapX < al_get_bitmap_width(mapBitmap); bitmapX += al_get_bitmap_width(mapTileBitmap)) {
		float bitmapY;
		for (bitmapY = 0; bitmapY < al_get_bitmap_height(mapBitmap); bitmapY += al_get_bitmap_height(mapTileBitmap)) {
			al_draw_bitmap(mapTileBitmap, bitmapX, bitmapY, 0);
		}
	}
	int mapWidth = game->getMap()->getMapWidth();
	int mapHeight = game->getMap()->getMapHeight();
	Entity*** mapArray = game->getMap()->getMapArray();
	float bitmapX = 0;
	float bitmapY = 0;
	//boxes
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
			al_draw_rectangle(bitmapX, bitmapY, bitmapX + boxWidth, bitmapY + boxHeight, al_map_rgba(255, 255, 255, 20), mapLineWidth);
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
			bitmapY += boxHeight;
		}
		bitmapX += boxWidth;
		bitmapY = 0;
	}
	al_set_target_bitmap(al_get_backbuffer(display));
}

void DisplayController::drawEntityBitmap(Entity *entity, bool fitInBox)
{
	al_set_target_bitmap(mapBitmap);
	ALLEGRO_BITMAP *bitmap = entity->getBitmap();
	float bitmapX = entity->getBitmapX();
	float bitmapY = entity->getBitmapY();
	int sw = al_get_bitmap_width(bitmap);
	int sh = al_get_bitmap_height(bitmap);
	int flags = entity->isFlippedLeft() ? ALLEGRO_FLIP_HORIZONTAL : 0;
	//fit in box calculation, draws scaled bitmap
	if (fitInBox && (sw >= boxWidth || sh >= boxHeight)) {
		bitmapX += mapLineWidth / 2;
		bitmapY += mapLineWidth / 2;
		float width = entity->getWidth()*boxWidth - mapLineWidth;
		float height = entity->getHeight()*boxHeight - mapLineWidth;
		bool widthBiggerScaleDifference = (width / float(sw)) < (height / float(sh));
		if (widthBiggerScaleDifference) {
			float scale = width / float(sw);
			height = scale*sh;
		}
		else
		{
			float scale = height / float(sh);
			width = scale*sw;
		}
		int marginLeft = (entity->getWidth()*boxWidth - width) / 2;
		int marginTop = (entity->getHeight()*boxHeight - height) / 2;
		al_draw_scaled_bitmap(bitmap, 0, 0, sw, sh, bitmapX + marginLeft, bitmapY + marginTop, width, height, flags);
	}
	//if moving entity, draws rotated bitmap
	else if (entity->isMovingEntity()) {
		MovingEntity *mentity = (MovingEntity*)entity;
		float cw = entity->isFlippedLeft() ? sw : 0;
		al_draw_rotated_bitmap(bitmap, cw, sh / 2, bitmapX, bitmapY, mentity->getAngle(), flags);
	}
	//draws other bitmaps
	else {
		bitmapX += (boxWidth - sw) / 2;
		bitmapY += (boxHeight - sh) / 2;
		al_draw_bitmap(bitmap, bitmapX, bitmapY, flags);
	}
	//if unit
	if (entity->isUnit()) {
		Unit *unit = (Unit*)entity;
		bitmapX = unit->getBitmapX();
		bitmapY = unit->getBitmapY();
		//HP
		float percent = unit->getHealth() / float(unit->getMaxHealth());
		int thickness = 5;
		int margin = 10;
		float length = (boxWidth - mapLineWidth * 2 - margin * 2)*percent;
		Player *player = unit->getPlayer();
		al_draw_line(bitmapX + margin, bitmapY + thickness, bitmapX + margin + mapLineWidth + length, bitmapY + thickness, player->getColor(), thickness);
		//selection
		if (unit == game->getSelectedUnit()) {
			margin = 20;
			thickness = 3;
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
			al_draw_line(bitmapX + margin, bitmapY + boxHeight - 2 * thickness, bitmapX + boxWidth - margin, bitmapY + boxHeight - 2 * thickness, al_map_rgba(255, 255, 0, 150), thickness);
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
		}
	}
	al_set_target_bitmap(al_get_backbuffer(display));
}

void DisplayController::drawHighlightedBox()
{
	if (highlightedBoxX > -1 && highlightedBoxY > -1 //mouse is on the map, player can interact with the box
		&& game->isBoxAvailable(highlightedBoxX, highlightedBoxY)) {
		al_set_target_bitmap(mapBitmap);
		float bitmapX = highlightedBoxX*boxWidth;
		float bitmapY = highlightedBoxY*boxHeight;
		ALLEGRO_COLOR color = game->getPlayer(0)->getColor();
		al_draw_rectangle(bitmapX, bitmapY, bitmapX + boxWidth, bitmapY + boxHeight, color, mapLineWidth);
		al_set_target_bitmap(al_get_backbuffer(display));
	}
}

void DisplayController::drawSelectedInfo()
{
	float x = mapMargin[3];
	float y = mapMargin[0] + al_get_bitmap_height(mapBitmap) + 10;
	std::string attackInfo = "Attack: " + std::to_string(game->getSelectedUnit()->getAttack());
	std::string healthInfo = "Health: " + std::to_string(game->getSelectedUnit()->getHealth());
	std::string playerInfo = game->getPlayer(0)->getName() + " is on move";
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y, ALLEGRO_ALIGN_LEFT, attackInfo.c_str());
	y += 20;
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y, ALLEGRO_ALIGN_LEFT, healthInfo.c_str());
	y -= 20;
	x = displayWidth - mapMargin[3];
	al_draw_text(fontBig, game->getPlayer(0)->getColor(), x, y, ALLEGRO_ALIGN_RIGHT, playerInfo.c_str());

}

void DisplayController::initEntityBitmapCoords(Entity * entity)
{
	float bitmapX = entity->getX()*boxWidth;
	float bitmapY = entity->getY()*boxHeight;
	entity->moveBitmapTo(bitmapX, bitmapY);
}

int DisplayController::getMapXFromBitmapX(float bitmapX)
{
	bitmapX -= mapMargin[3];
	int mapWidth = game->getMap()->getMapWidth();
	for (int i = 0; i < mapWidth; i++) {
		if (bitmapX >= i*boxWidth && bitmapX < (i + 1)*boxWidth) {
			return i;
		}
	}
	return -1;
}

int DisplayController::getMapYFromBitmapY(float bitmapY)
{
	bitmapY -= mapMargin[0];
	int mapHeight = game->getMap()->getMapHeight();
	for (int i = 0; i < mapHeight; i++) {
		if (bitmapY >= i*boxHeight && bitmapY < (i + 1)*boxHeight) {
			return i;
		}
	}
	return -1;
}

void DisplayController::moveSelectedUnit(int x, int y)
{
	if (x > -1 && y > -1) {
		Entity *selectedUnit = game->getSelectedUnit();
		std::vector<int> path = game->moveSelectedUnit(x, y);
		MoveAnimation *nextAnimation = nullptr;
		if (!path.empty()) {
			std::reverse(path.begin(), path.end()); //animations must be created dfrom last to first
			for (int i = 0, ilen = (int)path.size(); i < ilen; i++) {
				nextAnimation = new MoveAnimation(selectedUnit, path[i + 1] * boxWidth, path[i] * boxHeight, 600, fps, nextAnimation);
				i++;
			}
			animations->push_back(nextAnimation);
		}
	}
}

void DisplayController::attackUnit(int x, int y)
{
	Unit *attacker = game->getSelectedUnit();
	Entity *target = getEntity(x, y);
	if (attacker->getX() > target->getX()) { //if the attacker attacks to the other side than he's looking now
		attacker->flipLeft();
	}
	else if (attacker->getX() < target->getX()) {
		attacker->flipRight();
	}
	if (attacker->isRanged()) { //create shot animation
		float fromX = attacker->getBitmapX() + boxWidth / 2;
		float fromY = attacker->getBitmapY() + boxHeight / 2;
		float toX = target->getBitmapX() + boxWidth / 2;
		float toY = target->getBitmapY() + boxHeight / 2;
		MovingEntity *shot = new MovingEntity(attacker->getAttackBitmapFile(), fromX, fromY, toX, toY);
		entities->push_back(shot);
		MoveAnimation *shotAnimation = new MoveAnimation(shot, toX, toY, 2000, fps);
		animations->push_back(shotAnimation);
	}
	else { //create weapon animation
		float fromX = attacker->getBitmapX() + boxWidth / 2;
		float fromY = attacker->getBitmapY() + boxHeight / 2;
		float toX = fromX;
		float toY = fromY;
		float fromAngle = -0.785398175;
		float toAngle = 1.1780972625;
		bool clockwise = true;
		if (attacker->isFlippedLeft()) {
			fromAngle = 0 - fromAngle;
			toAngle = 0 - toAngle;
			clockwise = false;
		}
		MovingEntity *weapon = new MovingEntity(attacker->getAttackBitmapFile(), fromX, fromY, toX, toY, fromAngle);
		entities->push_back(weapon);
		if (attacker->isFlippedLeft()) {
			weapon->flipLeft();
		}
		else {
			weapon->flipRight();
		}
		RotateAnimation *weaponAnimation = new RotateAnimation(weapon, toAngle, clockwise, 6000, fps);
		animations->push_back(weaponAnimation);
	}
	if (game->die(x, y)) { //removes the unit from vector, if he's dead
		if (target != nullptr) {
			entities->erase(std::find(entities->begin(), entities->end(), target));
		}
	}
	if (game->isEnd()) {
		exit = true;
	}
}

void DisplayController::healUnit()
{
	Unit *unit = game->getSelectedUnit();
	float fromX = unit->getBitmapX() + boxWidth / 2;
	float fromY = unit->getBitmapY() + boxHeight / 2;
	float toX = fromX;
	float toY = fromY - 50;
	MovingEntity *heal = new MovingEntity("Images\\heal.png", fromX, fromY, toX, toY, 0);
	entities->push_back(heal);
	MoveAnimation *healAnimation = new MoveAnimation(heal, toX, toY, 200, fps);
	animations->push_back(healAnimation);
}

void DisplayController::animate()
{
	game->pause();
	std::vector<MoveAnimation*>::size_type size = animations->size();
	for (std::vector<MoveAnimation*>::size_type i = 0; i < size; ++i)
	{
		Animation *animation = animations->at(i);
		Animation *nextAnimation = (animation->getNextAnimation());
		bool hasNext = animation->hasNext();
		if (animation->tick()) { //if the animation is finished, remove it, also remove moving entity
			Entity* entity = animation->getEntity();
			delete (animation);
			animations->erase(animations->begin() + i);
			--size;
			if (hasNext) {
				animations->push_back(nextAnimation);
				++size;
			}
			else if (entity->isMovingEntity()) {
				std::vector<Entity *>::iterator it = std::find(entities->begin(), entities->end(), entity);
				entities->erase(it);
				delete entity;
			}
		}
	}
	if (animations->empty()) { //if all animations are finished, unpause the game
		game->unpause();
	}
}

Entity * DisplayController::getEntity(int x, int y)
{
	for (Entity* e : *entities) {
		if (e != NULL && e->getX() == x && e->getY() == y) {
			return e;
		}
	}
	return nullptr;
}

DisplayController::DisplayController(std::string settingsFile)
{
	//initialize Allegro5
	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_native_dialog_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	//load settings from file
	Settings settings;
	try {
		settings.load(settingsFile);
	}
	catch (std::exception ex) {
		al_show_native_message_box(al_get_current_display(), "Parsing error", "Parsing error:", ex.what(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
		std::exit(-1);
	}
	displayWidth = settings.displayWidth;
	displayHeight = settings.displayHeight;
	fps = settings.fps;
	game = new Game(settings.mapWidth, settings.mapHeight);
	redraw = false;
	exit = false;
	entities = settings.entities;
	animations = new std::vector<Animation*>();
	mapMargin[0] = 20;
	mapMargin[1] = 20;
	mapMargin[2] = 60;
	mapMargin[3] = 20;
	boxWidth = (displayWidth - mapMargin[3] - mapMargin[1]) / game->getMap()->getMapWidth();
	boxHeight = (displayHeight - mapMargin[0] - mapMargin[2]) / game->getMap()->getMapHeight();
	highlightedBoxX = -1;
	highlightedBoxY = -1;
	mapLineWidth = 2;

	game->loadSettings(&settings);
	loadEntities(&settings);

	//create Allegro bitmaps, display
	al_set_new_display_flags(ALLEGRO_OPENGL);
	display = al_create_display(displayWidth, displayHeight);
	al_set_window_title(display, "The Battle of the Two Armies");
	al_clear_to_color(al_map_rgb(255, 255, 255));
	mapBitmap = al_create_bitmap(displayWidth - mapMargin[3] - mapMargin[1], displayHeight - mapMargin[0] - mapMargin[2]);
	displayTileBitmap = al_load_bitmap("Images\\displayBGTile.jpg");
	mapTileBitmap = al_load_bitmap("Images\\BGTile.png");
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / fps);
	font = al_load_ttf_font("Vera.ttf", 16, 0);
	fontBig = al_load_ttf_font("Vera.ttf", 36, 0);

	//register allegro event sources (display, timer, mouse)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
}

void DisplayController::start()
{
	al_start_timer(timer);

	while (!exit || !animations->empty())
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) { //if timer event, call the tick function
			game->tick();
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { //if click, do stuff
			int x = getMapXFromBitmapX(ev.mouse.x);
			int y = getMapYFromBitmapY(ev.mouse.y);
			if (x >= 0 && y >= 0) {
				if (game->isEnemyPlayer(x, y) && game->attackUnitAt(x, y)) { //attack
					attackUnit(x, y);
				}
				else if (game->isSelectedUnit(x, y) && game->healSelectedUnit()) { //heal
					healUnit();
				}
				else { //move
					moveSelectedUnit(x, y);
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY || //on mouse move, select highlighted box
			ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			int x = getMapXFromBitmapX(ev.mouse.x);
			int y = getMapYFromBitmapY(ev.mouse.y);
			highlightedBoxX = x;
			highlightedBoxY = y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) { //on mouse leave, unselect highlighted box
			highlightedBoxX = -1;
			highlightedBoxY = -1;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //on close, exit the game
			exit = true;
			return;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) { //redraws if the event queue is empty and we need redraw
			redraw = false;
			redrawDisplay();
		}
	}
	//show the win dialog
	std::string winString = game->getPlayer(0)->getName() + " has won!";
	al_show_native_message_box(al_get_current_display(), "Game over", "Game over", winString.c_str(), NULL, ALLEGRO_MESSAGEBOX_WARN);
}


DisplayController::~DisplayController()
{
	al_destroy_bitmap(mapBitmap);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	delete game;
	delete entities;
	delete animations;
}
