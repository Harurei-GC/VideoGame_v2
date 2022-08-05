#include "MakeDangeon.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
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


	// �ʘH�����
	

	
	//// �e�ϐ��́A��܂��͍��ɐڑ����Ă��镔�����[�����ł���ꍇ�ihor==0�܂���ver==0�̂Ƃ��j
	//// �l���ݒ肳��Ă��Ȃ����ߒ���
	//// corriHead:�ʘH�̓�
	//Vector2Int corriHead[HORIZONTAL][VERTICAL] = { 0 };
	//// corriConnect:area���܂����Ƃ��̒ʘH�̐ڑ���
	//Vector2Int corriConnect[HORIZONTAL][VERTICAL] = {0};
	//// btwnHeadConnect:corriHead��corriConnect�̊Ԃ̋���
	//Vector2Int btwnHeadConnect[HORIZONTAL][VERTICAL] = { 0 };
	//// btwnConnectRoom:corriConnect��roomBoxPosition�̊Ԃ̋���
	//Vector2Int btwnConnectRoom[HORIZONTAL][VERTICAL] = { 0 };
	//// ���l���
	//for (int hor = 0; hor < areaNumX; hor++)
	//{
	//	for(int ver = 0; ver < areaNumY; ver++)
	//	{
	//		if (hor != 0) { // x����
	//			corriHead[hor][ver].x = roomBoxPosition[hor-1][ver ].x + roomBoxes[hor-1][ver].x;
	//			corriConnect[hor][ver].x = hor * areaCountSize.x + 1;
	//			btwnHeadConnect[hor][ver].x = corriConnect[hor][ver].x - corriHead[hor][ver].x;
	//			btwnConnectRoom[hor][ver].x = roomBoxPosition[hor][ver].x - corriHead[hor][ver].x + 1;
	//		}
	//		if (ver != 0) { // y����
	//			corriHead[hor][ver].y = roomBoxPosition[hor][ver-1].y + roomBoxes[hor][ver-1].y;
	//			corriConnect[hor][ver].y = ver*areaCountSize.y + 1;
	//			btwnHeadConnect[hor][ver].y = corriConnect[hor][ver].y-corriHead[hor][ver].y;
	//			btwnConnectRoom[hor][ver].y = roomBoxPosition[hor][ver].y - corriHead[hor][ver].y + 1;
	//		}
	//	}
	//}
	//// �ʘH���W�ϐ�
	//// �ʘH�̍��W�������_���Ɍ���
	//int tmp = -1;
	//for (int hor = 0; hor < areaNumX; hor++)
	//{
	//	for (int ver = 0; ver < areaNumY; ver++)
	//	{
	//		// ���������̒ʘH�쐬
	//		if (hor != 0) {
	//			// �����̍�����W��corriHead�ʒu�̊Ԃ���ʘH�̐ڑ��ʒu����
	//			// HACK:��₱����
	//			// �ŏ��ɒʘH��y���W�������_���Ɍ��߂�
	//			tmp = rand->Sampling(roomBoxPosition[hor-1][ver].y,corriHead[hor-1][ver+1].y - roomBoxPosition[hor-1][ver].y);
	//			// �ʘH�̑O���������
	//			for (int i = 0; i < btwnHeadConnect[hor][ver].x; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriHead[hor][ver].x + i, tmp });
	//			}
	//			// ������xy���W�������_���ɐ���
	//			tmp = rand->Sampling(roomBoxPosition[hor][ver].y, corriHead[hor][ver+1].y - roomBoxPosition[hor][ver].y);
	//			// �ʘH�̌㔼�������
	//			for (int i = 0; i < btwnConnectRoom[hor][ver].x; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriConnect[hor][ver].x + i, tmp });
	//			}
	//		}
	//		// ���������̒ʘH�쐬
	//		if (ver != 0)
	//		{
	//			tmp = rand->Sampling(roomBoxPosition[hor][ver - 1].x, corriHead[hor+1][ver-1].x - roomBoxPosition[hor][ver - 1].x);

	//			for (int i = 0; i < btwnHeadConnect[hor][ver].y; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriHead[hor][ver].y + i,tmp });
	//			}

	//			tmp = rand->Sampling(roomBoxPosition[hor][ver].x, corriHead[hor + 1][ver].x - roomBoxPosition[hor][ver].x);

	//			for (int i = 0; i < btwnConnectRoom[hor][ver].y; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriHead[hor][ver].y + i,tmp });
	//			}
	//		}
	//	}
	//}

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
	for (int hor = 0; hor < areaNumX; hor++)
	{
		for (int ver = 0; ver < areaNumY; ver++)
		{


			// ���ݎw���Ă��镔��
			position = roomBoxPosition[hor][ver];
			// ���͍��W��xy�ǂ���ɂ�����Ă��Ȃ����

			// x�����̘A���ʘH
			if (y == roomBoxPosition[hor][ver + 1].y)
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
			if (x == roomBoxPosition[hor + 1][ver].x)
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
			if (x == position.x)
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
			if (y == position.y)
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



	//for (int i = 1; i < allCorridor.size(); i++)
	//{
	//	if (allCorridor.at(i).x == x && allCorridor.at(i).y == y) 
	//	{
	//		return true;
	//	}
	//}
	//return false;
}