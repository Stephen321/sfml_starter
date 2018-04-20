#include "GameOverScene.h"
#include "GameData.h"
#include "SceneManager.h"

GameOverScene::GameOverScene(sf::RenderWindow* _window)
	: Scene(Type::GameOverScene, _window) {
	sf::View view = window->getView();
	sf::FloatRect bounds(0.f, 0.f, view.getSize().x, view.getSize().y);

	m_background.setTexture(GameData::getInstance().getAsset<sf::Texture>("gameover"));
	m_background.setPosition(0.f, 0.f);
	m_background.setScale(bounds.width / m_background.getLocalBounds().width, bounds.height / m_background.getLocalBounds().height);
}

void GameOverScene::start() {
}

void GameOverScene::stop() {

}

void GameOverScene::handleEvents(const sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space) {
		SceneManager::getInstance().changeScene(Type::MenuScene);
	}
}

void GameOverScene::update(float dt) {
}

void GameOverScene::render(sf::RenderStates states) const {
	window->draw(m_background);
}