#pragma once
#include <vector>
#define HORIZONTAL 3 // x����
#define VERTICAL 4 // y����

// TODO:���Z�q�̃I�[�o�[���[�h�o������y
struct Vector2Int
{
	int x;
	int y;

	Vector2Int operator+(Vector2Int obj)
	{
		return Vector2Int{ this->x + obj.x, this->y + obj.y };
	}

	Vector2Int operator-(Vector2Int obj)
	{
		return Vector2Int{ this->x - obj.x, this->y - obj.y };
	}
	bool operator==(Vector2Int obj)
	{
		return (this->x == obj.x) && (this->y == obj.y);
	}
};

struct Vector2Vector
{
	Vector2Int x;
	Vector2Int y;
};

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
	//void getRoomSize(Vector2Int data[3][4])
	//{
	//	for (int i = 0; i < HORIZONTAL; i++)
	//	{
	//		for (int j = 0; j < VERTICAL; j++)
	//		{
	//			data[i][j] = roomBoxes[i][j];
	//		}
	//	}
	//}
	//void getRoomBoxPosition(Vector2Int data[3][4])
	//{
	//	for (int i = 0; i < HORIZONTAL; i++)
	//	{
	//		for (int j = 0; j < VERTICAL; j++)
	//		{
	//			data[i][j] = roomBoxPosition[i][j];
	//		}
	//	}
	//}
private:
	void MakeMaps();

	// 7/27 �ϐ����ύX
	// xBox,yBox->areaNumX,areaNumY
	// areaSize->areaCountSize
	// roomSize->roomBoxes
	// roomPosition->roomBoxPosition
	
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
	// �������W�ꎞ�ۑ��p
	Vector2Int position;

	class Random* rand;
};

