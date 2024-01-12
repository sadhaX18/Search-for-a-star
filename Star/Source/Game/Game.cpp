#include "Game.h"
#include "box2d/box2d.h"
#include "Engine/EntityComponentSystem/Scene.h"

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
	resources = std::make_shared<Resources>();	

	currentScene = std::make_shared<Scene>(Graphics, SceneType::MENU);
}

Game::~Game() {}

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
		// SetupScene
		currentScene->SetupScene(resources);

		State = GameState::Playing;
	}

	// If mode is Playing then read controller input and manage which ring is selected, the rotation of each ring and waiting for select to confirm positions 
	if (State == GameState::Playing)
	{
		currentScene->UpdateScene(Input);
		if (currentScene->SceneChange() || currentScene->getResetLVL()) {
			State = GameState::SceneChange;
		}
	}

	// Anything to be done for switching scenes { deleting current scene}
	if (State == GameState::SceneChange)
	{
		// Delete scene
		currentScene->ClearScene();

		// Load next scene
		if(!currentScene->getResetLVL())
			currentScene->SwitchScene();
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