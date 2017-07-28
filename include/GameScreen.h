#pragma once

#include "Screen.h"
#include "GameLoader.h"

class GameScreen : public Screen {
public:
	Screen::Type run(sf::RenderWindow &window) override;
};