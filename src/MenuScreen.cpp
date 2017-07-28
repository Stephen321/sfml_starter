#include "MenuScreen.h"

Screen::Type MenuScreen::run(sf::RenderWindow &window) {
	sf::Event Event;
	bool Running = true;
	sf::Clock frameClock;
	int menu = 0;

	sf::View view = window.getView();
	sf::FloatRect bounds(0.f, 0.f, view.getSize().x, view.getSize().y);

	sf::Texture startTexture;
	startTexture.loadFromFile("assets/sprites/start.png");
	sf::Sprite start(startTexture);
	start.setPosition(0.f, 0.f);
	start.setScale(bounds.width / start.getLocalBounds().width, bounds.height / start.getLocalBounds().height);

	while (Running)	{
		float dt = frameClock.restart().asSeconds();

		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed) {
				return Screen::Type::Exit;
			}

			if (Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Space) {
				return Screen::Type::Game;
			}
		}

		window.clear();
		window.draw(start);
		window.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return Screen::Type::Exit;
}