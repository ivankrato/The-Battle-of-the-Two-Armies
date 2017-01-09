#include "DisplayController.h"
#include <allegro5\allegro.h>
#include <time.h>

//TODO documentation

int main(int argc, char **argv) {
	srand(unsigned(time(0)));
	DisplayController *controller = new DisplayController("settings.csv");
	controller->start();
	delete controller;
}