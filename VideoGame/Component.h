#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	// FIXME: Start���N���b�V������
	virtual void Start() {};
	virtual void ProcessInput(const uint8_t *keyState){};
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//
	class Actor* mOwner;
	// �l���������������ɍX�V�����
	int mUpdateOrder;
	class Game* mGame;
};