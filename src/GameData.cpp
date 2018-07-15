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
    addTexture("menu", "assets/sprites/menu.png");
    addTexture("gameover", "assets/sprites/gameover.png");

    //add model asset and entities in it 
    std::vector<std::string> entities;
    entities.push_back("Snakato");
    addModel("test", "assets/animations/TestAnimation/test.scon", entities);

    assert(assets.size() && "no asserts were loaded");
}

void GameData::addTexture(const char * name, const char * path) {
    Asset<sf::Texture>* a = new Asset<sf::Texture>;
    a->data.loadFromFile(path);
    assets[std::string(name)] = a;
}