#pragma once
#include <memory>
#include <list>

class b2World;
class IInput;
class WorldMap;
class Entity;
class Player;
class StaticEntity;
class IGraphics;
class Resources;

enum SceneType {
	MENU,
	LVL1,
	LVL2,
	LVL3
};

class Scene {
public:
	Scene(IGraphics* Graphics, SceneType scene);
	~Scene();

	void SetupScene(std::shared_ptr<Resources> resources);
	void UpdateScene(IInput* Input);
	void ClearScene();

	Player* getPlayer() { return player; }
	bool SceneChange() { return changeScene; }

private:

	IGraphics* Graphics;

	SceneType scene;
	Player* player;
	std::shared_ptr<std::list<StaticEntity*>> entities;
	std::shared_ptr<WorldMap> mapGenerator;
	std::shared_ptr<b2World> gameWorld;

	std::shared_ptr<Scene> nextScene;

	bool changeScene = false;
};