#include <iostream>
#include "Data.h"
#include "Tank.h"
#include "missile.h"
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


//���캯��
TankInfo::TankInfo() {
}


TankInfo::TankInfo(int tankID, int tankType) {
	switch (tankType){						/* ̹�˱�� ̹������   ��Ӫ     ����  ����  ��ɫ       Ѫ��      �ٶ�   ��ʾ����       ��������    ����   ������   ״̬ ����*/
	case TANKTYPE_1: /*�ͼ�̹��*/ setTankInfo(tankID, TANKTYPE_1, CAMP_NPC, 0, 0, UP, F_GREEN, 3, 7, TANKSHOWLEVEL, MISSILETYPE_1, LIFE_0, BOMBS_P, STATE_UNBORN, 4); break;
	case TANKTYPE_3: /*�߼�̹��*/ setTankInfo(tankID, TANKTYPE_3, CAMP_NPC, 0, 0, DOWN, F_GREEN|B_H_YELLOW, 5, 3, TANKSHOWLEVEL, MISSILETYPE_3, LIFE_0, BOMBS_N, STATE_UNBORN, 2); break;
	case TANKTYPE_4: /*�ƶ��Ǳ�*/ setTankInfo(tankID, TANKTYPE_4, CAMP_NPC, 0, 0, DOWN, F_GREEN | B_H_RED, 100, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_UNBORN, 1); break;
	case TANKTYPE_BOSS: /*BOSS*/ setTankInfo(tankID, TANKTYPE_BOSS, CAMP_NPC, 0, 0, DOWN, F_GREEN | B_H_BLUE, 500, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_UNBORN, 1); break;
	}
}

//��������
TankInfo::~TankInfo()
{
	//std::cout << "Tank Destory";
}

void TankInfo::setTankInfo(int tankID, int tankType, int camp, int posX, int posY, int orientation, int color, int blood, int speed, int showLevel, int missile, int life, int bombs, int state, int fireSpeed)
{
	this->tankID = tankID;
	this->tankType = tankType;
	this->camp = camp;
	this->posX = posX;
	this->posY = posY;
	this->orientation = orientation;
	this->color = color;
	this->blood = blood;
	this->speed = speed;
	this->showLevel = showLevel;
	this->missile = missile;
	this->life = life;
	this->bombs = bombs;
	this->state = state;
	this->fireSpeed = fireSpeed;
	this->FireTimeStart = 0;
	this->FireTimeFinish = 100;
	this->MoveTimeStart = 0;
	this->MoveTimeFinish = 100;
}

void TankInfo::Move(int orientation) {

	drawTank();												// ˢ�µ�ǰ̹�ˣ�Ϊ�˼�ʱ����Ѫ���ı仯���ָ���ǰ����ɫ�ȣ�
	MoveTimeFinish = clock();								// �ƶ���ʱ��
	if (MoveTimeFinish - MoveTimeStart > 10 * speed)		// ���δ���ƶ�ʱ���� ���ƶ�
	{
		
		TankInfo temp = *this;

		if (orientation != temp.orientation)
		{
			temp.orientation = orientation;
		}
		else{
			switch (orientation)
			{
			case UP:    temp.posY--; break;
			case DOWN:  temp.posY++; break;
			case LEFT:  temp.posX--; break;
			case RIGHT: temp.posX++; break;
			}
		}
		if (temp.checkTank())
		{
			clsTank();
			*this = temp;
			if (this->Blood() > 0)						// ���̹����Ȼ���
			{
				MoveTimeStart = MoveTimeFinish;			// ����ʱ��
				drawTank();								// ����̹��
			}
			else
				return;									// ����Ͳ�����
		}
	}
}

