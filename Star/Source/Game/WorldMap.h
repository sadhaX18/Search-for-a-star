#pragma once
#include<memory>
#include<list>

class IRenderable;
class IShader;
struct b2BodyDef;
class IGraphics;
class StaticEntity;

class Tile {
public:
	Tile();
	~Tile();
	std::shared_ptr<IRenderable> tileRenderable;
	b2Body* tileBody;
};

class WorldMap
{
public:
	WorldMap();
	~WorldMap();
	std::list<StaticEntity*> initMap(int map[16][28], IGraphics* Graphics, std::shared_ptr<b2World> gameWorld, std::shared_ptr<Resources> resources);

	void clearMap(IGraphics* Graphics, std::shared_ptr<b2World> gameWorld);

private:
	TileSet getTileSetType(int map[16][28], int i, int j);
	Tile worldMap[16][28];
};