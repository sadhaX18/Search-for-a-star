#include "Scene.h"
#include "box2d/box2d.h"
#include "Entity.h"
#include "Player.h"
#include "Command.h"

void MoveRightCommand::execute(Scene* scene) {
	//scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(10.0f, 0.0f), true);
	Player* temp = scene->getPlayer();
	temp->faceRight();

	b2Vec2 initVelocity = temp->getPhysicsComponent()->GetLinearVelocity();

	temp->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(1.0f, 0.0f));
}
void MoveLeftCommand::execute(Scene* scene) {
	//game->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(-10.0f, 0.0f), true);
	Player* temp = scene->getPlayer();
	temp->faceLeft();

	b2Vec2 initVelocity = temp->getPhysicsComponent()->GetLinearVelocity();

	temp->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(-1.0f,0.0f));
}
void JumpCommand::execute(Scene* scene) {
	b2Vec2 initVelocity = scene->getPlayer()->getPhysicsComponent()->GetLinearVelocity();
	if (scene->getPlayer()->getFloorContact() > 0) {
		scene->getPlayer()->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(0.0f, 20.0f));
	}
	else if (scene->getPlayer()->getLeftContact() > 0) {
		scene->getPlayer()->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(10.0f, 20.0f));
		//scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(200.0f, 100.0f), true);
	}
	else if (scene->getPlayer()->getRightContact() > 0) {
		scene->getPlayer()->getPhysicsComponent()->SetLinearVelocity(initVelocity + b2Vec2(-10.0f, 20.0f));
		//scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(-2000.0f, 100.0f), true);
	}
}
void FallCommand::execute(Scene* scene) {
	scene->getPlayer()->getPhysicsComponent()->ApplyForceToCenter(b2Vec2(0.0f, -20.0f), true);
}