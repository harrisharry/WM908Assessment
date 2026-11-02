#pragma once

#include "src/Mathf.h"
#include "GamesEngineeringBase.h"
#include "SpriteSheet.h"
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
	SpriteDefinition* _spriteDef; //Also acts as the sprite.
public:
	Sprite() : Entity()
	{

	}
	Sprite(CustomMath::Vector3 position, GamesEngineeringBase::Image* spriteImage = nullptr) : Entity() {
		_position = position;
		_spriteImage = spriteImage;
	}
	Sprite(CustomMath::Vector3 position, SpriteDefinition* def) : Entity() {
		_position = position;
		_spriteImage = nullptr;
		_spriteDef = def;
	}

	GamesEngineeringBase::Image* GetSprite() {
		return _spriteImage;
	}
	SpriteDefinition* GetSpriteDef() {
		return _spriteDef;
	}
	virtual void SetSprite(GamesEngineeringBase::Image* newSprite) {
		_spriteImage = newSprite;
	}
	virtual void SetSprite(SpriteDefinition* def) {
		_spriteDef = def;
	}

	//Getters and setters.
	void Position(CustomMath::Vector3 newPos) {
		_position = newPos;
	}
	virtual void Update(float deltaTime) override {}
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


	virtual void Update(float deltaTime) override {

	}


};

class Hero : public GameObject //Base hero class, implements health speed and movement but can be overwritten by other classes.
{
protected:
	int _maxHealth = 100;
	float _health;
	float speed = 10.0f;
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