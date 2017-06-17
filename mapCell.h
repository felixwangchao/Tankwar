#pragma once
#include "Data.h"
#include "Draw.h"

//��ͼԪ�ص�Ԫ�ṹ��
class mapCell:virtual public CDraw {
private:
	unsigned int mapCellType;		// 32��״̬ ֧��7��ǽ����,�Լ������ر�����,��ҳ�����,CAMP_NPC������,buff,defuff......	

	unsigned int showLevel;			// ��ʾ���� ��3���� ��Ӱ0,̹��1,��Ʒ������2 //���������ص����ж�

	unsigned int color;

	bool mis_pass;					// �ӵ��Ƿ��ܹ������õ���

	bool mis_destory;				// �ӵ��Ƿ��ܹ��ݻٸõ���

	bool tank_pass;					// ̹���Ƿ��ܹ�ͨ���õ���

public:
	mapCell();						// �޲ι��캯��

	mapCell(int mapCellType);		// �вι��캯��

	void setMapCellInfo(			// ���õ�ͼ����Ϣ
		int mapCellType,			// ��ͼ������
		int color,					// ��ɫ
		int showLevel,				// ��ʾ�ȼ�
		bool mis_pass,				// �ӵ��Ƿ���ͨ��
		bool mis_destory,			// �ӵ��Ƿ��ܴݻ�
		bool tank_pass);			// ̹���Ƿ���ͨ��

	void drawMapCell(int row, int col, int tmp_color = 0);		// ���Ƶ�ͼ��

	void Destory();

public:

	// ShowLevel�ӿ�
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// Mis_PASS �ӿ�
	bool Mis_pass() const { return mis_pass; }
	void Mis_pass(bool val) { mis_pass = val; }

	// mis_destory �ӿ�
	bool Mis_destory() const { return mis_destory; }
	void Mis_destory(bool val) { mis_destory = val; }

	// Tank_pass�ӿ�
	bool Tank_pass() const { return tank_pass; }
	void Tank_pass(bool val) { tank_pass = val; }

	// MapCellType�ӿ�
	unsigned int MapCellType() const { return mapCellType; }
	void MapCellType(unsigned int val) { mapCellType = val; }

	// Color �ӿ�
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }
};

class Map: virtual public CDraw{
public:
	mapCell MapData[40][40];			//��̬��ͼ
	int LMapData[40][40];
	Map();
	void InitMap(int load_map[][40]);
	void drawMap();
};

extern Map CurrentMap;