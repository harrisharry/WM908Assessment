#pragma once
#include "Mathf.h"

class BoxCollider;
class SphereCollider;
class GameObject;

//Base collider class.
class Collider
{
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	bool moves = true;

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
	virtual bool CheckCollision(SphereCollider* other) override;
	virtual bool CheckCollision(BoxCollider* other) override;


	virtual void ResolveCollision(Collider* other, GameObject* objToCheck) override;
	virtual void ResolveCollision(SphereCollider* other, GameObject* objToCheck) override;
	virtual void ResolveCollision(BoxCollider* other, GameObject* objToCheck) override;
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
	virtual bool CheckCollision(Collider* other) override;
	virtual bool CheckCollision(SphereCollider* other) override;
	virtual bool CheckCollision(BoxCollider* other) override;

	virtual void ResolveCollision(Collider* other, GameObject* objToCheck) override;
	virtual void ResolveCollision(SphereCollider* other, GameObject* objToCheck) override;
	virtual void ResolveCollision(BoxCollider* other, GameObject* objToCheck) override;
};