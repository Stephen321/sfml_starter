#pragma once

#include "Scene.h"

class GameOverScene: public Scene {
public:
	GameOverScene(sf::RenderWindow* _window);
	void start() override;
	void stop() override;
	void handleEvents(const sf::Event& ev) override;
	void update(float dt) override;
	void render(sf::RenderStates states) const override;

private:
	sf::Sprite m_background;
};