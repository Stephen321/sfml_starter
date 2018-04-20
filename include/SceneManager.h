#pragma once

#include <vector>
#include "Constants.h"
#include "Scene.h"

class SceneManager {
public:
	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}
	bool getRunning() const;
	void handleEvents();
	void update();
	void render();
	void changeScene(Scene::Type type);

private:
	SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;
	~SceneManager();

	bool m_running;
	bool m_pause;
	std::vector<Scene*> m_scenes;
	sf::Clock m_clock;
	Scene* m_currentScene;
	sf::RenderWindow m_window;
};