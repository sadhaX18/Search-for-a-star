#pragma once

class CollisionHandler : public b2ContactListener {
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};