
#include "World.h"

World::World(sf::Vector2f gravity) : gravity(gravity)
{
}

void World::AddGameObject(GameObject& obj)
{
    objects.push_back(&obj);
}

void World::RemoveGameObject(GameObject& obj)
{
    objects.remove(&obj);
}

void World::UpdatePhysics(float deltaTime)
{

    // Clear collision states after all updates and collisions have been handled
    for (auto& obj : objects) {
        obj->clearCollision();
    }

    // Apply gravity to all non-static objects and update their physics
    for (auto& obj : objects) {
        if (!obj->getStatic()) {
            obj->move(gravity * obj->getMass() * deltaTime);
        }
        // Update object physics
        obj->UpdatePhysics(&gravity, deltaTime);
        obj->update(deltaTime);
    }
    // Handle collision checks
    for (auto it1 = objects.begin(); it1 != objects.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != objects.end(); ++it2) {
            if ((*it1)->checkCollision(*it2)) {
                // Call collision response here if needed
                //std::cout << "Collision is happening\n";
                (*it1)->collisionResponse(*it2);
                (*it2)->collisionResponse(*it1);
            }
        }
    }
}


