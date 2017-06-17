#include "Astar.h"
#include "Tank.h"
#include "NPCTank.h"
#include <queue>
#include <stack>
#include <map>
#include <math.h>


// 添加n个基础型坦克,k个增强型坦克，j个高级坦克，m个boss坦克
void NPCTank::AddNPC(int n, int k, int j, int m){
	for (int i = 0; i < n+k+j+m; i++){
		int ID = tank.size() + i + 3;
		if (i<n)
			tank.push_back(TankInfo(ID, TANKTYPE_1));
		else if (i>=n && i<n+k)
			tank.push_back(TankInfo(ID, TANKTYPE_3));
		else if (i>=n+k && i< n+k+j)
			tank.push_back(TankInfo(ID, TANKTYPE_4));
		else if (i >= n + k +j && i < n + k + j + m)
			tank.push_back(TankInfo(ID, TANKTYPE_BOSS));
	}
}

// 在重生点上刷新坦克
void NPCTank::AddNPCOnScreen(){
	for (int i = 2; i < tank.size(); i++)
	{
		if (tank[i].State() == STATE_UNBORN)
		{
			for (int j = 2; j < 36; j += 2)				// 重生点为（2，2）（4，2）（6，2）（8，2） ---- （36，2）
			{
				tank[i].PosX(j);						// 给坦克赋坐标
				tank[i].PosY(2);
				if (tank[i].checkTank())				// 检查该点是否能够放下坦克
				{		
					tank[i].State(STATE_VALID);			// 设置坦克状态
					tank[i].drawTank();					// 画坦克
					return;
				}
			}
		}
	}
	return;
}

void NPCTank::AllNPCTankMove(){

	// 移动所有存活坦克
	vector<TankInfo>::iterator iter;
	for (iter = tank.begin()+2; iter != tank.end();)
	{
		if (iter->State() == STATE_VALID)											// 首先，只有活着的坦克才能移动
		{	
			iter->drawTank();														// 在该位置画坦克（由于增加了被击中会变红的功能，这里恢复原来的颜色）
			if (tank[0].State() == STATE_VALID || tank[1].State()==STATE_VALID)		// 检查两个我方坦克是否存活
			{
				int flag = true;													// 标志位 
				
				if (iter->TankType() == TANKTYPE_4){								// 由于3型坦克是穿甲弹，不会受到建筑物限制，所以只要在同一直线上就开火
					
					iter->fireTank();												// 开火

					if (iter->PosX() == tank[0].PosX() && tank[0].State()==STATE_VALID)	// 如果与玩家1同行或同列且玩家1存活，则移动，开火
					{
						if (iter->PosY() > tank[0].PosY())
						{
							iter->Move(0);
							iter->fireTank();
							flag = false;
						}
						else
						{
							iter->Move(1);
							iter->fireTank();
							flag = false;
						}
					}
					else if (iter->PosY() == tank[0].PosY() && tank[0].State() == STATE_VALID)	
					{
						if (iter->PosX() > tank[0].PosX())
						{
							iter->Move(2);
							iter->fireTank();
							flag = false;
						}
						else
						{
							iter->Move(3);
							iter->fireTank();
							flag = false;
						}
					}
					else if (iter->PosX() == tank[1].PosX() && tank[1].State() == STATE_VALID)	// 玩家2同上
						{
							if (iter->PosY() > tank[1].PosY())
							{
								iter->Move(0);
								iter->fireTank();
								flag = false;
							}
							else
							{
								iter->Move(1);
								iter->fireTank();
								flag = false;
							}
						}
					else if (iter->PosY() == tank[1].PosY() && tank[1].State() == STATE_VALID)
					{
						if (iter->PosX() > tank[1].PosX())
						{
							iter->Move(2);
							iter->fireTank();
							flag = false;
						}
						else
						{
							iter->Move(3);
							iter->fireTank();
							flag = false;
						}
					}
				}
				if(flag == true){		//如果flag为true，说明之前已经移动过，则放弃移动

					int target = 0;		// 设定target为零

					if (CurrentMap.MapData[tank[0].PosX()][tank[0].PosY()].ShowLevel() < SHOWLEVEL_1 && tank[0].State()==STATE_VALID)	// 如果玩家1活着，且玩家1不在草丛中，则第一位置1
						target |= 1;
					if (CurrentMap.MapData[tank[1].PosX()][tank[1].PosY()].ShowLevel() < SHOWLEVEL_1 && tank[1].State()==STATE_VALID)	// 如果玩家2活着，且玩家2不在草丛中，则第二位置2
						target |= 2;
					if ((target & 1) == 1 && (target & 2) == 2)	// 如果发现两个玩家都活着， 则计算到两个玩家的距离谁比较近，将目标设为近的
						target = sqrt((tank[0].PosX() - iter->PosX())*(tank[0].PosX() - iter->PosX()) + (tank[0].PosY() - iter->PosY())*(tank[0].PosY() - iter->PosY())) - 
						sqrt((tank[1].PosX() - iter->PosX())*(tank[1].PosX() - iter->PosX()) + (tank[1].PosY() - iter->PosY())*(tank[1].PosY() - iter->PosY())) > 0 ? 2 : 1;

					if (target != 0)	// 如果找到了一个目标
					{
						if (sqrt((tank[target - 1].PosX() - iter->PosX())
							*(tank[target - 1].PosX() - iter->PosX())
							+ (tank[target - 1].PosY() - iter->PosY())
							*(tank[target - 1].PosY() - iter->PosY())) > 30)		// 设置坦克的感知距离为横坐标纵坐标之差30以内，超过半径30的范围则不追踪
						{
							int a = rand() % 4;										// 随机移动
							iter->Move(a);											// 移动
						}
						else
						{
							Astar c(iter->PosX(), iter->PosY(), tank[target-1].PosX(), tank[target-1].PosY(), iter->TankID());	// 如果在感知范围内，构建A*算法

							if (c.Start())											// 启动A*算法，观察是否找到路径
								iter->Move(c.path.front());							// 如果找到路径，则移动一步
							else                                                    // 否则随机移动一步
							{
								int a = rand() % 4;
								iter->Move(a);
							}
						}
					}
					else                                                           // 如果没有找到目标，则随机移动
					{
						int a = rand() % 4;
						iter->Move(a);
					}
					iter->fireTank();												// 并且开一枪
				}
			}
		}
		iter++;																		// 迭代器移动
	}

	// 检查页面上的坦克信息
	UnBorn = 0,Die = 0,Valid = 0;
	for (int i = 2; i < tank.size(); i++)											// 根据坦克状态，刷新坦克信息
	{
		switch (tank[i].State())
		{
		case STATE_UNBORN: UnBorn++; break;							
		case STATE_VALID: Valid++; break;
		case STATE_DIE: Die++; break;
		}
	}
	alive = Valid + UnBorn;															// 计算处剩余的坦克

	int RestPosition = 2 - Valid;													// 计算出需要刷新几个坦克，现在设定为屏幕上只能有两个敌方坦克
	if (RestPosition > 0)
	{
		for (int i = 0; i < RestPosition; i++)
		{
			AddNPCOnScreen();														// 在屏幕上增加坦克
		}
	}
}