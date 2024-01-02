#pragma once
#include<memory>

class IRenderable;
class b2Body;
class b2World;
class IShader;
class IGraphics;
class Resources;

enum class EntityType
{
	UNDEFINED = -1,
	KEY = 0,
	DOOR = 1,
	SPIKE = 2,
	PLAYER = 3
};

class Entity {
public:
	Entity();
	Entity(EntityType type,int id);
	virtual ~Entity();

	void syncGraphics();
	void syncPhysics();
	
	virtual void initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics, 
		std::shared_ptr<b2World> gameWorld, float x = 0.0f, float y = 0.0f) = 0;

	std::shared_ptr<IRenderable> getRenderable() { return renderable; }

	b2Body* getPhysicsComponent() { return physics; }

	EntityType getEntityType() { return entityType; }

protected:
	EntityType entityType;
	int entityID;
	std::shared_ptr<IRenderable> renderable; // Graphics component
	b2Body* physics; // physics component - using raw pointer as Box2D does not return smart pointers
};