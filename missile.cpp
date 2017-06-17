#include "mapCell.h"
#include "Tank.h"
#include "missile.h"
#include "Engine.h"



MissileInfo::MissileInfo(TankInfo& Tank, int ID)		// һ�㹹�캯��
{

	/*			�ӵ���� �ӵ�����   ��Ӫ     ��ײ         ����   ����  ��ɫ       �ٶ�     ��ʾ����          ״̬          ̹��ID  �Ƿ�б��*/
	setMissileInfo(ID, Tank.Missile(), Tank.Camp(), Tank.PosX(), Tank.PosY(), Tank.Orientation(), Tank.Color(), SPEED_1, MISSILESHOWLEVEL, STATE_UNBORN, Tank.TankID(),0);
}

MissileInfo::MissileInfo(TankInfo& Tank, int ID,int x, int y,int direction)		// б���ӵ����캯��
{
	int ob = 0;																	// �����Ƿ�б�ɣ�Ĭ��Ϊ����
	if (Tank.PosX() == x || Tank.PosY() == y)									// ����ӵ���̹��ˮƽ��ֱ������ʱ
		ob = 0;																	// ��ʱΪ����
	else
	{
		ob = 1;																	// ����Ϊб��
	}
	/*			�ӵ���� �ӵ�����   ��Ӫ     ��ײ         ����   ����  ��ɫ       �ٶ�     ��ʾ����          ״̬          ̹��ID  �Ƿ�б��*/
	setMissileInfo(ID, Tank.Missile(), Tank.Camp(), x, y, direction, Tank.Color(), SPEED_1, MISSILESHOWLEVEL, STATE_UNBORN, Tank.TankID(),ob);
}

	MissileInfo::MissileInfo(const MissileInfo& _mis,int oblique,int orientation){	// α�������캯���������Ƿ�б�ɺͷ�������
		int ID = 0 - (mis.size() + 1);
		this->missileID = ID;
		this->missileType = _mis.missileType;
		this->camp = _mis.camp;
		this->posX = _mis.posX;
		this->posY = _mis.posY;
		this->orientation = orientation;
		this->color = _mis.color;
		this->speed = _mis.speed;
		this->showLevel = _mis.showLevel;
		this->state = _mis.state;
		this->tankID = _mis.tankID;
		this->oblique = oblique;
		this->count = _mis.count;													// �������ԣ�б���ӵ�ÿ������ǰ��һ��
	}

// �����ӵ���Ϣ
void MissileInfo::setMissileInfo(int missileID, int missileType, int camp, int posX, int posY, int orientation, int color, int speed, int showLevel, int state, int tankID, int oblique)
{
	this->missileID = missileID;
	this->missileType = missileType;
	this->camp = camp;
	this->posX = posX;
	this->posY = posY;
	this->orientation = orientation;
	this->color = color;
	this->speed = speed;
	this->showLevel = showLevel;
	this->state = state;
	this->tankID = tankID;
	this->oblique = oblique;
}

bool MissileInfo::HitWall(){

	// ���ǽ����Ա��ݻ�
	if (CurrentMap.MapData[posX][posY].Mis_destory() == true || missileType == MISSILETYPE_7)
	{
		// ����ǽ����Ϣ
		CurrentMap.MapData[posX][posY].Destory();
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);

		// �ӵ�������ɾ���ӵ�
		MisDestory();
		return false;
	}
	// �����ܱ��ݻ�
	else
	{
		//�ӵ�������ɾ���ӵ�
		MisDestory();
		return false;
	}
}

