#pragma once

class Entity;

class StaticEntity : public Entity {
public:
	StaticEntity();
	void initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics,
		std::shared_ptr<b2World> gameWorld, float x = 0.0f, float y = 0.0f) override;

private:
};