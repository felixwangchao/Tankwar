#pragma once
#include "Data.h"
#include "Draw.h"

//地图元素单元结构体
class mapCell:virtual public CDraw {
private:
	unsigned int mapCellType;		// 32种状态 支持7种墙种类,以及多种特别属性,玩家出生点,CAMP_NPC出生点,buff,defuff......	

	unsigned int showLevel;			// 显示级别 分3级别 阴影0,坦克1,物品或树林2 //当两物体重叠是判断

	unsigned int color;

	bool mis_pass;					// 子弹是否能够穿过该地形

	bool mis_destory;				// 子弹是否能够摧毁该地形

	bool tank_pass;					// 坦克是否能够通过该地形

public:
	mapCell();						// 无参构造函数

	mapCell(int mapCellType);		// 有参构造函数

	void setMapCellInfo(			// 设置地图点信息
		int mapCellType,			// 地图点类型
		int color,					// 颜色
		int showLevel,				// 显示等级
		bool mis_pass,				// 子弹是否能通过
		bool mis_destory,			// 子弹是否能摧毁
		bool tank_pass);			// 坦克是否能通过

	void drawMapCell(int row, int col, int tmp_color = 0);		// 绘制地图点

	void Destory();

public:

	// ShowLevel接口
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// Mis_PASS 接口
	bool Mis_pass() const { return mis_pass; }
	void Mis_pass(bool val) { mis_pass = val; }

	// mis_destory 接口
	bool Mis_destory() const { return mis_destory; }
	void Mis_destory(bool val) { mis_destory = val; }

	// Tank_pass接口
	bool Tank_pass() const { return tank_pass; }
	void Tank_pass(bool val) { tank_pass = val; }

	// MapCellType接口
	unsigned int MapCellType() const { return mapCellType; }
	void MapCellType(unsigned int val) { mapCellType = val; }

	// Color 接口
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }
};

class Map: virtual public CDraw{
public:
	mapCell MapData[40][40];			//静态地图
	int LMapData[40][40];
	Map();
	void InitMap(int load_map[][40]);
	void drawMap();
};

extern Map CurrentMap;