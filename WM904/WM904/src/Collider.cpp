#include "Collider.h"
#include "Entity.h"

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
	return false;
}

void SphereCollider::ResolveCollision(Collider* other,GameObject* objToCheck) {
	other->ResolveCollision(this,objToCheck);
}
void SphereCollider::ResolveCollision(SphereCollider* other, GameObject* objToCheck) {
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
void SphereCollider::ResolveCollision(BoxCollider* other, GameObject* objToCheck) {

}

bool BoxCollider::CheckCollision(Collider* other) {

	return other->CheckCollision(this);
}
 bool BoxCollider::CheckCollision(SphereCollider* other) {
	return other->CheckCollision(this);
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

}
void BoxCollider::ResolveCollision(BoxCollider* other, GameObject* objToCheck) {

}
