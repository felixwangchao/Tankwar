#pragma once
#include "Draw.h"
#include "mapCell.h"

class MapEditor : public CDraw{
public:
	MapEditor();
	void InitMapEditor();					// 初始化

	void printMapEditorMenu();				// 打印菜单

	void cleanMenu();						// 清除菜单

	void GetMousePos();						// 获取鼠标坐标

	void terrainPrint(int x, int y);		// 在目标位置画地形

	void paintWithBrush(int x, int y, int wall, char* str, int color);	// 在目标位置画指定的内容
private:
	int DrawingBoard[40][40];
	Map m;
	HANDLE hInput;					/*  获取标准输入设备句柄 */
	INPUT_RECORD inRec;				/*  返回数据记录 */
	DWORD numRead;					/*  返回已读取的记录数 */
	COORD pos;						/*  坐标  */
	int X, Y;						/*  坐标，使用方法：X = pos.x */
	int terrainType = 0;				/*  定义土地类型 */

};