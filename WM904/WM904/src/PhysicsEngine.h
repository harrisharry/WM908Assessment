#pragma once
#include "DStructures.h"
#include "Entity.h"

class PhysicsEngine
{
private:
	DataStructures::List<GameObject*>* gameObjects;

public :
	void StartUp(DataStructures::List<GameObject*>& objects);
	void Update(float deltaTime);
	void Shutdown();
};