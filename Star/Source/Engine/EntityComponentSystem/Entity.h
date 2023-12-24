#pragma once
#include<memory>

class IRenderable;
class b2Body;

enum class EntityType
{
	UNDEFINED = -1,
	ARROW = 0,
	RING = 1,
	PLAYER = 2
};

class Entity {
public:
	Entity();
	Entity(EntityType type,int id);
	virtual ~Entity();

	void syncGraphics();
	void syncPhysics();

	virtual void Update();
	
	virtual void initEntity(EntityType type, int id, IShader* shader, IGraphics* graphics, 
		std::shared_ptr<b2World> gameWorld, float x = 0.0f, float y = 0.0f);

	std::shared_ptr<IRenderable> getRenderable() { return renderable; }


protected:
	EntityType entityType;
	int entityID;
	std::shared_ptr<IRenderable> renderable; // Graphics component
	b2Body* physics; // physics component - using raw pointer as Box2D does not return smart pointers
};