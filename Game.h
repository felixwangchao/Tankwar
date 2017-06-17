#pragma once
#include "Engine.h"
#include "mapCell.h"
#include "Tank.h"

class CGame:public CEngine,public virtual CDraw,public virtual Map
{
public:
	CGame();
	~CGame();

	//游戏选项界面
	int index();

	//设置单双人游戏
	int setPlayer();

	//游戏开始
	bool startGame(int load_map[][40]);
	
	// 开始闯关模式
	bool startStageGame();

	//编辑地图
	bool makeMap();

	//打开游戏帮助
	bool help();

	//退出游戏
	void exit();
private:
	//打印地图
	void drawGameMapInfo();
	
	//检查游戏是否暂停
	bool checkGamePause();

	//检查游戏是否结束
	bool checkGameOver();

	//响应玩家操作
	void catchPlayerCtrl(char w, char s, char a, char d, char space, TankInfo& Tanks);

	// 打印计分版
	void printScorePanel();

	// 升级计分信息
	void updateScore();

};

