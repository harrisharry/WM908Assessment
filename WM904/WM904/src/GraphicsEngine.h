#pragma once

#include "GamesEngineeringBase.h"
#include "Colour.h"
#include "ShapeDrawer.h"
using namespace GamesEngineeringBase;
//Responsible for creating the start of the game, and any other graphical requirements.
class GraphicsEngine
{
private:
	Window* _mainCanvas = NULL;

	Colour::Colour defaultColour = Colour::Colour(128,0,128);
	ShapeDrawer2D* _shapeManager;
	void SetBackground(Colour::Colour colour);
public:
	void StartUp(int sizeX = 1204, int sizeY = 768);
	void Update();
	bool ShouldClose();
	//void DrawSprite(Here will be a Sprite class.);// Function to draw a given sprite. Will be usefull when implementing game objects etc.
};

