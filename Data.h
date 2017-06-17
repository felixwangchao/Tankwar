#pragma once
#include <windows.h>
#include <vector>
using std::vector;


/*******	常用颜色定义	************************/
// 字体显示相关
#define REVERSE    COMMON_LVB_REVERSE_VIDEO	 // 反色
#define UNDER_SCORE COMMON_LVB_UNDERSCORE    // 下划线

#define AUTO_STYLE 0x0007				//浅灰
#define play0_STYLE F_RED				//深红
#define play1_STYLE F_H_PURPLE			//亮紫
#define play2_STYLE F_H_GREEN			//亮绿

// 字体颜色
#define F_BLUE     FOREGROUND_BLUE      // 深蓝
#define F_H_BLUE   0x0001|0x0008        // 亮蓝
#define F_GREEN    0x0002               // 深绿
#define F_H_GREEN  0x0002|0x0008        // 亮绿
#define F_RED      0x0004               // 深红
#define F_H_RED    0x0004|0x0008        // 亮红
#define F_YELLOW   0x0002|0x0004        // 深黄
#define F_H_YELLOW 0x0002|0x0004|0x0008 // 亮黄
#define F_PURPLE   0x0001|0x0004        // 深紫
#define F_H_PURPLE 0x0001|0x0004|0x0008 // 亮紫
#define F_CYAN     0x0002|0x0004        // 深青
#define F_H_CYAN   0x0002|0x0004|0x0008 // 亮青
#define F_WHITE    0x0004|0x0002|0x0001
#define F_H_WHITE  0x0004|0x0002|0x0001|0x0008

// 背景颜色
#define B_BLUE     BACKGROUND_BLUE      // 深蓝
#define B_H_BLUE   0x0010|0x0080        // 亮蓝
#define B_GREEN    0x0020               // 深绿
#define B_H_GREEN  0x0020|0x0080        // 亮绿
#define B_RED      0x0040               // 深红
#define B_H_RED    0x0040|0x0080        // 亮红
#define B_YELLOW   0x0020|0x0040        // 深黄
#define B_H_YELLOW 0x0020|0x0040|0x0080 // 亮黄
#define B_PURPLE   0x0010|0x0040        // 深紫
#define B_H_PURPLE 0x0010|0x0040|0x0080 // 亮紫
#define B_CYAN     0x0020|0x0040        // 深青
#define B_H_CYAN   0x0020|0x0040|0x0080 // 亮青
#define B_WHITE    0x0010|0x0020|0x0040
#define B_H_WHITE  0x0010|0x0020|0x0040|0x0080


/*******	窗口界面定义	************************/
//窗口大小
#define WINDOWS_WIDTH 120
#define WINDOWS_HIGH  40

//默认窗口标题
#define AUTO_CONSOLE_TITLE "坦克大战"

//地图大小
#define MAP_WIDTH 40					//地图宽
#define MAP_HIGH  40					//地图高

/*******	操作相关定义	************************/
//方向
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#define SINGLE  0X0001	//player游戏人数
#define DOUBLE  0X0002
#define THREE   0X0003

/*******	界面元素定义	************************/
#define MISSILETYPE_1      0x01 // ☉  炮弹
#define MISSILETYPE_3      0x03 // ¤  榴弹
#define MISSILETYPE_7      0x07 // ◎  穿甲弹
#define MISSILETYPE_1_PC   "☉" 
#define MISSILETYPE_3_PC   "¤" 
#define MISSILETYPE_7_PC   "◎" 

#define WALL_NULL         0x0  // 空道						默认
#define WALL_A1           0x2  // ▓  土墙（可破坏）		默认
#define WALL_A2           0x3  // 卍  土墙（可破坏,破坏形态）class CData
#define WALL_B            0x4  // 〓  铁墙 (可破坏){
#define WALL_C            0x5  // ≈  河流（减速）public:
#define WALL_D            0x6  // ■  路障（无敌,不可穿过）默认:	CData();
#define WALL_E            0x7  // ≡  丛林（隐身）	~CData();
#define WALL_F            0x8  // ※  高速路(加速)
#define WALL_G            0x9  // ☆  箱子（随机加BUff）
#define WALL_A1_PC        "▓"	
#define WALL_A2_PC        "卍"
#define WALL_B_PC         "〓"
#define WALL_C_PC         "≈"
#define WALL_D_PC         "■"
#define WALL_E_PC         "≡"
#define WALL_F_PC         "※"
#define WALL_G_PC         "☆"

