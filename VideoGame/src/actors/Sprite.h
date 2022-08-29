#pragma once
#include "Actor.h"

class Sprite :public Actor
{
public:
	Sprite(class Scene* scene);
	~Sprite();
private:
	class SpriteComponent* sprite;
};