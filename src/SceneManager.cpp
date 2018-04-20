#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "GameData.h"
#include "Spriter.h"

SceneManager::SceneManager()
	: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), TITLE)
	, m_running(true)
	, m_pause(false) {
	GameData::getInstance().load(&m_window);

	m_scenes.push_back(new MenuScene(&m_window));
	m_scenes.push_back(new GameScene(&m_window));
	m_scenes.push_back(new GameOverScene(&m_window));
	m_currentScene = m_scenes[0];
	m_currentScene->start();


	SpriterEngine::Settings::setErrorFunction(SpriterEngine::Settings::simpleError);

	// load Spriter file into SpriterModel object using our custom factories
	SpriterEngine::SpriterModel scmlModel("assets/animations/TestAnimation/test.scon", new SpriterEngine::ExampleFileFactory(&m_window), new SpriterEngine::ExampleObjectFactory(&m_window));

}

SceneManager::~SceneManager() {
}

bool SceneManager::getRunning() const {
	return m_running;
}

void SceneManager::handleEvents() {
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed ||
			(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)) {
			m_running = false;
		}
		if (ev.type == sf::Event::LostFocus) {
			m_pause = true;
		}
		if (ev.type == sf::Event::GainedFocus) {
			m_pause = false;
		}
		m_currentScene->handleEvents(ev);
	}
}

void SceneManager::update() {
	float dt = m_clock.restart().asSeconds();
	if (dt > 1.f || m_pause)
		dt = 0.f;
	m_currentScene->update(dt);
}

void SceneManager::render() {
	m_window.clear(sf::Color(96, 23, 54));
	m_currentScene->render(sf::RenderStates::Default);
	m_window.display();
}

void SceneManager::changeScene(Scene::Type type) {
	for (int i = 0; i < m_scenes.size(); ++i) {
		if (m_scenes[i]->getType() == type) {
			m_currentScene->stop();
			m_currentScene = m_scenes[i];
			m_currentScene->start();
			return;
		}
	}
	assert(false && "No scene of that type could be found.");
}