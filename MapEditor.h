#pragma once
#include "Draw.h"
#include "mapCell.h"

class MapEditor : public CDraw{
public:
	MapEditor();
	void InitMapEditor();					// ��ʼ��

	void printMapEditorMenu();				// ��ӡ�˵�

	void cleanMenu();						// ����˵�

	void GetMousePos();						// ��ȡ�������

	void terrainPrint(int x, int y);		// ��Ŀ��λ�û�����

	void paintWithBrush(int x, int y, int wall, char* str, int color);	// ��Ŀ��λ�û�ָ��������
private:
	int DrawingBoard[40][40];
	Map m;
	HANDLE hInput;					/*  ��ȡ��׼�����豸��� */
	INPUT_RECORD inRec;				/*  �������ݼ�¼ */
	DWORD numRead;					/*  �����Ѷ�ȡ�ļ�¼�� */
	COORD pos;						/*  ����  */
	int X, Y;						/*  ���꣬ʹ�÷�����X = pos.x */
	int terrainType = 0;				/*  ������������ */

};