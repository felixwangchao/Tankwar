#include "mapCell.h"
#include "Data.h"
#include "Draw.h"

// �޲ι��캯��
mapCell::mapCell(){
	this->mapCellType = 0;
	this->color = 0;
	this->showLevel = 0;
	this->mis_pass = 0;
	this->mis_destory = 0;
	this->tank_pass = 0;
}

//�вι��캯��
mapCell::mapCell(int mapCellType){

	switch (mapCellType){							/*   ����   ��ɫ      ��ʾ����  �ӵ��ܷ�ͨ���� �ӵ��ܷ�ݻ٣� ̹���ܷ�ͨ�� */
	case WALL_NULL:		/*��  �յ�*/    setMapCellInfo(WALL_NULL, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case WALL_A1:		/*��  ��ǽ*/    setMapCellInfo(WALL_A1, F_RED, SHOWLEVEL_1,false,true,false);	break;
	case WALL_A2:		/*�d  ��ǽ*/    setMapCellInfo(WALL_A2, F_RED, SHOWLEVEL_1,false,true,false);	break;
	case WALL_B:		/*��  ��ǽ*/    setMapCellInfo(WALL_B, F_CYAN, SHOWLEVEL_1,false,false,false);	break;
	case WALL_C:		/*��  ����*/    setMapCellInfo(WALL_C, F_H_BLUE, SHOWLEVEL_0,true,false,false);	break;
	case WALL_D:		/*��  ·��*/    setMapCellInfo(WALL_D, F_WHITE, SHOWLEVEL_1,false,false,false);	break;
	case WALL_E:		/*��  ����*/    setMapCellInfo(WALL_E, F_H_GREEN, SHOWLEVEL_2,true,false,true);	break;
	case WALL_F:		/*��  ����·*/  setMapCellInfo(WALL_F, F_YELLOW, SHOWLEVEL_0,true,false,true);	break;
	case WALL_G:		/*��  ����*/    setMapCellInfo(WALL_G, B_H_YELLOW, SHOWLEVEL_3,true,false,true);	break;
	case CELLSTART_P1:	/*���1������*/	setMapCellInfo(CELLSTART_P1, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_P2:	/*���2������*/	setMapCellInfo(CELLSTART_P2, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_P3:	/*���3������*/	setMapCellInfo(CELLSTART_P3, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N1:	/*NPC1������ */	setMapCellInfo(CELLSTART_N1, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N2:	/*NPC2������ */	setMapCellInfo(CELLSTART_N2, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N3:	/*NPC3������ */	setMapCellInfo(CELLSTART_N3, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N4:	/*NPC4������ */	setMapCellInfo(CELLSTART_N4, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N5:	/*NPC5������ */	setMapCellInfo(CELLSTART_N5, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_N6:	/*NPC6������ */	setMapCellInfo(CELLSTART_N6, F_WHITE, SHOWLEVEL_0,true,false,true);	break;
	case CELLSTART_H1:	/*��Ӫ1����	 */	setMapCellInfo(CELLSTART_H1, F_GREEN, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H2:	/*��Ӫ2����	 */	setMapCellInfo(CELLSTART_H2, F_H_PURPLE, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H3:	/*��Ӫ3����	 */	setMapCellInfo(CELLSTART_H3, F_H_RED, SHOWLEVEL_3,false,true,false);	break;
	case CELLSTART_H4:	/*��ӪNPC����*/ setMapCellInfo(CELLSTART_H4, F_H_BLUE, SHOWLEVEL_3,false,true,false);	break;

	}
}

// ������Ϣ����
void mapCell::setMapCellInfo(int mapCellType, int color,int showLevel,bool mis_pass, bool mis_destory, bool tank_pass)
{
	this->mapCellType = mapCellType;
	this->color = color;
	this->showLevel = showLevel;
	this->mis_pass = mis_pass;
	this->mis_destory = mis_destory;
	this->tank_pass = tank_pass;
}

// ���Ƶ�ͼ�㺯��
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

void mapCell::Destory(){					// ���α��ݻ�ʱ����
	setMapCellInfo(WALL_NULL, F_WHITE, SHOWLEVEL_0, true, false, true);
};

// Map�޲ι��캯��
Map::Map(){
}

// ��ʼ����ͼ��Ϣ��ע���ȡʱX��Y�ύ��
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

// ���Ƶ�ͼ
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

// ����ʹ�õĵ�ͼ
Map CurrentMap;