#define STATE_UNBORN	  0x00
#define STATE_VALID		  0x01
#define STATE_DIE		  0x02



#define CELLSTART_P1   0xa   // 玩家1出生点
#define CELLSTART_P2   0xb   // 玩家2出生点
#define CELLSTART_P3   0xc   // 玩家3出生点
#define CELLSTART_N1   0xd   // NPC1出生点
#define CELLSTART_N2   0xe   // NPC2出生点
#define CELLSTART_N3   0xf   // NPC3出生点
#define CELLSTART_N4   0x10  // NPC4出生点
#define CELLSTART_N5   0x11  // NPC5出生点
#define CELLSTART_N6   0x12  // NPC6出生点
#define CELLSTART_H1   0x13  // 阵营1基地
#define CELLSTART_H2   0x14  // 阵营2基地
#define CELLSTART_H3   0x15  // 阵营3基地
#define CELLSTART_H4   0x16  // 阵营CAMP_NPC基地

#define CAMP_1    0x0  // camp阵营1(play1)
#define CAMP_2    0x1  // camp阵营2(play2)
#define CAMP_3    0x2  // camp阵营3(play3)
#define CAMP_NPC  0x3  // camp阵营CAMP_NPC

#define VOLUME_NO   0x0  // 不会碰撞						volume碰撞体积
#define VOLUME_YES  0x1  // 会碰撞							volume碰撞体积
#define VOLUME_HUGE 0x2  // 会碰撞,距中心范围1以内都会碰撞  volume碰撞体积

#define BLOOD_0		0x0		//死亡状态	血量0
#define BLOOD_1		0x1		//濒死状态  血量1
#define BLOOD_2		0x2		//受伤状态  血量2
#define BLOOD_3		0x3		//新状态	血量3 //复活时的血量
#define BLOOD_MAX	0x9		//最大血量	血量9

// #define ISINVINCIBLE_0 0x0 //是否无敌 否			//通用tank
// #define ISINVINCIBLE_1 0x1 //是否无敌 是

#define STRENGTH_1 0x1	 //强度1,威力>=1的导弹能造成伤害	//强度(防御),跟导弹种类数对应,威力小于该强度的子弹打不动该墙体
#define STRENGTH_3 0x3	 //强度3,威力>=3的导弹能造成伤害   
#define STRENGTH_7 0x7	 //强度7,威力>=7的导弹能造成伤害

#define SHOWLEVEL_0 0x0	 //同一个位置,当有一方volume(体积)=0时即VOLUME_NO时,会出现物体重叠,此时优先级高的显示,优先级低的被覆盖
#define SHOWLEVEL_1 0x1	 //显示优先级
#define SHOWLEVEL_2 0x2	 //显示优先级          地下的优先级0,坦克,导弹,一般墙体2,丛林3宝箱4(宝箱暂时不可覆盖在其他墙体上,为3,为4现阶段没什么区别)
#define SHOWLEVEL_3 0x3	 //显示优先级
#define TANKSHOWLEVEL 0x1		 //坦克显示优先级
#define MISSILESHOWLEVEL 0x1	 //导弹显示优先级

#define ISSLOW_0 0x0	 //0,不减速 同一个位置,当有一方volume(体积)=0时即VOLUME_NO时,会出现物体重叠,此时判断是否加减速
#define ISSLOW_1 0x1	 //1,减速
#define ISFAST_0 0x0	 //0,不加速 同一个位置,当有一方volume(体积)=0时即VOLUME_NO时,会出现物体重叠,此时判断是否加减速
#define ISFAST_1 0x1	 //1,减加

#define ISALIVE_0 0x0	 //0,不能移动
#define ISALIVE_1 0x1	 //1,可以移动(可以移动的物体,坦克可以把它推动,类似推箱子的功能)

#define EFFECT_0 0x0	 //特效0 无特效
#define EFFECT_1 0x1	 //特效1 减速
#define EFFECT_2 0x2	 //特效2 加速	
#define EFFECT_3 0x3	 //特效3 冰冻(冻住坦克不能移动)
#define EFFECT_4 0x4	 //特效4 加子弹
#define EFFECT_5 0x5	 //特效5 升级武器
#define EFFECT_6 0x6	 //特效6 增加生命
#define EFFECT_7 0x7	 //特效7 增加一次大技能机会

