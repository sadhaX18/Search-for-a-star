#include "box2d/box2d.h"
#include "Engine/IRenderable.h"
#include "Engine/IShader.h"
#include "Engine/ITexture.h"
#include "Engine/EntityComponentSystem/Resources.h"
#include "WorldMap.h"

#include "Engine/EntityComponentSystem/Entity.h"
#include "Engine/EntityComponentSystem/StaticEntity.h"

Tile::Tile() : tileBody(nullptr) {}
Tile::~Tile() {} // Not deleting tileBody here, will be automatically deleted when world is deleted at scene change

WorldMap::WorldMap(){}
WorldMap::~WorldMap() {}

std::list<StaticEntity*> WorldMap::initMap(int map[16][28], IGraphics* Graphics, std::shared_ptr<b2World> gameWorld, std::shared_ptr<Resources> resources) {
	
	std::list<StaticEntity*> entities;

	for (int i = 0; i < 16; i++) {
		float y = +505.0f - (i * 70.0f);
		for (int j = 0; j < 28; j++) {
			float x = -925.0f + (j * 70.0f);
			if (map[i][j] == 1) {
				// physics object
				Tile temp;
				b2BodyDef groundBodyDef;
				groundBodyDef.position.Set(x / 100.0f, y / 100.0f);
				temp.tileBody = gameWorld->CreateBody(&groundBodyDef);
				b2PolygonShape groundBox;
				groundBox.SetAsBox(35.0f / 100.0f, 35.0f / 100.0f);
				temp.tileBody->CreateFixture(&groundBox, 0.0f);

				// graphics object
				temp.tileRenderable = Graphics->CreateBillboard(resources->getTileMap()->at(getTileSetType(map, i, j)));

				// Syncing physics and graphics locations
				b2Transform transform = temp.tileBody->GetTransform();

				temp.tileRenderable->SetPosition(transform.p.x * 100.0f, transform.p.y * 100.0f);
				temp.tileRenderable->SetRotation(transform.q.GetAngle());

				worldMap[i][j] = temp;
			}
			else if (map[i][j] == 2) {
				StaticEntity* spike = new StaticEntity();
				spike->initEntity(EntityType::SPIKE, 5, resources, Graphics, gameWorld, x, y);
				entities.push_back(spike);
			}
			else if (map[i][j] == 3) {
				StaticEntity* door = new StaticEntity();
				door->initEntity(EntityType::DOOR, 10, resources, Graphics, gameWorld, x, y);
				entities.push_back(door);
			}
		}
	}
	return entities;
}

TileSet WorldMap::getTileSetType(int map[16][28], int i, int j) {
	// 1-> tile 0-> empty
	bool left = false, right = false, top = false, bottom = false; // true => empty
	
	if (i != 0 && map[i - 1][j] == 0)
		bottom = true;
	if (j != 0 && map[i][j-1] == 0)
		left = true;
	if (i != 15 && map[i + 1][j] == 0)
		top = true;
	if (j != 28 && map[i][j+1] == 0)
		right = true;

	if (!top) {
		if (!bottom) {
			if (!left) {
				if (!right)
					return TileSet::MIDDLE; // All neighbours contain tiles
				else
					return TileSet::RIGHT; // Only right is empty
			}
			else {
				if (!right)
					return TileSet::LEFT; // Only left is empty
				else
					return TileSet::MIDDLE; // left and right empty, no sprite yet
			}
		}
		else {
			if (!left) {
				if (!right)
					return TileSet::BOTTOM; // Only bottom is empty
				else
					return TileSet::BOTTOM_RIGHT; // bottom and right is empty
			}
			else {
				if (!right)
					return TileSet::BOTTOM_LEFT; // bottom and left is empty
				else
					return TileSet::MIDDLE; // bottom left and right is empty, no sprite yet
			}
		}
	}
	else {
		if (!bottom) {
			if (!left) {
				if (!right)
					return TileSet::TOP; // Only top is empty
				else
					return TileSet::TOP_RIGHT; // top and right is empty
			}
			else {
				if (!right)
					return TileSet::TOP_LEFT; // top and left is empty
				else
					return TileSet::MIDDLE; // top left and right empty, no sprite yet
			}
		}
		else {
			if (!left) {
				if (!right)
					return TileSet::MIDDLE; // top and bottom is empty, no sprite yet
				else
					return TileSet::MIDDLE; // top bottom and right is empty, no sprite yet
			}
			else {
				if (!right)
					return TileSet::MIDDLE; // top bottom and left is empty, no sprite yet
				else
					return TileSet::MIDDLE; // top bottom left and right is empty, no sprite yet
			}
		}
	}
}

void WorldMap::clearMap(IGraphics* Graphics, std::shared_ptr<b2World> gameWorld) {
	for (int i = 0; i < 16 ; i++) {
		for (int j = 0; j < 28 ; j++) {
			if (worldMap[i][j].tileBody != nullptr) {
				gameWorld->DestroyBody(worldMap[i][j].tileBody);
				Graphics->deleteRenderable(worldMap[i][j].tileRenderable);

				worldMap[i][j].tileBody = nullptr;
				worldMap[i][j].tileRenderable.reset();
			}
		}
	}
}