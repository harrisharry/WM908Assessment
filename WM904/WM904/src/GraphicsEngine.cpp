#include "GraphicsEngine.h"
#include <iostream>


GamesEngineeringBase::Image* sprite1 = new GamesEngineeringBase::Image();
Hero* hero = new Hero();
GameObject testObj;

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


	//Create images that are required. 

	//GamesEngineeringBase::Image* sprite1 = new GamesEngineeringBase::Image();
	sprite1->load("./Resources/TestSprite.png");
	hero->SetSprite(sprite1);
	/*Create entities here to be drawn in update.
	In future this would be stored in the actual main, then passed to the graphics engine to render sprites at the required positions*/
	
	testObj = GameObject(CustomMath::Vector3::Zero(), sprite1);

}
void GraphicsEngine::Update(float deltaTime) {
	//Clears the entire screen before continuing.
	_mainCanvas->clear();
	SetBackground(defaultColour);
	//Get input for this frame
	CustomMath::Vector2 totalInput = CustomMath::Vector2::Zero();
	if (_mainCanvas->keyPressed('W'))
		totalInput += CustomMath::Vector2( 0, -1);
	if (_mainCanvas->keyPressed('S'))
		totalInput += CustomMath::Vector2( 0,1);
	if (_mainCanvas->keyPressed('A'))
		totalInput += CustomMath::Vector2(-1, 0);
	if (_mainCanvas->keyPressed('D'))
		totalInput += CustomMath::Vector2( 1, 0);

	hero->SetInputVec(totalInput);

	hero->Update(0.01667);

	
	//Any drawing required will go here.
	//DrawImage(sprite1,CustomMath::Vector3::Zero() - CustomMath::Vector3(0,0,0));
	//DrawImage(sprite1,CustomMath::Vector3::Zero() - CustomMath::Vector3(-250,-250,0));

	_mainCamera->Position(CustomMath::Vector2(hero->Position().x, hero->Position().y));

	DrawImage(hero->GetSprite(), hero->Position());
	DrawImage(testObj.GetSprite(), testObj.Position());
	
	//Presents the canvas.
	
	
	_mainCanvas->present();
}
bool GraphicsEngine::ShouldClose() {
	if (_mainCanvas->keyPressed(VK_ESCAPE)) return true;
	return false;
}
void GraphicsEngine::DrawImage(const GamesEngineeringBase::Image* imageToDraw, CustomMath::Vector3 position) {

	if (imageToDraw->data == nullptr) {
		std::cout << "Draw request had no image data!\n";
		return;
	}

	unsigned int height = imageToDraw->height;
	unsigned int width = imageToDraw->width;

	//Calculate draw position from world space to screen.
	CustomMath::Vector3 screenPos = position - _mainCamera->Position() + _mainCamera->Offset();

	//Iterrate over all the rows of the image
	for (int x = 0; x < width; x++) {

		//Then interate all the pixels on that row
		for (int y = 0; y < height; y++) {
			

			const unsigned int pixelIndex = (x * width + y) * imageToDraw->channels;

			if (imageToDraw->channels == 3 || imageToDraw->data[pixelIndex + 3] != 0)
			{
				//std::cout << "X is " << x << " and Y is " << y << std::endl;
				_mainCanvas->draw(x + screenPos.x,y + screenPos.y,&imageToDraw->data[pixelIndex]);
			}
		}
	}

}
void GraphicsEngine::SetBackground(Colour::Colour colour) {

	for (int i = 0; i < _mainCanvas->getWidth(); i++) {
		for (int j = 0; j < _mainCanvas->getHeight(); j++) {
			_mainCanvas->draw(i,j,colour.red,colour.green,colour.blue);
		}
	}
}