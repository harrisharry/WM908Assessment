#include "PhysicsEngine.h"
#include <algorithm>

void PhysicsEngine::StartUp(DataStructures::List<GameObject*>& objects) {
	gameObjects = &objects;
} 
void PhysicsEngine::Update(float deltaTime) {
	//Foreach physics object, get their position and calculate their new position, to be used in drawing. 

	for (auto it = gameObjects->Begin(); it != gameObjects->End(); it++) {

		Collider* current = it->data->Collider();
		if (current == nullptr) {
			continue; 
		}
		for (auto it2 = gameObjects->Begin(); it2 != gameObjects->End(); it2++)
		{
			Collider* toCheck = it2->data->Collider();
			if (toCheck == nullptr) continue;
			if (current == toCheck) continue;
			if (current->CheckCollision(toCheck)) {
				
				current->ResolveCollision(toCheck, it2->data);
				it2->data->OnCollisionEnter(it->data);
				it->data->OnCollisionEnter(it2->data);
			}
		}

	}
	
}

void PhysicsEngine::Shutdown() {



}

