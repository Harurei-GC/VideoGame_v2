#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent :public Component
{
public:
	CircleComponent(class Actor* owner);
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius()const;
	const Vector2& GetCenter() const;
private:
	float mRadius;
};

//// 2つのオブジェクトが衝突している場合true
//bool Intersect(const CircleComponent& a, const CircleComponent& b);
//bool IntersectAsPosition(class CircleComponent& ac, class CircleComponent& bc, Vector2 a, Vector2 b);
