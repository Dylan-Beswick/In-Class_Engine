#include "Enemy.h"

Enemy::Enemy(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames)
	: Character::Character(CharacterTexture, Pos, NumberOfFrames)
{
	MaxSpeed = 300.0f;
	Tag = "Enemy";
}

Enemy::~Enemy()
{

}

void Enemy::Update(float DeltaTime)
{
	Character::Update(DeltaTime);

	float Speed = 1200.0f;

	AddForce(Speed, Vector2(1.0f, 0.0f));
}
