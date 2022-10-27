#pragma once
#include "message/Message.h"

namespace managers
{
	class MakeDangeon;
}

namespace message
{
	class ManagerMessage:public Message
	{
	public:
		ManagerMessage();
		managers::MakeDangeon* makeDangeon;
	};

}