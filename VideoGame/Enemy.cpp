#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"

Enemy::Enemy(Game* game)
	:Actor(game)
{
	SpriteComponent* sprite = new SpriteComponent(this);
	mGame->AddEnemy(this);
}

Enemy::~Enemy()
{
	mGame->RemoveEnemy(this);
}