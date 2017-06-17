#include<windows.h>
#include "Game.h"
#include <time.h>
#include <WinUser.h>
#include "Draw.h"
#include "mapCell.h"
#include "Tank.h"
#include "missile.h"
#include "NPCTank.h"
#include "MapEditor.h"
#pragma comment(lib,"User32.lib")
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)

void PlayMusic()
{
	PlaySound(TEXT("music\\��ʼ.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
	Sleep(10);
}


CGame::CGame()
{
	setCmdWindowsInfo(L"̹�˼�ʾ��",120,40);
}


CGame::~CGame()
{

}

//��Ϸѡ�����
int CGame::index()
{
	//0.����
	clsConsole();
	//1.���延ӭ����
	char * options[] = { "�������", "����ģʽ", "������ͼ", "�Զ�����Ϸ", "��Ϸ����", "�˳���Ϸ" };
	//2.��ӡһ����Ϸѡ���б�
	for (int i = 0; i < _countof(options); i++)
	{
		writeChar(20, 10 + 2 * i, options[i], F_H_YELLOW);
	}
	//3.����û�ѡ��
	int  option = 0;					//����ѡ��
	char  ch=0;
	while (true)
	{
		ch = keyBoardMonitor();
		if (ch == 27){						//ESC���˳���Ϸ
			return -1;
		}
		if (ch){
			if (ch == (char)0xE0)			//���¼���Ҫ��ȡ���Σ���һ�η���0xe0
			{				
				ch = keyBoardMonitor();		//�ڶ��λ�ȡ
				if (ch == 72)				//UP
				{
					writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
					option--;
				}else if (ch == 80)	{		//DOWN
					writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
					option++;
				}
			}
			//����option����̬ˢ�½���
			if (option<0)
			{
				option = 0;
			}
			else if (option == _countof(options))
			{
				option = _countof(options) - 1;
			}
			writeChar(20, 10 + 2 * option, options[option], B_H_YELLOW);
			if (ch == '\r')					//�س���
			{
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], B_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], B_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], B_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
				return option;				//����ѡ����±�
			}
		}
	}
	return option;				//����ѡ����±�
}

