#include "Command.h"
#include "Engine/IInput.h"
#include "InputComponent.h"

InputComponent::InputComponent() : 
	moveRightCommand{ std::make_shared<MoveRightCommand>() },
	moveLeftCommand{ std::make_shared<MoveLeftCommand>() },
	jumpCommand{ std::make_shared<JumpCommand>() },
	fallCommand{ std::make_shared<FallCommand>() }, boundCommands() {

	boundCommands.insert(std::make_pair< Action, InputAction>(MOVE_RIGHT, DirectionPadRight));
	boundCommands.insert(std::make_pair< Action, InputAction>(MOVE_LEFT, DirectionPadLeft));
	boundCommands.insert(std::make_pair< Action, InputAction>(JUMP, ButtonBottom));
	boundCommands.insert(std::make_pair< Action, InputAction>(FALL, DirectionPadBottom));
}
std::vector<std::shared_ptr<Command>>& InputComponent::handleInput(IInput* input) {
	simultaneousCommands.clear();

	if (input->IsHeld(boundCommands.at(MOVE_RIGHT))) {
		simultaneousCommands.push_back(moveRightCommand);
	}
	if (input->IsHeld(boundCommands.at(MOVE_LEFT))) {
		simultaneousCommands.push_back(moveLeftCommand);
	}
	if (input->IsPressed(boundCommands.at(JUMP))) {
		simultaneousCommands.push_back(jumpCommand);
	}
	if (input->IsPressed(boundCommands.at(FALL))) {
		simultaneousCommands.push_back(fallCommand);
	}
	return simultaneousCommands;
}