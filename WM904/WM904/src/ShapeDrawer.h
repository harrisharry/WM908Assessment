#pragma once
#include "Shape.h"
#include "GamesEngineeringBase.h"

class ShapeDrawer2D {
	
private: 
	GamesEngineeringBase::Window* window; //Reference to the window to draw on.

public:

	ShapeDrawer2D(GamesEngineeringBase::Window* windowRef) {
		window = windowRef;
	}
	void Draw(Shapes::Circle circle) {
		
		

	}
	void Draw(Shapes::Rectangle rec) {
	
		CustomMath::Vector2 min = rec.MinPoint();
		CustomMath::Vector2 max = rec.MaxPoint();
		for (int i = min.x; i <= max.x; i++)
		{
			for (int j = min.y; j <= max.y; j++)
			{
				window->draw(i,j,255,255,255);
			}
		}
	}
};