//���õ�˫����Ϸ
int CGame::setPlayer()
{
	//0.����
	clsConsole();
	//1.�������ѡ����
	char * plays[] = { "��Ϸ����", "�ҷ�̹�˵ȼ�","�з��ͼ�̹������","�з��м�̹������","�з��߼�̹������","�з�Boss����","�ҷ���ʼѪ��" };
	char a[40];
	//2.��ӡһ����Ϸѡ���б�
	for (int i = 0; i < _countof(plays); i++)
	{
		writeChar(20, 10 + 2 * i, plays[i], F_H_YELLOW);
	}
	//3.����û�ѡ��
	int  option = 0;					//����ѡ��
	char  ch = 0;
	while (true)
	{
		
		ch = keyBoardMonitor();
		switch (ch)
		{
		case 27:
			return -1;
		case 'w':
		case 'W':
			writeChar(20, 10 + 2 * option, plays[option], F_H_YELLOW);
			option--;
			if (option < 0)
				option = 0;
			writeChar(20, 10 + 2 * option, plays[option], B_H_YELLOW);
			Sleep(100);
			writeChar(20, 10 + 2 * option, plays[option], F_H_YELLOW);
			Sleep(100);
			writeChar(20, 10 + 2 * option, plays[option], B_H_YELLOW);
			break;
		case 's':
		case 'S':
			writeChar(20, 10 + 2 * option, plays[option], F_H_YELLOW);
			option++;
			if (option == _countof(plays))
				option = _countof(plays) - 1;
			writeChar(20, 10 + 2 * option, plays[option], B_H_YELLOW);
			Sleep(100);
			writeChar(20, 10 + 2 * option, plays[option], F_H_YELLOW);
			Sleep(100);
			writeChar(20, 10 + 2 * option, plays[option], B_H_YELLOW);
			break;
		case 'a':
		case 'A':
			switch (option)
			{
			case 0:
				m_playerCount--;
				if (m_playerCount < 1)
					m_playerCount = 1;

				sprintf_s(a, "%4d", m_playerCount);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 1:
				playerTankLevel--;
				if (playerTankLevel < 1)
					playerTankLevel = 1;

				sprintf_s(a, "%4d", playerTankLevel);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 2:
				Enemy1ClassCount--;
				if (Enemy1ClassCount < 1)
					Enemy1ClassCount = 1;

				sprintf_s(a, "%4d", Enemy1ClassCount);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 3:
				Enemy2ClassCount--;
				if (Enemy2ClassCount < 1)
					Enemy2ClassCount = 1;

				sprintf_s(a, "%4d", Enemy2ClassCount);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 4:
				Enemy3ClassCount--;
				if (Enemy3ClassCount < 1)
					Enemy3ClassCount = 1;

				sprintf_s(a, "%4d", Enemy3ClassCount);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 5:
				EnemyBossClassCount--;
				if (EnemyBossClassCount < 0)
					EnemyBossClassCount = 0;

				sprintf_s(a, "%4d", EnemyBossClassCount);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

				break;
			case 6:
				InitBlood--;
				if (InitBlood < 1)
					InitBlood = 9999;

				sprintf_s(a, "%4d", InitBlood);
				writeChar(28, 10 + 2 * option, a, F_H_YELLOW);
			}
				break;
			case 'd':
			case 'D':
				switch (option)
				{
				case 0:
					m_playerCount++;
					if (m_playerCount > 2)
						m_playerCount = 2;

					sprintf_s(a, "%4d", m_playerCount);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 1:
					playerTankLevel++;
					if (playerTankLevel > 4)
						playerTankLevel = 4;

					sprintf_s(a, "%4d", playerTankLevel);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 2:
					Enemy1ClassCount++;
					if (Enemy1ClassCount > 100)
						Enemy1ClassCount = 100;

					sprintf_s(a, "%4d", Enemy1ClassCount);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 3:
					Enemy2ClassCount++;
					if (Enemy2ClassCount > 50)
						Enemy2ClassCount = 50;

					sprintf_s(a, "%4d", Enemy2ClassCount);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 4:
					Enemy3ClassCount++;
					if (Enemy3ClassCount > 10)
						Enemy3ClassCount = 10;

					sprintf_s(a, "%4d", Enemy3ClassCount);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 5:
					EnemyBossClassCount++;
					if (EnemyBossClassCount > 1)
						EnemyBossClassCount = 1;

					sprintf_s(a, "%4d", EnemyBossClassCount);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
				case 6:
					InitBlood++;
					if (InitBlood > 9999)
						InitBlood = 9999;


					sprintf_s(a, "%4d", InitBlood);
					writeChar(28, 10 + 2 * option, a, F_H_YELLOW);

					break;
			}
		}
			if (ch == '\r')					//�س���
			{
				Sleep(100);
				writeChar(20, 10 + 2 * option, plays[option], F_H_YELLOW);
				Sleep(100);
				writeChar(20, 10 + 2 * option, plays[option], B_H_YELLOW);
				Sleep(100);
				clsConsole();
				return true;
			}
		}
	return true;
}

bool CGame::startStageGame()
{
	for (int i = 0; i < 3; i++)								// ����ģʽʱ
	{
		Enemy1ClassCount = 20*(i+1);						// ���ݹؿ����ı��������
		Enemy2ClassCount = 20 * i;							// �ڶ�������2��̹��
		Enemy3ClassCount = 5 * i;							// �ڶ�������3��̹��
		EnemyBossClassCount = (i-1);						// ����������Boss��̹��
		
		startGame(stageMode[i]);							// ��ʼ��Ϸ
		if (tank[0].State() != STATE_VALID && tank[1].State() != STATE_VALID)	// �����Ϸʧ�ܣ�����ѭ��
			break;
	}
	return false;
}

