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


	// 通路を作る
	

	
	//// 各変数は、上または左に接続している部屋が端っこである場合（hor==0またはver==0のとき）
	//// 値が設定されていないため注意
	//// corriHead:通路の頭
	//Vector2Int corriHead[HORIZONTAL][VERTICAL] = { 0 };
	//// corriConnect:areaをまたぐときの通路の接続部
	//Vector2Int corriConnect[HORIZONTAL][VERTICAL] = {0};
	//// btwnHeadConnect:corriHeadとcorriConnectの間の距離
	//Vector2Int btwnHeadConnect[HORIZONTAL][VERTICAL] = { 0 };
	//// btwnConnectRoom:corriConnectとroomBoxPositionの間の距離
	//Vector2Int btwnConnectRoom[HORIZONTAL][VERTICAL] = { 0 };
	//// 数値代入
	//for (int hor = 0; hor < areaNumX; hor++)
	//{
	//	for(int ver = 0; ver < areaNumY; ver++)
	//	{
	//		if (hor != 0) { // x方向
	//			corriHead[hor][ver].x = roomBoxPosition[hor-1][ver ].x + roomBoxes[hor-1][ver].x;
	//			corriConnect[hor][ver].x = hor * areaCountSize.x + 1;
	//			btwnHeadConnect[hor][ver].x = corriConnect[hor][ver].x - corriHead[hor][ver].x;
	//			btwnConnectRoom[hor][ver].x = roomBoxPosition[hor][ver].x - corriHead[hor][ver].x + 1;
	//		}
	//		if (ver != 0) { // y方向
	//			corriHead[hor][ver].y = roomBoxPosition[hor][ver-1].y + roomBoxes[hor][ver-1].y;
	//			corriConnect[hor][ver].y = ver*areaCountSize.y + 1;
	//			btwnHeadConnect[hor][ver].y = corriConnect[hor][ver].y-corriHead[hor][ver].y;
	//			btwnConnectRoom[hor][ver].y = roomBoxPosition[hor][ver].y - corriHead[hor][ver].y + 1;
	//		}
	//	}
	//}
	//// 通路座標変数
	//// 通路の座標をランダムに決定
	//int tmp = -1;
	//for (int hor = 0; hor < areaNumX; hor++)
	//{
	//	for (int ver = 0; ver < areaNumY; ver++)
	//	{
	//		// 水平方向の通路作成
	//		if (hor != 0) {
	//			// 部屋の左上座標とcorriHead位置の間から通路の接続位置決定
	//			// HACK:ややこしい
	//			// 最初に通路のy座標をランダムに決める
	//			tmp = rand->Sampling(roomBoxPosition[hor-1][ver].y,corriHead[hor-1][ver+1].y - roomBoxPosition[hor-1][ver].y);
	//			// 通路の前半分を作る
	//			for (int i = 0; i < btwnHeadConnect[hor][ver].x; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriHead[hor][ver].x + i, tmp });
	//			}
	//			// もう一度y座標をランダムに生成
	//			tmp = rand->Sampling(roomBoxPosition[hor][ver].y, corriHead[hor][ver+1].y - roomBoxPosition[hor][ver].y);
	//			// 通路の後半分を作る
	//			for (int i = 0; i < btwnConnectRoom[hor][ver].x; i++)
	//			{
	//				allCorridor.push_back(Vector2Int{ corriConnect[hor][ver].x + i, tmp });
	//			}
	//		}
	//		// 垂直方向の通路作成
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
	for (int hor = 0; hor < areaNumX; hor++)
	{
		for (int ver = 0; ver < areaNumY; ver++)
		{


			// 現在指している部屋
			position = roomBoxPosition[hor][ver];
			// 入力座標がxyどちらにも被っていなければ

			// x方向の連絡通路
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
			// y方向の連絡通路
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
				// y方向の通路なのか確認
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
				// x方向の通路なのか確認
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