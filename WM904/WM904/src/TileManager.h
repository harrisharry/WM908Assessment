#pragma once

#include "Entity.h"
#include "DStructures.h"

class TileManager {
private:
	GameObject** tileMap;
	SpriteDefinition** tileDefsPointer; //Points to the array of SpriteDefinition pointers.

public:
	TileManager(SpriteDefinition** defs) {

		tileDefsPointer = defs;
		
	}

	void LoadMap(std::string fileToLoad, DataStructures::List<GameObject*>& listToAdd);
	void Reload();
	void ClearMap();

};