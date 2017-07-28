#include "GameOverScreen.h"

Screen::Type GameOverScreen::run(sf::RenderWindow &window) {
	sf::Event Event;
	bool Running = true;
	sf::Clock frameClock;
	int menu = 0;

	while (Running)	{
		float dt = frameClock.restart().asSeconds();

		while (window.pollEvent(Event))	{
			if (Event.type == sf::Event::Closed) {
				return Screen::Type::Exit;
			}

			if (Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Space) {
				return Screen::Type::Menu;
			}
		}

		window.clear();

		window.display();
	}

	return Screen::Type::Exit;
}