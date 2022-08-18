#pragma once
#include "Actor.h"
class Enemy :public Actor
{
public:
	Enemy(class Game* game,Vector2 pos,int number);
	~Enemy();
	void UpdateActor(float deltaTime) override;
	Vector2 GetEnemyPosition() const { return mPosition; }
private:
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	class AIComponent* mAI;
	// 0����n�܂�Enemy���ʔԍ�
	int IDNo;
	Vector2 mPosition;
};