bool MissileInfo::HitTank(){

	int ID = CurrentMap.LMapData[posX][posY];				//��λ̹��ID

	vector<TankInfo>::iterator iter;
	for (iter = tank.begin(); iter != tank.end(); iter++){
		if (iter->TankID() == ID)							// �ҵ���̹��ʱ
		{
			if (iter->Camp() != camp)
			{
				switch (missileType)						// �����ӵ����ͣ�����̹�����˺���
				{
				case MISSILETYPE_7:
					if (iter->Injury()){
							if (tankID == 1)
							{
								switch (iter->TankType()){
								case TANKTYPE_1: player1score += 100; break;
								case TANKTYPE_3: player1score += 300; break;
								case TANKTYPE_4: player1score += 700; break;
								}
							}
							if (tankID == 2)
							{
								switch (iter->TankType()){
								case TANKTYPE_1: player2score += 100; break;
								case TANKTYPE_3: player2score += 300; break;
								case TANKTYPE_4: player2score += 700; break;
								}
							}
					}
				case MISSILETYPE_3:
					if (iter->Injury()){
						if (tankID == 1)
						{
							switch (iter->TankType()){
							case TANKTYPE_1: player1score += 100; break;
							case TANKTYPE_3: player1score += 300; break;
							case TANKTYPE_4: player1score += 700; break;
							}
						}
						if (tankID == 2)
						{
							switch (iter->TankType()){
							case TANKTYPE_1: player2score += 100; break;
							case TANKTYPE_3: player2score += 300; break;
							case TANKTYPE_4: player2score += 700; break;
							}
						}
					}
				case MISSILETYPE_1:
					if (iter->Injury()){
						if (tankID == 1)
						{
							switch (iter->TankType()){
							case TANKTYPE_1: player1score += 100; break;
							case TANKTYPE_3: player1score += 300; break;
							case TANKTYPE_4: player1score += 700; break;
							}
						}
						if (tankID == 2)
						{
							switch (iter->TankType()){
							case TANKTYPE_1: player2score += 100; break;
							case TANKTYPE_3: player2score += 300; break;
							case TANKTYPE_4: player2score += 700; break;
							}
						}
					}
						break;
				}
				
			}
												
			MisDestory();										// �����ӵ�������
			return true;
		}
	}
}

bool MissileInfo::HitMissile(){

	int ID = CurrentMap.LMapData[posX][posY];		// �������ײ�ӵ���ID

	vector<MissileInfo>::iterator iter;
	for (iter = mis.begin(); iter != mis.end(); iter++){
		if (iter->MissileID() == ID)							// �ҵ���̹��ʱ
		{
			iter->MisDestory();										// �����ӵ�������
			break;
		}
	}
	MisDestory();											// �ݻٵ�ǰ�ӵ�
	return true;
}

bool MissileInfo::CheckMissile()
{
	// �ж��Ƿ�Խ��
	if (posX <= 1 || posX >= 38 || posY <= 1 || posY >= 38)
	{
		MisDestory();
		return false;
	}
	// �ж��Ƿ��ǿ���ͨ���ĵ���
	else if (CurrentMap.MapData[posX][posY].Mis_pass() == false)
	{
		return false;
	}
	// �ж��Ƿ����̹��,�Ҳ����Լ�
	else if (CurrentMap.LMapData[posX][posY] > 0 && CurrentMap.LMapData[posX][posY] != tankID)
	{
		return false;
	}
	// �ж��ӵ���ײ�ӵ�ʱ
	else if (CurrentMap.LMapData[posX][posY] < 0)
	{
		return false;
	}
	// ������֤ͨ��
	return true;
}

void MissileInfo::MisDestory(){
	State(STATE_DIE);
	clsMissile();
}

void MissileInfo::drawMissile()
{

	//�ӵ�����ʾ�ȼ��ߣ�����ȫ��ʾ̹��
	if (showLevel > CurrentMap.MapData[posX][posY].ShowLevel() && CurrentMap.LMapData[posX][posY] == 0)
	{
		// �����ӵ����ͣ�ѡ���ӡ���ӵ�
		switch (missileType){
		case 1:writeChar(posX, posY, MISSILETYPE_1_PC, color); break;
		case 3:writeChar(posX, posY, MISSILETYPE_3_PC, color); break;
		case 7:writeChar(posX, posY, MISSILETYPE_7_PC, color); break;
		}
		CurrentMap.LMapData[posX][posY] = missileID;
	}

	//�����ӵ�����ʾ�ȼ��ͣ�����ʾ��ͼԪ�أ����Ҹı���ɫ
	else if (CurrentMap.LMapData[posX][posY]==0)
	{
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);
		CurrentMap.LMapData[posX][posY] = missileID;
	}
		

	// �����߼���ͼ
	
}

void MissileInfo::clsMissile()
{
	// ����ӵ�  ���õ�û��̹��ʱ
	if (CurrentMap.LMapData[posX][posY] <= 0){
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);
		CurrentMap.LMapData[posX][posY] = 0;
	}

}

