#include "visitors/VisitorGetPositions.h"

#define DEBUG_VISITORGETPOSITION_CPP_
#ifdef DEBUG_VISITORGETPOSITION_CPP_ // デバッグ時のみインクルード
#include <iostream>
#endif

namespace visitors
{
	VisitorGetPositions::VisitorGetPositions(::Scene* scene)
		:Visitor(scene)
	{

	}

	VisitorGetPositions::~VisitorGetPositions()
	{

	}

	void VisitorGetPositions::VstEnemy(::Enemy* enemy)
	{
		Vector2 pos = enemy->GetPosition();
		enemy->SetPosition(Vector2{pos.x + 1.0f,pos.y + 1.0f });

#ifdef DEBUG_VISITORGETPOSITION_CPP_
		std::cout << enemy->GetPosition().x << ", " << enemy->GetPosition().y << std::endl;
#endif
	}
}