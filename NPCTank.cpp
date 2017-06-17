#include "Astar.h"
#include "Tank.h"
#include "NPCTank.h"
#include <queue>
#include <stack>
#include <map>
#include <math.h>


// ���n��������̹��,k����ǿ��̹�ˣ�j���߼�̹�ˣ�m��boss̹��
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

// ����������ˢ��̹��
void NPCTank::AddNPCOnScreen(){
	for (int i = 2; i < tank.size(); i++)
	{
		if (tank[i].State() == STATE_UNBORN)
		{
			for (int j = 2; j < 36; j += 2)				// ������Ϊ��2��2����4��2����6��2����8��2�� ---- ��36��2��
			{
				tank[i].PosX(j);						// ��̹�˸�����
				tank[i].PosY(2);
				if (tank[i].checkTank())				// ���õ��Ƿ��ܹ�����̹��
				{		
					tank[i].State(STATE_VALID);			// ����̹��״̬
					tank[i].drawTank();					// ��̹��
					return;
				}
			}
		}
	}
	return;
}

void NPCTank::AllNPCTankMove(){

	// �ƶ����д��̹��
	vector<TankInfo>::iterator iter;
	for (iter = tank.begin()+2; iter != tank.end();)
	{
		if (iter->State() == STATE_VALID)											// ���ȣ�ֻ�л��ŵ�̹�˲����ƶ�
		{	
			iter->drawTank();														// �ڸ�λ�û�̹�ˣ����������˱����л���Ĺ��ܣ�����ָ�ԭ������ɫ��
			if (tank[0].State() == STATE_VALID || tank[1].State()==STATE_VALID)		// ��������ҷ�̹���Ƿ���
			{
				int flag = true;													// ��־λ 
				
				if (iter->TankType() == TANKTYPE_4){								// ����3��̹���Ǵ��׵��������ܵ����������ƣ�����ֻҪ��ͬһֱ���ϾͿ���
					
					iter->fireTank();												// ����

					if (iter->PosX() == tank[0].PosX() && tank[0].State()==STATE_VALID)	// ��������1ͬ�л�ͬ�������1�����ƶ�������
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
					else if (iter->PosX() == tank[1].PosX() && tank[1].State() == STATE_VALID)	// ���2ͬ��
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
				if(flag == true){		//���flagΪtrue��˵��֮ǰ�Ѿ��ƶ�����������ƶ�

					int target = 0;		// �趨targetΪ��

					if (CurrentMap.MapData[tank[0].PosX()][tank[0].PosY()].ShowLevel() < SHOWLEVEL_1 && tank[0].State()==STATE_VALID)	// ������1���ţ������1���ڲݴ��У����һλ��1
						target |= 1;
					if (CurrentMap.MapData[tank[1].PosX()][tank[1].PosY()].ShowLevel() < SHOWLEVEL_1 && tank[1].State()==STATE_VALID)	// ������2���ţ������2���ڲݴ��У���ڶ�λ��2
						target |= 2;
					if ((target & 1) == 1 && (target & 2) == 2)	// �������������Ҷ����ţ� ����㵽������ҵľ���˭�ȽϽ�����Ŀ����Ϊ����
						target = sqrt((tank[0].PosX() - iter->PosX())*(tank[0].PosX() - iter->PosX()) + (tank[0].PosY() - iter->PosY())*(tank[0].PosY() - iter->PosY())) - 
						sqrt((tank[1].PosX() - iter->PosX())*(tank[1].PosX() - iter->PosX()) + (tank[1].PosY() - iter->PosY())*(tank[1].PosY() - iter->PosY())) > 0 ? 2 : 1;

					if (target != 0)	// ����ҵ���һ��Ŀ��
					{
						if (sqrt((tank[target - 1].PosX() - iter->PosX())
							*(tank[target - 1].PosX() - iter->PosX())
							+ (tank[target - 1].PosY() - iter->PosY())
							*(tank[target - 1].PosY() - iter->PosY())) > 30)		// ����̹�˵ĸ�֪����Ϊ������������֮��30���ڣ������뾶30�ķ�Χ��׷��
						{
							int a = rand() % 4;										// ����ƶ�
							iter->Move(a);											// �ƶ�
						}
						else
						{
							Astar c(iter->PosX(), iter->PosY(), tank[target-1].PosX(), tank[target-1].PosY(), iter->TankID());	// ����ڸ�֪��Χ�ڣ�����A*�㷨

							if (c.Start())											// ����A*�㷨���۲��Ƿ��ҵ�·��
								iter->Move(c.path.front());							// ����ҵ�·�������ƶ�һ��
							else                                                    // ��������ƶ�һ��
							{
								int a = rand() % 4;
								iter->Move(a);
							}
						}
					}
					else                                                           // ���û���ҵ�Ŀ�꣬������ƶ�
					{
						int a = rand() % 4;
						iter->Move(a);
					}
					iter->fireTank();												// ���ҿ�һǹ
				}
			}
		}
		iter++;																		// �������ƶ�
	}

	// ���ҳ���ϵ�̹����Ϣ
	UnBorn = 0,Die = 0,Valid = 0;
	for (int i = 2; i < tank.size(); i++)											// ����̹��״̬��ˢ��̹����Ϣ
	{
		switch (tank[i].State())
		{
		case STATE_UNBORN: UnBorn++; break;							
		case STATE_VALID: Valid++; break;
		case STATE_DIE: Die++; break;
		}
	}
	alive = Valid + UnBorn;															// ���㴦ʣ���̹��

	int RestPosition = 2 - Valid;													// �������Ҫˢ�¼���̹�ˣ������趨Ϊ��Ļ��ֻ���������з�̹��
	if (RestPosition > 0)
	{
		for (int i = 0; i < RestPosition; i++)
		{
			AddNPCOnScreen();														// ����Ļ������̹��
		}
	}
}