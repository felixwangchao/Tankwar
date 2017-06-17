#pragma once
#include <ctime>
#include <map>
#include<queue>

using namespace std;
using std::map;

typedef struct _Node{
	int PosX;
	int PosY;
	int Dir;
	int Fn;
	int Gn;
	int Hn;
	_Node* Ppre;

	bool operator<(const _Node& _A){
		if (PosX * 100 + PosY < _A.PosX * 100 + _A.PosY * 100)
			return true;
		else
			return false;
	}

}Node,*PNODE;

class Astar{
private:
	PNODE start;
	PNODE end;
	vector<PNODE> Visited;
	vector<PNODE> NonVisit;
	clock_t ct;
	int tankID;
public:
	queue<int> path;
	enum DIRECTION{UP,DOWN,LEFT,RIGHT};

	// 构造，初始化路径指针，设置出发地址，目的地址
	Astar(int src_x, int src_y, int dst_x, int dst_y,int tankID);
	// 析构：删除指针指向数据
	~Astar();
	bool Start();
	void expand(PNODE p);
	PNODE FindNextPoint();
	void SavePath(PNODE p);
	bool isFindCheck(PNODE next);
	//double hn(POS p);
};
