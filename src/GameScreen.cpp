#include "GameScreen.h"

Screen::Type GameScreen::run(sf::RenderWindow &window) {
	GameLoader gameLoader("assets/");
	sf::Event Event;
	bool Running = true;
	sf::Clock frameClock;

	bool pause = false;
	
	while (Running)	{
		while (window.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed || 
				(Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)) {
				return Screen::Type::Exit;
			}
			if (Event.type == sf::Event::LostFocus) {
				pause = true;
			}
			if (Event.type == sf::Event::GainedFocus) {
				pause = false;
			}				
		}		

		float dt = frameClock.restart().asSeconds();
		if (dt > 0.3f || pause)
			dt = 0.f;


		window.clear(sf::Color(96, 23, 54));


		window.display();
	}

	return Screen::Type::GameOver;
}