#include "MenuScene.h"
#include "GameData.h"
#include "SceneManager.h"

MenuScene::MenuScene(sf::RenderWindow* _window)
	: Scene(Type::MenuScene, _window) {
	sf::View view = window->getView();
	sf::FloatRect bounds(0.f, 0.f, view.getSize().x, view.getSize().y);

	m_background.setTexture(GameData::getInstance().getAsset<sf::Texture>("menu"));
	m_background.setPosition(0.f, 0.f);
	m_background.setScale(bounds.width / m_background.getLocalBounds().width, bounds.height / m_background.getLocalBounds().height);
}

void MenuScene::start() {
}

void MenuScene::stop() {

}

void MenuScene::handleEvents(const sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space) {
		SceneManager::getInstance().changeScene(Type::GameScene);
	}
}

void MenuScene::update(float dt) {
}

void MenuScene::render(sf::RenderStates states) const {
	window->draw(m_background);
}