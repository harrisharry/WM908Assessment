#pragma once
#include "src/Mathf.h"

//Base collider class.
class Collider
{
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();

public:
	virtual bool CheckCollision(SphereCollider other) = 0;
};
class SphereCollider : public Collider {
private:
	float _radius = 1.0f;
public:
	SphereCollider() {

	}
	SphereCollider(float radius) {

	}

	void Position(CustomMath::Vector3 newPos) {
		_position = newPos;
	}
	CustomMath::Vector3 Position() { return _position;  }
	float Radius() { return _radius; }

	virtual bool CheckCollision(SphereCollider other) override {
		
		//Get distance between colliders
		float distance = _position.Distance(other.Position());

		if (distance > other.Radius()) { return false; }
		return true;
	}
};