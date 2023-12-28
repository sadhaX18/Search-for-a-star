#pragma once
#include <memory>

class b2World;
class WorldMap;
class Entity;
class Player;

enum Scene {
	MENU,
	LVL1,
	LVL2,
	LVL3
};

class SceneManager {
public:

private:
	Scene scene;
	std::shared_ptr<Player> player;
	std::shared_ptr<WorldMap> mapGenerator;
	std::shared_ptr<b2World> gameWorld;
};