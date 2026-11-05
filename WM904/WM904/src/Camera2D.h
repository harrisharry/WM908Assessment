#pragma once
#include "GamesEngineeringBase.h"
#include "Mathf.h"
class Camera2D
{	
private:
	CustomMath::Vector2 _position = CustomMath::Vector2 ::Zero(); // World position.
	CustomMath::Vector2 _cameraOffset = CustomMath::Vector2::Zero(); //Half of the screen size.
	unsigned int screenSizeX;
	unsigned int screenSizeY;
public:
	Camera2D(GamesEngineeringBase::Window* window){
		screenSizeX = window->getWidth();
		screenSizeY = window->getHeight();

		int x = screenSizeX * 0.5f; //Half x.
		int y = screenSizeY* 0.5f; //Half y.

		_cameraOffset = CustomMath::Vector2(x,y);
	}

	CustomMath::Vector2 GetScreenCoords(CustomMath::Vector3 worldPos) {
		
	}

	CustomMath::Vector2 Offset() { return _cameraOffset; }
	void Position(CustomMath::Vector2 newPos) {
		_position = newPos;
	}
	CustomMath::Vector2 Position() { return _position; }
	CustomMath::Vector2 WorldToScreenSpace(CustomMath::Vector2 worldPos) {
		 
		return ((worldPos - _position)) * 32 + _cameraOffset;

	}
	bool OutsideCam(CustomMath::Vector2 position, bool isScreenSpace = false) {

		int maxX;
		int minX;
		int maxY;
		int minY;
		if (isScreenSpace == true) {
			maxX = position.x;
			minX = maxX;
			maxY = position.y;
			minY = maxY;
		}
		else {
			CustomMath::Vector2 screenPos = WorldToScreenSpace(position);
			maxX = screenPos.x;
			minX = screenPos.x;
			maxY = screenPos.y;
			minY = screenPos.y;
		}



		if (minX >= 0 && maxX <= screenSizeX)
		{
			if (minY >= 0 && maxY <= screenSizeY) {
				//std::cout << "Inside\n";
				return false;
			}
		}
		//std::cout << "Outside\n";
		return true;
	}

};

