#pragma once
#include "Component.h"

class AIComponent :public Component
{
public:
	AIComponent(class Actor* owner, int updateOrder = 40);
private:

};