#include "GameLoader.h"
#include "SFML/Graphics.hpp" 
#include "GameData.h"
#include <memory>
#include <fstream>

GameLoader::GameLoader(const std::string& filePath) {
	loadData(filePath);
}

void GameLoader::loadJSONDATA(std::string const & filename) {
	std::ifstream file(filename);
	std::string line;
	if (file.is_open()) {
		while (std::getline(file, line)) {
			m_JSONData.append(line);
		}
	}
}

void GameLoader::loadData(const std::string& filePath) {
	GameData& ptr = GameData::getInstance();
	m_JSONData.clear();
	loadJSONDATA(filePath + "data.json");
	m_document.Parse<0>(m_JSONData.c_str());

	Value::ConstMemberIterator it = m_document.MemberBegin();
	Value::ConstMemberIterator spritesIt = it->value.GetObject().MemberBegin();
	std::string spritesPath = spritesIt->value.GetString();
	++it;
}