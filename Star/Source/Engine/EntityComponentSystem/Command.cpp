#include "Game/Game.h"
#include "Command.h"

void PauseCommand::execute(Game* game) {
	if (game->getState() == GameState::Paused)
		game->setState(GameState::Playing);
	else
		game->setState(GameState::Paused);
}

void MoveRightCommand::execute(Game* game) {

}
void MoveLeftCommand::execute(Game* game) {

}
void JumpCommand::execute(Game* game) {

}
void CrouchCommand::execute(Game* game) {

}