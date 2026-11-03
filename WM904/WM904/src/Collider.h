#pragma once
#include "src/Mathf.h"

class BoxCollider;
class SphereCollider;

//Base collider class.
class Collider
{
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	bool moves = false;

public:
	virtual bool CheckCollision(SphereCollider& other) = 0;
	virtual bool CheckCollision(BoxCollider& other) = 0;

	//Getters and setters.
	void Move(bool can) {
		moves = can;
	}
	bool Move() {
		return moves;
	}
};

class SphereCollider : public Collider {
private:
	float _radius = 1.0f;
public:
	SphereCollider() {

	}
	SphereCollider(float radius) {
		_radius = radius;
	}
	SphereCollider(float radius, CustomMath::Vector3 position) {
		_radius = radius;
		_position = position;
	}

	void Position(CustomMath::Vector3 newPos) {
		_position = newPos;
	}
	CustomMath::Vector3 Position() { return _position;  }
	float Radius() { return _radius; }

	virtual bool CheckCollision(SphereCollider& other) override {
		
		//Get distance between colliders
		float distance = _position.Distance(other.Position());

		if (distance >= other.Radius() + _radius) {
			return false; 
		}
		return true;
	}
	virtual bool CheckCollision(BoxCollider& other) override {

		return false;
	}
};

class BoxCollider : public Collider { // 2D Axis alligned bounding box.
private:
	float _width = 0;
	float _height = 0;
	CustomMath::Vector2 _maxPoint;
	CustomMath::Vector2 _minPoint;

	CustomMath::Vector2 CalculateMax() {

		CustomMath::Vector2 max;

		float xMax = _position.x + (_width * 0.5f);
		float yMax = _position.y + (_height * 0.5f);

		max.x = xMax;
		max.y = yMax;

		std::cout << "Max vec is + " << max.To_String() << std::endl;

		return max;

	}
	CustomMath::Vector2 CalculateMin() {
		CustomMath::Vector2 min;
		
		float xMin = _position.x - (_width * 0.5f);
		float yMin = _position.y - (_height * 0.5f);

		min.x = xMin;
		min.y = yMin;


		std::cout << "Min vec is + " << min.To_String() << std::endl;
			
		return min;
	}
public:
	BoxCollider() = default;
	BoxCollider(CustomMath::Vector3 position) {
		_position = position;

	}
	BoxCollider(float xWidth, float yHeight) {
		_width = xWidth;
		_height = yHeight;

		_maxPoint = CalculateMax();
		_minPoint = CalculateMin();
	}
	BoxCollider(float xWidth, float yHeight, CustomMath::Vector3 position) {
		_width = xWidth;
		_height = yHeight;
		_position = position;

		_maxPoint = CalculateMax();
		_minPoint = CalculateMin();
	}
	void RecalculatePoints() {
		_maxPoint = CalculateMax();
		_minPoint = CalculateMin();
	}
	
	virtual bool CheckCollision(SphereCollider& other) override {
		return other.CheckCollision(*this);
	}
	virtual bool CheckCollision(BoxCollider& other) override {

		//Check if the x axis are overlapping
		//If the max x of box a is less than the min x of box b, they are seperated or if the min x of box a is greather than the max x of box b, then there is a seperation in the opposite direction.
		if (_maxPoint.x <= other._minPoint.x || _minPoint.x >= other._maxPoint.x){
			return false; //There is a seperation so they arent colliding.
		}
		//Check if now there is a seperation in the y direction.
		if (_maxPoint.y <= other._minPoint.y || _minPoint.y >= other._maxPoint.y) {
			//There is seperation in the y axis return false. They are not colliding.
			return false;
		}

		//If there is neither a seperation in the x axis or the y axis, then they must be colliding. 
		return true;
	}

};