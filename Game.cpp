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
	PlaySound(TEXT("music\\开始.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
	Sleep(10);
}


CGame::CGame()
{
	setCmdWindowsInfo(L"坦克简单示例",120,40);
}


CGame::~CGame()
{

}

//游戏选项界面
int CGame::index()
{
	//0.清屏
	clsConsole();
	//1.定义欢迎画面
	char * options[] = { "玩家设置", "闯关模式", "制作地图", "自定义游戏", "游戏帮助", "退出游戏" };
	//2.打印一个游戏选项列表
	for (int i = 0; i < _countof(options); i++)
	{
		writeChar(20, 10 + 2 * i, options[i], F_H_YELLOW);
	}
	//3.监测用户选择
	int  option = 0;					//保存选择
	char  ch=0;
	while (true)
	{
		ch = keyBoardMonitor();
		if (ch == 27){						//ESC，退出游戏
			return -1;
		}
		if (ch){
			if (ch == (char)0xE0)			//上下键需要获取两次，第一次返回0xe0
			{				
				ch = keyBoardMonitor();		//第二次获取
				if (ch == 72)				//UP
				{
					writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
					option--;
				}else if (ch == 80)	{		//DOWN
					writeChar(20, 10 + 2 * option, options[option], F_H_YELLOW);
					option++;
				}
			}
			//根据option，动态刷新界面
			if (option<0)
			{
				option = 0;
			}
			else if (option == _countof(options))
			{
				option = _countof(options) - 1;
			}
			writeChar(20, 10 + 2 * option, options[option], B_H_YELLOW);
			if (ch == '\r')					//回车键
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
				return option;				//返回选择的下标
			}
		}
	}
	return option;				//返回选择的下标
}

//设置单双人游戏
int CGame::setPlayer()
{
	//0.清屏
	clsConsole();
	//1.定义玩家选择画面
	char * plays[] = { "游戏人数", "我方坦克等级","敌方低级坦克数量","敌方中级坦克数量","敌方高级坦克数量","敌方Boss数量","我方初始血量" };
	char a[40];
	//2.打印一个游戏选项列表
	for (int i = 0; i < _countof(plays); i++)
	{
		writeChar(20, 10 + 2 * i, plays[i], F_H_YELLOW);
	}
	//3.监测用户选择
	int  option = 0;					//保存选择
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
			if (ch == '\r')					//回车键
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
	for (int i = 0; i < 3; i++)								// 闯关模式时
	{
		Enemy1ClassCount = 20*(i+1);						// 根据关卡，改变敌人数量
		Enemy2ClassCount = 20 * i;							// 第二关增加2型坦克
		Enemy3ClassCount = 5 * i;							// 第二关增加3型坦克
		EnemyBossClassCount = (i-1);						// 第三关增加Boss型坦克
		
		startGame(stageMode[i]);							// 开始游戏
		if (tank[0].State() != STATE_VALID && tank[1].State() != STATE_VALID)	// 如果游戏失败，跳出循环
			break;
	}
	return false;
}

//游戏开始
bool CGame::startGame(int load_map[][40])
{
	clsConsole();							// 清屏
	CurrentMap.InitMap(load_map);			//读取地图
	CurrentMap.drawMap();					// 画地图
	printScorePanel();						// 画计分信息
	InitGameInfo();							// 初始化游戏信息
	box_flag = false;

	//3.设置一些必要的变量
	m_isRunning = true;						//游戏是否正在运行（暂停为false）
	clock_t plarCtrl_ClockStart = clock();	//定义多组时钟，用来控制不同的动作频率				
	clock_t plarCtrl_ClockFinish;
	clock_t misCtrl_ClockStart = clock();
	clock_t misCtrl_ClockFinish;
    clock_t allNPCTanksMove_ClockStart = clock();
    clock_t allNPCTanksMove_Clockfinish;
	clock_t updateBoxStart = clock();
	clock_t updateBoxFinish;

	//4.进入游戏主循环	
	while(true){
		
		// 检查游戏是否暂停
		while (!checkGamePause());

		// 检查游戏是否结束
		if (!checkGameOver())break;

		// 玩家控制
		plarCtrl_ClockFinish = clock();
		if ((plarCtrl_ClockFinish - plarCtrl_ClockStart) > 50){
			plarCtrl_ClockStart = plarCtrl_ClockFinish;
			
			// 如果玩家1活着，控制玩家1
			if (tank[0].State() == STATE_VALID)
			{
				tank[0].drawTank();
				catchPlayerCtrl('W', 'S', 'A', 'D', ' ', tank[0]);
			}

			// 如果玩家2存在
			if (m_playerCount > 1) {

				// 如果玩家2活着
				if (tank[1].State() == STATE_VALID)
				{
					// 控制玩家2
					tank[1].drawTank();
					catchPlayerCtrl(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, tank[1]);
				}
			}
		}

		// 子弹移动时钟
		misCtrl_ClockFinish = clock();
		if ((misCtrl_ClockFinish - misCtrl_ClockStart) > 50){
			misCtrl_ClockStart = misCtrl_ClockFinish;

			// 所有子弹移动
			AllMissilesMove();
		}

		// NPC移动时钟
		allNPCTanksMove_Clockfinish = clock();
		if ((allNPCTanksMove_Clockfinish - allNPCTanksMove_ClockStart) > 200) {
			allNPCTanksMove_ClockStart = allNPCTanksMove_Clockfinish;

			//所有npc移动
			n.AllNPCTankMove();
		}

		// 箱子刷新时钟
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

		// 更新积分版
		updateScore();
	}
	clsConsole();
	return 1;
}

