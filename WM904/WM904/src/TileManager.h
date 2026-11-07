#pragma once

#include "Entity.h"
#include "DStructures.h"

class TileManager {
private:
	Hero* _heroRef;
	ObjectFactory* facRef;
	GameObject** tileMap;
	SpriteDefinition** tileDefsPointer; //Points to the array of SpriteDefinition pointers.
	SpriteDefinition** spriteDefsPointer; //Points to the array of SpriteDefinition pointers.

public:
	TileManager(SpriteDefinition** defs,SpriteDefinition** spriteDefs) {

		tileDefsPointer = defs;
		spriteDefsPointer = spriteDefs;
		
	}
	void SetHeroRef(Hero* heroRef) {
		_heroRef = heroRef;
	}
	void SetFactory(ObjectFactory* fac) {
		facRef = fac;
	}

	void LoadMap(std::string fileToLoad, DataStructures::List<GameObject*>& listToAdd);
	void Reload();
	void ClearMap();

};