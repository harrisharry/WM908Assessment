#pragma once

#include "src/Mathf.h"
#include "GamesEngineeringBase.h"
class Entity {
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	
public:

	Entity() {
	
	}
	virtual void Update(float deltaTime) = 0;
};

class Sprite : public Entity {
protected:
	//Raw pointer to the image data. Stored on the heap, no copies.
	GamesEngineeringBase::Image* _spriteImage;
public:
	Sprite() : Entity()
	{

	}
	Sprite(CustomMath::Vector3 position, GamesEngineeringBase::Image* spriteImage) : Entity() {
		_position = position;
		_spriteImage = spriteImage;
	}


	//Getters and setters.
	void Position(CustomMath::Vector3 newPos) {
		_position = newPos;
	}
	CustomMath::Vector3 Position() {
		return _position;
	}
};

class GameObject : public Sprite
{
public:

	GameObject() : Sprite(){
	}

	GameObject(CustomMath::Vector3 position,GamesEngineeringBase::Image* spriteImage) : Sprite(position,spriteImage) {

	}

	/// <summary>
	/// Changes this objects visual representation.
	/// </summary>
	/// <param name="newSprite">The preloaded image to be used when drawing this object</param>
	void SetSprite(GamesEngineeringBase::Image* newSprite) {
		_spriteImage = newSprite;
	}

	virtual void Update(float deltaTime) override {

	}

};