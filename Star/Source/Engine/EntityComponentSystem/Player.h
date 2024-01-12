#pragma once
class Entity;
class IShader;
class IGraphics;
class b2World;
class InputComponent;

class Player : public Entity {
public:

	Player();
	~Player();

	void initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics,
		std::shared_ptr<b2World> gameWorld, float x = 0.0f, float y = 0.0f) override;

	std::shared_ptr<InputComponent> getInputComponent() { return input; }

	bool isHit() { return hit; }
	void hitSpike() { hit = true; }

private:
	bool hit = false;
	std::shared_ptr<InputComponent> input;
};