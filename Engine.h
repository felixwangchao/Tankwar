#pragma once
#include "Draw.h"
#include "Tank.h"
#include "NPCTank.h"

class CEngine :virtual public CData, public TankInfo,public NPCTank
{
public:
	CEngine();
	~CEngine();

	//初始化地图信息
	void InitGameInfo();

	//监控键盘按键
	char keyBoardMonitor();
	
	//移动，刷新所有子弹
	void AllMissilesMove();

public:
	int  m_playerCount;
	bool m_isRunning=true;				//游戏是否正在运行（暂停为false）

	TankInfo player1;
	TankInfo player2;
	NPCTank n;

	int playerTankLevel = 1;			// 我方坦克初始等级
	int Enemy1ClassCount = 1;			// 敌方1型坦克数量
	int Enemy2ClassCount = 1;			// 敌方2型坦克数量
	int Enemy3ClassCount = 1;			// 敌方3型坦克数量
	int EnemyBossClassCount = 0;		// 敌方boos坦克数量
	int InitBlood = 10;					// 我方坦克初始血量
};

