#pragma once
#include "src/GamesEngineeringBase.h"
#include "src/Mathf.h"
class Camera2D
{	
private:
	CustomMath::Vector2 _position = CustomMath::Vector2 ::Zero(); // World position.
	CustomMath::Vector2 _cameraOffset = CustomMath::Vector2::Zero(); //Half of the screen size.
public:
	Camera2D(GamesEngineeringBase::Window* window){
		int x = window->getWidth() * 0.5f; //Half x.
		int y = window->getHeight() * 0.5f; //Half y.

		_cameraOffset = CustomMath::Vector2(x,y);
	}

	CustomMath::Vector2 GetScreenCoords(CustomMath::Vector3 worldPos) {
		
	}

	CustomMath::Vector2 Offset() { return _cameraOffset; }
	void Position(CustomMath::Vector2 newPos) {

		_position = newPos;
	}
	CustomMath::Vector2 Position() { return _position; }

};

