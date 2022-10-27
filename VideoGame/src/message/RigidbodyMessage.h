#pragma once
#include "message/Message.h"
#include "components/RigidbodyComponent.h"

namespace message
{
	class RigidbodyMessage :public Message
	{
	public:
		RigidbodyMessage();
		components::RigidbodyComponent* rigidbody;
	};

	RigidbodyMessage::RigidbodyMessage()
		:rigidbody(nullptr)
	{

	}
}