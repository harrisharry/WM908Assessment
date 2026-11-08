#pragma once

#include "Mathf.h"
#include "GamesEngineeringBase.h"
#include "Collider.h"
#include "SpriteSheet.h"
#include "Timer.h"
#include "ObjectFactory.h"
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
	float speed = 8.0f;

public:
	Character() {
		_health = _maxHealth;
	}
	void Damage(int damage) {
		if (damage < 0) { damage *= -1; } //Absolute value.
		_health -= damage;
		std::cout << "Health is now " << _health << std::endl;
		//Need to check if dead after damage is taken, and handle death.
	}
	virtual void OnCollisionEnter(GameObject* obj) override {


	}
	bool CheckDead() {
		return _health <= 0;
	}
};
class Hero;
class Enemy : public Character
{
protected:
	Hero* heroToFollow;
	float detectionRange = 3.0f;
public:
	Enemy() {
		_collider = new SphereCollider(0.5f);
	}
	Enemy(Hero* hero) {
		heroToFollow = hero;
		speed = 5;
		_collider = new SphereCollider(0.5f);
	}

	virtual void Update(float deltaTime) override {
		//std::cout << "Enemy health is " << _health << std::endl;
		if (CheckDead()) {
			_collider->Active(false);
			_spriteDef = nullptr;
		}

		FollowPlayer(deltaTime);
		if (_collider != nullptr) {
			_collider->Position(_position);
		}
	}

	void FollowPlayer(float deltaTime);
};
class Spawner : public Enemy
{
	Time::Timer timer;
	ObjectFactory* facRef; 
	SpriteDefinition* defToSpawn;
	float spawnTime = 5;
public:
	Spawner(CustomMath::Vector3 pos,
			Hero* hero,
			ObjectFactory* fac) : Enemy(hero)
	{
		_health = 50;
		_position = pos;
		_collider = new SphereCollider(.5f);
		_collider->Move(false);
		facRef = fac;
		timer.Start();
	}
	virtual void Update(float deltaTinme) override
	{
		if (CheckDead()) { return; }//Stops spawning enemies.
		SpawnEnemy();
	}
	void SpawnEnemy() {
		timer.Stop();
		if (timer.Duration() < spawnTime * 1000) return;
		Enemy* newEnemy = new Enemy(heroToFollow);
		newEnemy->Position(_position);
		newEnemy->SetSprite(defToSpawn);
		facRef->AddObject(newEnemy);
		timer.Start();
	}
	void SetSpawnedSprite(SpriteDefinition* def)
	{
		defToSpawn = def;
	}
};
class Speedster : public Enemy
{
protected:
public:
	Speedster(Hero* hero) : Enemy(hero){
		speed = 7.0f;
		_health = 25;
	}
};
class Giant : public Enemy
{
protected:
public:
	Giant(Hero* hero) : Enemy(hero) {
		speed = 3.0f;
		_health = 150;
	}
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
		if (shouldDestroy) return;
		if (dynamic_cast<Hero*>(obj)) { return; } //For now dont let the bullet get destroyed.
		if (Enemy* enemy = dynamic_cast<Enemy*>(obj)) {
			enemy->Damage(25);
		}
		_spriteDef = nullptr;
		shouldDestroy = true;
	}
};
class WizardHero : public Hero
{
protected:
	Time::Timer timer;
	float shootCooldown = 2; //In seconds
public:
	WizardHero() :  Hero() {
		timer.Start();
	}
	virtual GameObject* Attack(CustomMath::Vector3 dir) override
	{
		timer.Stop(); //Stop the end time to check how long it has been.
		double duration = timer.Duration();
		if (duration < shootCooldown * 1000) return nullptr; //Check it has been long enough, convrts seconds into miliseconds.
		dir.Normalise();
		CustomMath::Vector3 pos = _position + dir * 1.0f;
		Projectile* newProj = new Projectile(pos,dir);
		timer.Start(); //Restart the start of the timer.
		return newProj;
	}
};