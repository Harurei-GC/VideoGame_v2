#pragma once
#include "Actor.h"

class Sprite :public Actor
{
public:
	Sprite(class Game* game);
	~Sprite();
private:
	class SpriteComponent* sprite;
};