#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Start() {};
	virtual void ProcessInput(const uint8_t *keyState){};
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	// ’l‚ª¬‚³‚¢•û‚©‚çæ‚ÉXV‚³‚ê‚é
	int mUpdateOrder;
	class Scene* mScene;
};