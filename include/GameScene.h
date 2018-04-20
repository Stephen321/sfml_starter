#pragma once

#include "Scene.h"
#include "Spriter.h"


class GameScene : public Scene {
public:
	GameScene(sf::RenderWindow* _window);
	void start() override;
	void stop() override;
	void handleEvents(const sf::Event& ev) override;
	void update(float dt) override;
	void render(sf::RenderStates states) const override;

private:
	SpriterEngine::EntityInstance* m_playerEntity;
	sf::CircleShape debugCircle;
};