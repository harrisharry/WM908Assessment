#include "GraphicsEngine.h"
/// <summary>
/// Called when starting up the graphics engine. Default creates a window.
/// </summary>
/// <param name="sizeX"></param>
/// <param name="sizeY"></param>
void GraphicsEngine::StartUp(int sizeX, int sizeY) {



	//Create a canvas.
	if (_mainCanvas == NULL) {
		_mainCanvas = new Window(); //Store the newly created window if there wasn't already one.
	}

	_mainCanvas->create(sizeX, sizeY, "Tiles"); //Create the required window with default size and name.
	_shapeManager = new ShapeDrawer2D(_mainCanvas);

}
void GraphicsEngine::Update() {
	//Clears the entire screen before continuing.
	_mainCanvas->clear();
	SetBackground(defaultColour);
	//Any drawing required will go here.
	

	//Presents the canvas.
	
	
	_mainCanvas->present();
}
bool GraphicsEngine::ShouldClose() {
	if (_mainCanvas->keyPressed(VK_ESCAPE)) return true;
	return false;
}
void GraphicsEngine::SetBackground(Colour::Colour colour) {

	for (int i = 0; i < _mainCanvas->getWidth(); i++) {
		for (int j = 0; j < _mainCanvas->getHeight(); j++) {
			_mainCanvas->draw(i,j,colour.red,colour.green,colour.blue);
		}
	}
}