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

enum class UIElement {
	MAIN_MENU = 0,
	PAUSED = 1,
	GAME_OVER = 2,
	GAME_WIN = 3,
	LEVEL_FAILED = 4
};

class Resources {
public:
	Resources();
	~Resources();

	void loadResources(IGraphics* graphics);
	std::shared_ptr<std::map<TileSet, IShader*>> getTileMap() { return tileMap; }
	std::shared_ptr<std::map<UIElement, IShader*>> getUIElements() { return UIElements; }

	IShader* getPlayerSprite() { return playerSprite; }
	IShader* getSpikeSprite() { return spikeSprite; }
	IShader* getDoorSprite() { return doorSprite; }

private:
	std::shared_ptr<std::map<UIElement, IShader*>> UIElements;
	std::shared_ptr<std::map<TileSet, IShader*>> tileMap;
	IShader* playerSprite;
	IShader* spikeSprite;
	IShader* doorSprite;
};