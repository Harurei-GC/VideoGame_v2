#pragma once

namespace actors { class Actor; }

namespace commands
{
	// �R�}���h�p�^�[�����������邽�߂̊�{�N���X
	class Command
	{
	public:
		~Command();
		virtual void execute(actors::Actor* actor) {}
	};
}