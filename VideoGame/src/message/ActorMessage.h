#pragma once
#include "message/Message.h"
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

namespace message
{
	class ActorMessage:public Message
	{
	public:
		ActorMessage();
		~ActorMessage();

		std::map<int, ch::Enemy*>* enemy;
		ch::Friend* fri;
		ch::MBox* mbox;
		ch::Player* player;
	};
}