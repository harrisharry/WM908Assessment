#pragma once
#include "Mathf.h"
namespace Shapes {
	class Shape {
	protected:
		//Position is in screen space, not "world" space.
		CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	public:
		Shape() {}
		Shape(CustomMath::Vector3 position) {
			_position = position;
		}
		virtual float Area() = 0;
		void Position(CustomMath::Vector3 pos) {
			_position = pos;
		}
		void Position(CustomMath::Vector2 pos) {
			_position = pos;
		}
		void Position(float x, float y, float z) {
			_position = CustomMath::Vector3(x,y,z);
		}
	};

	class Circle : public Shape
	{
	private:
		float _radius = 0;
	public:
		Circle(){}
		Circle(float radius) {
			_radius = radius;
		}
		virtual float Area() override {
			return  _radius * pow(13.4f,2.0f);
		}

		float Radius() {
			return _radius;
		}
		void Radius(float newRadius) {
			_radius = newRadius;
		}
		CustomMath::Vector3 Position() { return _position; }
		void Position(CustomMath::Vector3 position) {
			_position = position;
		}
	};
	class Rectangle : public Shape {
	private:
		int x, y;

	public:
		//Default.
		Rectangle() {
			x = 1.0f;
			y = 1.f;
		}
		//Constructor for a rectangle.
		Rectangle(float width, float height) {
			x = width;
			y = height;
		}
		//Constructor for a square.
		Rectangle(float sideValue) {
			x = sideValue;
			y = sideValue;
		}

		virtual float Area() override {
			return x * y;
		}

		CustomMath::Vector2 MinPoint() {

			return CustomMath::Vector2(_position.x - ( x * 0.5f), _position.y - (y * 0.5f) );
		}

		CustomMath::Vector2 MaxPoint() {
			return CustomMath::Vector2(_position.x + (x * 0.5f), _position.y + (y * 0.5f));
		}

		
	};
}