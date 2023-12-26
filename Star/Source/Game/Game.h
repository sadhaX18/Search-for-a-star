
#pragma once

#include <vector>
#include <memory>
#include "Engine/IApplication.h"

class IGraphics;
class ITexture;
class IShader;
class IRenderable;
class Entity;
class Player;
class WorldMap;
class b2World;

enum RingLayer { Outer, Middle, Inner, NumRings };
enum GameState { Setup, Playing, Test, NumModes, Paused };
static const unsigned int NumberOfRings = static_cast<int>(NumRings);

class Game : public IApplication
{
public:

	Game(IGraphics* Graphics, IInput* InputIn);
	virtual ~Game();

	virtual bool IsValid();
	virtual bool Load();
	virtual void Update();
	virtual void Cleanup();

	void setState(GameState state) { State = state; }
	GameState getState() const { return State; }

	std::shared_ptr<Player> getPlayer() { return player; }

private:

	void SetupEachRing();
	void UpdateRingSelection();
	void UpdateSelectedRingRotation();
	void UpdateRingTestSelection();
	void TestRingSolution();

	// IRenderable* Rings[NumberOfRings];
	std::shared_ptr<Entity> Arrow;
	std::vector<std::shared_ptr<Entity>> Entities;
	RingLayer SelectedRing;
	GameState State;

	std::shared_ptr<Player> player;
	std::shared_ptr<WorldMap> mapGenerator;
	std::shared_ptr<b2World> gameWorld;
};

