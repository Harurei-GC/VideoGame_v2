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

	// 範囲外参照防止のため要素1つ多めに作成
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

// TODO:呼び出し1回で十分だからコンストラクタでよくね
void MakeDangeon::MakeMaps()
{
	// areaSizeとroomSize[][]とroomPosition[][]を決定
	// （Game.cpp）roomSizeとroomPositionを使用して空白となる空間を描画
	areaNumX = rand->Sampling(1, 3);
	areaNumY = rand->Sampling(2, 4);
	areaCountSize.x = W_BOXES / areaNumX;
	areaCountSize.y = H_BOXES / areaNumY;
	// roomPositionが変化しうる範囲
	Vector2Int range;
	// roomPositionを決定するための乱数生成
	Vector2Int r;
	for (int i = 0; i < areaNumX; i++)
	{
		for (int j = 0; j < areaNumY; j++)
		{
			if ((i == 0)&&(j == 0))
			{// プレイヤー登場エリアのみ固定で、そこに最大値の部屋を生成
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
	// HACK:もっときれいに書きたい
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
	// TODO:一部の通路は行き止まりにしたい
	// 最初の部屋以外でランダムに
	int rx = rand->Sampling(1, areaNumX-1);
	int ry = rand->Sampling(1, areaNumY-1);

	for (int hor = 0; hor < areaNumX; hor++)
	{
		for (int ver = 0; ver < areaNumY; ver++)
		{


			// 現在指している部屋
			position = roomBoxPosition[hor][ver];
			// 入力座標がxyどちらにも被っていなければ

			// x方向の連絡通路
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
			// y方向の連絡通路
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
				// y方向の通路なのか確認
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
				// x方向の通路なのか確認
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