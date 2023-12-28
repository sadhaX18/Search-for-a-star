#include "box2d/box2d.h"
#include "Engine/IRenderable.h"
#include "Engine/IShader.h"
#include "Engine/ITexture.h"
#include "Engine/EntityComponentSystem/Resources.h"
#include "WorldMap.h"

Tile::Tile() : tileBody(nullptr) {}
Tile::~Tile() {} // Not deleting tileBody here, will be automatically deleted when world is deleted at scene change

WorldMap::WorldMap(IGraphics* graphics) {}

void WorldMap::initMap(IGraphics* graphics, std::shared_ptr<b2World> gameWorld, std::shared_ptr<Resources> resources) {
	for (int i = 0; i < 16; i++) {
		float y = +505.0f - (i * 70.0f);
		for (int j = 0; j < 28; j++) {
			float x = -925.0f + (j * 70.0f);
			if (mapDef[i][j] == 1) {
				// physics object
				Tile temp;
				b2BodyDef groundBodyDef;
				groundBodyDef.position.Set(x / 100.0f, y / 100.0f);
				temp.tileBody = gameWorld->CreateBody(&groundBodyDef);
				b2PolygonShape groundBox;
				groundBox.SetAsBox(35.0f / 100.0f, 35.0f / 100.0f);
				temp.tileBody->CreateFixture(&groundBox, 0.0f);

				// graphics object
				temp.tileRenderable = graphics->CreateBillboard(resources->getTileMap()->at(getTileSetType(i, j)));

				// Syncing physics and graphics locations
				b2Transform transform = temp.tileBody->GetTransform();

				temp.tileRenderable->SetPosition(transform.p.x * 100.0f, transform.p.y * 100.0f);
				temp.tileRenderable->SetRotation(transform.q.GetAngle());

				worldMap[i][j] = temp;
			}
		}
	}
}

TileSet WorldMap::getTileSetType(int i, int j) {
	// 1-> tile 0-> empty
	bool left = false, right = false, top = false, bottom = false; // true => empty
	
	if (i != 0 && mapDef[i - 1][j] == 0)
		bottom = true;
	if (j != 0 && mapDef[i][j-1] == 0)
		left = true;
	if (i != 15 && mapDef[i + 1][j] == 0)
		top = true;
	if (j != 28 && mapDef[i][j+1] == 0)
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