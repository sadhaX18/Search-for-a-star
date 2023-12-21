#include "../IGraphics.h"
#include "Entity.h"
#include "../IRenderable.h"

Entity::Entity() : entityType(EntityType::UNDEFINED), entityID(0) {}
Entity::Entity(EntityType type, int id) : entityType(type), entityID(id){}

Entity::~Entity() {}

void Entity::initEntity(EntityType type, int id, IShader* shader, IGraphics* graphics) {
	renderable = graphics->CreateBillboard(shader);
	entityType = type;
	entityID = id;
}