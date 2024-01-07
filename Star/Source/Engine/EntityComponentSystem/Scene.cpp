#include "Game/Game.h"
#include "box2d/box2d.h"
#include "Scene.h"

#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Engine/EntityComponentSystem/Entity.h"
#include "Engine/EntityComponentSystem/Player.h"
#include "Engine/EntityComponentSystem/StaticEntity.h"

#include "Engine/EntityComponentSystem/Resources.h"

#include "Engine/EntityComponentSystem/Command.h"
#include "Engine/EntityComponentSystem/InputComponent.h"
#include "Engine//EntityComponentSystem/CollisionHandler.h"

#include "Game/WorldMap.h"

#include <ctime>
#include <math.h>

Scene::Scene(IGraphics* Graphics, SceneType scene) : Graphics(Graphics), scene(scene) {

	player = new Player();
	entities = std::make_shared<std::list<StaticEntity*>>();

	//init gameWorld
	b2Vec2 gravity(0.0f, -100.0f);
	gameWorld = std::make_shared<b2World>(gravity);

	gameWorld->SetContactListener(new CollisionHandler());

	switch (scene) {
	case SceneType::MENU:
		mapGenerator = std::make_shared<WorldMap>(Graphics);
		break;
	default:
		{
		int temp[16][28] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
		mapGenerator = std::make_shared<WorldMap>(Graphics, temp); }
		break;
	}
}

Scene::~Scene() {}

void Scene::ClearScene() {
	// Delete player
	gameWorld->DestroyBody(player->getPhysicsComponent());
	Graphics->deleteRenderable(player->getRenderable());
	// Delete Entities
	auto it = entities->begin();
	while (it != entities->end()) {
		gameWorld->DestroyBody((*it)->getPhysicsComponent());
		Graphics->deleteRenderable((*it)->getRenderable());
		delete (*it);
		entities->erase(it);
	}
}

void Scene::SetupScene(std::shared_ptr<Resources> resources) {
	// Load map
	std::list<StaticEntity*> mapEntities = mapGenerator->initMap(Graphics, gameWorld, resources);

	for (auto it = mapEntities.begin(); it != mapEntities.end(); it++) {
		entities->push_back((*it));
		(*it)->getPhysicsComponent()->SetUserData(*it);
	}

	// initialize player
	player->initEntity(EntityType::PLAYER, 5, resources, Graphics, gameWorld, 0.0f, 0.0f);
	player->getPhysicsComponent()->SetUserData(player);
}

void Scene::UpdateScene(IInput* Input) {
	// Input update
	std::vector<std::shared_ptr<Command>> commands = player->getInputComponent()->handleInput(Input);
	if (!commands.empty()) {
		for (auto it = commands.begin(); it != commands.end(); it++) {
			(*it)->execute(this);
		}
	}

	// Physics update
	float timeStep = 1.0f / 60.0f;
	gameWorld->Step(timeStep, 6, 2);

	// Game logics (ex colliding with enemy, interacting with end goal door or collecting coins)


	// Deleting entities
	auto it = entities->begin();
	while (it != entities->end()) {
		if ((*it)->isDelete()) {
			auto type = (*it)->getEntityType();
			switch (type) {
			case EntityType::DOOR:
				// static_cast<StaticEntity*>(*it)->deleteEntity();
				// delete physics and graphics components in their respective systems
				gameWorld->DestroyBody((*it)->getPhysicsComponent());
				Graphics->deleteRenderable((*it)->getRenderable());
				delete (*it);
				break;
			default:
				break;
			}
			it = entities->erase(it);
		}
		else {
			it++;
		}
	}

	// Syncing renderable and physics locations (Graphics update)
	player->syncGraphics();
}