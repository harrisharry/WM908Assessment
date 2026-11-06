#include "TileManager.h"
#include <fstream>

void TileManager::LoadMap(std::string fileToLoad, DataStructures::List<GameObject*>& listToAdd) {

	std::ifstream fileIn(fileToLoad);

	if (!fileIn.is_open()) {
		std::cout << "File did not open\n";
	}

	std::string line;

	int xSize = 0;
	int ySize = 0;

	//First two values are the world size.
	fileIn >> xSize; ////Read the x size of the map
	fileIn >> ySize; //Read the y size of the map

	tileMap = new GameObject*[xSize * ySize]; //Allocate the array to the correct size of the map.


	int currentValue;
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++)
		{
			int index = i * xSize + j;
			fileIn >> currentValue; //Get the next tile value.

			GameObject* object;
			CustomMath::Vector2 pos(i, j);

			switch (currentValue)
			{
			case 1: //If the value is 1, set the sprite to be the wall.
				object = new WallTile(CustomMath::Vector3(pos.x, pos.y, 0));
				object->Position(pos);
				object->SetSprite(tileDefsPointer[(int)Wall]);
				break;

			default: //If value is 0, set the sprite to be the background.
				object = new GameObject();
				object->Position(pos);
				object->SetSprite(tileDefsPointer[(int)Background]);

				break;

			}
			
			listToAdd.Add(object);
			tileMap[index] = object;
		}
	}

	fileIn.close(); //Close the file.
}