#pragma once
class Entity;
class IShader;
class IGraphics;
class b2World;
class InputComponent;

class Player : public Entity {
public:
	const int maxHealth = 100;
	const int startingHealth = 60;

	Player();
	~Player();

	void initEntity(EntityType type, int id, IShader* shader, IGraphics* graphics,
		std::shared_ptr<b2World> gameWorld, float x, float y) override;
private:
	std::shared_ptr<InputComponent> input;
};