//��Ϸ��ʼ
bool CGame::startGame(int load_map[][40])
{
	clsConsole();							// ����
	CurrentMap.InitMap(load_map);			//��ȡ��ͼ
	CurrentMap.drawMap();					// ����ͼ
	printScorePanel();						// ���Ʒ���Ϣ
	InitGameInfo();							// ��ʼ����Ϸ��Ϣ
	box_flag = false;

	//3.����һЩ��Ҫ�ı���
	m_isRunning = true;						//��Ϸ�Ƿ��������У���ͣΪfalse��
	clock_t plarCtrl_ClockStart = clock();	//�������ʱ�ӣ��������Ʋ�ͬ�Ķ���Ƶ��				
	clock_t plarCtrl_ClockFinish;
	clock_t misCtrl_ClockStart = clock();
	clock_t misCtrl_ClockFinish;
    clock_t allNPCTanksMove_ClockStart = clock();
    clock_t allNPCTanksMove_Clockfinish;
	clock_t updateBoxStart = clock();
	clock_t updateBoxFinish;

	//4.������Ϸ��ѭ��	
	while(true){
		
		// �����Ϸ�Ƿ���ͣ
		while (!checkGamePause());

		// �����Ϸ�Ƿ����
		if (!checkGameOver())break;

		// ��ҿ���
		plarCtrl_ClockFinish = clock();
		if ((plarCtrl_ClockFinish - plarCtrl_ClockStart) > 50){
			plarCtrl_ClockStart = plarCtrl_ClockFinish;
			
			// ������1���ţ��������1
			if (tank[0].State() == STATE_VALID)
			{
				tank[0].drawTank();
				catchPlayerCtrl('W', 'S', 'A', 'D', ' ', tank[0]);
			}

			// ������2����
			if (m_playerCount > 1) {

				// ������2����
				if (tank[1].State() == STATE_VALID)
				{
					// �������2
					tank[1].drawTank();
					catchPlayerCtrl(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, tank[1]);
				}
			}
		}

		// �ӵ��ƶ�ʱ��
		misCtrl_ClockFinish = clock();
		if ((misCtrl_ClockFinish - misCtrl_ClockStart) > 50){
			misCtrl_ClockStart = misCtrl_ClockFinish;

			// �����ӵ��ƶ�
			AllMissilesMove();
		}

		// NPC�ƶ�ʱ��
		allNPCTanksMove_Clockfinish = clock();
		if ((allNPCTanksMove_Clockfinish - allNPCTanksMove_ClockStart) > 200) {
			allNPCTanksMove_ClockStart = allNPCTanksMove_Clockfinish;

			//����npc�ƶ�
			n.AllNPCTankMove();
		}

		// ����ˢ��ʱ��
		updateBoxFinish = clock();
		if ((updateBoxFinish - updateBoxStart) > 1000){
			while (!box_flag)
			{
				int i = rand() % 40;
				int j = rand() % 40;
				if (CurrentMap.MapData[i][j].MapCellType() == WALL_NULL && CurrentMap.LMapData[i][j] == 0)
				{
					CurrentMap.MapData[i][j].setMapCellInfo(WALL_G, B_H_YELLOW, SHOWLEVEL_3, true, false, true);
					CurrentMap.MapData[i][j].drawMapCell(i, j);
					box_flag = 1;
					updateBoxStart = updateBoxFinish;
					break;
				}
			}
		}

		// ���»��ְ�
		updateScore();
	}
	clsConsole();
	return 1;
}

//�༭��ͼ
bool CGame::makeMap()
{
	//0.����
	clsConsole();
	MapEditor map_editor;
	map_editor.InitMapEditor();
	return 1;

}

//����Ϸ����
bool CGame::help()
{
	//0.����
	clsConsole();
	char a[200];
	sprintf_s(a, "̹�˹���Ϊ���ࣺ\n������ - �ƶ��ٶȻ��� - ɱ��Ч����\n��ǿ�� - �ƶ��ٶ��� - ɱ��Ч����\nɱ���� - �ƶ��ٶȿ� - ɱ��Ч��ǿ - �ܹ���͸��ǽ");
	writeChar(0, 3, a, F_H_YELLOW);
	sprintf_s(a, "Boss�� - �ƶ��ٶȿ� - ȫ�����׵�ɱ�� - ����������ǿ��\n\n�ӵ�����Ϊ���ࣺ\n������ - һ�ο�һ��Ѫ\n��ǿ�� - һ����Ѫ\n������ - һ����Ѫ - �ɻ�����ǽ");
	writeChar(0, 7, a, F_H_YELLOW);
	writeChar(37, 37, " ",F_H_YELLOW);
	system("pause;");
	return 1;
}

