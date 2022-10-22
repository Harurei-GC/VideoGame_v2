#pragma once
#include <cstdint>

namespace actors
{
	class Actor;
}
namespace scenes { class Scene; }

namespace components
{
	class Component
	{
	public:
		Component(actors::Actor* owner, int updateOrder = 100);
		virtual ~Component();
		virtual void Start() {};
		virtual void ProcessInput(const uint8_t *keyState){};
		virtual void Update(float deltaTime);
		int GetUpdateOrder() const { return mUpdateOrder; }
	protected:
		actors::Actor* mOwner;
		// 値が小さい方から先に更新される
		int mUpdateOrder;
		scenes::Scene* mScene;
	};
}
