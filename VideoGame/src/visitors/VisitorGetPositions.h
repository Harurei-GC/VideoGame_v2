#pragma once
#include "visitors/Visitor.h"
#include "actors/characters/Enemy.h"

namespace visitors
{
	class VisitorGetPositions :public Visitor
	{
	public:
		VisitorGetPositions(scenes::Scene* scene);
		~VisitorGetPositions();
		void VstEnemy(ch::Enemy* enemy) override;

	};
}