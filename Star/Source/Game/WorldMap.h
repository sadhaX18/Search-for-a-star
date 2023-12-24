#pragma once
#include<memory>
#include<list>
#include<map>

class IRenderable;
class IShader;
class IGraphics;

enum class TileSet {
	TOP = 0,
	BOTTOM = 1,
	LEFT = 2,
	RIGHT = 3,
	MIDDLE = 4,
	TOP_LEFT = 5,
	TOP_RIGHT = 6,
	BOTTOM_LEFT = 7,
	BOTTOM_RIGHT = 8
};

struct Tile {
public:
	std::shared_ptr<IRenderable> tileRenderable;
	std::shared_ptr<b2Body> tileBody;
};

class WorldMap
{
	WorldMap(IGraphics* graphics);
	WorldMap(IGraphics* graphics, int mapDef[28][16]);
private:
	int mapDef[28][16];
	std::map<TileSet, IShader*> tileMap;
	std::list<std::shared_ptr<Tile>> worldMap;

};