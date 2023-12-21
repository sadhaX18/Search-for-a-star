#pragma once
#include<memory>

class IRenderable;

enum class EntityType
{
	UNDEFINED = -1,
	ARROW = 0,
	RING = 1
};

class Entity {
public:
	Entity();
	Entity(EntityType type,int id);
	virtual ~Entity();
	
	void initEntity(EntityType type, int id, IShader* shader, IGraphics* graphics);

	std::shared_ptr<IRenderable> getRenderable() { return renderable; }


private:
	EntityType entityType;
	int entityID;
	std::shared_ptr<IRenderable> renderable; // position component??

};