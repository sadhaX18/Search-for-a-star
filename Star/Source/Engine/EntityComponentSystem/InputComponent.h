#pragma once
#include<memory>
#include<vector>
#include<memory>
#include<map>

enum Action {
	MOVE_RIGHT,
	MOVE_LEFT,
	JUMP,
	FALL,
	PAUSE
};

class Command;
class IInput;
enum InputAction;
class InputComponent {
public:
	InputComponent();
	std::vector<std::shared_ptr<Command>>& handleInput(IInput* input);
private:

	std::vector<std::shared_ptr<Command>> simultaneousCommands;
	std::shared_ptr<Command> moveRightCommand;
	std::shared_ptr<Command> moveLeftCommand;
	std::shared_ptr<Command> jumpCommand;
	std::shared_ptr<Command> fallCommand;
	std::shared_ptr<Command> pauseCommand;

	std::map<Action, InputAction> boundCommands;

};