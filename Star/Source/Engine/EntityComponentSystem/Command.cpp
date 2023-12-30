#include "Game/Game.h"
#include "box2d/box2d.h"
#include "Entity.h"
#include "Player.h"
#include "Command.h"

void PauseCommand::execute(Game* game) {
	if (game->getState() == GameState::Paused)
		game->setState(GameState::Playing);
	else
		game->setState(GameState::Paused);
}

void MoveRightCommand::execute(Game* game) {
	game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(1000.0f, 0.0f), true);
}
void MoveLeftCommand::execute(Game* game) {
	game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(-1000.0f, 0.0f), true);
}
void JumpCommand::execute(Game* game) {
	game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(0.0f, 1000.0f), true);
}
void FallCommand::execute(Game* game) {
	game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(0.0f, -1000.0f), true);
}