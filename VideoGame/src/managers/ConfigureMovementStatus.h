#pragma once
#include <vector>
#include "math/Math.h"

namespace scenes { class ScnBattle; }
namespace actors
{
	namespace characters
	{
		class Player;
		class MBox;
		class Enemy;
	}
}namespace ch = actors::characters;

namespace managers
{
	using RADIUS = float;

	class ConfigureMovementStatus
	{
	public:
		ConfigureMovementStatus(scenes::ScnBattle* battle);
		void Start();
		void Update(float deltaTime);
		void SetActorsPosition();
		void EraseEnemy(int i) { enemy.erase(enemy.find(i)); }
	private:
		bool Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos);
		void JudgeActorsCollision(float deltaTime, actors::Actor* you, actors::Actor* me, int ID, Dim2 axis);
		template<typename T>void SwapSpeed(T& aSpeed, T& bSpeed);
		bool IsMeDamaged(Vector2 youSpeed, Vector2 meSpeed, Vector2 youPos, Vector2 mePos);
		scenes::ScnBattle* cBattle;
		ch::Player* player;
		// class Friend* fri;
		ch::MBox* mbox;
		std::map<int, ch::Enemy*>enemy;
	};
}
