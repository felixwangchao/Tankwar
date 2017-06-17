#pragma once
#include "Engine.h"
#include "mapCell.h"
#include "Tank.h"

class CGame:public CEngine,public virtual CDraw,public virtual Map
{
public:
	CGame();
	~CGame();

	//��Ϸѡ�����
	int index();

	//���õ�˫����Ϸ
	int setPlayer();

	//��Ϸ��ʼ
	bool startGame(int load_map[][40]);
	
	// ��ʼ����ģʽ
	bool startStageGame();

	//�༭��ͼ
	bool makeMap();

	//����Ϸ����
	bool help();

	//�˳���Ϸ
	void exit();
private:
	//��ӡ��ͼ
	void drawGameMapInfo();
	
	//�����Ϸ�Ƿ���ͣ
	bool checkGamePause();

	//�����Ϸ�Ƿ����
	bool checkGameOver();

	//��Ӧ��Ҳ���
	void catchPlayerCtrl(char w, char s, char a, char d, char space, TankInfo& Tanks);

	// ��ӡ�Ʒְ�
	void printScorePanel();

	// �����Ʒ���Ϣ
	void updateScore();

};

