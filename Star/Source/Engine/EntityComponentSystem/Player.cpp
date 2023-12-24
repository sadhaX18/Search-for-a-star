#include "Entity.h"
#include "Player.h"
#include "box2d/box2d.h"
#include "../IGraphics.h"
#include "../IRenderable.h"

Player::Player() : Entity(EntityType::PLAYER, 5) {}
Player::~Player() {}

void Player::initEntity(EntityType type, int id, IShader* shader, IGraphics* graphics,
	std::shared_ptr<b2World> gameWorld, float x, float y) {
	entityID = id;

	renderable = graphics->CreateBillboard(shader);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	physics = gameWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(80.0f, 80.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	physics->CreateFixture(&fixtureDef);
}