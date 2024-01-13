#include "box2d/box2d.h"
#include "CollisionHandler.h"
#include "Engine/EntityComponentSystem/Entity.h"
#include "Engine/EntityComponentSystem/Player.h"
#include "Engine/EntityComponentSystem/StaticEntity.h"

#include "Engine/IRenderable.h"

void CollisionHandler::BeginContact(b2Contact* contact) {
    b2BodyUserData bodyAData = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData bodyBData = contact->GetFixtureB()->GetBody()->GetUserData();

    //check if fixture A is player
    if (bodyAData.pointer != nullptr) {
        if (static_cast<Entity*>(bodyAData.pointer)->getEntityType() == EntityType::PLAYER)
        {
            Player* temp = static_cast<Player*>(bodyAData.pointer);
            if (bodyBData.pointer != nullptr) {
                EntityType type = static_cast<Entity*>(bodyBData.pointer)->getEntityType();
                if ( type == EntityType::DOOR) {
                    static_cast<Entity*>(bodyBData.pointer)->deleteEntity();
                }
                else if (type == EntityType::SPIKE) {
                    temp->hitSpike();
                }
            }
        }
    }
    //check if fixture B is player
    if (bodyBData.pointer != nullptr) {
        if (static_cast<Entity*>(bodyBData.pointer)->getEntityType() == EntityType::PLAYER)
        {
            if (static_cast<Entity*>(bodyBData.pointer)->getEntityType() == EntityType::PLAYER)
            {
                Player* temp = static_cast<Player*>(bodyBData.pointer);
                if (bodyAData.pointer != nullptr) {
                    EntityType type = static_cast<Entity*>(bodyAData.pointer)->getEntityType();
                    if (type == EntityType::DOOR) {
                        static_cast<Entity*>(bodyAData.pointer)->deleteEntity();
                        //temp->getRenderable()->SetScale(1.0f, 1.0f);

                    }
                    else if (type == EntityType::SPIKE) {
                        temp->hitSpike();
                    }
                }
            }
        }
    }
}
void CollisionHandler::EndContact(b2Contact* contact) {
    b2BodyUserData bodyAData = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData bodyBData = contact->GetFixtureB()->GetBody()->GetUserData();

    //check if fixture A is player
    if (bodyAData.pointer != nullptr) {
        if (static_cast<Entity*>(bodyAData.pointer)->getEntityType() == EntityType::PLAYER)
        {
            Player* temp = static_cast<Player*>(bodyAData.pointer);
            if (bodyBData.pointer != nullptr) {
                EntityType type = static_cast<Entity*>(bodyBData.pointer)->getEntityType();
                if (type == EntityType::SPIKE) {
                    temp->hitSpike();
                }
            }
        }
    }
    //check if fixture B is player
    if (bodyBData.pointer != nullptr)
    {
        if (static_cast<Entity*>(bodyBData.pointer)->getEntityType() == EntityType::PLAYER)
        {
            Player* temp = static_cast<Player*>(bodyBData.pointer);
            if (bodyAData.pointer != nullptr) {
                EntityType type = static_cast<Entity*>(bodyAData.pointer)->getEntityType();
                if (type == EntityType::SPIKE) {
                    temp->hitSpike();
                }
            }
        }
    }
}