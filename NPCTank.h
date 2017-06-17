#pragma once
#include "Tank.h"

class NPCTank{
public:
	void AddNPC(int n = 1, int k = 1,int j=1, int m=1);		// ���NPC

	void AddNPCOnScreen();									// ����Ļ��ˢ��̹��

	void AllNPCTankMove();									// ���ез�̹���ƶ�

	// Valid��Ա�Ľӿ�
	int ReturnValidTank() const { return Valid; }
	void ReturnValidTank(int val) { Valid = val; }

	// Unborn��Ա�Ľӿ�
	int ReturnUnBornTank() const { return UnBorn; }
	void ReturnUnBornTank(int val) { UnBorn = val; }

	// Die��Ա�Ľӿ�
	int ReturnDiedTank() const { return Die; }
	void ReturnDiedTank(int val) { Die = val; }

private:
	int	Valid;			// ����Ļ�ϵ�̹������

	int UnBorn;			// δ������̹������

	int Die;			// �����˵�̹������
};