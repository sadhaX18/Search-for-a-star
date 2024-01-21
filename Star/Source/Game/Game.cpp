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
	switch (State) {
	case Setup:
		// SetupScene
		currentScene->SetupScene(resources);
		if (currentScene->getSceneType() == SceneType::MENU) {
			lives = 3;
			UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::MAIN_MENU), true));
		}
		State = GameState::Playing;
		break;
	case Playing:
		// UI
		if (currentScene->getSceneType() == MENU) {
			if (Input->IsPressed(ButtonLeft)) {
				currentScene->ChangeScene();
				clearUI();
			}
		}
		else { // Pause
			if (Input->IsPressed(ButtonLeft)) {
				State = GameState::Paused;
				UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::PAUSED), true));
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
				UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::GAME_OVER), true));
			}
		}
		if (currentScene->SceneChange()) {
			if (currentScene->getSceneType() == LVL3) {
				State = GameWin;
				UIRenderables.push_back(Graphics->CreateBillboard(resources->getUIElements()->at(UIElement::GAME_WIN), true));
			}
			else
				State = GameState::SceneChange;
		}
		break;
	case ResetLVL:
		if (Input->IsPressed(ButtonLeft)) {
			clearUI();
			State = GameState::SceneChange;
		}
		break;
	case Defeated:
	case GameWin:
		if (Input->IsPressed(ButtonLeft)) {
			State = GameState::Setup;
			clearUI();
			currentScene->ClearScene();
			currentScene->SwitchScene(MENU);
		}
		break;
	case SceneChange:
		// Delete scene
		currentScene->ClearScene();

		State = GameState::Setup;
		// Load next scene
		if (currentScene->SceneChange()) {
			currentScene->NextScene();
		}
		break;
	case Paused:
		if (Input->IsPressed(ButtonLeft)) {
			State = GameState::Playing;
			clearUI();
		}
		break;

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