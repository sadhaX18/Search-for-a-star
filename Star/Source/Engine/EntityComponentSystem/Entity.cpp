#include "box2d/box2d.h"
#include "Entity.h"
#include "../IGraphics.h"
#include "../IRenderable.h"
#include "../IShader.h"

Entity::Entity() : entityType(EntityType::UNDEFINED), entityID(0), physics(nullptr) {}
Entity::Entity(EntityType type, int id) : entityType(type), entityID(id), physics(nullptr) {}

Entity::~Entity() {}

void Entity::syncGraphics() {
	b2Transform transform = physics->GetTransform();

	renderable->SetPosition(transform.p.x * 100.0f, transform.p.y * 100.0f);
	renderable->SetRotation(transform.q.GetAngle());
}

void Entity::syncPhysics() {
	auto transform = renderable->GetTransform();
	physics->SetTransform(b2Vec2(transform.PositionX / 100.0f, transform.PositionY / 100.0f), transform.Rotation);
}