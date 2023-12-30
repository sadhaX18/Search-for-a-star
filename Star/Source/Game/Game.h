
#pragma once

#include <vector>
#include <memory>
#include <list>
#include "Engine/IApplication.h"

class IGraphics;
class ITexture;
class IShader;
class IRenderable;
class StaticEntity;
class Player;
class WorldMap;
class b2World;
class Resources;

enum GameState { Setup, Playing, SceneChange, NumModes, Paused };

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

	GameState State;

	std::shared_ptr<Resources> resources;

	// Scene 
	std::shared_ptr<Player> player;
	std::shared_ptr<std::list<StaticEntity>> entities;
	std::shared_ptr<WorldMap> mapGenerator;
	std::shared_ptr<b2World> gameWorld;
};

