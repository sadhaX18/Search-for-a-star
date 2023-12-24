#include "Game.h"

#include "Engine/IGraphics.h"
#include "Engine/ITexture.h"
#include "Engine/IShader.h"
#include "Engine/IRenderable.h"
#include "Engine/IInput.h"
#include "Engine/EntityComponentSystem/Entity.h"

#include <ctime>
#include <math.h>

#define CLAMP(v, x, y) fmin(fmax(v, x), y)

constexpr float Pie = 3.14159265359f;
constexpr float TwoPies = Pie * 2.0f;
constexpr float DeltaTime = 0.016f;
constexpr float SpinSpeed = 0.1f;
constexpr float WinTolerance = Pie / 10.0f;

IApplication* GetApplication(IGraphics* Graphics, IInput* Input)
{
	return new Game(Graphics, Input);
}

Game::Game(IGraphics* GraphicsIn, IInput* InputIn) : IApplication(GraphicsIn, InputIn), Entities(), SelectedRing(), State()
{
	Arrow = std::make_shared<Entity>();

	//init gameWorld
	b2Vec2 gravity(0.0f, 10.0f);
	gameWorld = std::make_shared<b2World>(gravity);

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
	ITexture* InnerTexture = Graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* MiddleTexture = Graphics->CreateTexture(L"Resource/Textures/MiddleRing.dds");
	ITexture* OuterTexture = Graphics->CreateTexture(L"Resource/Textures/OuterRing.dds");
	ITexture* ArrowTexture = Graphics->CreateTexture(L"Resource/Textures/Arrow.dds");
	IShader* InnerShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", InnerTexture);
	IShader* MiddleShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", MiddleTexture);
	IShader* OuterShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", OuterTexture);
	IShader* ArrowShader = Graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", ArrowTexture);
	
	// Loading map
	// Base floor
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -100.0f);
	b2Body* groundBody = gameWorld->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);


	// dynamic body to be transferred to player
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = gameWorld->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);



	// Loading all entities

	//Rings[static_cast<unsigned int>(RingLayer::Inner)] = Graphics->CreateBillboard(InnerShader);
	//Rings[static_cast<unsigned int>(RingLayer::Middle)] = Graphics->CreateBillboard(MiddleShader);
	//Rings[static_cast<unsigned int>(RingLayer::Outer)] = Graphics->CreateBillboard(OuterShader);
	//Arrow = Graphics->CreateBillboard(ArrowShader);


	{
		Entity tempEntity;
		tempEntity.initEntity(EntityType::RING, 0, InnerShader, Graphics, gameWorld);
		std::shared_ptr<Entity> temp = std::make_shared<Entity>(tempEntity);
		Entities.push_back(temp);
	}
	{
		Entity tempEntity;
		tempEntity.initEntity(EntityType::RING, 1, MiddleShader, Graphics, gameWorld);
		std::shared_ptr<Entity> temp = std::make_shared<Entity>(tempEntity);
		Entities.push_back(temp);
	}
	{
		Entity tempEntity;
		tempEntity.initEntity(EntityType::RING, 2, OuterShader, Graphics, gameWorld);
		std::shared_ptr<Entity> temp = std::make_shared<Entity>(tempEntity);
		Entities.push_back(temp);
	}

	Arrow->initEntity(EntityType::ARROW, 3, ArrowShader, Graphics, gameWorld);

	// Setting initial game state
	std::srand(static_cast<unsigned int>(std::time(0)));

	SelectedRing = RingLayer::Outer;
	State = GameState::Setup;

	return true;
}

void Game::Update()
{
	// If mode is Setup game then set each ring to a random rotation
	if (State == GameState::Setup)
	{
		SetupEachRing();
		State = GameState::Playing;
	}

	// If mode is Playing then read controller input and manage which ring is selected, the rotation of each ring and waiting for select to confirm positions 
	if (State == GameState::Playing)
	{
		UpdateRingSelection();
		UpdateSelectedRingRotation();
		UpdateRingTestSelection();

		// Input update
		// Physics update
		// Game logics (ex colliding with enemy, interacting with end goal door or collecting coins)


		// Syncing renderable and physics locations

		std::vector<std::shared_ptr<Entity>>::iterator it;
		for (it = Entities.begin(); it != Entities.end(); it++) {
			(*it)->syncGraphics();
		}
		Arrow->syncGraphics();
	}

	// If mode is Test then check to see if the rings are in their correct positions, play a noise corresponding to how close the player is 
	if (State == GameState::Test)
	{
		TestRingSolution();
		State = GameState::Setup;
	}

	if (State == GameState::Paused) {

	}
}

void Game::Cleanup()
{

}

void Game::SetupEachRing()
{
	for (unsigned int Ring = 0; Ring < NumberOfRings; ++Ring)
	{
		Entities.at(Ring)->getRenderable()->SetRotation(static_cast<float>(fmod(rand(), Pie)));
		Entities.at(Ring)->syncPhysics();
	}

	Arrow->getRenderable()->SetRotation(static_cast<float>(fmod(rand(), Pie)));
	Arrow->syncPhysics();
}

void Game::UpdateRingSelection()
{
	int selectionChange = 0;

	if (Input->IsPressed(InputAction::ShoulderButtonLeft))
	{
		// Change ring selection towards outer
		selectionChange = -1;
	}
	else if (Input->IsPressed(InputAction::ShoulderButtonRight))
	{
		// Change ring selection towards inner
		selectionChange = 1;
	}
		
	SelectedRing = static_cast<RingLayer>(CLAMP(static_cast<int>(SelectedRing) + selectionChange, 0, NumberOfRings - 1));
}

void Game::UpdateSelectedRingRotation()
{
	float delta = Input->GetValue(InputAction::RightStickXAxis) * SpinSpeed * DeltaTime;
	float rotation = Entities.at(static_cast<int>(SelectedRing))->getRenderable()->GetTransform().Rotation;
	float newRotation = static_cast<float>(fmod(rotation + delta, TwoPies));
	Entities.at(static_cast<int>(SelectedRing))->getRenderable()->SetRotation(newRotation);
}

void Game::UpdateRingTestSelection()
{
	if (Input->IsPressed(InputAction::DefaultSelect))
	{
		State = GameState::Test;
	}
}

void Game::TestRingSolution()
{
	float totalRotationDifference = 0.0f;
	float arrowRotation = Arrow->getRenderable()->GetTransform().Rotation + TwoPies;

	for (unsigned int Ring = 0; Ring < NumberOfRings; ++Ring)
	{
		totalRotationDifference += abs(arrowRotation - (Entities[Ring]->getRenderable()->GetTransform().Rotation + TwoPies));
	}

	float averageRotationDifference = totalRotationDifference / NumberOfRings;

	if (averageRotationDifference < WinTolerance)
	{
		// Win
	}
	else
	{
		// Lose
	}
}
