#include "visitors/Visitor.h"


namespace visitors
{
	Visitor::Visitor(Scene* scene)
	{
		mScene = scene;
		mScene->AddVisitor(this);
	}

	visitors::Visitor::~Visitor()
	{
		mScene->RemoveVisitor(this);
	}
}