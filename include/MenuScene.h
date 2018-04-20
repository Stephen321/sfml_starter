#pragma once

#include "Scene.h"

class MenuScene : public Scene {
public:
	MenuScene(sf::RenderWindow* _window);
	void start() override;
	void stop() override;
	void handleEvents(const sf::Event& ev) override;
	void update(float dt) override;
	void render(sf::RenderStates states) const override;

private:
	sf::Sprite m_background;
};