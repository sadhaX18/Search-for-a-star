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

		if (currentScene->getSceneType() == SceneType::MENU) {
			lives = 3;
			UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::MAIN_MENU),true));
		}

		State = GameState::Playing;
	}

	// If mode is Playing then read controller input and manage which ring is selected, the rotation of each ring and waiting for select to confirm positions 
	if (State == GameState::Playing)
	{
		// UI
		if (currentScene->getSceneType() == MENU) {
			if (Input->IsPressed(DefaultSelect)) {
				currentScene->ChangeScene();
				clearUI();
			}
		}

		currentScene->UpdateScene(Input);

		// Checking for scene changes
		if (currentScene->getPlayerHit()) {
			if (lives > 0) {
				lives--;
				State = GameState::ResetLVL;
				// Initialize UI elements
				UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::LEVEL_FAILED), true));
			}
			else {
				State = GameState::Defeated;
				// Initialize UI elements

			}
		}
		if (currentScene->SceneChange()) {
			State = GameState::SceneChange;
		}
	}

	if (State == GameState::ResetLVL) {
		if (Input->IsPressed(DefaultSelect)) {
			clearUI();
			State = GameState::SceneChange;
		}
	}
	// To be implemented
	if (State == GameState::Defeated) {
		if (Input->IsPressed(DefaultSelect)) {
			State = GameState::SceneChange;
			currentScene->SwitchScene(MENU);
		}
	}

	// Anything to be done for switching scenes { deleting current scene}
	if (State == GameState::SceneChange)
	{
		// Delete scene
		currentScene->ClearScene();

		// Load next scene
		if(currentScene->SceneChange())
			currentScene->NextScene();

		State = GameState::Setup;
	}

	if (State == GameState::Paused) {
		if (Input->IsPressed(DefaultSelect)) {
			State = GameState::Playing;
			clearUI();
		}
	}
}

void Game::Cleanup()
{

}

void Game::clearUI() {
	while (!UIRenderables.empty()) {
		Graphics->deleteUIRenderable(UIRenderables.front());
		UIRenderables.pop_front();
	}
}