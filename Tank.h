#pragma once
#include "Data.h"
#include "mapCell.h"
#include <time.h>

class TankInfo: public mapCell{
private:
	unsigned int tankID;						//̹�˱��		(���������ͼ��ӳ��)�о�����������һͬ���ֵ�̹�˸����û�ѡ������,40*40/9=177, ��ſռ䲻���ܳ���177 (1011,0001),8λ�����Ϊ255.����255��ŵ�̹����ǰ��̹������ʱ,��ǰ��λ.�����޸ı��

	unsigned int tankType : 3;						//����			̹���ͺ�

	unsigned int camp : 2;							//��Ӫ			֧�����4����Ӫ

	unsigned int posX : 6;							//����X			֧����64*64�ľ�����������ˣ

	unsigned int posY : 6;							//����Y

	unsigned int orientation : 2;					//����			��������

	unsigned int color ;							//��ɫ			֧�ֶ���ǰ��ɫ����ɫ����ɫ

	unsigned int blood ;							//Ѫ��			���֧��4��Ѫ(��þ�����Ѫ,��,ʵ����״̬)

	unsigned int speed;							//�ٶ�			2������		

	unsigned int showLevel : 2;						//��ʾ����		��3���� ��Ӱ0,̹��1,��Ʒ������2

	unsigned int missile : 3;						//��������		����������,��������7��

	unsigned int life : 3;							//���8����

	unsigned int bombs : 8;							//����			���256������,��͵�������Ӧ�ö�����  ̹����*Ѫ��(50*3=150)  ���ĺ��ͨ����ȡ��Ʒ����

	unsigned int state : 2;							//״̬			δ����,����,������

	unsigned int fireSpeed;						// ̹������		��	��

	clock_t FireTimeStart;							// ����ʼʱ��

	clock_t FireTimeFinish;							// �������ʱ��

	clock_t MoveTimeStart;							// �ƶ���ʼʱ��

	clock_t MoveTimeFinish;							// �ƶ�����ʱ��

public:

	#define TANK_F_SP_SLOW		0x4					// ����̹���ٶ�
	#define TANK_F_SP_FAST		0x1					// ��һ̹���ٶ�

	TankInfo();

	TankInfo(int tankID, int tankType);				// ���캯��

	~TankInfo();									// ��������

	void setTankInfo(	int tankID,					// ̹��ID
						int tankType,				// ̹������
						int camp,					// ��Ӫ
						int posX,					// X����
						int posY,					// Y����
						int orientation,			// ����
						int color,					// ��ɫ
						int blood,					// Ѫ��
						int speed,					// �ٶ�
						int showLevel,				// ��ʾ����
						int missile,				// �ӵ�
						int life,					// ����
						int bombs,					// ը��
						int state,					// ״̬
						int fireSpeed				// ����
						);

	void Move(int orientation);						// ̹���ƶ�

	void drawTank(int flag = 0);					// ��̹��

	void clsTank();									// ��̹��

	bool checkTank();								// ���̹��

	bool fireTank();								// ̹�˿���

	bool Injury();									// ̹������

public:
	// State�ӿ�
	unsigned int State() const { return state; }
	void State(unsigned int val) { state = val; }

	// Bomb�ӿ�
	unsigned int Bombs() const { return bombs; }
	void Bombs(unsigned int val) { bombs = val; }

	// Life�ӿ�
	unsigned int Life() const { return life; }
	void Life(unsigned int val) { life = val; }

	// Missile�ӿ�
	unsigned int Missile() const { return missile; }
	void Missile(unsigned int val) { missile = val; }

	// Showlevel�ӿ�
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// Speed�ӿ�
	unsigned int Speed() const { return speed; }
	void Speed(unsigned int val) { speed = val; }

	// Blood�ӿ�
	unsigned int Blood() const { return blood; }
	void Blood(unsigned int val) { blood = val; }

	// Color�ӿ�
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }

	// Orientation�ӿ�
	unsigned int Orientation() const { return orientation; }
	void Orientation(unsigned int val) { orientation = val; }

	// PosY�ӿ�
	unsigned int PosY() const { return posY; }
	void PosY(unsigned int val) { posY = val; }

	// PosX�ӿ�
	unsigned int PosX() const { return posX; }
	void PosX(unsigned int val) { posX = val; }

	// Camp�ӿ�
	unsigned int Camp() const { return camp; }
	void Camp(unsigned int val) { camp = val; }

	// ̹�����ͽӿ�
	unsigned int TankType() const { return tankType; }
	void TankType(unsigned int val) { tankType = val; }

	// ̹��ID�ӿ�
	unsigned int TankID() const { return tankID; }
	void TankID(unsigned int val) { tankID = val; }

	clock_t ReturnFireTimeFinish() const { return FireTimeFinish; }
	void ReturnFireTimeFinish(clock_t val) { FireTimeFinish = val; }

	clock_t ReturnFireTimeStart() const { return FireTimeStart; }
	void ReturnFireTimeStart(clock_t val) { FireTimeStart = val; }
};

extern vector<TankInfo> tank;