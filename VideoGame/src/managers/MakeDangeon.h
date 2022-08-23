#pragma once
#include <vector>
#define HORIZONTAL 3 // x方向
#define VERTICAL 4 // y方向

// TODO:演算子のオーバーロード出来たら楽
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
	// 引数の座標が部屋の中にあるか
	bool IsInRooms(int x, int y);
	// 引数の座標が通路と被っているか
	bool IsInCorridor(int x, int y);
	// 最後尾の部屋のposition取得
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

	// 7/27 変数名変更
	// xBox,yBox->areaNumX,areaNumY
	// areaSize->areaCountSize
	// roomSize->roomBoxes
	// roomPosition->roomBoxPosition
	
	// 縦方向もしくは横方向のエリアの数
	int areaNumX;
	int areaNumY;
	// エリア：部屋が生成される可能性のある空間の区切り
	// 各エリアのマス数
	Vector2Int areaCountSize;
	// 各部屋のマス数
	// 要素+1
	Vector2Int roomBoxes[HORIZONTAL+1][VERTICAL+1];
	// 各部屋の左上頂点のマス位置
	// 要素+1
	Vector2Int roomBoxPosition[HORIZONTAL+1][VERTICAL+1];
	// 通路座標変数
	// 最初に(-1,-1)のダミーが格納されているため注意
	std::vector<Vector2Int> allCorridor;
	// 部屋座標一時保存用
	Vector2Int position;

	class Random* rand;
};

