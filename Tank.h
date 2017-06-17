#pragma once
#include "Data.h"
#include "mapCell.h"
#include <time.h>

class TankInfo: public mapCell{
private:
	unsigned int tankID;						//坦克编号		(可用来向地图中映射)敌军界面上允许一同出现的坦克根据用户选择来定,40*40/9=177, 编号空间不可能超过177 (1011,0001),8位最大编号为255.超过255编号的坦克在前方坦克消亡时,往前补位.并且修改编号

	unsigned int tankType : 3;						//类型			坦克型号

	unsigned int camp : 2;							//阵营			支持最多4方阵营

	unsigned int posX : 6;							//坐标X			支持在64*64的矩阵中愉快的玩耍

	unsigned int posY : 6;							//坐标Y

	unsigned int orientation : 2;					//朝向			上下左右

	unsigned int color ;							//颜色			支持多种前景色背景色种颜色

	unsigned int blood ;							//血量			最多支持4滴血(最好就两滴血,虚,实两个状态)

	unsigned int speed;							//速度			2档变速		

	unsigned int showLevel : 2;						//显示级别		分3级别 阴影0,坦克1,物品或树林2

	unsigned int missile : 3;						//导弹种类		描述攻击力,最多可描述7种

	unsigned int life : 3;							//最多8条命

	unsigned int bombs : 8;							//弹量			最多256发导弹,最低导导弹数应该定义在  坦克数*血量(50*3=150)  消耗后可通过捡取物品增加

	unsigned int state : 2;							//状态			未出生,激活,已死亡

	unsigned int fireSpeed;						// 坦克射速		慢	快

	clock_t FireTimeStart;							// 开火开始时间

	clock_t FireTimeFinish;							// 开火结束时间

	clock_t MoveTimeStart;							// 移动开始时间

	clock_t MoveTimeFinish;							// 移动结束时间

public:

	#define TANK_F_SP_SLOW		0x4					// 定义坦克速度
	#define TANK_F_SP_FAST		0x1					// 第一坦克速度

	TankInfo();

	TankInfo(int tankID, int tankType);				// 构造函数

	~TankInfo();									// 析构函数

	void setTankInfo(	int tankID,					// 坦克ID
						int tankType,				// 坦克类型
						int camp,					// 阵营
						int posX,					// X坐标
						int posY,					// Y坐标
						int orientation,			// 方向
						int color,					// 颜色
						int blood,					// 血量
						int speed,					// 速度
						int showLevel,				// 显示级别
						int missile,				// 子弹
						int life,					// 生命
						int bombs,					// 炸弹
						int state,					// 状态
						int fireSpeed				// 射速
						);

	void Move(int orientation);						// 坦克移动

	void drawTank(int flag = 0);					// 画坦克

	void clsTank();									// 清坦克

	bool checkTank();								// 检查坦克

	bool fireTank();								// 坦克开火

	bool Injury();									// 坦克受伤

public:
	// State接口
	unsigned int State() const { return state; }
	void State(unsigned int val) { state = val; }

	// Bomb接口
	unsigned int Bombs() const { return bombs; }
	void Bombs(unsigned int val) { bombs = val; }

	// Life接口
	unsigned int Life() const { return life; }
	void Life(unsigned int val) { life = val; }

	// Missile接口
	unsigned int Missile() const { return missile; }
	void Missile(unsigned int val) { missile = val; }

	// Showlevel接口
	unsigned int ShowLevel() const { return showLevel; }
	void ShowLevel(unsigned int val) { showLevel = val; }

	// Speed接口
	unsigned int Speed() const { return speed; }
	void Speed(unsigned int val) { speed = val; }

	// Blood接口
	unsigned int Blood() const { return blood; }
	void Blood(unsigned int val) { blood = val; }

	// Color接口
	unsigned int Color() const { return color; }
	void Color(unsigned int val) { color = val; }

	// Orientation接口
	unsigned int Orientation() const { return orientation; }
	void Orientation(unsigned int val) { orientation = val; }

	// PosY接口
	unsigned int PosY() const { return posY; }
	void PosY(unsigned int val) { posY = val; }

	// PosX接口
	unsigned int PosX() const { return posX; }
	void PosX(unsigned int val) { posX = val; }

	// Camp接口
	unsigned int Camp() const { return camp; }
	void Camp(unsigned int val) { camp = val; }

	// 坦克类型接口
	unsigned int TankType() const { return tankType; }
	void TankType(unsigned int val) { tankType = val; }

	// 坦克ID接口
	unsigned int TankID() const { return tankID; }
	void TankID(unsigned int val) { tankID = val; }

	clock_t ReturnFireTimeFinish() const { return FireTimeFinish; }
	void ReturnFireTimeFinish(clock_t val) { FireTimeFinish = val; }

	clock_t ReturnFireTimeStart() const { return FireTimeStart; }
	void ReturnFireTimeStart(clock_t val) { FireTimeStart = val; }
};

extern vector<TankInfo> tank;