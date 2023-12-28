#pragma once
#include <memory>
#include <map>

class IShader;
class IGraphics;

enum class TileSet {
	EMPTY = -1,
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

class Resources {
public:
	Resources();
	~Resources();

	void loadResources(IGraphics* graphics);
	std::shared_ptr<std::map<TileSet, IShader*>> getTileMap() { return tileMap; }

	IShader* getPlayerSprite() { return playerSprite; }

private:
	std::shared_ptr<std::map<TileSet, IShader*>> tileMap;
	IShader* playerSprite;
};