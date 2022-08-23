#include "MakeDangeon.h"
#include "../Game.h"
#include "../Random.h"
#include "../Math.h"
#include <vector>
#include <iostream>

MakeDangeon::MakeDangeon()
	:areaNumX(0)
	,areaNumY(0)
	,areaCountSize({0,0})
	,allCorridor{ Vector2Int{-1,-1} }
{
	Random* rand = new Random();

	// �͈͊O�Q�Ɩh�~�̂��ߗv�f1���߂ɍ쐬
	for (int i = 0; i <= HORIZONTAL; i++)
	{
		for (int j = 0; j <= VERTICAL; j++)
		{
			roomBoxes[i][j] = { 0,0 };
			roomBoxPosition[i][j] = { -1,-1 };
		}
	}

	MakeMaps();
}

// TODO:�Ăяo��1��ŏ\��������R���X�g���N�^�ł悭��
void MakeDangeon::MakeMaps()
{
	// areaSize��roomSize[][]��roomPosition[][]������
	// �iGame.cpp�jroomSize��roomPosition���g�p���ċ󔒂ƂȂ��Ԃ�`��
	areaNumX = rand->Sampling(1, 3);
	areaNumY = rand->Sampling(2, 4);
	areaCountSize.x = W_BOXES / areaNumX;
	areaCountSize.y = H_BOXES / areaNumY;
	// roomPosition���ω�������͈�
	Vector2Int range;
	// roomPosition�����肷�邽�߂̗�������
	Vector2Int r;
	for (int i = 0; i < areaNumX; i++)
	{
		for (int j = 0; j < areaNumY; j++)
		{
			if ((i == 0)&&(j == 0))
			{// �v���C���[�o��G���A�̂݌Œ�ŁA�����ɍő�l�̕����𐶐�
				roomBoxes[i][j] = { areaCountSize.x - 2, areaCountSize.y - 2 };

				roomBoxPosition[i][j] = { 1 + areaCountSize.x - 2 - roomBoxes[i][j].x, 1 + areaCountSize.y - 2 - roomBoxes[i][j].y };
				
				continue;
			}
			roomBoxes[i][j] = { rand->Sampling(2,areaCountSize.x - 2), rand->Sampling(2,areaCountSize.y - 2) };

			range = { areaCountSize.x-2 - roomBoxes[i][j].x, areaCountSize.y - 2 - roomBoxes[i][j].y};
			r = { rand->Sampling(0,range.x),rand->Sampling(0,range.y) };

			roomBoxPosition[i][j] = {(i * areaCountSize.x) +1+ r.x , (j * areaCountSize.y) +1+ r.y};
		}
	}

}

bool MakeDangeon::IsInRooms(int x, int y) 
{
	// HACK:�����Ƃ��ꂢ�ɏ�������
	for (int i = 0; i < areaNumX; i++)
	{
		for (int j = 0; j < areaNumY; j++)
		{
			if ((roomBoxPosition[i][j].x <= x) && (x < roomBoxPosition[i][j].x + roomBoxes[i][j].x))
			{
				if ((roomBoxPosition[i][j].y <= y) && (y < roomBoxPosition[i][j].y + roomBoxes[i][j].y))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool MakeDangeon::IsInCorridor(int x, int y)
{
	// TODO:�ꕔ�̒ʘH�͍s���~�܂�ɂ�����
	// �ŏ��̕����ȊO�Ń����_����
	int rx = rand->Sampling(1, areaNumX-1);
	int ry = rand->Sampling(1, areaNumY-1);

	for (int hor = 0; hor < areaNumX; hor++)
	{
		for (int ver = 0; ver < areaNumY; ver++)
		{


			// ���ݎw���Ă��镔��
			position = roomBoxPosition[hor][ver];
			// ���͍��W��xy�ǂ���ɂ�����Ă��Ȃ����

			// x�����̘A���ʘH
			if (y == roomBoxPosition[hor][ver + 1].y || y == roomBoxPosition[hor][ver+1].y+1)
			{
				for (int i = 1; i < (roomBoxPosition[hor][ver + 1].x - roomBoxPosition[hor][ver].x); i++)
				{
					if (x == position.x + i)
					{
						return true;
					}
				}
			}
			// y�����̘A���ʘH
			if (x == roomBoxPosition[hor + 1][ver].x || x == roomBoxPosition[hor+1][ver].x + 1)
			{
				for (int i = 1; i < (roomBoxPosition[hor + 1][ver].y - roomBoxPosition[hor][ver].y); i++)
				{
					if (y == position.y + i)
					{
						return true;
					}
				}
			}
				// y�����̒ʘH�Ȃ̂��m�F
			if (x == position.x || x == position.x+1)
			{
				for (int i = 0; i <= (roomBoxPosition[hor][ver+1].y - roomBoxPosition[hor][ver].y); i++)
				{
					if (y == position.y + i)
					{
						return true;
					}
				}
			}
				// x�����̒ʘH�Ȃ̂��m�F
			if (y == position.y || y == position.y+1)
			{
				for (int i = 0; i <= (roomBoxPosition[hor + 1][ver].x - roomBoxPosition[hor][ver].x); i++)
				{
					if (x == position.x + i)
					{
						return true;
					}
				}
			}
		}
	}

	return false;

}