#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	// このコンポーネントに対する処理入力（オーバーライド）
	virtual void ProcessInput(const uint8_t *keyState){};
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//
	class Actor* mOwner;
	//
	int mUpdateOrder;
	class Game* mGame;
};