#include "Command.h"
#include "Engine/IInput.h"
#include "InputComponent.h"

InputComponent::InputComponent() : moveRightCommand{ std::make_shared<MoveRightCommand>() } {
	moveLeftCommand = std::make_shared<MoveLeftCommand>();
	jumpCommand = std::make_shared<JumpCommand>();
	crouchCommand = std::make_shared<CrouchCommand>();

	boundCommands.insert({ MOVE_RIGHT, DirectionPadRight });
	boundCommands.insert({ MOVE_LEFT, DirectionPadLeft });
	boundCommands.insert({ JUMP, DirectionPadTop });
	boundCommands.insert({ CROUCH, DirectionPadBottom });
	boundCommands.insert({ PAUSE, DefaultSelect });
}
std::vector<std::shared_ptr<Command>>& InputComponent::handleInput(IInput* input) {
	simultaneousCommands.clear();

	if (input->IsPressed(boundCommands.at(MOVE_RIGHT))) {
		simultaneousCommands.push_back(moveRightCommand);
	}
	if (input->IsPressed(boundCommands.at(MOVE_LEFT))) {
		simultaneousCommands.push_back(moveLeftCommand);
	}
	if (input->IsPressed(boundCommands.at(JUMP))) {
		simultaneousCommands.push_back(jumpCommand);
	}
	if (input->IsPressed(boundCommands.at(CROUCH))) {
		simultaneousCommands.push_back(crouchCommand);
	}
	if (input->IsPressed(boundCommands.at(PAUSE))) {
		simultaneousCommands.push_back(pauseCommand);
	}
	return simultaneousCommands;
}