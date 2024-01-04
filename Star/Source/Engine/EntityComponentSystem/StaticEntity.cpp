#include "Engine/EntityComponentSystem/Entity.h"
#include "box2d/box2d.h"
#include "Engine/IGraphics.h"
#include "Engine/IRenderable.h"

#include "Engine/EntityComponentSystem/Resources.h"
#include "StaticEntity.h"

StaticEntity::StaticEntity() : Entity::Entity() {}

void StaticEntity::initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics,
	std::shared_ptr<b2World> gameWorld, float x, float y) {
	
	entityID = id;
	entityType = type;
	if (type == EntityType::SPIKE) {
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(x / 100.0f, (y - 17.5f) / 100.0f);
		physics = gameWorld->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(35.0f / 100.0f, 17.5f / 100.0f);
		physics->CreateFixture(&groundBox, 0.0f);

		// graphics object
		renderable = graphics->CreateBillboard(resources->getSpikeSprite());
	}
	else if (type == EntityType::DOOR) {
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(x / 100.0f, (y + 35.0f) / 100.0f);
		physics = gameWorld->CreateBody(&groundBodyDef);
		b2PolygonShape groundBox;
		groundBox.SetAsBox(35.0f / 100.0f, 70.0f / 100.0f);
		physics->CreateFixture(&groundBox, 0.0f);

		physics->GetFixtureList()->SetSensor(true);

		// graphics object
		renderable = graphics->CreateBillboard(resources->getDoorSprite());
	}

	//physics->SetUserData(this);

	// Syncing physics and graphics locations
	b2Transform transform = physics->GetTransform();

	renderable->SetPosition(transform.p.x * 100.0f, transform.p.y * 100.0f);
	renderable->SetRotation(transform.q.GetAngle());

}