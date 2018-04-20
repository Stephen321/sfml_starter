#pragma once

#include <cassert>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

class Scene {
public:
	enum class Type {
		MenuScene,
		GameScene,
		GameOverScene
	};
	Scene(Type type, sf::RenderWindow* _window) : m_type(type), window(_window){}
	virtual ~Scene() {}
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void handleEvents(const sf::Event& ev) = 0;
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderStates states) const = 0;
	Type getType() const {
		return m_type;
	}

protected:
	sf::RenderWindow* window;

private:
	Type m_type;
};
