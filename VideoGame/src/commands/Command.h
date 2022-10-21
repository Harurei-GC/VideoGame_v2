#pragma once

namespace actors { class Actor; }

namespace commands
{
	// コマンドパターンを実装するための基本クラス
	class Command
	{
	public:
		~Command();
		virtual void execute(actors::Actor* actor) {}
	};
}