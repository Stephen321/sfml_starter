#include "SceneManager.h"

int main() {
	srand((unsigned int)time(NULL));
	SceneManager& sceneManager = SceneManager::getInstance();
	while (sceneManager.getRunning()) {
		sceneManager.handleEvents();
		sceneManager.update();
		sceneManager.render();
	}
	return 0;
	return EXIT_SUCCESS;
}