bool MissileInfo::MissileMove()											// �ӵ����к���
{
	MissileInfo temp = *this;											// ��ʱ�ӵ�

	if (oblique == 0)													// ������ӵ�����б���ӵ�������������
	{
		switch (temp.orientation)
		{
		case UP:    temp.posY--; break;
		case DOWN:  temp.posY++; break;
		case LEFT:  temp.posX--; break;
		case RIGHT: temp.posX++; break;
		}
	}
	else
	{																	// ����Ϊб���ӵ�ʱ

		switch (temp.orientation)										// ���ݷ��򣬸ı���ʱ�ӵ�����
		{
		case UP:{														// �Ϸ�����45��ʱ��
			temp.posX--; temp.posY--;									// ��������
			if (count == false)											// countΪfalseʱ�����ӵ��������Լ�����ǰ��
			{
				MissileInfo tmp1(temp, 0, 0);							// �������ӵ����趨б�Ⱥͷ���
				tmp1.PosX(temp.PosX() + 1);
				if (tmp1.CheckMissile()){
					tmp1.drawMissile();
					mis.push_back(tmp1);
				}
				MissileInfo tmp2(temp, 0, 2);							// �������ӵ����趨б�Ⱥͷ���
				tmp2.PosY(temp.PosY() + 1);
				if (tmp2.CheckMissile()){
					tmp2.drawMissile();
					mis.push_back(tmp2);
				}
			}

			break;
		}
		case DOWN:{
			temp.posX++; temp.posY++;
			if (count == false)
			{
				MissileInfo tmp1(temp, 0, 1);
				tmp1.PosX(temp.PosX() - 1);
				if (tmp1.CheckMissile()){
					tmp1.drawMissile();
					mis.push_back(tmp1);
				}
				MissileInfo tmp2(temp, 0, 3);
				tmp2.PosY(temp.PosY() - 1);
				if (tmp2.CheckMissile()){
					tmp2.drawMissile();
					mis.push_back(tmp2);
				}
			}

			break;
		}
		case LEFT: {
			temp.posX--; temp.posY++;
			if (count == false)
			{
				MissileInfo tmp1(temp, 0, 1);
				tmp1.PosX(temp.PosX() + 1);
				if (tmp1.CheckMissile()){
					tmp1.drawMissile();
					mis.push_back(tmp1);
				}
				MissileInfo tmp2(temp, 0, 2);
				tmp2.PosY(temp.PosY() - 1);
				if (tmp2.CheckMissile()){
					tmp2.drawMissile();
					mis.push_back(tmp2);
				}
			}

			break;
		}
		case RIGHT: {
			temp.posX++; temp.posY--;
			if (count == false)
			{
				MissileInfo tmp1(temp, 0, 0);
				tmp1.PosX(temp.PosX() - 1);
				if (tmp1.CheckMissile()){
					tmp1.drawMissile();
					mis.push_back(tmp1);
				}

				MissileInfo tmp2(temp, 0, 3);
				tmp2.PosY(temp.PosY() + 1);
				if (tmp2.CheckMissile()){
					tmp2.drawMissile();
					mis.push_back(tmp2);
				}
			}
			break;
		}
		}
		if (count == false)											// ��תcount
		{
			temp = *this;
			temp.count = true;
		}
		else
		{
			temp.count = false;										// ��תcount
		}
	}

	if (temp.CheckMissile())										// ����ӵ�
	{
		clsMissile();												// ����ӵ�
		*this = temp;
		drawMissile();												//�����ӵ�
		return true;
	}
	else
	{
		clsMissile();												// ���checkʧ��
		*this = temp;

		if (CurrentMap.MapData[posX][posY].Mis_pass() == false)		// ���ǽ����ͨ����
		{
			HitWall();												// ����ǽ
		}
		else if (CurrentMap.LMapData[posX][posY] > 0)				// �������̹��
		{
			HitTank();												// ����̹��
		}
		else if (CurrentMap.LMapData[posX][posY] < 0)
		{
			HitMissile();											// ����ӵ���ײ
		}
	}
	return false;
}

vector<MissileInfo> mis;