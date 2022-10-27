#pragma once
#include <vector>
#include "math/Math.h"

#define HORIZONTAL 3 // x方向
#define VERTICAL 4 // y方向
#define W_BOXES 32 // 横方向のマス目の数
#define H_BOXES 24 // 縦方向のマス目の数

namespace managers
{
	class MakeDangeon
	{
	public:
		MakeDangeon();
		// 引数の座標が部屋の中にあるか
		bool IsInRooms(int x, int y);
		// 引数の座標がどの部屋にいるか
		Vector2Int WhereInRoom(int x, int y);
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
		int GetAreaNumX() { return areaNumX; }
		int GetAreaNumY() { return areaNumY; }
		Vector2Int GetRoomBoxPosition(int x, int y) { return roomBoxPosition[x][y]; }
		Vector2Int GetRoomBoxes(int x, int y) { return roomBoxes[x][y]; }

	private:
		void MakeMaps();
	
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

	};


}
