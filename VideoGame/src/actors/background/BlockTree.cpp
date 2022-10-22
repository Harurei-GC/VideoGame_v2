// @todo 名前をBlockにリネームしたい

#include "actors/background/BlockTree.h"
#include "scenes/Scene.h"
#include "Math.h"
#include "components/SpriteComponent.h"

namespace actors
{
	namespace background
	{
		BlockTree::BlockTree(scenes::Scene* scene, Vector2 pos)
			:Actor(scene)
		{
			SetRole(Role::BlockTree);
			SetPosition(pos);
			components::SpriteComponent* sprite = new components::SpriteComponent(this,90);
			sprite->SetTexture(scene->GetTexture("assets/Tree.png"));

			mScene->AddBlockTree(this);
		}

		BlockTree::~BlockTree()
		{
			mScene->RemoveBlockTree(this);
		}

		void BlockTree::ActorInput(const uint8_t* keyState)
		{

		}

		void BlockTree::UpdateActor(float deltaTime)
		{

		}
	}
}
