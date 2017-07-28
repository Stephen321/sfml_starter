#pragma once

#include "Screen.h"

class MenuScreen : public Screen {
public:
	Screen::Type run(sf::RenderWindow &window) override;
};