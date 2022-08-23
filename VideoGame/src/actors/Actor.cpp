#include "Actor.h"
#include "../components/Component.h"
#include "../Game.h"

Actor::Actor(Game* game)
	:mState(State::Active)
	,mScale(1.0f)
	,mPosition(Vector2::Zero)
	,mRotation(0.0f)
	,mMass(1.0f)
	,mFriction(0.0f)
	,mGame(game)
	,IDNo(-1)
	,mHP(100)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Start()
{
	if (mState == State::Active)
	{
		for (auto component : mComponents)
		{
			component->Start();
		}
	}
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == State::Active)
	{
		for (auto component : mComponents)
		{
			component->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::AddComponent(Component* component)
{
	// ソートされたベクトルの挿入点を探す
	// (自分より高い次数を持つ最初の要素)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == State::Active)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{

}
