#include<iostream>
#include<stdlib.h>
#include "Astar.h"
#include "mapCell.h"
#include <ctime>
#include <vector>
#include <queue>


using std::queue;
using namespace std;

//���캯��
Astar::Astar(int src_x, int src_y, int dst_x, int dst_y, int tankID):tankID(tankID){
	start = new Node{ src_x, src_y };		// ��ʼ��start
	end = new Node{dst_x,dst_y,0,99999};	// ��ʼ��end
	Visited.push_back(start);				// ��start����Visited��
}

//��������
Astar::~Astar(){
	Visited.clear();		// ����Visited��	
	NonVisit.clear();		// ����NonVisit��
}

void Astar::expand(PNODE p){

	Node tmp[4];

	//�����ĸ������ϵĵ�
	tmp[UP].PosX = p->PosX;
	tmp[UP].PosY = (p->PosY) - 1;

	tmp[DOWN].PosX = p->PosX;
	tmp[DOWN].PosY = p->PosY + 1;

	tmp[LEFT].PosX = p->PosX - 1;
	tmp[LEFT].PosY = p->PosY;

	tmp[RIGHT].PosX = p->PosX + 1;
	tmp[RIGHT].PosY = p->PosY;

	for (int i = 0; i < 4; i++){

		// ������������Ҫ��Ϣ
		tmp[i].Dir = i;																				// ���������ķ���
		tmp[i].Hn = abs(tmp[i].PosX - end->PosX) + abs(tmp[i].PosY - end->PosY);					// ���㵽�յ�ľ���
		tmp[i].Gn = (p->Gn) + 1;																	// �������
		tmp[i].Fn = tmp[i].Hn + tmp[i].Gn;															// �������ֵ
		tmp[i].Ppre = p;																			// ǰһ���ڵ�

		bool IsNeeded = true;
		// �ж��ĸ����Ƿ���visited����
		for (int j = 0; j < Visited.size(); j++)
		{
			if (Visited[j]->PosX == tmp[i].PosX && Visited[j]->PosY == tmp[i].PosY)		// ����ҵ��õ�
			{
				IsNeeded = false;		//flag��0
				break;					//����
			}
		}
		if (IsNeeded == false)
			continue;

		// �ж�ÿ���㼰�������Ƿ��ܹ��ƶ�
		for (int k = -1; k <= 1; k++){
			for (int j = -1; j <= 1; j++)
			{
				if (CurrentMap.MapData[k + tmp[i].PosX][j + tmp[i].PosY].Tank_pass() == false)
				{
					IsNeeded = false;
					break;
				}
			}
		}

		if (IsNeeded == false)
			continue;

		for (int j = 0; j < NonVisit.size(); j++){
			if (NonVisit[j]->PosX == tmp[i].PosX && NonVisit[j]->PosY == tmp[i].PosY){
				if (NonVisit[j]->Fn > tmp[i].Fn)
				{
					NonVisit[j]->Ppre = tmp[i].Ppre;
					NonVisit[j]->Hn = tmp[i].Hn;
					NonVisit[j]->Gn = tmp[i].Gn;
					NonVisit[j]->Fn = tmp[i].Fn;
					NonVisit[j]->Dir = tmp[i].Dir;
				}
				IsNeeded = false;
				break;
			}
		}

		if (IsNeeded == false)
			continue;

		if (IsNeeded == true)
		{
			PNODE s = new Node;
			*s = tmp[i];
			NonVisit.push_back(s);
		}
		else continue;
	}
}

PNODE Astar::FindNextPoint(){														// Ѱ����һ���ڵ�

	double MIN = 99999;																// ��Сֵ��ΪMax
	if (NonVisit.empty())															// ���NonVisit��Ϊ�գ��׳��쳣
		throw 99999;

	int pos = 0;


	for (int i = 0; i < NonVisit.size(); i++){										// ����ܹ�ˢ��NonVisit���е���Ϣ����ˢ����Ϣ
		if (NonVisit[i] -> Fn < MIN){	
			MIN = NonVisit[i]->Fn;
			pos = i;
		}
	}

	if (MIN == 99999){																//���û�ҵ���Сֵ���׳��쳣
		throw 99999;
	}

	Visited.push_back(NonVisit[pos]);												// ��Visited���м����Ԫ��
	NonVisit.erase(NonVisit.begin()+pos);											// ��NonVisit��Ĩȥ��Ԫ��
	return *(Visited.end() - 1);													// ���ظ�Ԫ��
}

bool Astar::isFindCheck(PNODE next){												// �ж��Ƿ񵽴�Ŀ���

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if ((end->PosX) + i == next->PosX && (end->PosY) + j == next->PosY)		// ֻҪ����Ŀ�����Χ 3*3 ��λ�ã�����Ϊ�ҵ���Ŀ���
				return false;
		}
	}
	return true;		// �������Ѱ��
}

bool Astar::Start(){

	expand(start);																// ��չĿ���
	try
	{
		PNODE next = FindNextPoint();											// �ҵ���һ���ڵ�
		while (isFindCheck(next)){												// �������Ŀ��㣬�������չ�����򱣴�·��
			expand(next);
			next = FindNextPoint();
		}
		SavePath(next);															// ����·��
		return true;
	}
	catch (int){										
		return false;															// ���û�ҵ�·�������ش���	
	}
}

void Astar::SavePath(PNODE p){													// �ݹ���ã��ҵ�·��
	if (p == start){
		return;
	}
	PNODE pre = p->Ppre;
	SavePath(pre);
	if (pre -> PosX > p -> PosX)
		path.push(2);
	else if (pre -> PosX < p -> PosX)
		path.push(3);
	else if (pre -> PosY < p -> PosY)
		path.push(1);
	else
		path.push(0);
}
