#include "GraphicsEngine.h"
#include <iostream>

GameObject testObj;
SpriteSheet* monsterSheet1;
/// <summary>
/// Called when starting up the graphics engine. Default creates a window.
/// </summary>
/// <param name="sizeX"></param>
/// <param name="sizeY"></param>
void GraphicsEngine::StartUp(DataStructures::List<GameObject*>& objects,int sizeX, int sizeY) {
	

	gameObjects = &objects;
	//Create a canvas.
	if (_mainCanvas == NULL) {
		_mainCanvas = new Window(); //Store the newly created window if there wasn't already one.
	}

	_mainCanvas->create(sizeX, sizeY, "Tiles"); //Create the required window with default size and name.
	_shapeManager = new ShapeDrawer2D(_mainCanvas); //Responsible for drawing shapes at given positions.
	_mainCamera = new Camera2D(_mainCanvas);


	//Create images that are required and store them.

	GamesEngineeringBase::Image* heroImage = new GamesEngineeringBase::Image();
	heroImage->load("./Resources/TestSprite.png"); //Test "hero" sprite.
	_loadedSprites[0] = heroImage;
	GamesEngineeringBase::Image* monstersSheet = new GamesEngineeringBase::Image();
	monstersSheet->load("./Resources/monsters.png");
	//_loadedSprites[5] = monstersSheet;

	monsterSheet1 = new SpriteSheet("./Resources/monsters.png");

	//Define sprite definitions for easy use in the sprite sheet.
	SpriteDefinition* wizard = new SpriteDefinition(1,0,monsterSheet1);
	spriteDefs[0] = wizard;

	SpriteDefinition* firstSprite = new SpriteDefinition(0,0,monsterSheet1);
	spriteDefs[1] = firstSprite;



	/*Create entities here to be drawn in update.
	In future this would be stored in the actual main, then passed to the graphics engine to render sprites at the required positions*/
	
	testObj = GameObject(CustomMath::Vector3::Zero(), heroImage);

}
void GraphicsEngine::Update(float deltaTime) {
	//Clears the entire screen before continuing.
	_mainCanvas->clear();


	CustomMath::Vector3 heroPos = gameObjects->Begin()->data->Position();

	for (DataStructures::ListIterator it = gameObjects->Begin(); it != gameObjects->End(); it++) {
		GamesEngineeringBase::Image* sprite = it->data->GetSprite();
		CustomMath::Vector3 pos = it->data->Position();


		if (!DrawImage(sprite, pos)) { //Draw the image, but GamesEngineeringBase::Image*
			DrawImage(it->data->GetSpriteDef(),pos); //If the drawing returns false, then that means we need to draw a sprite definition instead.
		}
	}




	//Any drawing required will go here.

	_mainCamera->Position(CustomMath::Vector2(heroPos.x, heroPos.y));
	DrawImage(testObj.GetSprite(), testObj.Position()); //Draw the test yellow png for movement reference.
	

	//Presents the canvas.
	_mainCanvas->present();
}
bool GraphicsEngine::ShouldClose() {
	if (_mainCanvas->keyPressed(VK_ESCAPE)) return true;
	return false;
}
bool GraphicsEngine::DrawImage(unsigned int indexX, unsigned int indexY, SpriteSheet* spriteSheet, CustomMath::Vector3 position) {
	if (spriteSheet->SheetData() == nullptr) {
		std::cout << "Sprite sheet had no image data!\n";
		return false;
	}
	
	unsigned int width = spriteSheet->SpriteWidth(); // Height of sprites
	unsigned int height = spriteSheet->SpriteHeight(); //Widht of sprites.

	unsigned int widthStart = width * indexX; //Start of the x value of the image we want to draw in the sprite sheet. 
	unsigned int heightStart = height * indexY; //Start of the y value of the image we want to draw in the sprite sheet.

	//Calculate draw position from world space to screen.
	CustomMath::Vector3 screenPos = position - _mainCamera->Position() + _mainCamera->Offset();

	for (int x = widthStart; x < widthStart + width; x++) { //widthStart + width represents the max x value of the Sprite we want to draw.
		for (int y = heightStart; y < heightStart + height; y++) { //heightStart + height represents the max y value of the Sprite we want to draw.
			
			const unsigned int pixelIndex = (y * spriteSheet->SheetData()->width + x) * spriteSheet->SheetData()->channels; //y * first so that it starts with rows and not columns.


			//if (spriteSheet->SheetData()->channels == 3 || spriteSheet->SheetData()->data[pixelIndex + 3] != 0)
			//{
			//	//std::cout << "X is " << x << " and Y is " << y << std::endl;
			//	_mainCanvas->draw(x, y, &spriteSheet->SheetData()->data[pixelIndex]);
			//}
			if (spriteSheet->SheetData()->channels == 4) {
				_mainCanvas->draw(x + screenPos.x, y + screenPos.y, &spriteSheet->SheetData()->data[pixelIndex]);
			}
		}
	}
	return true;
}
bool GraphicsEngine::DrawImage(SpriteDefinition* def, CustomMath::Vector3 position) {
	if (def->GetSpriteSheet() == nullptr) {
		std::cout << "Sprite sheet had no image data!\n";
		return false;
	}

	unsigned int width = def->GetSpriteSheet()->SpriteWidth(); // Height of sprites
	unsigned int height = def->GetSpriteSheet()->SpriteHeight(); //Widht of sprites.

	unsigned int widthStart = width * def->indexX(); //Start of the x value of the image we want to draw in the sprite sheet. 
	unsigned int heightStart = height * def->indexY(); //Start of the y value of the image we want to draw in the sprite sheet.

	//Calculate draw position from world space to screen.
	CustomMath::Vector3 screenPos = position - _mainCamera->Position() + _mainCamera->Offset();

	int xLoopIcrement = 0;
	int yLoopIcrement = 0;

	for (int x = widthStart; x < widthStart + width; x++) { //widthStart + width represents the max x value of the Sprite we want to draw.
		for (int y = heightStart; y < heightStart + height; y++) { //heightStart + height represents the max y value of the Sprite we want to draw.

			const unsigned int pixelIndex = (y * def->GetSpriteSheet()->SheetData()->width + x) * def->GetSpriteSheet()->SheetData()->channels; //y * first so that it starts with rows and not columns.


			if (def->GetSpriteSheet()->SheetData()->channels == 3 || def->GetSpriteSheet()->SheetData()->data[pixelIndex + 3] != 0)
			{
				//std::cout << "X is " << x << " and Y is " << y << std::endl;
				_mainCanvas->draw(x + screenPos.x - (width * 0.5f), y + screenPos.y - (height * 0.5f), &def->GetSpriteSheet()->SheetData()->data[pixelIndex]);
			}
			else if (def->GetSpriteSheet()->SheetData()->channels == 4) {
				_mainCanvas->draw(x + screenPos.x, y + screenPos.y, &def->GetSpriteSheet()->SheetData()->data[pixelIndex]);
			}
			yLoopIcrement++;
		}
		xLoopIcrement++;
	}

	return true;
}
bool GraphicsEngine::DrawImage(const GamesEngineeringBase::Image* imageToDraw, CustomMath::Vector3 position) {

	if (imageToDraw == nullptr) {
		std::cout << "Draw request had no image data!\n";
		return false;
	}

	unsigned int height = imageToDraw->height;
	unsigned int width = imageToDraw->width;

	//Calculate draw position from world space to screen.
	CustomMath::Vector3 screenPos = position - _mainCamera->Position() + _mainCamera->Offset();

	//Iterrate over all the rows of the image
	for (int x = 0; x < width; x++) {

		//Then interate all the pixels on that row
		for (int y = 0; y < height; y++) {
			

			const unsigned int pixelIndex = (y * width + x) * imageToDraw->channels;

			if (imageToDraw->channels == 3 || imageToDraw->data[pixelIndex + 3] != 0)
			{
				//std::cout << "X is " << x << " and Y is " << y << std::endl;
				_mainCanvas->draw(x + screenPos.x,y + screenPos.y,&imageToDraw->data[pixelIndex]);
			}
		}
	}
	return true;
}
void GraphicsEngine::SetBackground(Colour::Colour colour) {

	for (int i = 0; i < _mainCanvas->getWidth(); i++) {
		for (int j = 0; j < _mainCanvas->getHeight(); j++) {
			_mainCanvas->draw(i,j,colour.red,colour.green,colour.blue);
		}
	}
}