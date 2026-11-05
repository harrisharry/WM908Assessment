#pragma once
#include "Collider.h"
#include "Entity.h"
#include <iostream>

bool SphereCollider::CheckCollision(Collider* other)
{
	return other->CheckCollision(this);
}
bool SphereCollider::CheckCollision(SphereCollider* other)
{
	//Get distance between colliders
	float distance = _position.Distance(other->Position());
	
	if (distance >= other->Radius() + _radius) {
		return false;
	}
	return true;
	
}
bool SphereCollider::CheckCollision(BoxCollider* other)
{
	return other->CheckCollision(this);
}

void SphereCollider::ResolveCollision(Collider* other,GameObject* objToCheck) {
	other->ResolveCollision(this,objToCheck);
}
void SphereCollider::ResolveCollision(SphereCollider* other, GameObject* objToCheck) {
	CustomMath::Vector3 collisionVector = _position - other->Position();
	float distance = collisionVector.Magnitude(); //Distance between the two objects needs to be the same as the sum of their radius.
	collisionVector.Normalise();
	float radiusSum = other->Radius() + this->Radius();
	float depth = radiusSum - distance; //The amount that each sphere is inside eachother.

	CustomMath::Vector3 newPos = this->Position() + collisionVector * depth;
	objToCheck->Position(newPos);



}
void SphereCollider::ResolveCollision(BoxCollider* other, GameObject* objToCheck) {
	return other->ResolveCollision(this, objToCheck);
}

bool BoxCollider::CheckCollision(Collider* other) {

	return other->CheckCollision(this);
}
bool BoxCollider::CheckCollision(SphereCollider* other) {
	
	RecalculatePoints();
	CustomMath::Vector3 closestPoint; //This is the closest on the AABB to the sphere center.

	if (other->Position().x > _maxPoint.x) {//If the x pos of sphere is greater than max x, set x pos to be max x.
		closestPoint.x = _maxPoint.x;
	}
	else if (other->Position().x < _minPoint.x) { //If the x pos of sphere is less than the min x, set the x pos to be min x.
		closestPoint.x = _minPoint.x;
	}
	else //If neither of the above is true, then wherever the x pos is, it is the right value.
	{
		closestPoint.x = other->Position().x;
	}
	//Same for y.
	if (other->Position().y > _maxPoint.y) {
		closestPoint.y = _maxPoint.y;
	}
	else if (other->Position().y < _minPoint.y) {
		closestPoint.y = _minPoint.y;
	}
	else
	{
		closestPoint.y = other->Position().y;
	}

	//Now we have the closest point on the AABB to the Sphere. We can calculate if they are colliding using distances.

	float disFromSphere =  (closestPoint - other->Position()).Magnitude();

	if (disFromSphere >= other->Radius()) {
		return false;
	}
	return true;
}
bool BoxCollider::CheckCollision(BoxCollider* other) {
	other->RecalculatePoints();
	this->RecalculatePoints();
	//Check if the x axis are overlapping
	//If the max x of box a is less than the min x of box b, they are seperated or if the min x of box a is greather than the max x of box b, then there is a seperation in the opposite direction.
	if (_maxPoint.x <= other->_minPoint.x || _minPoint.x >= other->_maxPoint.x) {
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

void BoxCollider::ResolveCollision(Collider* other, GameObject* objToCheck) {
	other->ResolveCollision(this, objToCheck);
}
void BoxCollider::ResolveCollision(SphereCollider* other, GameObject* objToCheck) {

	RecalculatePoints();
	CustomMath::Vector3 closestPoint; //This is the closest on the AABB to the sphere center.

	if (other->Position().x > _maxPoint.x) {//If the x pos of sphere is greater than max x, set x pos to be max x.
		closestPoint.x = _maxPoint.x;
	}
	else if (other->Position().x < _minPoint.x) { //If the x pos of sphere is less than the min x, set the x pos to be min x.
		closestPoint.x = _minPoint.x;
	}
	else //If neither of the above is true, then wherever the x pos is, it is the right value.
	{
		closestPoint.x = other->Position().x;
	}
	//Same for y.
	if (other->Position().y > _maxPoint.y) {
		closestPoint.y = _maxPoint.y;
	}
	else if (other->Position().y < _minPoint.y) {
		closestPoint.y = _minPoint.y;
	}
	else
	{
		closestPoint.y = other->Position().y;
	}

	CustomMath::Vector3 dirVec = closestPoint - other->Position();
	float distance = dirVec.Magnitude();
	float depth = other->Radius() - distance;

	dirVec.Normalise();

	CustomMath::Vector3 newPos = objToCheck->Position() + dirVec * depth;

	other->Position(newPos);
	objToCheck->Position(newPos);

}
void BoxCollider::ResolveCollision(BoxCollider* other, GameObject* objToCheck) {

}
