#pragma once
#include"SFML/Graphics.hpp"

using namespace sf;
using std::string;

class Map
{
public:
	Map(int heightMap, int widthMap_);
	~Map();
	void createMap(RenderWindow& window);
	string* getTileMap() const;

private:
	int				heightMap_;
	int				widthMap_;
	string*			TileMap_;
	Texture			cross_, earth_, lava_, road_;
	Sprite			sprite_;

	void createTemplateMap();
};



