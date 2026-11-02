#pragma once

#include "GamesEngineeringBase.h"
#include "Colour.h"
#include "ShapeDrawer.h"
#include "Camera2D.h"
#include "DStructures.h"
#include "Entity.h"
#include "SpriteSheet.h"

using namespace GamesEngineeringBase;

enum Sprites
{
	Wizard,
	Default,
};


//Responsible for creating the start of the game, and any other graphical requirements.
class GraphicsEngine
{
private:
	Window* _mainCanvas = nullptr;
	Camera2D* _mainCamera = nullptr;

	DataStructures::List<GameObject*>* gameObjects;
	SpriteDefinition* spriteDefs[5];
	GamesEngineeringBase::Image* _loadedSprites[5];
	Colour::Colour defaultColour = Colour::Colour(128,0,128);
	ShapeDrawer2D* _shapeManager;
	const unsigned int _pixelPerUnit = 32;

	void SetBackground(Colour::Colour colour);
public:
	GraphicsEngine() = default;
	GamesEngineeringBase::Window* GetWindow() { return _mainCanvas; }
	void StartUp(DataStructures::List<GameObject*>& objects,int sizeX = 320, int sizeY = 180);
	void Update(float deltaTime);
	bool DrawImage(unsigned int indexX, unsigned int indexY, SpriteSheet* spriteSheet, CustomMath::Vector3 position);
	bool DrawImage(SpriteDefinition* def, CustomMath::Vector3 position);
	bool DrawImage(const GamesEngineeringBase::Image* imageToDraw, CustomMath::Vector3 position);
	bool ShouldClose();
	GamesEngineeringBase::Image* GetSpriteAtIndex(unsigned int index) {
		return _loadedSprites[index];
	}

	SpriteDefinition* GetSpriteDef(Sprites sprite) { return spriteDefs[(int)sprite]; }
	SpriteDefinition* GetSpriteDef(int index) { return spriteDefs[index]; }
	//void DrawSprite(Here will be a Sprite class.);// Function to draw a given sprite. Will be usefull when implementing game objects etc.
};

