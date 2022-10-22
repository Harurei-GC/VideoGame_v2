#pragma once
#include "scenes/Scene.h"

namespace actors
{
	namespace characters
	{
		class Player;
		class Enemy;
		class Friend;
		class MBox;
	}
}namespace ch = actors::characters;


namespace visitors
{
	class Visitor
	{
		// @note　Visitorの機能について
		// 
		// Visitorは、クラス間のデータのやり取りにおいて結合度が
		// 高くならないように設定されたクラスである。
		// 
		// 一つの目的をこなすためにVisitorを派生させる。
		// 例えば、Positionを取得するためのVisitorGetPositionsクラスなど。
		// 取得する必要のあるオブジェクトクラスの関数のみをオーバーライド。
		// 
		// VisitorのインスタンスはSceneクラスで作成する。
		// このインスタンスは、SceneのUpdateで呼び出される。
		// Enemyなどのオブジェクトクラスにてvoid AcceptVisitor(Visitor)を
		// 宣言し、visitors::VstEnemyなどの中に処理を記述する。

	public:
		Visitor(scenes::Scene* scene);
		~Visitor();

		// 各関数で、visit先のオブジェクトに行う処理を記述
		virtual void VstPlayer(ch::Player* player){}
		virtual void VstEnemy(ch::Enemy* enemy){}
		virtual void VstFriend(ch::Friend* fri){}
		virtual void VstMBox(ch::MBox* box){}

	private:
		scenes::Scene* mScene;
	};
}