#include<iostream>
#include "Engine.h"
#include "Data.h"
#include "Draw.h"
#include "missile.h"
#include <conio.h>


CEngine::CEngine()
{
    m_playerCount = 1;
}


CEngine::~CEngine()
{
}

void CEngine::InitGameInfo(){
	vector <TankInfo>().swap(tank);
	vector<MissileInfo>().swap(mis);
	mis.reserve(2000);							// 预制子弹数量

	player1 = TankInfo(1, playerTankLevel);		// 初始化player1信息
	player1.PosX(2);							// 初始化player1坐标
	player1.PosY(37);
	player1.State(STATE_VALID);					// 初始化play1 state
	player1.Camp(CAMP_1);						// 初始化player1 阵营
	player1.Color(B_H_RED | F_H_YELLOW);		// 初始化player1 颜色
	player1.Blood(InitBlood);
	player1.drawTank();							// 画坦克
	tank.push_back(player1);					// 坦克入列

	player2 = TankInfo(2, playerTankLevel);			// play2 相同
	player2.PosX(37);
	player2.PosY(37);
	if (m_playerCount == 2)
		player2.State(STATE_VALID);
	player2.Camp(CAMP_1);
	player2.Color(B_H_RED | F_H_YELLOW);
	player2.Blood(InitBlood);
	if (m_playerCount == 2)
		player2.drawTank();
	tank.push_back(player2);


	if (EnemyBossClassCount < 0)				// 如果boss数量小于零，则置为0
		EnemyBossClassCount = 0;
	n.AddNPC(Enemy1ClassCount, Enemy2ClassCount, Enemy3ClassCount, EnemyBossClassCount);					// 设置npc数量
	alive = Enemy1ClassCount+Enemy2ClassCount+Enemy3ClassCount+EnemyBossClassCount;							// 计算剩余敌方数量
	
}

char CEngine::keyBoardMonitor() {
    char ch;
    if (_kbhit()) {
        ch = _getch();
    }
    else {
        return 0;
    }
    return ch;
}

void CEngine::AllMissilesMove()			// 所有子弹移动
{

	for (int i = 0; i < mis.size(); i++)		// 遍历所有子弹
	{
		if (mis[i].State() != STATE_DIE)		// 如果子弹没死
			mis[i].MissileMove();				// 移动子弹
	}

	vector<MissileInfo>::iterator iter;

	for (iter = mis.begin(); iter != mis.end();)	// 遍历所有子弹
	{
		if ((iter->State() == STATE_DIE )){			// 当前子弹移动	如果移动失败，迭代器后移，摧毁当前子弹
			iter = mis.erase(iter);					// 从向量中删除子弹
		}
		else
		{
			iter++;
		}
	}
}