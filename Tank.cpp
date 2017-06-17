#include <iostream>
#include "Data.h"
#include "Tank.h"
#include "missile.h"
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


//构造函数
TankInfo::TankInfo() {
}


TankInfo::TankInfo(int tankID, int tankType) {
	switch (tankType){						/* 坦克编号 坦克类型   阵营     坐标  朝向  颜色       血量      速度   显示级别       导弹类型    生命   地雷数   状态 射速*/
	case TANKTYPE_1: /*低级坦克*/ setTankInfo(tankID, TANKTYPE_1, CAMP_NPC, 0, 0, UP, F_GREEN, 3, 7, TANKSHOWLEVEL, MISSILETYPE_1, LIFE_0, BOMBS_P, STATE_UNBORN, 4); break;
	case TANKTYPE_3: /*高级坦克*/ setTankInfo(tankID, TANKTYPE_3, CAMP_NPC, 0, 0, DOWN, F_GREEN|B_H_YELLOW, 5, 3, TANKSHOWLEVEL, MISSILETYPE_3, LIFE_0, BOMBS_N, STATE_UNBORN, 2); break;
	case TANKTYPE_4: /*移动城堡*/ setTankInfo(tankID, TANKTYPE_4, CAMP_NPC, 0, 0, DOWN, F_GREEN | B_H_RED, 100, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_UNBORN, 1); break;
	case TANKTYPE_BOSS: /*BOSS*/ setTankInfo(tankID, TANKTYPE_BOSS, CAMP_NPC, 0, 0, DOWN, F_GREEN | B_H_BLUE, 500, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_UNBORN, 1); break;
	}
}

//析构函数
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

	drawTank();												// 刷新当前坦克（为了及时更新血量的变化，恢复当前的颜色等）
	MoveTimeFinish = clock();								// 移动的时钟
	if (MoveTimeFinish - MoveTimeStart > 10 * speed)		// 如果未到移动时机， 则不移动
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
			if (this->Blood() > 0)						// 如果坦克仍然存活
			{
				MoveTimeStart = MoveTimeFinish;			// 更新时钟
				drawTank();								// 画新坦克
			}
			else
				return;									// 否则就不画了
		}
	}
}