bool TankInfo::checkTank(){
	for (int row = -1, i = 0; row <= 1; row++, i++)
	{
		for (int col = -1, j = 0; col <= 1; col++, j++)
		{
			// ���жϵ����Ƿ��ܹ�ͨ�����������ͨ������false
			if (CurrentMap.MapData[row + posX][col + posY].Tank_pass() == false)
				return false;

			// ���ж��Ƿ��в����Լ���̹�ˣ�����з���false
			if(CurrentMap.LMapData[row + posX][col + posY] > 0 && CurrentMap.LMapData[row + posX][col + posY] != tankID)
				return false;
			
			if (state == STATE_VALID && CurrentMap.LMapData[row + posX][col + posY] < 0 )
			{
				int ID = CurrentMap.LMapData[row + posX][col + posY];			// ͨ���߼���ͼ��Ϣ������ӵ��ڱ��е�λ��
				
				for (int i = 0; i < mis.size(); i++)
				{
					if (mis[i].MissileID() == ID)
					{
						if (mis[i].Camp() != camp)								// ��������Լ���Ӫ���ӵ�����ô�ӵ����ݻ�
						{
							switch (mis[i].MissileType())						// ̹������
							{
							case MISSILETYPE_7:									// ̹�����ˣ�����̹���Ƿ�����
								if (Injury()){
									if (mis[i].TankID() == 1)					// ��������1���еģ����1�ӷ�
									{
										switch (TankType()){
										case TANKTYPE_1: player1score += 100; break;
										case TANKTYPE_3: player1score += 300; break;
										case TANKTYPE_4: player1score += 700; break;
										}
									}
									if (mis[i].TankID() == 2)					// ��������2���еģ����2�ӷ�
									{
										switch (TankType()){
										case TANKTYPE_1: player2score += 100; break;
										case TANKTYPE_3: player2score += 300; break;
										case TANKTYPE_4: player2score += 700; break;
										}
									}
								}
							case MISSILETYPE_3:
								if (Injury()){
									if (mis[i].TankID() == 1)
									{
										switch (TankType()){
										case TANKTYPE_1: player1score += 100; break;
										case TANKTYPE_3: player1score += 300; break;
										case TANKTYPE_4: player1score += 700; break;
										}
									}
									if (mis[i].TankID() == 2)
									{
										switch (TankType()){
										case TANKTYPE_1: player2score += 100; break;
										case TANKTYPE_3: player2score += 300; break;
										case TANKTYPE_4: player2score += 700; break;
										}
									}
								}
							case MISSILETYPE_1:
								if (Injury()){
									if (mis[i].TankID() == 1)
									{
										switch (TankType()){
										case TANKTYPE_1: player1score += 100; break;
										case TANKTYPE_3: player1score += 300; break;
										case TANKTYPE_4: player1score += 700; break;
										}
									}
									if (mis[i].TankID() == 2)
									{
										switch (TankType()){
										case TANKTYPE_1: player2score += 100; break;
										case TANKTYPE_3: player2score += 300; break;
										case TANKTYPE_4: player2score += 700; break;
										}
									}
								}
								break;
							}
						}
									
						mis[i].MisDestory();									// �ӵ�������
						break;
					}
				}											
			}

			if (CurrentMap.MapData[row + posX][col + posY].MapCellType() == WALL_G && (tankID == 1 || tankID == 2))				// ���ƶ�ʱ�������������
			{
				switch (tankType)																								// ����̹�˵����ͣ��ı�̹�˵�״̬������
				{
				case TANKTYPE_1:setTankInfo(tankID, TANKTYPE_3, CAMP_1, posX, posY, DOWN, F_PURPLE | B_H_WHITE, Blood()+10, 10, TANKSHOWLEVEL, MISSILETYPE_3, LIFE_0, BOMBS_N, STATE_VALID, 4); break;
				case TANKTYPE_3:setTankInfo(tankID, TANKTYPE_4, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 25, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 2); break;
				case TANKTYPE_4:setTankInfo(tankID, TANKTYPE_BOSS, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 100, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 1); break;
				case TANKTYPE_BOSS:setTankInfo(tankID, TANKTYPE_BOSS, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 300, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 0); break;
					break;
				}
				CurrentMap.MapData[row + posX][col + posY].Destory();															// �ı侲̬��ͼ�����ӵ�����
				box_flag = 0;																									// ��ע��ͼ��û��������
			}
		}
	}
	return true;
}


