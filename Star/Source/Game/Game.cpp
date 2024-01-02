#include "Game.h"
#include "box2d/box2d.h"

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

#include "WorldMap.h"

#include <ctime>
#include <math.h>

IApplication* GetApplication(IGraphics* Graphics, IInput* Input)
{
	return new Game(Graphics, Input);
}

Game::Game(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), State()
{
	player = std::make_shared<Player>();
	resources = std::make_shared<Resources>();
	entities = std::make_shared<std::list<StaticEntity>>();

	//init gameWorld
	b2Vec2 gravity(0.0f, -10.0f);
	gameWorld = std::make_shared<b2World>(gravity);

	gameWorld->SetContactListener(new CollisionHandler());

	mapGenerator = std::make_shared<WorldMap>(Graphics);

}

Game::~Game()
{
}

bool Game::IsValid()
{
	return true;
}

bool Game::Load()
{
	// Loading all textures
	resources->loadResources(Graphics);

	// Setting initial game state
	std::srand(static_cast<unsigned int>(std::time(0)));
	State = GameState::Setup;

	return true;
}

void Game::Update()
{
	// Anything needed to be done to initialize scene
	if (State == GameState::Setup)
	{
		// Load map
		std::list<StaticEntity> mapEntities = mapGenerator->initMap(Graphics, gameWorld, resources);

		for (auto it = mapEntities.begin(); it != mapEntities.end(); it++) {
			entities->push_back((*it));
			(*it).getPhysicsComponent()->SetUserData(&it);
		}

		// initialize player
		player->initEntity(EntityType::PLAYER, 5, resources, Graphics, gameWorld, 0.0f, 0.0f);
		player->getPhysicsComponent()->SetUserData(player.get());

		// initialize game components
		State = GameState::Playing;
	}

	// If mode is Playing then read controller input and manage which ring is selected, the rotation of each ring and waiting for select to confirm positions 
	if (State == GameState::Playing)
	{
		// Input update
		std::vector<std::shared_ptr<Command>> commands = player->getInputComponent()->handleInput(Input);
		if (!commands.empty()) {
			for (auto it = commands.begin(); it != commands.end(); it++) {
				(*it)->execute(this);
			}
		}

		// Physics update
		float timeStep = 1.0f / 600.0f;
		gameWorld->Step(timeStep, 6, 2);

		// Game logics (ex colliding with enemy, interacting with end goal door or collecting coins)



		// Syncing renderable and physics locations (Graphics update)
		player->syncGraphics();
	}

	// Anything to be done for switching scenes { deleting current scene}
	if (State == GameState::SceneChange)
	{
		// Delete scene
		// Load next scene
		State = GameState::Setup;
	}

	if (State == GameState::Paused) {
		if (Input->IsPressed(DefaultSelect))
			State = GameState::Playing;
	}
}

void Game::Cleanup()
{

}