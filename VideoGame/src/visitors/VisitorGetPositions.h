#pragma once
#include "visitors/Visitor.h"
#include "actors/Enemy.h"

namespace visitors
{
	class VisitorGetPositions :public Visitor
	{
	public:
		VisitorGetPositions(class ::Scene* scene);
		~VisitorGetPositions();
		void VstEnemy(class ::Enemy* enemy) override;

	};
}