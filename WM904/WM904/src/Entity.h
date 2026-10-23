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
	GamesEngineeringBase::Image* GetSprite() {
		return _spriteImage;
	}

	virtual void Update(float deltaTime) override {

	}


};

class Hero : public GameObject //Base hero class, implements health speed and movement but can be overwritten by other classes.
{
protected:
	int _maxHealth = 100;
	float _health;
	float speed = 100.0f;
	CustomMath::Vector2 inputVec = CustomMath::Vector2::Zero();

public:
	Hero() : GameObject() {
		_health = _maxHealth;
	}
	void Damage(int damage) {
		if (damage < 0) { damage *= -1; } //Absolute value.
		_health -= damage;
		
		//Need to check if dead after damage is taken, and handle death.
	}
	bool CheckDead(){
		return _health < 0;
	}
	virtual void Update(float deltaTime) override{
		


		//Check if dead at the start of the frame, if so handle the death.
		if (CheckDead()) {
			//Handle death.
			std::cout << "Hero has died, Handle death here.\n";
		}

		//Deal with movement.

		_position = _position + (inputVec * deltaTime) * speed; //Calculate new position.

		inputVec = CustomMath::Vector2::Zero(); //Reset input for the next frame.
	}
	void SetInputVec(CustomMath::Vector2 newInput) {
		inputVec = newInput;
	}
};