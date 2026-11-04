#pragma once
#include "Mathf.h"
#include "Entity.h"

class BoxCollider;
class SphereCollider;
class GameObject;

//Base collider class.
class Collider
{
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	bool moves = false;

public:
	virtual bool CheckCollision(Collider* other) = 0;
	virtual bool CheckCollision(SphereCollider* other) = 0;
	virtual bool CheckCollision(BoxCollider* other) = 0;

	virtual void ResolveCollision(Collider* other, GameObject* objToCheck) = 0;
	virtual void ResolveCollision(SphereCollider* other, GameObject* objToCheck) = 0;
	virtual void ResolveCollision(BoxCollider* other, GameObject* objToCheck) = 0;

	//Getters and setters.
	void Position(CustomMath::Vector3 pos) { _position = pos; }
	CustomMath::Vector3 Position() { return _position; }
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
	virtual bool CheckCollision(Collider* other) override;
	virtual bool CheckCollision(SphereCollider* other) override {
		
		//Get distance between colliders
		float distance = _position.Distance(other->Position());
		
		if (distance >= other->Radius() + _radius) {
			return false; 
		}
		return true;
	}
	virtual bool CheckCollision(BoxCollider* other) override {

		return false;
	}


	virtual void ResolveCollision(Collider* other, GameObject* objToCheck) override;
	virtual void ResolveCollision(SphereCollider* other, GameObject* objToCheck) override {
		
		std::cout << "Resolving sphere sphere collision\n";
		CustomMath::Vector3 collisionVector = _position - other->Position();
		float distance = collisionVector.Magnitude(); //Distance between the two objects needs to be the same as the sum of their radius.
		collisionVector.Normalise();
		float radiusSum = other->Radius() + this->Radius();
		float depth = radiusSum - distance; //The amount that each sphere is inside eachother.

		CustomMath::Vector3 newPos = other->Position() - collisionVector * depth;
		std::cout << "New pos is " + newPos.To_String() << std::endl;
		objToCheck->Position(newPos);

		

	}
	virtual void ResolveCollision(BoxCollider* other, GameObject* objToCheck) override {

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
		return max;

	}
	CustomMath::Vector2 CalculateMin() {
		CustomMath::Vector2 min;
		
		float xMin = _position.x - (_width * 0.5f);
		float yMin = _position.y - (_height * 0.5f);

		min.x = xMin;
		min.y = yMin;
			
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
	virtual bool CheckCollision(Collider* other) override {
		return other->CheckCollision(this);
	}
	virtual bool CheckCollision(SphereCollider* other) override {
		return other->CheckCollision(this);
	}
	virtual bool CheckCollision(BoxCollider* other) override {
		other->RecalculatePoints();
		this->RecalculatePoints();
		//Check if the x axis are overlapping
		//If the max x of box a is less than the min x of box b, they are seperated or if the min x of box a is greather than the max x of box b, then there is a seperation in the opposite direction.
		if (_maxPoint.x <= other->_minPoint.x || _minPoint.x >= other->_maxPoint.x){
			return false; //There is a seperation so they arent colliding.
		}
		//Check if now there is a seperation in the y direction.
		if (_maxPoint.y <= other->_minPoint.y || _minPoint.y >= other->_maxPoint.y) {
			//There is seperation in the y axis return false. They are not colliding.
			return false;
		}

		//If there is neither a seperation in the x axis or the y axis, then they must be colliding. 
		return true;
	}

	virtual void ResolveCollision(Collider* other, GameObject* objToCheck) override {
		other->ResolveCollision(this, objToCheck);
	}
	virtual void ResolveCollision(SphereCollider* other, GameObject* objToCheck) override {

	}
	virtual void ResolveCollision(BoxCollider* other, GameObject* objToCheck) override {

	}
};