#pragma once

#include "Screen.h"

class GameOverScreen : public Screen {
public:
	Screen::Type run(sf::RenderWindow &window) override;
};