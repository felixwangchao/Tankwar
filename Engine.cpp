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
	mis.reserve(2000);							// Ԥ���ӵ�����

	player1 = TankInfo(1, playerTankLevel);		// ��ʼ��player1��Ϣ
	player1.PosX(2);							// ��ʼ��player1����
	player1.PosY(37);
	player1.State(STATE_VALID);					// ��ʼ��play1 state
	player1.Camp(CAMP_1);						// ��ʼ��player1 ��Ӫ
	player1.Color(B_H_RED | F_H_YELLOW);		// ��ʼ��player1 ��ɫ
	player1.Blood(InitBlood);
	player1.drawTank();							// ��̹��
	tank.push_back(player1);					// ̹������

	player2 = TankInfo(2, playerTankLevel);			// play2 ��ͬ
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


	if (EnemyBossClassCount < 0)				// ���boss����С���㣬����Ϊ0
		EnemyBossClassCount = 0;
	n.AddNPC(Enemy1ClassCount, Enemy2ClassCount, Enemy3ClassCount, EnemyBossClassCount);					// ����npc����
	alive = Enemy1ClassCount+Enemy2ClassCount+Enemy3ClassCount+EnemyBossClassCount;							// ����ʣ��з�����
	
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

void CEngine::AllMissilesMove()			// �����ӵ��ƶ�
{

	for (int i = 0; i < mis.size(); i++)		// ���������ӵ�
	{
		if (mis[i].State() != STATE_DIE)		// ����ӵ�û��
			mis[i].MissileMove();				// �ƶ��ӵ�
	}

	vector<MissileInfo>::iterator iter;

	for (iter = mis.begin(); iter != mis.end();)	// ���������ӵ�
	{
		if ((iter->State() == STATE_DIE )){			// ��ǰ�ӵ��ƶ�	����ƶ�ʧ�ܣ����������ƣ��ݻٵ�ǰ�ӵ�
			iter = mis.erase(iter);					// ��������ɾ���ӵ�
		}
		else
		{
			iter++;
		}
	}
}