bool TankInfo::checkTank(){
	for (int row = -1, i = 0; row <= 1; row++, i++)
	{
		for (int col = -1, j = 0; col <= 1; col++, j++)
		{
			// 先判断地形是否能够通过，如果不能通过返回false
			if (CurrentMap.MapData[row + posX][col + posY].Tank_pass() == false)
				return false;

			// 再判断是否有不是自己的坦克，如果有返回false
			if(CurrentMap.LMapData[row + posX][col + posY] > 0 && CurrentMap.LMapData[row + posX][col + posY] != tankID)
				return false;
			
			if (state == STATE_VALID && CurrentMap.LMapData[row + posX][col + posY] < 0 )
			{
				int ID = CurrentMap.LMapData[row + posX][col + posY];			// 通过逻辑地图信息计算出子弹在表中的位置
				
				for (int i = 0; i < mis.size(); i++)
				{
					if (mis[i].MissileID() == ID)
					{
						if (mis[i].Camp() != camp)								// 如果不是自己阵营的子弹，那么子弹被摧毁
						{
							switch (mis[i].MissileType())						// 坦克受伤
							{
							case MISSILETYPE_7:									// 坦克受伤，返回坦克是否死亡
								if (Injury()){
									if (mis[i].TankID() == 1)					// 如果是玩家1击毙的，玩家1加分
									{
										switch (TankType()){
										case TANKTYPE_1: player1score += 100; break;
										case TANKTYPE_3: player1score += 300; break;
										case TANKTYPE_4: player1score += 700; break;
										}
									}
									if (mis[i].TankID() == 2)					// 如果是玩家2击毙的，玩家2加分
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
									
						mis[i].MisDestory();									// 子弹被消灭
						break;
					}
				}											
			}

			if (CurrentMap.MapData[row + posX][col + posY].MapCellType() == WALL_G && (tankID == 1 || tankID == 2))				// 在移动时如果碰到了箱子
			{
				switch (tankType)																								// 根据坦克的类型，改变坦克的状态，升级
				{
				case TANKTYPE_1:setTankInfo(tankID, TANKTYPE_3, CAMP_1, posX, posY, DOWN, F_PURPLE | B_H_WHITE, Blood()+10, 10, TANKSHOWLEVEL, MISSILETYPE_3, LIFE_0, BOMBS_N, STATE_VALID, 4); break;
				case TANKTYPE_3:setTankInfo(tankID, TANKTYPE_4, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 25, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 2); break;
				case TANKTYPE_4:setTankInfo(tankID, TANKTYPE_BOSS, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 100, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 1); break;
				case TANKTYPE_BOSS:setTankInfo(tankID, TANKTYPE_BOSS, CAMP_1, posX, posY, DOWN, F_H_PURPLE | B_H_WHITE, Blood() + 300, 0, TANKSHOWLEVEL, MISSILETYPE_7, LIFE_0, BOMBS_N, STATE_VALID, 0); break;
					break;
				}
				CurrentMap.MapData[row + posX][col + posY].Destory();															// 改变静态地图上箱子的类型
				box_flag = 0;																									// 标注地图上没有箱子了
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
			//坦克的显示等级高，就完全显示坦克
			if (showLevel>CurrentMap.MapData[row + posX][col + posY].ShowLevel() && m_tanksStyle[orientation][j][i] == 1)
			{
				writeChar(row + posX,col + posY, TANK_BODY, (flag)?(F_H_RED):color);

			//否则坦克的显示等级低，就显示地图元素，并且改变颜色
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

			// 在逻辑地图上画下坦克信息,使用坦克的ID表示
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
			// 在实际地图上清除坦克
			CurrentMap.MapData[row + posX][col + posY].drawMapCell(row + posX,col + posY);

			// 在逻辑地图上清除坦克
			CurrentMap.LMapData[row + posX][col + posY] = 0;
		}
	}
}

bool TankInfo::fireTank() {												// 坦克开火
	if (tankType != TANKTYPE_BOSS)										// 如果不是boss型坦克
	{
		FireTimeFinish = clock();										// 开火时钟
		if (FireTimeFinish - FireTimeStart > 200 * fireSpeed)			// 未到时间则不开火
		{
			int ID = 0 - (mis.size() + 1);								
			MissileInfo tmp(*this, ID);
			FireTimeStart = FireTimeFinish;
			if (tmp.CheckMissile()){									// 验证子弹
				tmp.drawMissile();										// 画子弹
				mis.push_back(tmp);										// 子弹入队
				return true;
			}
		}
		return false;
	}
	else                                                                // 如果是Boss型坦克
	{
		FireTimeFinish = clock();
		if (FireTimeFinish - FireTimeStart > 200 * fireSpeed)			// 射速空值
		{
			for (int i = -1; i < 2; i++)								// 生成八个方向的子弹
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
					MissileInfo tmp(*this, ID,this->PosX()+i,this->PosY()+j,direction);			// 为每个子弹初始化
					if (tmp.CheckMissile()){													// 检查每个子弹是能生成
						tmp.drawMissile();														// 画子弹
						mis.push_back(tmp);														// 子弹入队
					}
				}
			}
			FireTimeStart = FireTimeFinish;														// 更新子弹时钟

		}
		return false;
	}
}

bool TankInfo::Injury(){																		// 坦克受伤
	if (state == STATE_VALID)																	// 如果坦克还活着
	{
		blood--;																				// 坦克减血
		drawTank(1);																			// 画坦克，1为一个flag，1时画的坦克是红色的	
	}

	if (blood <= 0)																				// 如果坦克的死了
	{
		state = STATE_DIE;																		// 设置坦克状态
		clsTank();																				// 清除坦克
		return true;																			// 返回true
	}
	return false;

}

vector<TankInfo> tank;																			// 坦克向量