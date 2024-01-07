#pragma once
class Scene;
class Command {
public:
	virtual ~Command() {};
	virtual void execute(Scene* scene) = 0;
};
class MoveRightCommand :public Command {
	void execute(Scene* scene) override;
};
class MoveLeftCommand :public Command {
	void execute(Scene* scene) override;
};
class JumpCommand :public Command {
	void execute(Scene* scene) override;
};
class FallCommand :public Command {
	void execute(Scene* scene) override;
};