//�˳���Ϸ
void CGame::exit()
{
	::exit(0);
}

void CGame::drawGameMapInfo()
{
	//��ӡ��ͼ
	CurrentMap.InitMap(tempMap);
	CurrentMap.drawMap();
	//��ӡ�Ʒ���
}

void CGame::printScorePanel(){
	writeChar(41, 2, " ���1��", F_H_WHITE);
	writeChar(41, 3, " ���2��", F_H_WHITE);
	writeChar(41, 5, " ʣ����������� ", F_H_WHITE);
}
void CGame::updateScore(){
	char a[20];
	sprintf_s(a, "%d ��", player1score, 20);
	writeChar(45, 2, a, F_H_WHITE);
	sprintf_s(a, "%d ��", player2score, 20);
	writeChar(45, 3, a, F_H_WHITE);
	sprintf_s(a, "%d ��", alive, 20);
	writeChar(48, 5, a, F_H_WHITE);
}

bool CGame::checkGamePause()
{
	char ch = keyBoardMonitor();
	if (ch == 'z' || ch == 'Z')	// ��z����ͣ
	{
		m_isRunning = !m_isRunning;
	}
	return m_isRunning;
}

bool CGame::checkGameOver()
{
	if (tank[0].State() != STATE_VALID && tank[1].State() != STATE_VALID)
	{
		char a[40];
		sprintf_s(a, "�Ҳ������˭����˵���������ĸ�λ",40);
		writeChar(42, 10, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "����...", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "����... ƤƤϺŶ", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		writeChar(42, 12, " ", F_H_YELLOW);
		writeChar(42, 13, " ", F_H_YELLOW);
		writeChar(42, 14, " ", F_H_YELLOW);
		system("pause");
		return false;
	}
	if (alive <= 0)
	{
		char a[40];
		sprintf_s(a, "��Ӯ�ˣ����ȻӮ��", 40);
		writeChar(42, 10, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "����...", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "����... ������ô����ҧ�Ұ�����", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		writeChar(42, 12, " ", F_H_YELLOW);
		writeChar(42, 13, " ", F_H_YELLOW);
		writeChar(42, 14, " ", F_H_YELLOW);
		system("pause");
		return false;
	}
		return true;
}

void CGame::catchPlayerCtrl(char up, char down, char left, char right, char fire, TankInfo& Tank)
{

	if (KEY_DOWN(up)){			//�����ƶ�
		
		Tank.Move(UP);
	}
	if (KEY_DOWN(down)){		//�����ƶ�		
		Tank.Move(DOWN);
	}
	if (KEY_DOWN(left)){		//�����ƶ�		
		
		Tank.Move(LEFT);
	}
	if (KEY_DOWN(right)){		//�����ƶ�		
		
		Tank.Move(RIGHT);
	}
	if (KEY_DOWN(fire)){		//����
		Tank.fireTank();
	}
}


int main()
{


	CGame game;

	bool isExit = false;
	PlayMusic();
	while (!isExit){

		int option = game.index();		//������Ϸѡ����棬����ȡѡ��

		switch (option){
		case 0: game.setPlayer();	break;	//������Ϸ��˫��
		case 1:	game.startStageGame();	break;	//��ʼ��Ϸ
		case 2: game.makeMap();		break;	//������ͼ
		case 3: game.startGame(tempMap);	break;	//�Զ�����Ϸ
		case 4: game.help();		break;	//�򿪰���
		case 5: game.exit();		break;	//�˳���Ϸ
		default:game.exit();		break;	//�������Ҳ�˳���Ϸ
		}

	}

	return 0;
}
