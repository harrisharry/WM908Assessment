#pragma once

#include "Mathf.h"
#include "GamesEngineeringBase.h"
#include "Collider.h"
#include "SpriteSheet.h"
class Entity {
protected:
	CustomMath::Vector3 _position = CustomMath::Vector3::Zero();
	
public:

	Entity() {
		_position = CustomMath::Vector3::Zero();
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
		_spriteImage = nullptr;
		_spriteDef = nullptr;
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
protected:
	bool shouldDestroy = false;
	Collider* _collider = nullptr;
public:

	GameObject() : Sprite(){
	}

	GameObject(CustomMath::Vector3 position,GamesEngineeringBase::Image* spriteImage) : Sprite(position,spriteImage) {

	}


	virtual void Update(float deltaTime) override {
		if(_collider != nullptr)
			_collider->Position(_position);
	}

	virtual void OnCollisionEnter(GameObject* obj) {}

	void SetCollider(Collider* collider) {
		_collider = collider;
	}
	CustomMath::Vector3 Position() { return _position; }
	void Position(CustomMath::Vector3 pos) { _position = pos; }
	Collider* Collider() { return _collider; }
	void ShouldDestroy(bool destroy) { shouldDestroy = destroy; }
	bool ShouldDestroy() { return shouldDestroy; }

};

class WallTile : public GameObject
{
public:
	WallTile(CustomMath::Vector3 position) {
		_position = position;
		_collider = new BoxCollider(0.5f,0.5f,position);
		_collider->Move(false);
	}
};
class Character : public GameObject
{
protected:
	int _maxHealth = 100;
	float _health = 0;
	float speed = .1f;

public:
	Character() {
		_health = _maxHealth;
	}
	void Damage(int damage) {
		if (damage < 0) { damage *= -1; } //Absolute value.
		_health -= damage;

		//Need to check if dead after damage is taken, and handle death.
	}
	virtual void OnCollisionEnter(GameObject* obj) override {


	}
	bool CheckDead() {
		return _health < 0;
	}
};
class Hero;
class Enemy : public Character
{
private:
	Hero* heroToFollow;
	float detectionRange = 3.0f;
public:
	//Enemy() {

	//}
	Enemy(Hero* hero) {
		heroToFollow = hero;
		speed = 0.05f;
	}

	virtual void Update(float deltaTime) override {
		FollowPlayer(deltaTime);
		if (_collider != nullptr) {
			_collider->Position(_position);
		}
	}

	void FollowPlayer(float deltaTime);
};
class Hero : public Character //Base hero class, implements health speed and movement but can be overwritten by other classes.
{
protected:
	CustomMath::Vector2 inputVec = CustomMath::Vector2::Zero();

public:
	Hero() : Character() {
		_health = _maxHealth;
		_collider = new SphereCollider(.5f, CustomMath::Vector3::Zero());
	}
	virtual void Update(float deltaTime) override { 
		


		//Check if dead at the start of the frame, if so handle the death.
		if (CheckDead()) {
			//Handle death.
			//std::cout << "Hero has died, Handle death here.\n";
		}

		//Deal with movement.

		_position = _position + (inputVec * deltaTime) * speed; //Calculate new position.
		inputVec = CustomMath::Vector2::Zero(); //Reset input for the next frame.

		if (_collider != nullptr) {
			_collider->Position(_position);
		}
	}
	virtual void OnCollisionEnter(GameObject* obj) {
		if (dynamic_cast<Enemy*>(obj))
		{
			Damage(10);
		}
	}
	virtual GameObject* Attack(CustomMath::Vector3 dir) {
		std::cout << "Attacking\n";
		return nullptr;
	}
	void SetInputVec(CustomMath::Vector2 newInput) {
		newInput.Normalise();
		inputVec = newInput;
	}

};
class Projectile : public GameObject {
protected:
	CustomMath::Vector3 _direction = CustomMath::Vector3::Zero();
	float speed = .05f;
	void ProgressProjectile(float deltaTime) {
		_position = _position + _direction * speed * deltaTime;
	}
public:
	Projectile(CustomMath::Vector3 pos, CustomMath::Vector3 dir) {
		_position = pos;
		_direction = dir;
		_collider = new SphereCollider(.15f, _position);
	}
	void Update(float deltaTime) override {

		ProgressProjectile(deltaTime);
		_collider->Position(_position);
	}
	void OnCollisionEnter(GameObject* obj) override {

		if (dynamic_cast<Hero*>(obj)) { std::cout << "Hero collided\n"; return; } //For now dont let the bullet get destroyed.
		if (Enemy* enemy = dynamic_cast<Enemy*>(obj)) {
			enemy->Damage(10);
		}
		shouldDestroy = true;
	}
};
class WizardHero : public Hero
{
protected:
	
	int shootOnce = 0;
public:
	WizardHero() :  Hero() {
		
	}
	virtual GameObject* Attack(CustomMath::Vector3 dir) override
	{
		if (shootOnce != 0) return nullptr;
		shootOnce++;
		dir.Normalise();
		CustomMath::Vector3 pos = _position + dir * 1.0f;
		Projectile* newProj = new Projectile(pos,dir);
		//std::cout << "The wizard is attacking\n";
		return newProj;
	}
};