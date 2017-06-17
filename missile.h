#pragma once
#include "Data.h"
#include "Draw.h"
#include "Tank.h"



class MissileInfo: public CDraw {
private:
	int missileID;					//�ӵ���� �������ͼ��ӳ���Ψһ��ʾ,�������±�һ��

	unsigned int missileType : 3;		//��������,����������,��������7��

	unsigned int camp : 2;				//��Ӫ	֧�����4����Ӫ

	unsigned int volume : 2;			//���	�Ƿ���Ҫ����ײ���,   0:����  1:��  2:���Ϊ�������ܼ�1����,����ը��������

	unsigned int posX : 6;				//����X	֧����64*64�ľ�����������ˣ

	unsigned int posY : 6;				//����Y

	unsigned int orientation : 2;		//����	��������

	unsigned int color : 4;				//��ɫ	֧��16����ɫ�仯

	unsigned int speed : 1;				//�ٶ�	2������	 //���� SPEED_0  0x0	//���� SPEED_1  0x1	

	unsigned int showLevel : 2;			//��ʾ���� ��3���� ����0,����1(̹��1),���� ��Ʒ��δ���

	unsigned int state : 2;				//״̬,δ����,����,������

	unsigned int tankID;  			//̹�˱�� �������ͼ��ӳ���Ψһ��ʾ

	unsigned int oblique = 0;

public:			
	MissileInfo(TankInfo& Tank, int ID);	// �ӵ����캯�� 
	MissileInfo(TankInfo& Tank, int ID, int x, int y,int direction);	// �ӵ����깹�캯��
	MissileInfo(const MissileInfo& _mis,int oblique,int orientation);
	void setMissileInfo(					// �����ӵ���Ϣ
		int missileID,						// �ӵ�ID
		int missileType,					// �ӵ�����
		int camp,							// ��Ӫ
		int posX,							// X����
		int posY,							// Y����
		int orientation,					// ����
		int color,							// ��ɫ
		int speed,							// �ٶ�
		int showLevel,						// ��ʾ����
		int state,							// ״̬
		int tankID,
		int oblique);						// Դ̹��ID

	bool CheckMissile();					// ����ӵ���ײ
	void MisDestory();						// �ӵ��ݻ�
	void drawMissile();						// ���ӵ�
	void clsMissile();						// �����ӵ�
	bool MissileMove();			// �ӵ��ƶ�
	bool HitWall();							// ����ǽ��
	bool HitTank();							// ����̹��
	bool HitMissile();						// �����ӵ�

public:
	// ̹��ԴID�ӿ�
	unsigned int TankID() const { return tankID; }
	void TankID(unsigned int val) { tankID = val; }

	// �ӵ�״̬�ӿ�
	unsigned int State() const { return state; }
	void State(unsigned int val) { state = val; }

	// ��ʾ����ӿ�
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// �ӵ��ٶȽӿ�
	unsigned int Speed() const { return speed; }
	void Speed(unsigned int val) { speed = val; }

	// �ӵ���ɫ�ӿ�
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }

	// �ӵ�����ӿ�
	unsigned int Orientation() const { return orientation; }
	void Orientation(unsigned int val) { orientation = val; }

	// �ӵ�Y����ӿ�
	unsigned int PosY() const { return posY; }
	void PosY(unsigned int val) { posY = val; }

	// �ӵ�X����ӿ�
	unsigned int PosX() const { return posX; }
	void PosX(unsigned int val) { posX = val; }

	// �ӵ���Ӫ�ӿ�
	unsigned int Camp() const { return camp; }
	void Camp(unsigned int val) { camp = val; }

	// �ӵ����ͽӿ�
	unsigned int MissileType() const { return missileType; }
	void MissileType(unsigned int val) { missileType = val; }

	// �ӵ�ID�ӿ�
	unsigned int MissileID() const { return missileID; }
	void MissileID(unsigned int val) { missileID = val; }

	unsigned int Oblique() const { return oblique; }
	void Oblique(unsigned int val) { oblique = val; }

public:
	bool count = false;
};

extern vector<MissileInfo> mis;

