#include "visitors/VisitorGetPositions.h"

#define DEBUG_VISITORGETPOSITION_CPP_
#ifdef DEBUG_VISITORGETPOSITION_CPP_ // �f�o�b�O���̂݃C���N���[�h
#include <iostream>
#endif

namespace visitors
{
	VisitorGetPositions::VisitorGetPositions(scenes::Scene* scene)
		:Visitor(scene)
	{

	}

	VisitorGetPositions::~VisitorGetPositions()
	{

	}

	void VisitorGetPositions::VstEnemy(ch::Enemy* enemy)
	{
#ifdef DEBUG_VISITORGETPOSITION_CPP_
		std::cout << enemy->GetPosition().x << ", " << enemy->GetPosition().y << std::endl;
#endif
	}
}