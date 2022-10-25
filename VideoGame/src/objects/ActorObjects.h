#pragma once
#include "objects/Objects.h"
#include <vector>
#include <map>

namespace actors
{
	namespace characters
	{
		class CharacterActor;
		class Enemy;
		class Friend;
		class MBox;
		class Player;
	}
}

namespace ch = actors::characters;

namespace objects
{
	class ActorObjects:public Objects
	{
	public:
		ActorObjects();
		~ActorObjects();

		std::map<int, ch::Enemy*>* enemy;
		ch::Friend* fri;
		ch::MBox* mbox;
		ch::Player* player;
	};
}