#include "Scene.h"
#include "box2d/box2d.h"
#include "Entity.h"
#include "Player.h"
#include "Command.h"

void MoveRightCommand::execute(Scene* scene) {
	//scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(10.0f, 0.0f), true);

	b2Vec2 initVelocity = scene->getPlayer()->getPhysicsComponent()->GetLinearVelocity();

	scene->getPlayer()->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(1.0f, 0.0f));
}
void MoveLeftCommand::execute(Scene* scene) {
	//game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(-10.0f, 0.0f), true);

	b2Vec2 initVelocity = scene->getPlayer()->getPhysicsComponent()->GetLinearVelocity();

	scene->getPlayer()->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(-1.0f,0.0f));
}
void JumpCommand::execute(Scene* scene) {
	if (scene->getPlayer()->getFloorContact() > 0) {
		scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(0.0f, 200.0f), true);
	}
}
void FallCommand::execute(Scene* scene) {
	scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(0.0f, -20.0f), true);
}