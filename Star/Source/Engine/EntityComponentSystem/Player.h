#pragma once
class Entity;
class IShader;
class IGraphics;
class b2World;
class InputComponent;

class Player : public Entity {
public:
	const int maxSpeed = 100;
	const int startingHealth = 60;

	Player();
	~Player();

	void initEntity(EntityType type, int id, std::shared_ptr<Resources> resources, IGraphics* graphics,
		std::shared_ptr<b2World> gameWorld, float x = 0.0f, float y = 0.0f) override;

	std::shared_ptr<InputComponent> getInputComponent() { return input; }

private:
	std::shared_ptr<InputComponent> input;
};