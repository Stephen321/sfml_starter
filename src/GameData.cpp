#include "GameData.h"
#include <cassert>


GameData::GameData() {

}


GameData& GameData::getInstance() {
	static GameData gd;
	return gd;
}

GameData::~GameData() {
	for (auto& a : assets) {
		delete a.second;
	}
}

void GameData::load(sf::RenderWindow* _window) {
	window = _window;
	assert(window && "should always be a window when load is called");

	//Add assets here
	//--

	//add textures
	addAsset<sf::Texture>("menu", "assets/sprites/menu.png");
	addAsset<sf::Texture>("gameover", "assets/sprites/gameover.png");

	//add model asset and entities in it 
	std::vector<std::string> entities;
	entities.push_back("Snakato");
	addModelAsset("test", "assets/animations/TestAnimation/test.scon", entities);

	assert(assets.size() && "no asserts were loaded");
}

void GameData::addTexture(const char * name, const char * path) {
	Asset<sf::Texture>* a = new Asset<sf::Texture>;
	a->data.loadFromFile(path);
	assets[std::string(name)] = a;
}

void GameData::addModelAsset(const char * name, const char * path, const std::vector<std::string>& entities) {
	Asset<se::SpriterModel*>* a = new Asset<se::SpriterModel*>;
	a->data = new se::SpriterModel(path, new se::ExampleFileFactory(window), new se::ExampleObjectFactory(window));
	assets[std::string(name)] = a;

	for (int i = 0; i < entities.size(); i++) {
		Asset<se::EntityInstance*>* e = new Asset<se::EntityInstance*>;
		e->data = a->data->getNewEntityInstance(entities[i]);
		assets[entities[i]] = e;
	}
}

void GameData::addEntity(const char * model, const char * name) {
	//getAsset<SpriterEngine::SpriterModel>
}