#define ISINVINCIBLE_0  0x0 //是否无敌 否	(坦克此属性大于0就是无敌状态,通过不断自减来达到倒计时作用)			
#define ISINVINCIBLE_1  0x1 //是否无敌 是
#define ISINVINCIBLE_3  0x3 //是否无敌 是				
#define ISINVINCIBLE_5  0x5 //是否无敌 是
#define ISINVINCIBLE_10 0xa //是否无敌 是
#define ISINVINCIBLE_15 0xf //是否无敌 是

#define TANKID_NULL		0x0  //0		该地图点上是否存在坦克,其编号是多少,0为无坦克,对应关系(编号=坦克数组下标)
#define MISSILEID_NULL  0x0  //0		该点上没有导弹

/*******	坦克信息定义	************************/
#define TANKTYPE_1 0x1	 //低级坦克		玩家出生类型(默认tankType:TANKTYPE_1 , volume:VOLUME_YES , orientation:UP , color:F_GREEN(玩家1) F_YELLOW(玩家2) F_BLUE(玩家3) , blood:BLOOD_3 , speed:SPEED_0 , isInvincible:ISINVINCIBLE_3 , showLevel:SHOWLEVEL_2 , missile:MISSILETYPE_1 , life:LIFE_3 , skills:SKILLS_1 , bombs:BOMBS_P , isFrozen:ISFROZEN_0 , mines:MINES_P)
						 //低级坦克		低级CAMP_NPC出生类型(默认tankType:TANKTYPE_1 , volume:VOLUME_YES , orientation:DOWN , color:F_H_YELLOW , blood:BLOOD_3 , speed:SPEED_0 , isInvincible:ISINVINCIBLE_0 , showLevel:SHOWLEVEL_2 , missile:MISSILETYPE_1 , life:LIFE_1 ,  bombs:BOMBS_N , isFrozen:ISFROZEN_0 , mines:MINES_N)
//#define TANKTYPE_2 0x2	 //中级坦克		 //坦克类型,映射坦克强度(防御),威力小于该强度的子弹打不动该坦克(此设计,需要先把宝物加攻击里做起来,否则让用户感觉不友好,先抛弃)
#define TANKTYPE_3 0x2	 //高级坦克
#define TANKTYPE_4 0x3	 //移动城堡
#define TANKTYPE_BOSS 0x4	 //移动城堡

#define SPEED_0  0x0	//慢速
#define SPEED_1  0x1	//快速

#define LIFE_0   0x0		//剩余生命值	
#define LIFE_1   0x1
#define LIFE_2   0x2
#define LIFE_3   0x3
#define LIFE_4   0x4
#define LIFE_5   0x5
#define LIFE_6   0x6
#define LIFE_7   0x7

#define SKILLS_0  0x0		//剩余大招数
#define SKILLS_1  0x1
#define SKILLS_2  0x2
#define SKILLS_3  0x3

#define BOMBS_P 0xFF		//CAMP_NPC初始化为255
#define BOMBS_N 0xFF		//CAMP_NPC初始化为255

#define ISFROZEN_0	0x0		//是否被冻住 否	(坦克此属性大于0就是无敌状态,通过不断自减来达到倒计时作用)
#define ISFROZEN_1  0x1		//是否被冻住 是
#define ISFROZEN_3  0x3		//是否被冻住 是				
#define ISFROZEN_5  0x5		//是否被冻住 是
#define ISFROZEN_10 0xa		//是否被冻住 是
#define ISFROZEN_15 0xf		//是否被冻住 是

#define MINES_0 0X0		//地雷数,没有
#define MINES_1 0X1		
#define MINES_4 0X4		//玩家初始化为4
#define MINES_7 0X7		//CAMP_NPC  初级:1,中级:4,高级:8

#define TANK_BODY	      "■"      //玩家默认

extern int tempMap[40][40];
extern int stageMode[3][40][40];
extern int player1score;
extern int player2score;
extern int alive;
extern int box_flag;

class CData
{
public:
	CData();
	~CData();

public://基本数据类型定义
	
public://基本数据定义
	int m_tanksStyle[4][3][3];				//坦克样式
	//bool m_isOldData;

	//bool readData(char * filePath);			//读档
	//bool writeData(char * filepath);		//存档

};

