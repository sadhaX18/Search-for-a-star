
#pragma once

#include <vector>
#include <memory>
#include <list>
#include "Engine/IApplication.h"

class IGraphics;
class ITexture;
class Scene;
class IShader;
class IRenderable;
class StaticEntity;
class Player;
class WorldMap;
class b2World;
class Resources;

enum GameState { Setup, Playing, SceneChange, NumModes, Paused, Defeated, ResetLVL };

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

	void clearUI();

private:

	bool paused = false;

	int lives = 3;

	GameState State;

	std::shared_ptr<Resources> resources;

	std::shared_ptr<Scene> currentScene;

	// Basic UI

	std::list<std::shared_ptr<IRenderable>> UIRenderables;

};