#include "visitors/Visitor.h"


namespace visitors
{
	Visitor::Visitor(scenes::Scene* scene)
	{
		mScene = scene;
		mScene->AddVisitor(this);
	}

	Visitor::~Visitor()
	{
		mScene->RemoveVisitor(this);
	}
}