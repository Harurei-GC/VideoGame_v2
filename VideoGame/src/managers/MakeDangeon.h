#pragma once
#include <vector>
#include "math/Math.h"

#define HORIZONTAL 3 // x����
#define VERTICAL 4 // y����
#define W_BOXES 32 // �������̃}�X�ڂ̐�
#define H_BOXES 24 // �c�����̃}�X�ڂ̐�

namespace managers
{
	class MakeDangeon
	{
	public:
		MakeDangeon();
		// �����̍��W�������̒��ɂ��邩
		bool IsInRooms(int x, int y);
		// �����̍��W���ʘH�Ɣ���Ă��邩
		bool IsInCorridor(int x, int y);
		// �Ō���̕�����position�擾
		Vector2Int getLastRoomBoxPosition()
		{
			return roomBoxPosition[areaNumX - 1][areaNumY - 1];
		}
		Vector2Int getLastRoomSize()
		{
			return roomBoxes[areaNumX - 1][areaNumY - 1];
		}
		int GetAreaNumX() { return areaNumX; }
		int GetAreaNumY() { return areaNumY; }
		Vector2Int GetRoomBoxPosition(int x, int y) { return roomBoxPosition[x][y]; }
		Vector2Int GetRoomBoxes(int x, int y) { return roomBoxes[x][y]; }

	private:
		void MakeMaps();
	
		// �c�����������͉������̃G���A�̐�
		int areaNumX;
		int areaNumY;
		// �G���A�F���������������\���̂����Ԃ̋�؂�
		// �e�G���A�̃}�X��
		Vector2Int areaCountSize;
		// �e�����̃}�X��
		// �v�f+1
		Vector2Int roomBoxes[HORIZONTAL+1][VERTICAL+1];
		// �e�����̍��㒸�_�̃}�X�ʒu
		// �v�f+1
		Vector2Int roomBoxPosition[HORIZONTAL+1][VERTICAL+1];
		// �ʘH���W�ϐ�
		// �ŏ���(-1,-1)�̃_�~�[���i�[����Ă��邽�ߒ���
		std::vector<Vector2Int> allCorridor;

	};


}