void TankInfo::drawTank(int flag)
{
	for (int row = -1, i=0; row <= 1;row++,i++)
	{
		for (int col = -1, j=0; col <= 1; col++,j++)
		{
			//̹�˵���ʾ�ȼ��ߣ�����ȫ��ʾ̹��
			if (showLevel>CurrentMap.MapData[row + posX][col + posY].ShowLevel() && m_tanksStyle[orientation][j][i] == 1)
			{
				writeChar(row + posX,col + posY, TANK_BODY, (flag)?(F_H_RED):color);

			//����̹�˵���ʾ�ȼ��ͣ�����ʾ��ͼԪ�أ����Ҹı���ɫ
			}
			else if (showLevel>CurrentMap.MapData[row + posX][col + posY].ShowLevel()&& m_tanksStyle[orientation][j][i] == 2){
				char str[10];
				if (blood > 99)
					sprintf_s(str, "??", 10);
				else
					sprintf_s(str, "%d",blood, 10);
				writeChar(row + posX, col + posY, str, F_H_WHITE);
			}
			else{
				CurrentMap.MapData[row + posX][col + posY].drawMapCell(row + posX,col + posY,color & 15);
			}

			// ���߼���ͼ�ϻ���̹����Ϣ,ʹ��̹�˵�ID��ʾ
			CurrentMap.LMapData[row + posX][col + posY] = tankID;
		}
	}
}
void TankInfo::clsTank()
{
	for (int row = -1; row <= 1; row++)
	{
		for (int col = -1; col <= 1; col++)
		{
			// ��ʵ�ʵ�ͼ�����̹��
			CurrentMap.MapData[row + posX][col + posY].drawMapCell(row + posX,col + posY);

			// ���߼���ͼ�����̹��
			CurrentMap.LMapData[row + posX][col + posY] = 0;
		}
	}
}

bool TankInfo::fireTank() {												// ̹�˿���
	if (tankType != TANKTYPE_BOSS)										// �������boss��̹��
	{
		FireTimeFinish = clock();										// ����ʱ��
		if (FireTimeFinish - FireTimeStart > 200 * fireSpeed)			// δ��ʱ���򲻿���
		{
			int ID = 0 - (mis.size() + 1);								
			MissileInfo tmp(*this, ID);
			FireTimeStart = FireTimeFinish;
			if (tmp.CheckMissile()){									// ��֤�ӵ�
				tmp.drawMissile();										// ���ӵ�
				mis.push_back(tmp);										// �ӵ����
				return true;
			}
		}
		return false;
	}
	else                                                                // �����Boss��̹��
	{
		FireTimeFinish = clock();
		if (FireTimeFinish - FireTimeStart > 200 * fireSpeed)			// ���ٿ�ֵ
		{
			for (int i = -1; i < 2; i++)								// ���ɰ˸�������ӵ�
			{
				for (int j = -1; j < 2; j++)
				{
					if (i == 0 && j == 0)
						continue;
					int ID = 0 - (mis.size() + 1);
					int direction = 0;
					if (i < 0 && j>0)
						direction = 2;
					if (i < 0 && j < 0)
						direction = 0;
					if (i > 0 && j>0)
						direction = 1;
					if (i > 0 && j < 0)
						direction = 3;
					if (i < 0 && j == 0)
						direction = 2;
					if (i > 0 && j == 0)
						direction = 3;
					if (i == 0 && j < 0)
						direction = 0;
					if (i == 0 && j > 0)
						direction = 1;
					MissileInfo tmp(*this, ID,this->PosX()+i,this->PosY()+j,direction);			// Ϊÿ���ӵ���ʼ��
					if (tmp.CheckMissile()){													// ���ÿ���ӵ���������
						tmp.drawMissile();														// ���ӵ�
						mis.push_back(tmp);														// �ӵ����
					}
				}
			}
			FireTimeStart = FireTimeFinish;														// �����ӵ�ʱ��

		}
		return false;
	}
}

bool TankInfo::Injury(){																		// ̹������
	if (state == STATE_VALID)																	// ���̹�˻�����
	{
		blood--;																				// ̹�˼�Ѫ
		drawTank(1);																			// ��̹�ˣ�1Ϊһ��flag��1ʱ����̹���Ǻ�ɫ��	
	}

	if (blood <= 0)																				// ���̹�˵�����
	{
		state = STATE_DIE;																		// ����̹��״̬
		clsTank();																				// ���̹��
		return true;																			// ����true
	}
	return false;

}

vector<TankInfo> tank;																			// ̹������