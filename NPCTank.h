#pragma once
#include "Tank.h"

class NPCTank{
public:
	void AddNPC(int n = 1, int k = 1,int j=1, int m=1);		// 添加NPC

	void AddNPCOnScreen();									// 在屏幕上刷新坦克

	void AllNPCTankMove();									// 所有敌方坦克移动

	// Valid成员的接口
	int ReturnValidTank() const { return Valid; }
	void ReturnValidTank(int val) { Valid = val; }

	// Unborn成员的接口
	int ReturnUnBornTank() const { return UnBorn; }
	void ReturnUnBornTank(int val) { UnBorn = val; }

	// Die成员的接口
	int ReturnDiedTank() const { return Die; }
	void ReturnDiedTank(int val) { Die = val; }

private:
	int	Valid;			// 在屏幕上的坦克数量

	int UnBorn;			// 未出生的坦克数量

	int Die;			// 死亡了的坦克数量
};