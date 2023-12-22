#pragma once
#include<memory>
#include<list>
#include<map>

class IRenderable;
class IShader;

enum class TileSet {
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3
};

struct Tile {
public:
	std::shared_ptr<IRenderable> tileRenderable;
	std::shared_ptr<b2Body> tileBody;
};

class WorldMap
{
private:
	int map[5][5];
	std::map<TileSet, std::shared_ptr<IShader>> tileMap;
	std::list<std::shared_ptr<Tile>> worldMap;

};