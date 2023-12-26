#pragma once
class Game;
class Command {
public:
	virtual ~Command() {};
	virtual void execute(Game* game) = 0;
};
class PauseCommand :public Command {
public:
	void execute(Game* game) override;
};
class MoveRightCommand :public Command {
	void execute(Game* game) override;
};
class MoveLeftCommand :public Command {
	void execute(Game* game) override;
};
class JumpCommand :public Command {
	void execute(Game* game) override;
};
class FallCommand :public Command {
	void execute(Game* game) override;
};