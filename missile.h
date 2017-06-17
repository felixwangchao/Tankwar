#pragma once
#include "Data.h"
#include "Draw.h"
#include "Tank.h"



class MissileInfo: public CDraw {
private:
	int missileID;					//子弹编号 用来向地图中映射的唯一标示,与数组下标一致

	unsigned int missileType : 3;		//导弹种类,描述攻击力,最多可描述7种

	unsigned int camp : 2;				//阵营	支持最多4方阵营

	unsigned int volume : 2;			//体积	是否需要做碰撞检测,   0:不做  1:做  2:体积为中心四周加1都做,形容炸弹的威力

	unsigned int posX : 6;				//坐标X	支持在64*64的矩阵中愉快的玩耍

	unsigned int posY : 6;				//坐标Y

	unsigned int orientation : 2;		//朝向	上下左右

	unsigned int color : 4;				//颜色	支持16种颜色变化

	unsigned int speed : 1;				//速度	2档变速	 //慢速 SPEED_0  0x0	//块速 SPEED_1  0x1	

	unsigned int showLevel : 2;			//显示级别 分3级别 地下0,地面1(坦克1),最上 物品其次丛林

	unsigned int state : 2;				//状态,未出生,激活,已死亡

	unsigned int tankID;  			//坦克编号 用来向地图中映射的唯一标示

	unsigned int oblique = 0;

public:			
	MissileInfo(TankInfo& Tank, int ID);	// 子弹构造函数 
	MissileInfo(TankInfo& Tank, int ID, int x, int y,int direction);	// 子弹坐标构造函数
	MissileInfo(const MissileInfo& _mis,int oblique,int orientation);
	void setMissileInfo(					// 设置子弹信息
		int missileID,						// 子弹ID
		int missileType,					// 子弹类型
		int camp,							// 阵营
		int posX,							// X坐标
		int posY,							// Y坐标
		int orientation,					// 方向
		int color,							// 颜色
		int speed,							// 速度
		int showLevel,						// 显示级别
		int state,							// 状态
		int tankID,
		int oblique);						// 源坦克ID

	bool CheckMissile();					// 检查子弹碰撞
	void MisDestory();						// 子弹摧毁
	void drawMissile();						// 画子弹
	void clsMissile();						// 擦除子弹
	bool MissileMove();			// 子弹移动
	bool HitWall();							// 击中墙壁
	bool HitTank();							// 击中坦克
	bool HitMissile();						// 击中子弹

public:
	// 坦克源ID接口
	unsigned int TankID() const { return tankID; }
	void TankID(unsigned int val) { tankID = val; }

	// 子弹状态接口
	unsigned int State() const { return state; }
	void State(unsigned int val) { state = val; }

	// 显示级别接口
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// 子弹速度接口
	unsigned int Speed() const { return speed; }
	void Speed(unsigned int val) { speed = val; }

	// 子弹颜色接口
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }

	// 子弹方向接口
	unsigned int Orientation() const { return orientation; }
	void Orientation(unsigned int val) { orientation = val; }

	// 子弹Y坐标接口
	unsigned int PosY() const { return posY; }
	void PosY(unsigned int val) { posY = val; }

	// 子弹X坐标接口
	unsigned int PosX() const { return posX; }
	void PosX(unsigned int val) { posX = val; }

	// 子弹阵营接口
	unsigned int Camp() const { return camp; }
	void Camp(unsigned int val) { camp = val; }

	// 子弹类型接口
	unsigned int MissileType() const { return missileType; }
	void MissileType(unsigned int val) { missileType = val; }

	// 子弹ID接口
	unsigned int MissileID() const { return missileID; }
	void MissileID(unsigned int val) { missileID = val; }

	unsigned int Oblique() const { return oblique; }
	void Oblique(unsigned int val) { oblique = val; }

public:
	bool count = false;
};

extern vector<MissileInfo> mis;

