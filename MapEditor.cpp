#include "Draw.h"
#include "mapCell.h"
#include "MapEditor.h"
#include "windows.h"

MapEditor::MapEditor(){
	for (int i = 0; i < 40; i++)					// ��ʼ������������Ϣ
		for (int j = 0; j < 40; j++)
			if (i==0||j==0||i==39||j==39)
				DrawingBoard[i][j] = WALL_D;				
			else
				DrawingBoard[i][j] = WALL_NULL;				

	m.InitMap(DrawingBoard);						// ���ݻ��幹���ͼ
}

void MapEditor::printMapEditorMenu(){
	writeChar(42, 20, "���ʴ�С��1", F_H_WHITE);
	writeChar(41, 1, " 1      �յ�", F_H_WHITE);
	writeChar(41, 2, " 2  ��  ��ǽ", F_H_WHITE);
	writeChar(41, 3, " 3  ��  ��ǽ", F_H_WHITE);
	writeChar(41, 4, " 4  ��  �ݴ�", F_H_WHITE);
	writeChar(41, 5, " 5  ��  ɳ��", F_H_WHITE);
	writeChar(41, 6, " 6  ��  ����", F_H_WHITE);
	writeChar(41, 8, " ������ ����ͼ", F_H_WHITE);
	writeChar(41, 9, " ����Ҽ� ���", F_H_WHITE);
	writeChar(41, 18, "��������������", F_H_WHITE);
	writeChar(41, 19, "|   �˳���Q��|", F_H_WHITE);
	writeChar(41, 20, "��������������", F_H_WHITE);
}

void MapEditor::cleanMenu(){

	writeChar(41, 1, "            ", F_H_WHITE);
	writeChar(41, 2, "            ", F_H_WHITE);
	writeChar(41, 3, "            ", F_H_WHITE);
	writeChar(41, 4, "            ", F_H_WHITE);
	writeChar(41, 5, "            ", F_H_WHITE);
	writeChar(41, 6, "            ", F_H_WHITE);
	writeChar(41, 8, "                ", F_H_WHITE);
	writeChar(41, 9, "                ", F_H_WHITE);
	writeChar(41, 11, "                ", F_H_WHITE);
	writeChar(41, 12, "                ", F_H_WHITE);
	writeChar(41, 14, "               ", F_H_WHITE);
	writeChar(41, 15, "              ", F_H_WHITE);
	writeChar(41, 16, "               ", F_H_WHITE);
	writeChar(41, 18, "               ", F_H_WHITE);
	writeChar(41, 19, "               ", F_H_WHITE);
	writeChar(41, 20, "               ", F_H_WHITE);
	writeChar(41, 22, "               ", F_H_WHITE);
	writeChar(41, 23, "               ", F_H_WHITE);
	writeChar(41, 24, "               ", F_H_WHITE);
	writeChar(41, 26, "               ", F_H_WHITE);
	writeChar(41, 27, "               ", F_H_WHITE);
	writeChar(41, 28, "               ", F_H_WHITE);
}

void MapEditor::paintWithBrush(int x, int y, int wall, char* str, int color){
		writeChar(x, y, str, color);
		DrawingBoard[y][x] = wall;
}

void MapEditor::terrainPrint(int x, int y){
	switch (terrainType){
	case 0x0:
		break;
	case 0x1:
		paintWithBrush(x, y, WALL_NULL, "  ", F_H_WHITE);
		break;
	case 0x2:
		paintWithBrush(x, y, WALL_D, "��", F_WHITE);
		break;
	case 0x3:
		paintWithBrush(x, y, WALL_A1, "��", F_RED);
		break;
	case 0x4:
		paintWithBrush(x, y, WALL_E, "��", F_H_GREEN);
		break;
	case 0x5:
		paintWithBrush(x, y, WALL_F, "��", F_YELLOW);
		break;
	case 0x6:
		paintWithBrush(x, y, WALL_C, "��", F_H_BLUE);
		break;
	default:
		break;
	}
}

// ��ȡ���λ��
void MapEditor::GetMousePos()
{

	pos = inRec.Event.MouseEvent.dwMousePosition;

	char str[100] = { 0 };
	X = (int)pos.X / 2;
	Y = (int)pos.Y;
	sprintf_s(str, "���꣺( %3d .%3d )", (int)pos.X, (int)pos.Y);
	writeChar(41, 30, str, F_H_WHITE);

	switch (inRec.Event.MouseEvent.dwButtonState)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:          // ��� ���A 
		if (X < 39 && Y < 39 && X>0 && Y>0)
			terrainPrint(X, Y);
		break;      // ���ʹ��printf�������֮ǰ��Ҫ�����ù���λ��  

	case RIGHTMOST_BUTTON_PRESSED:              // �Ҽ� ���a  
		if (X < 39 && Y < 39 && X>0 && Y>0){
			writeChar(X, Y, "  ", F_H_WHITE);
			DrawingBoard[Y][X] = WALL_NULL;
		}
		break;
	default:
		break;
	}
}

void MapEditor::InitMapEditor(){
	m.drawMap();								// ����ͼ
	printMapEditorMenu();						// ��ӡ�˵�

	char cKey;

	hInput = GetStdHandle(STD_INPUT_HANDLE);	// ���ñ�׼������
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);	// ���������������ģʽ

	int i = 1;

	while (i)
	{
		ReadConsoleInput(hInput, &inRec, 1, &numRead);	// ��ȡ��׼����

		if (inRec.EventType == MOUSE_EVENT)				// ���������¼������������Ӧ�������ж�
		{

			GetMousePos();
			continue;
		}

		if (inRec.EventType == KEY_EVENT)				// ����Ǽ����¼�
		{
			cKey = inRec.Event.KeyEvent.uChar.AsciiChar;
			switch (cKey)
			{
			case '1':
				terrainType = 0x1;						// �ı���������
				break;
			case '2':
				terrainType = 0x2;						// �ı���������
				break;
			case '3':
				terrainType = 0x3;						// �ı���������
				break;
			case '4':
				terrainType = 0x4;						// �ı���������
				break;
			case '5':
				terrainType = 0x5;						// �ı���������
				break;
			case '6':
				terrainType = 0x6;						// �ı���������
				break;
			case 'q':									// ������˳�
			case 'Q':
				for (int k = 0; k < 40; k++)
					for (int j = 0; j < 40; j++)
						tempMap[k][j] = DrawingBoard[k][j];		// д���ͼȫ�ֱ���
				i = 0;
				break;
			default:
				continue;
			}
		}
	}
}