#pragma once
#include "scenes/Scene.h"

class Player;
class Enemy;
class Friend;
class Mob;

namespace visitors
{
	class Visitor
	{
		// @note�@Visitor�̋@�\�ɂ���
		// 
		// Visitor�́A�N���X�Ԃ̃f�[�^�̂����ɂ����Č����x��
		// �����Ȃ�Ȃ��悤�ɐݒ肳�ꂽ�N���X�ł���B
		// 
		// ��̖ړI�����Ȃ����߂�Visitor��h��������B
		// �Ⴆ�΁APosition���擾���邽�߂�VisitorGetPositions�N���X�ȂǁB
		// �擾����K�v�̂���I�u�W�F�N�g�N���X�̊֐��݂̂��I�[�o�[���C�h�B
		// 
		// Visitor�̃C���X�^���X��Scene�N���X�ō쐬����B
		// ���̃C���X�^���X�́AScene��Update�ŌĂяo�����B
		// Enemy�Ȃǂ̃I�u�W�F�N�g�N���X�ɂ�void AcceptVisitor(Visitor)��
		// �錾���Avisitors::VstEnemy�Ȃǂ̒��ɏ������L�q����B

	public:
		Visitor(Scene* scene);
		~Visitor();

		// �e�֐��ŁAvisit��̃I�u�W�F�N�g�ɍs���������L�q
		virtual void VstPlayer(class ::Player* player){}
		virtual void VstEnemy(class ::Enemy* enemy){}
		virtual void VstFriend(class ::Friend* fri){}
		virtual void VstMob(class  ::Mob* mob){}

	private:
		Scene* mScene;
	};
}