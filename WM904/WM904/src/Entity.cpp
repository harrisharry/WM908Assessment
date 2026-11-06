#include "Entity.h"

void Enemy::FollowPlayer(float deltaTime) 
{
	CustomMath::Vector3 dirVec = heroToFollow->Position() - _position;
	if (dirVec.Magnitude() > detectionRange)return; //Dont follow if they are too far.
	
	dirVec.Normalise();
	_position = _position + dirVec * speed * deltaTime;
	
}
