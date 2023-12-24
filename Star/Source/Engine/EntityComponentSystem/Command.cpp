#include "Game/Game.h"
#include "Command.h"

void PauseCommand::execute(Game* game) {
	if (game->getState() == GameState::Paused)
		game->setState(GameState::Playing);
	else
		game->setState(GameState::Paused);
}