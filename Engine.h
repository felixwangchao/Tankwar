#pragma once
#include "Draw.h"
#include "Tank.h"
#include "NPCTank.h"

class CEngine :virtual public CData, public TankInfo,public NPCTank
{
public:
	CEngine();
	~CEngine();

	//��ʼ����ͼ��Ϣ
	void InitGameInfo();

	//��ؼ��̰���
	char keyBoardMonitor();
	
	//�ƶ���ˢ�������ӵ�
	void AllMissilesMove();

public:
	int  m_playerCount;
	bool m_isRunning=true;				//��Ϸ�Ƿ��������У���ͣΪfalse��

	TankInfo player1;
	TankInfo player2;
	NPCTank n;

	int playerTankLevel = 1;			// �ҷ�̹�˳�ʼ�ȼ�
	int Enemy1ClassCount = 1;			// �з�1��̹������
	int Enemy2ClassCount = 1;			// �з�2��̹������
	int Enemy3ClassCount = 1;			// �з�3��̹������
	int EnemyBossClassCount = 0;		// �з�boos̹������
	int InitBlood = 10;					// �ҷ�̹�˳�ʼѪ��
};

