#include<iostream>
#include<stdlib.h>
#include "Astar.h"
#include "mapCell.h"
#include <ctime>
#include <vector>
#include <queue>


using std::queue;
using namespace std;

//构造函数
Astar::Astar(int src_x, int src_y, int dst_x, int dst_y, int tankID):tankID(tankID){
	start = new Node{ src_x, src_y };		// 初始化start
	end = new Node{dst_x,dst_y,0,99999};	// 初始化end
	Visited.push_back(start);				// 将start放入Visited表
}

//析构函数
Astar::~Astar(){
	Visited.clear();		// 清理Visited表	
	NonVisit.clear();		// 清理NonVisit表
}

void Astar::expand(PNODE p){

	Node tmp[4];

	//生成四个方向上的点
	tmp[UP].PosX = p->PosX;
	tmp[UP].PosY = (p->PosY) - 1;

	tmp[DOWN].PosX = p->PosX;
	tmp[DOWN].PosY = p->PosY + 1;

	tmp[LEFT].PosX = p->PosX - 1;
	tmp[LEFT].PosY = p->PosY;

	tmp[RIGHT].PosX = p->PosX + 1;
	tmp[RIGHT].PosY = p->PosY;

	for (int i = 0; i < 4; i++){

		// 计算各个点的重要信息
		tmp[i].Dir = i;																				// 到达这个点的方向
		tmp[i].Hn = abs(tmp[i].PosX - end->PosX) + abs(tmp[i].PosY - end->PosY);					// 计算到终点的距离
		tmp[i].Gn = (p->Gn) + 1;																	// 计算损耗
		tmp[i].Fn = tmp[i].Hn + tmp[i].Gn;															// 计算估价值
		tmp[i].Ppre = p;																			// 前一个节点

		bool IsNeeded = true;
		// 判断四个点是否在visited表中
		for (int j = 0; j < Visited.size(); j++)
		{
			if (Visited[j]->PosX == tmp[i].PosX && Visited[j]->PosY == tmp[i].PosY)		// 如果找到该点
			{
				IsNeeded = false;		//flag置0
				break;					//跳出
			}
		}
		if (IsNeeded == false)
			continue;

		// 判断每个点及其四周是否能够移动
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

PNODE Astar::FindNextPoint(){														// 寻找下一个节点

	double MIN = 99999;																// 最小值置为Max
	if (NonVisit.empty())															// 如果NonVisit表为空，抛出异常
		throw 99999;

	int pos = 0;


	for (int i = 0; i < NonVisit.size(); i++){										// 如果能够刷新NonVisit表中的信息，则刷新信息
		if (NonVisit[i] -> Fn < MIN){	
			MIN = NonVisit[i]->Fn;
			pos = i;
		}
	}

	if (MIN == 99999){																//如果没找到最小值，抛出异常
		throw 99999;
	}

	Visited.push_back(NonVisit[pos]);												// 在Visited表中加入该元素
	NonVisit.erase(NonVisit.begin()+pos);											// 在NonVisit中抹去该元素
	return *(Visited.end() - 1);													// 返回该元素
}

bool Astar::isFindCheck(PNODE next){												// 判断是否到达目标点

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if ((end->PosX) + i == next->PosX && (end->PosY) + j == next->PosY)		// 只要到达目标点周围 3*3 的位置，就认为找到了目标点
				return false;
		}
	}
	return true;		// 否则继续寻找
}

bool Astar::Start(){

	expand(start);																// 扩展目标点
	try
	{
		PNODE next = FindNextPoint();											// 找到下一个节点
		while (isFindCheck(next)){												// 如果不是目标点，则继续扩展，否则保存路径
			expand(next);
			next = FindNextPoint();
		}
		SavePath(next);															// 保存路径
		return true;
	}
	catch (int){										
		return false;															// 如果没找到路径，返回错误	
	}
}

void Astar::SavePath(PNODE p){													// 递归调用，找到路径
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
