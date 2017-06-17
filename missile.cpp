#include "mapCell.h"
#include "Tank.h"
#include "missile.h"
#include "Engine.h"



MissileInfo::MissileInfo(TankInfo& Tank, int ID)		// 一般构造函数
{

	/*			子弹编号 子弹类型   阵营     碰撞         坐标   朝向  颜色       速度     显示级别          状态          坦克ID  是否斜飞*/
	setMissileInfo(ID, Tank.Missile(), Tank.Camp(), Tank.PosX(), Tank.PosY(), Tank.Orientation(), Tank.Color(), SPEED_1, MISSILESHOWLEVEL, STATE_UNBORN, Tank.TankID(),0);
}

MissileInfo::MissileInfo(TankInfo& Tank, int ID,int x, int y,int direction)		// 斜飞子弹构造函数
{
	int ob = 0;																	// 设置是否斜飞，默认为正飞
	if (Tank.PosX() == x || Tank.PosY() == y)									// 如果子弹在坦克水平或垂直方向上时
		ob = 0;																	// 此时为正飞
	else
	{
		ob = 1;																	// 否则为斜飞
	}
	/*			子弹编号 子弹类型   阵营     碰撞         坐标   朝向  颜色       速度     显示级别          状态          坦克ID  是否斜飞*/
	setMissileInfo(ID, Tank.Missile(), Tank.Camp(), x, y, direction, Tank.Color(), SPEED_1, MISSILESHOWLEVEL, STATE_UNBORN, Tank.TankID(),ob);
}

	MissileInfo::MissileInfo(const MissileInfo& _mis,int oblique,int orientation){	// 伪拷贝构造函数，加入是否斜飞和方向属性
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
		this->count = _mis.count;													// 计数属性，斜飞子弹每两次向前走一步
	}

// 设置子弹信息
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

	// 如果墙体可以被摧毁
	if (CurrentMap.MapData[posX][posY].Mis_destory() == true || missileType == MISSILETYPE_7)
	{
		// 更新墙体信息
		CurrentMap.MapData[posX][posY].Destory();
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);

		// 子弹向量中删除子弹
		MisDestory();
		return false;
	}
	// 否则不能被摧毁
	else
	{
		//子弹向量中删除子弹
		MisDestory();
		return false;
	}
}

bool MissileInfo::HitTank(){

	int ID = CurrentMap.LMapData[posX][posY];				//定位坦克ID

	vector<TankInfo>::iterator iter;
	for (iter = tank.begin(); iter != tank.end(); iter++){
		if (iter->TankID() == ID)							// 找到该坦克时
		{
			if (iter->Camp() != camp)
			{
				switch (missileType)						// 根据子弹类型，调用坦克受伤函数
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
												
			MisDestory();										// 调用子弹毁灭函数
			return true;
		}
	}
}

bool MissileInfo::HitMissile(){

	int ID = CurrentMap.LMapData[posX][posY];		// 计算出被撞子弹的ID

	vector<MissileInfo>::iterator iter;
	for (iter = mis.begin(); iter != mis.end(); iter++){
		if (iter->MissileID() == ID)							// 找到该坦克时
		{
			iter->MisDestory();										// 调用子弹毁灭函数
			break;
		}
	}
	MisDestory();											// 摧毁当前子弹
	return true;
}

bool MissileInfo::CheckMissile()
{
	// 判断是否越界
	if (posX <= 1 || posX >= 38 || posY <= 1 || posY >= 38)
	{
		MisDestory();
		return false;
	}
	// 判断是否是可以通过的地形
	else if (CurrentMap.MapData[posX][posY].Mis_pass() == false)
	{
		return false;
	}
	// 判断是否击中坦克,且不是自己
	else if (CurrentMap.LMapData[posX][posY] > 0 && CurrentMap.LMapData[posX][posY] != tankID)
	{
		return false;
	}
	// 判断子弹碰撞子弹时
	else if (CurrentMap.LMapData[posX][posY] < 0)
	{
		return false;
	}
	// 否则，验证通过
	return true;
}

void MissileInfo::MisDestory(){
	State(STATE_DIE);
	clsMissile();
}

void MissileInfo::drawMissile()
{

	//子弹的显示等级高，就完全显示坦克
	if (showLevel > CurrentMap.MapData[posX][posY].ShowLevel() && CurrentMap.LMapData[posX][posY] == 0)
	{
		// 根据子弹类型，选择打印的子弹
		switch (missileType){
		case 1:writeChar(posX, posY, MISSILETYPE_1_PC, color); break;
		case 3:writeChar(posX, posY, MISSILETYPE_3_PC, color); break;
		case 7:writeChar(posX, posY, MISSILETYPE_7_PC, color); break;
		}
		CurrentMap.LMapData[posX][posY] = missileID;
	}

	//否则子弹的显示等级低，就显示地图元素，并且改变颜色
	else if (CurrentMap.LMapData[posX][posY]==0)
	{
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);
		CurrentMap.LMapData[posX][posY] = missileID;
	}
		

	// 更新逻辑地图
	
}

void MissileInfo::clsMissile()
{
	// 清除子弹  当该地没有坦克时
	if (CurrentMap.LMapData[posX][posY] <= 0){
		CurrentMap.MapData[posX][posY].drawMapCell(posX, posY);
		CurrentMap.LMapData[posX][posY] = 0;
	}

}

bool MissileInfo::MissileMove()											// 子弹飞行函数
{
	MissileInfo temp = *this;											// 临时子弹

	if (oblique == 0)													// 如果该子弹不是斜飞子弹，则正常飞行
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
	{																	// 否则为斜飞子弹时

		switch (temp.orientation)										// 根据方向，改变零时子弹坐标
		{
		case UP:{														// 上方左旋45°时，
			temp.posX--; temp.posY--;									// 更新坐标
			if (count == false)											// count为false时，造子弹，但是自己不向前飞
			{
				MissileInfo tmp1(temp, 0, 0);							// 制造新子弹，设定斜度和方向
				tmp1.PosX(temp.PosX() + 1);
				if (tmp1.CheckMissile()){
					tmp1.drawMissile();
					mis.push_back(tmp1);
				}
				MissileInfo tmp2(temp, 0, 2);							// 制造新子弹，设定斜度和方向
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
		if (count == false)											// 反转count
		{
			temp = *this;
			temp.count = true;
		}
		else
		{
			temp.count = false;										// 反转count
		}
	}

	if (temp.CheckMissile())										// 检查子弹
	{
		clsMissile();												// 清除子弹
		*this = temp;
		drawMissile();												//更新子弹
		return true;
	}
	else
	{
		clsMissile();												// 如果check失败
		*this = temp;

		if (CurrentMap.MapData[posX][posY].Mis_pass() == false)		// 如果墙不能通过，
		{
			HitWall();												// 击中墙
		}
		else if (CurrentMap.LMapData[posX][posY] > 0)				// 如果击中坦克
		{
			HitTank();												// 击中坦克
		}
		else if (CurrentMap.LMapData[posX][posY] < 0)
		{
			HitMissile();											// 如果子弹相撞
		}
	}
	return false;
}

vector<MissileInfo> mis;