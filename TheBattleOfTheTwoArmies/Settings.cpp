#include "Settings.h"

void Settings::load(std::string file)
{
	std::ifstream fs(file);
	int lineNo = 0;
	while (!fs.eof()) {
		std::string line;
		std::getline(fs, line); //gets line
		++lineNo;
		if (line.empty() || line.at(0) == '#') continue; //if comment or empty skip
		std::vector<std::string> lineVector;
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss, cell, ';')) { //splits the line to parts
			lineVector.push_back(cell);
		}
		//checks the first part of every line, parses the settings from it, throws exception if the parsing was unsuccessful
		if (lineVector[0] == "displayResolution") {
			try {
				displayWidth = std::stoi(lineVector[1]);
				displayHeight = std::stoi(lineVector[2]);
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error on line displayResolution (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "fps") {
			try {
				fps = std::stoi(lineVector[1]);
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error on line fps (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "firstPlayer") {
			try {
				std::string name = lineVector[1];
				char r = (char)std::stoi(lineVector[2]);
				char g = (char)std::stoi(lineVector[3]);
				char b = (char)std::stoi(lineVector[4]);
				firstPlayer = new Player(name, r, g, b);
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error on line firstPlayer (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "secondPlayer") {
			try {
				std::string name = lineVector[1];
				char r = std::stoi(lineVector[2]);
				char g = std::stoi(lineVector[3]);
				char b = std::stoi(lineVector[4]);
				secondPlayer = new Player(name, r, g, b);
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error on line secondPlayer (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "mapDimensions") {
			try {
				mapWidth = std::stoi(lineVector[1]);
				mapHeight = std::stoi(lineVector[2]);
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error on line mapDimensions (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "Unit") { //creates unit settings
			try {
				std::string name = lineVector[1];
				UnitSettings us;
				us.attack = std::stoi(lineVector[2]);
				us.hp = std::stoi(lineVector[3]);
				us.bitmap = lineVector[4];
				us.speed = std::stoi(lineVector[5]);
				us.attackBitmap = lineVector[6];
				us.efRange = std::stoi(lineVector[7]);
				unitSettings[name] = us;
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error at Unit settings (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else if (lineVector[0] == "Entity") { //creates static entity settings
			try {
				std::string name = lineVector[1];
				EntitySettings es;
				es.bitmap = lineVector[2];
				es.width = std::stoi(lineVector[3]);
				es.height = std::stoi(lineVector[4]);
				entitySettings[name] = es;
			}
			catch (std::exception ex)
			{
				fs.close();
				std::string exstr = "Parsing error at Entity settings (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
		else {
			try {
				std::string fcell = lineVector[0];
				if (unitSettings.find(fcell) != unitSettings.end()) { //serach the unit settings by name and creates unit from it, if the setting was found
					int x = std::stoi(lineVector[1]);
					int y = std::stoi(lineVector[2]);
					UnitSettings us = unitSettings[fcell];
					Player *player = lineVector[3] == "firstPlayer" ? firstPlayer : secondPlayer;
					if (unitSettings[fcell].efRange == 0) {
						MeleeUnit *mu = new MeleeUnit(us.attack, us.hp, player, us.bitmap, us.speed, us.attackBitmap, x, y);
						entities->push_back(mu);
						if (!mu->getBitmap()) {
							throw std::exception("Bitmap not loaded (missing file?)");
						}
					}
					else {
						RangedUnit *ru = new RangedUnit(us.attack, us.hp, player, us.bitmap, us.speed, us.attackBitmap, us.efRange, x, y);
						entities->push_back(ru);
						if (!ru->getBitmap()) {
							throw std::exception("Bitmap not loaded (missing file?)");
						}
					}
				}
				else if (entitySettings.find(lineVector[0]) != entitySettings.end()) { //serach the static entity settings by name and creates unit from it, if the setting was found
					int x = std::stoi(lineVector[1]);
					int y = std::stoi(lineVector[2]);
					EntitySettings es = entitySettings[fcell];
					StaticEntity *se = new StaticEntity(es.bitmap, es.width, es.height, x, y);
					entities->push_back(se);
					if (!se->getBitmap()) {
						throw std::exception("Bitmap not loaded (missing file?)");
					}
				}
				else {
					continue;
				}
			}
			catch (std::exception ex) {
				fs.close();
				std::string exstr = "Parsing error at Map settings (" + std::to_string(lineNo) + ")";
				throw std::exception(exstr.c_str());
			}
		}
	}
	//shuffle the player's units, so the play order is random
	std::random_shuffle(firstPlayer->getUnits()->begin(), firstPlayer->getUnits()->end());
	std::random_shuffle(secondPlayer->getUnits()->begin(), secondPlayer->getUnits()->end());
	fs.close();
}

Settings::Settings()
{
	entities = new std::vector<Entity*>();
}