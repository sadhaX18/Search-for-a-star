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
	void increaseFloorContact() { floorContact++; }
	void decreaseFloorContact() { floorContact--; }
	int getFloorContact() { return floorContact; }

	void increaseLeftContact() { leftContact++; }
	void decreaseLeftContact() { leftContact--; }

	void increaseRightContact() { rightContact++; }
	void decreaseRightContact() { rightContact--; }

private:
	bool hit = false;

	int floorContact = 0, leftContact = 0, rightContact = 0;

	std::shared_ptr<InputComponent> input;
};