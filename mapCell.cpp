#include "mapCell.h"
#include "Data.h"
#include "Draw.h"

// 无参构造函数
mapCell::mapCell(){
	this->mapCellType = 0;
	this->color = 0;
	this->showLevel = 0;
	this->mis_pass = 0;
	this->mis_destory = 0;
	this->tank_pass = 0;
}

//有参构造函数
mapCell::mapCell(int mapCellType){

	switch (mapCellType){							/*   类型   颜色      显示级别  子弹能否通过， 子弹能否摧毁， 坦克能否通过 */
	case WALL_NULL:		/*空  空道*/    setMapCellInfo(WALL_NULL, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case WALL_A1:		/*▓  土墙*/    setMapCellInfo(WALL_A1, F_RED, SHOWLEVEL_1,false,true,false);	break;
	case WALL_A2:		/*卍  土墙*/    setMapCellInfo(WALL_A2, F_RED, SHOWLEVEL_1,false,true,false);	break;
	case WALL_B:		/*〓  铁墙*/    setMapCellInfo(WALL_B, F_CYAN, SHOWLEVEL_1,false,false,false);	break;
	case WALL_C:		/*≈  河流*/    setMapCellInfo(WALL_C, F_H_BLUE, SHOWLEVEL_0,true,false,false);	break;
	case WALL_D:		/*■  路障*/    setMapCellInfo(WALL_D, F_WHITE, SHOWLEVEL_1,false,false,false);	break;
	case WALL_E:		/*≡  丛林*/    setMapCellInfo(WALL_E, F_H_GREEN, SHOWLEVEL_2,true,false,true);	break;
	case WALL_F:		/*※  高速路*/  setMapCellInfo(WALL_F, F_YELLOW, SHOWLEVEL_0,true,false,true);	break;
	case WALL_G:		/*☆  箱子*/    setMapCellInfo(WALL_G, B_H_YELLOW, SHOWLEVEL_3,true,false,true);	break;
	case CELLSTART_P1:	/*玩家1出生点*/	setMapCellInfo(CELLSTART_P1, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_P2:	/*玩家2出生点*/	setMapCellInfo(CELLSTART_P2, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_P3:	/*玩家3出生点*/	setMapCellInfo(CELLSTART_P3, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N1:	/*NPC1出生点 */	setMapCellInfo(CELLSTART_N1, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N2:	/*NPC2出生点 */	setMapCellInfo(CELLSTART_N2, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N3:	/*NPC3出生点 */	setMapCellInfo(CELLSTART_N3, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N4:	/*NPC4出生点 */	setMapCellInfo(CELLSTART_N4, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N5:	/*NPC5出生点 */	setMapCellInfo(CELLSTART_N5, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N6:	/*NPC6出生点 */	setMapCellInfo(CELLSTART_N6, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_H1:	/*阵营1基地	 */	setMapCellInfo(CELLSTART_H1, F_GREEN, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H2:	/*阵营2基地	 */	setMapCellInfo(CELLSTART_H2, F_H_PURPLE, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H3:	/*阵营3基地	 */	setMapCellInfo(CELLSTART_H3, F_H_RED, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H4:	/*阵营NPC基地*/ setMapCellInfo(CELLSTART_H4, F_H_BLUE, SHOWLEVEL_3,false,true,false);	break;

	}
}

// 设置信息函数
void mapCell::setMapCellInfo(int mapCellType, int color,int showLevel,bool mis_pass, bool mis_destory, bool tank_pass)
{
	this->mapCellType = mapCellType;
	this->color = color;
	this->showLevel = showLevel;
	this->mis_pass = mis_pass;
	this->mis_destory = mis_destory;
	this->tank_pass = tank_pass;
}

// 绘制地图点函数
void mapCell::drawMapCell(int row, int col,int tmp_color)
{
	int wallType = mapCellType;
	int color_print = (tmp_color > 0) ? tmp_color : color;
	if (wallType == WALL_NULL)
	{
		writeChar(row, col, "  ", color_print);
	}
	if (wallType == WALL_A1)
	{
		writeChar(row, col, WALL_A1_PC, color_print);
	}
	if (wallType == WALL_A2)
	{
		writeChar(row, col, WALL_A2_PC, color_print);
	}
	if (wallType == WALL_B)
	{
		writeChar(row, col, WALL_B_PC, color_print);
	}
	if (wallType == WALL_C)
	{
		writeChar(row, col, WALL_C_PC, color_print);
	}
	if (wallType == WALL_D)
	{
		writeChar(row, col, WALL_D_PC, color_print);
	}
	if (wallType == WALL_E)
	{
		writeChar(row, col, WALL_E_PC, color_print);
	}
	if (wallType == WALL_F)
	{
		writeChar(row, col, WALL_F_PC, color_print);
	}
	if (wallType == WALL_G)
	{
		writeChar(row, col, WALL_G_PC, color_print);
	}
	if (wallType == CELLSTART_H1)
	{
		writeChar(row, col, WALL_G_PC, color_print);
	}
}

void mapCell::Destory(){					// 地形被摧毁时调用
	setMapCellInfo(WALL_NULL, F_WHITE, SHOWLEVEL_0, true, false, true);
};

// Map无参构造函数
Map::Map(){
}

// 初始化地图信息，注意读取时X轴Y轴交换
void Map::InitMap(int load_map[][40]){
	for (int row = 0; row < MAP_HIGH; row++)
	{
		for (int col = 0; col < MAP_WIDTH; col++)
		{
			MapData[row][col] = mapCell(load_map[col][row]);
			LMapData[row][col] = 0;
		}
	}
}

// 绘制地图
void Map::drawMap()
{
	for (int row = 0; row < MAP_HIGH; row++)
	{
		for (int col = 0; col < MAP_WIDTH; col++)
		{
			MapData[row][col].drawMapCell(row,col);
			if (MapData[row][col].MapCellType() == WALL_G)
				box_flag = 1;
		}
	}
}

// 正在使用的地图
Map CurrentMap;