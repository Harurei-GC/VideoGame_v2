#include "Game.h"
#include "Goal.h"
#include "SpriteComponent.h"
#include "CircleComponent.h"
#include "Mob.h"
#include "Random.h"

Goal::Goal(Game* game) 
	:Actor(game)
{
	SetRole(Role::Goal);

	SpriteComponent* sprite = new SpriteComponent(this,80);
	sprite->SetTexture(game->GetTexture("assets/Goal.png"));
	Random* rand = new Random();
}

void Goal::UpdateActor(float deltaTime)
{

}

void Goal::ActorInput(const uint8_t* keyState)
{

}

Vector2Int Goal::RandomPosition(class MakeDangeon* dangeon)
{
	Vector2Int position = dangeon->getLastRoomBoxPosition();
	Vector2Int size = dangeon->getLastRoomSize();
	while (true)
	{
		Vector2Int mPosition = { rand->Sampling(position.x, position.x + size.x - 1),rand->Sampling(position.y, position.y + size.y - 1) };
		if (mPosition == position) { continue; }
		return mPosition;
	}

}

bool GoalIntersect(const Goal& goal, Mob& mob)
{
	float X = goal.GetPosition().x - mob.GetPosition().x;
	if (X < 0) { X = -X; }
	float Y = goal.GetPosition().y - mob.GetPosition().y;
	if (Y < 0) { Y = -Y; }
	Vector2 diff = Vector2(X, Y);

	float XY = CHARACHIP_EDGE / 2 + mob.GetCircle()->GetRadius();
	Vector2 radiiSq = Vector2(XY, XY);

	return (diff.x <= radiiSq.x) && (diff.y <= radiiSq.y);
}