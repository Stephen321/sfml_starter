#include "GameScene.h"
#include "SceneManager.h"
#include "GameData.h"

GameScene::GameScene(sf::RenderWindow* _window)
	: Scene(Type::GameScene, _window) {
	m_playerEntity = GameData::getInstance().getAsset<se::EntityInstance*>("Snakato");
	m_playerEntity->setCurrentAnimation("NewAnimation");

	m_playerEntity->setScale(se::point(0.5f, 0.5f));
	m_playerEntity->setPosition(se::point(window->getSize().x / 2.f, window->getSize().y / 2.f));
	//m_playerEntity->setAngle(se::toRadians(45));

	debugCircle.setFillColor(sf::Color::Green);
	debugCircle.setRadius(2);
	debugCircle.setPosition(m_playerEntity->getPosition().x, m_playerEntity->getPosition().y);
}

void GameScene::start() {
}

void GameScene::stop() {

}

void GameScene::handleEvents(const sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space) {
		SceneManager::getInstance().changeScene(Type::GameOverScene);
	}
}

void GameScene::update(float dt) {
	m_playerEntity->setTimeElapsed(dt * 1000);
}

void GameScene::render(sf::RenderStates states) const {
	m_playerEntity->render();
	window->draw(debugCircle);
}