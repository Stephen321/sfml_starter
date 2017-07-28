#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "SFML\Graphics\Texture.hpp"

class GameData {
public:
	static GameData& getInstance();
	GameData(GameData const&) = delete;             
	GameData(GameData&&) = delete;                  
	GameData& operator=(GameData const&) = delete;
	GameData& operator=(GameData &&) = delete;
private:
	GameData();
};
#endif