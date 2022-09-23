#include "../scenes/Battle.h"
#include "../actors/Object.h"
#include "../actors/Actor.h"
#include "../actors/Player.h"
#include "../actors/Friend.h"
#include "../actors/Mob.h"
#include "../actors/Enemy.h"
#include <iostream>

ConfigureMovementStatus::ConfigureMovementStatus(Battle* battle)
	:cBattle(battle)
{
}

void ConfigureMovementStatus::Start()
{
	player = cBattle->GetPlayer();
	// fri = cBattle->GetFriend();
	mob = cBattle->GetMob();
	enemy = cBattle->GetEnemiesMap();
}

void ConfigureMovementStatus::Update(float deltaTime)
{
	bool isEnemyDamaged[ENEMIES] = { 0 };

	// NOTE:x������y����������
	for (int i = 0; i < 2; i++)
	{
		// ���̌J��Ԃ���x����y����
		char a;
		(i == 0) ? a = 'x' : a = 'y';
		// player���_
		// NOTE:����Rigidbody�Ŏ��t���[���̍��W���v�Z�ς݂ł��邩��A��{�I�ɂ��̍��W�ł���ReplacePosition���g���B
		if (Intersect(player->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
			, player->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, mob, player,-1, a);
		}
		//if (Intersect(player->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
		//	, player->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
		//{
		//	JudgeActorsCollision(deltaTime, fri, player,-1, a);
		//}
		// friend���_
		//if (Intersect(fri->GetCircle()->GetRadius(), mob->GetCircle()->GetRadius()
		//	, fri->GetRigidbody()->GetReplacePosition(), mob->GetRigidbody()->GetReplacePosition()))
		//{
		//	JudgeActorsCollision(deltaTime, mob, fri,-1, a);
		//}
		//if (Intersect(fri->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
		//	, fri->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
		//{
		//	JudgeActorsCollision(deltaTime, player, fri,-1, a);
		//}
		// mob���_
		if (Intersect(mob->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
			, mob->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
		{
			JudgeActorsCollision(deltaTime, player, mob,-1, a);
		}
		//if (Intersect(mob->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
		//	, mob->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
		//{
		//	JudgeActorsCollision(deltaTime, fri, mob,-1, a);
		//}
		
		// enemy�Ɋ֘A���鏈��
		for (int j = 0; j < ENEMIES; j++)
		{
			// �L�[j���w���v�f���c���Ă���Δ���
			if (enemy.find(j) != enemy.end())
			{
				// WARNING:y�����ɏՓ˂���ƁAx���̏ꍇ��y���̏ꍇ��2������������肩�������
				if (Intersect(enemy.at(j)->GetCircle()->GetRadius(), player->GetCircle()->GetRadius()
					, enemy.at(j)->GetRigidbody()->GetReplacePosition(), player->GetRigidbody()->GetReplacePosition()))
				{
					isEnemyDamaged[j] = IsMeDamaged(player->GetRigidbody()->GetSpeed(),enemy.at(j)->GetRigidbody()->GetSpeed(),
						player->GetRigidbody()->GetReplacePosition(), enemy.at(j)->GetRigidbody()->GetReplacePosition());
					// WARNING:���̊֐���Player���_�Benemy��player�̈������t�ɂ���Ƌ��������������Ȃ�B
					// Player���_�̏�������Ɏ����Ă������ɂ��Aenemy�����ʂ��邱�Ƃ��o���Ȃ��Ȃ�B�Ȃ̂ł����ɒu���Ă����B
					JudgeActorsCollision(deltaTime, enemy.at(j),player, j, a);
				}
				//if (Intersect(enemy.at(j)->GetCircle()->GetRadius(), fri->GetCircle()->GetRadius()
				//	, enemy.at(j)->GetRigidbody()->GetReplacePosition(), fri->GetRigidbody()->GetReplacePosition()))
				//{
				//	isEnemyDamaged[j] = IsMeDamaged();
				//	JudgeActorsCollision(deltaTime, enemy.at(j), fri, j, a);
				//}
			}
		}
	}

	// �_���[�W��^���邽�߂̏���
	// NOTE:���̏����Ɛ؂藣�����ƂŁA1�t���[�����Ń_���[�W�������Z����鎖��h��
	for (int i = 0; i < ENEMIES; i++)
	{
		if (isEnemyDamaged[i])
		{
			enemy.at(i)->TakeDamage(50);
		}
	}
}

bool ConfigureMovementStatus::Intersect(RADIUS arad, RADIUS brad, Vector2 apos, Vector2 bpos)
{
	Vector2 diff = apos - bpos;
	float distSq = diff.LengthSq();
	float radiiSq = arad + brad;
	radiiSq *= radiiSq;
	return distSq <= radiiSq;
}

void ConfigureMovementStatus::JudgeActorsCollision(float deltaTime,Actor* you, Actor* me,int ID, char axis)
{
	Vector2 position;
	Vector2 meSpeed;
	Vector2 youSpeed;
	position = me->GetRigidbody()->GetReplacePosition();
	meSpeed = me->GetRigidbody()->GetSpeed();
	youSpeed = you->GetRigidbody()->GetSpeed();
	
	// �Փ˔���
	// me��ReplacePosition�Ayou�͌��݂�Position
	if (Intersect(me->GetCircle()->GetRadius(),you->GetCircle()->GetRadius(),me->GetRigidbody()->GetReplacePosition(),you->GetPosition()))
	{
		switch (axis)
		{
		case 'x':
			position.x -= meSpeed.x * deltaTime;
			SwapSpeed(meSpeed.x, youSpeed.x);
			break;
		case 'y':
			position.y -= meSpeed.y * deltaTime;
			SwapSpeed(meSpeed.y, youSpeed.y);
			break;
		default:
			break;
		}
		me->GetRigidbody()->SetReplacePosition(position);
		me->GetRigidbody()->SetSpeed(meSpeed);
		switch (you->GetRole())
		{
		case Actor::Role::Mob:
			mob->GetRigidbody()->SetSpeed(youSpeed);
			break;
		case Actor::Role::Player:
			player->GetRigidbody()->SetSpeed(youSpeed);
			break;
		//case Actor::Role::Friend:
		//	fri->GetRigidbody()->SetSpeed(youSpeed);
		//	break;
		case Actor::Role::Enemy:
			enemy.at(ID)->GetRigidbody()->SetSpeed(youSpeed);
			break;
		default:
			break;
		}
	}
}

template<typename T>
void ConfigureMovementStatus::SwapSpeed(T& aSpeed, T& bSpeed)
{
	T tmp = aSpeed;
	aSpeed = bSpeed;
	bSpeed = tmp;
}

// NOTE:Battle.cpp�ŌĂяo��
void ConfigureMovementStatus::SetActorsPosition()
{
	player->SetPosition(player->GetRigidbody()->GetReplacePosition());
	//fri->SetPosition(fri->GetRigidbody()->GetReplacePosition());
	mob->SetPosition(mob->GetRigidbody()->GetReplacePosition());
	for (auto iter = enemy.begin(); iter != enemy.end(); ++iter)
	{
		iter->second->SetPosition(iter->second->GetRigidbody()->GetReplacePosition());
	}
}

bool ConfigureMovementStatus::IsMeDamaged(Vector2 youSpeed, Vector2 meSpeed, Vector2 youPos, Vector2 mePos)
{
	if ((youSpeed.x == 0.0f)&&(youSpeed.y == 0.0f))
	{// �Փː�̑���̑��x���O�i�����Ă��Ȃ��j�Ȃ�΁Ame�Ƀ_���[�W�͓���Ȃ�
		return false;
	}
	else if ((meSpeed.x == 0.0f) && (meSpeed.y == 0.0f) )
	{// �Փˎ�me�̑��x���O�i�����Ă��Ȃ��j�Ȃ�΁A�_���[�W�󂯂�
		return true;
	}

	// ���x�̓��ς��v�Z���A���������������ꍇ�_���[�W���肪������
	if (Vector2::Dot(youSpeed, meSpeed) < 0)
	{// ���̏ꍇ�����ʏՓˁ��_���[�W�͂Ȃ�
		return false;
	}
	else
	{// ���̏ꍇ
		// you��me�ǂ��炪�O���ɂ��邩���肵�Ame���O���ɂ���ꍇ�Ƀ_���[�W�����B
		// ���̂��߂ɁAyouPos���猩��mePos�ւ̕����x�N�g���̕����ƁAyouSpeed�̕����x�N�g���̕������r����B
		// x����y�����ꂼ�ꕄ���������Ȃ�΁Ame��you�����O���ɂ��邱�ƂƂȂ�B
		Vector2Int sign = Vector2Int{ int(mePos.x - youPos.x), int(mePos.y - youPos.y) };
		// NOTE:0���Z�h�~�̂��ߏꍇ����
		sign = Vector2Int{ (sign.x == 0.0f)?0:(sign.x / std::abs(sign.x))
			, (sign.y==0.0f)?0:(sign.y / std::abs(sign.y)) };
		Vector2Int speed = Vector2Int{ (youSpeed.x == 0.0f) ? 0 : (int(youSpeed.x / std::abs(youSpeed.x))) 
			,(youSpeed.y == 0.0f)?0: (int(youSpeed.y / std::abs(youSpeed.y))) };
		if ((sign.x == speed.x) && (sign.y == speed.y))
		{// you���猩��me��you�̐i�s�����ɂ���ꍇ��me�̓_���[�W�󂯂�
			return true;
		}
		else
		{// �_���[�W�͓���Ȃ�
			return false;
		}
	}
}