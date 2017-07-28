#include "GameData.h"

GameData::GameData() {
}

GameData& GameData::getInstance() {
	static GameData gd;
	return gd;
}