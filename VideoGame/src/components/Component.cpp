#include "components/Component.h"
#include "actors/Actor.h"

namespace components
{
	Component::Component(actors::Actor* owner, int updateOrder)
		:mOwner(owner)
		,mUpdateOrder(updateOrder)
		,mScene(owner->GetScene())
	{
		// Actorの成分ベクトルに追加
		mOwner->AddComponent(this);
	}


	Component::~Component()
	{
		mOwner->RemoveComponent(this);
	}


	void Component::Update(float deltaTime)
	{

	}
}
