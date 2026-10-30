#pragma once

#include "GamesEngineeringBase.h"
#include "Colour.h"
#include "ShapeDrawer.h"
#include "Camera2D.h"
#include "DStructures.h"
#include "Entity.h"
using namespace GamesEngineeringBase;
//Responsible for creating the start of the game, and any other graphical requirements.
class GraphicsEngine
{
private:
	Window* _mainCanvas = nullptr;
	Camera2D* _mainCamera = nullptr;

	DataStructures::List<GameObject*>* gameObjects;
	GamesEngineeringBase::Image* _loadedSprites[5];
	Colour::Colour defaultColour = Colour::Colour(128,0,128);
	ShapeDrawer2D* _shapeManager;
	

	void SetBackground(Colour::Colour colour);
public:
	GamesEngineeringBase::Window* GetWindow() { return _mainCanvas; }
	void StartUp(DataStructures::List<GameObject*>& objects,int sizeX = 200, int sizeY = 200);
	void Update(float deltaTime);
	void DrawImage(const GamesEngineeringBase::Image* imageToDraw, CustomMath::Vector3 position);
	bool ShouldClose();
	GamesEngineeringBase::Image* GetSpriteAtIndex(unsigned int index) {
		return _loadedSprites[index];
	}
	//void DrawSprite(Here will be a Sprite class.);// Function to draw a given sprite. Will be usefull when implementing game objects etc.
};