//编辑地图
bool CGame::makeMap()
{
	//0.清屏
	clsConsole();
	MapEditor map_editor;
	map_editor.InitMapEditor();
	return 1;

}

//打开游戏帮助
bool CGame::help()
{
	//0.清屏
	clsConsole();
	char a[200];
	sprintf_s(a, "坦克共分为四类：\n基础型 - 移动速度缓慢 - 杀伤效果差\n增强型 - 移动速度中 - 杀伤效果中\n杀手型 - 移动速度快 - 杀伤效果强 - 能够穿透铁墙");
	writeChar(0, 3, a, F_H_YELLOW);
	sprintf_s(a, "Boss型 - 移动速度快 - 全屏穿甲弹杀伤 - 生命力极其强大\n\n子弹共分为三类：\n基础型 - 一次扣一点血\n增强型 - 一次两血\n穿甲型 - 一次三血 - 可击碎铁墙");
	writeChar(0, 7, a, F_H_YELLOW);
	writeChar(37, 37, " ",F_H_YELLOW);
	system("pause;");
	return 1;
}

//退出游戏
void CGame::exit()
{
	::exit(0);
}

void CGame::drawGameMapInfo()
{
	//打印地图
	CurrentMap.InitMap(tempMap);
	CurrentMap.drawMap();
	//打印计分牌
}

void CGame::printScorePanel(){
	writeChar(41, 2, " 玩家1：", F_H_WHITE);
	writeChar(41, 3, " 玩家2：", F_H_WHITE);
	writeChar(41, 5, " 剩余敌人数量： ", F_H_WHITE);
}
void CGame::updateScore(){
	char a[20];
	sprintf_s(a, "%d 分", player1score, 20);
	writeChar(45, 2, a, F_H_WHITE);
	sprintf_s(a, "%d 分", player2score, 20);
	writeChar(45, 3, a, F_H_WHITE);
	sprintf_s(a, "%d 个", alive, 20);
	writeChar(48, 5, a, F_H_WHITE);
}

bool CGame::checkGamePause()
{
	char ch = keyBoardMonitor();
	if (ch == 'z' || ch == 'Z')	// 按z键暂停
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
		sprintf_s(a, "我不是针对谁，我说的是在座的各位",40);
		writeChar(42, 10, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "都是...", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "都是... 皮皮虾哦", 40);
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
		sprintf_s(a, "你赢了，你居然赢了", 40);
		writeChar(42, 10, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "所以...", 40);
		writeChar(42, 11, a, F_H_YELLOW);
		Sleep(1500);
		sprintf_s(a, "所以... 那又怎么样？咬我啊？！", 40);
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

	if (KEY_DOWN(up)){			//向上移动
		
		Tank.Move(UP);
	}
	if (KEY_DOWN(down)){		//向下移动		
		Tank.Move(DOWN);
	}
	if (KEY_DOWN(left)){		//向左移动		
		
		Tank.Move(LEFT);
	}
	if (KEY_DOWN(right)){		//向右移动		
		
		Tank.Move(RIGHT);
	}
	if (KEY_DOWN(fire)){		//开火
		Tank.fireTank();
	}
}


int main()
{


	CGame game;

	bool isExit = false;
	PlayMusic();
	while (!isExit){

		int option = game.index();		//进入游戏选项界面，并获取选项

		switch (option){
		case 0: game.setPlayer();	break;	//设置游戏单双人
		case 1:	game.startStageGame();	break;	//开始游戏
		case 2: game.makeMap();		break;	//制作地图
		case 3: game.startGame(tempMap);	break;	//自定义游戏
		case 4: game.help();		break;	//打开帮助
		case 5: game.exit();		break;	//退出游戏
		default:game.exit();		break;	//其他情况也退出游戏
		}

	}

	return 0;
}
