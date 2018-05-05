#pragma once


#include "SFML/Graphics.hpp"


class Screen {
public:
	enum class Type {
		Exit = -1,
		Menu,
		Game,
		GameOver
	};
	virtual Screen::Type run(sf::RenderWindow &window) = 0;
};