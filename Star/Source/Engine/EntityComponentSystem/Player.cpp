#include "Entity.h"
#include "Player.h"
#include "box2d/box2d.h"
#include "../IGraphics.h"
#include "../IRenderable.h"

#include "Engine/EntityComponentSystem/Resources.h"
#include "InputComponent.h"

Player::Player() : Entity(EntityType::PLAYER, 5) {}
Player::~Player() {}

void Player::initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics,
	std::shared_ptr<b2World> gameWorld, float x, float y) {
	entityID = id;

	renderable = graphics->CreateBillboard(resources->getPlayerSprite());

	renderable->SetScale(0.25f, 0.25f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x / 100.0f, y / 100.0f);
	bodyDef.fixedRotation = true;
	physics = gameWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(20.0f / 100.0f, 20.0f / 100.0f);

	b2CircleShape circle;
	circle.m_radius = 20.0f / 100.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	physics->CreateFixture(&fixtureDef);

	//physics->SetUserData(this);

	// Syncing physics and graphics locations
	b2Transform transform = physics->GetTransform();

	renderable->SetPosition(transform.p.x * 100.0f, transform.p.y * 100.0f);
	renderable->SetRotation(transform.q.GetAngle());

	input = std::make_shared<InputComponent>();
}