#pragma once
#include <windows.h>
#include <vector>
using std::vector;


/*******	������ɫ����	************************/
// ������ʾ���
#define REVERSE    COMMON_LVB_REVERSE_VIDEO	 // ��ɫ
#define UNDER_SCORE COMMON_LVB_UNDERSCORE    // �»���

#define AUTO_STYLE 0x0007				//ǳ��
#define play0_STYLE F_RED				//���
#define play1_STYLE F_H_PURPLE			//����
#define play2_STYLE F_H_GREEN			//����

// ������ɫ
#define F_BLUE     FOREGROUND_BLUE      // ����
#define F_H_BLUE   0x0001|0x0008        // ����
#define F_GREEN    0x0002               // ����
#define F_H_GREEN  0x0002|0x0008        // ����
#define F_RED      0x0004               // ���
#define F_H_RED    0x0004|0x0008        // ����
#define F_YELLOW   0x0002|0x0004        // ���
#define F_H_YELLOW 0x0002|0x0004|0x0008 // ����
#define F_PURPLE   0x0001|0x0004        // ����
#define F_H_PURPLE 0x0001|0x0004|0x0008 // ����
#define F_CYAN     0x0002|0x0004        // ����
#define F_H_CYAN   0x0002|0x0004|0x0008 // ����
#define F_WHITE    0x0004|0x0002|0x0001
#define F_H_WHITE  0x0004|0x0002|0x0001|0x0008

// ������ɫ
#define B_BLUE     BACKGROUND_BLUE      // ����
#define B_H_BLUE   0x0010|0x0080        // ����
#define B_GREEN    0x0020               // ����
#define B_H_GREEN  0x0020|0x0080        // ����
#define B_RED      0x0040               // ���
#define B_H_RED    0x0040|0x0080        // ����
#define B_YELLOW   0x0020|0x0040        // ���
#define B_H_YELLOW 0x0020|0x0040|0x0080 // ����
#define B_PURPLE   0x0010|0x0040        // ����
#define B_H_PURPLE 0x0010|0x0040|0x0080 // ����
#define B_CYAN     0x0020|0x0040        // ����
#define B_H_CYAN   0x0020|0x0040|0x0080 // ����
#define B_WHITE    0x0010|0x0020|0x0040
#define B_H_WHITE  0x0010|0x0020|0x0040|0x0080


/*******	���ڽ��涨��	************************/
//���ڴ�С
#define WINDOWS_WIDTH 120
#define WINDOWS_HIGH  40

//Ĭ�ϴ��ڱ���
#define AUTO_CONSOLE_TITLE "̹�˴�ս"

//��ͼ��С
#define MAP_WIDTH 40					//��ͼ��
#define MAP_HIGH  40					//��ͼ��

/*******	������ض���	************************/
//����
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#define SINGLE  0X0001	//player��Ϸ����
#define DOUBLE  0X0002
#define THREE   0X0003

/*******	����Ԫ�ض���	************************/
#define MISSILETYPE_1      0x01 // ��  �ڵ�
#define MISSILETYPE_3      0x03 // ��  ��
#define MISSILETYPE_7      0x07 // ��  ���׵�
#define MISSILETYPE_1_PC   "��" 
#define MISSILETYPE_3_PC   "��" 
#define MISSILETYPE_7_PC   "��" 

#define WALL_NULL         0x0  // �յ�						Ĭ��
#define WALL_A1           0x2  // ��  ��ǽ�����ƻ���		Ĭ��
#define WALL_A2           0x3  // �d  ��ǽ�����ƻ�,�ƻ���̬��class CData
#define WALL_B            0x4  // ��  ��ǽ (���ƻ�){
#define WALL_C            0x5  // ��  ���������٣�public:
#define WALL_D            0x6  // ��  ·�ϣ��޵�,���ɴ�����Ĭ��:	CData();
#define WALL_E            0x7  // ��  ���֣�����	~CData();
#define WALL_F            0x8  // ��  ����·(����)
#define WALL_G            0x9  // ��  ���ӣ������BUff��
#define WALL_A1_PC        "��"	
#define WALL_A2_PC        "�d"
#define WALL_B_PC         "��"
#define WALL_C_PC         "��"
#define WALL_D_PC         "��"
#define WALL_E_PC         "��"
#define WALL_F_PC         "��"
#define WALL_G_PC         "��"

#define STATE_UNBORN	  0x00
#define STATE_VALID		  0x01
#define STATE_DIE		  0x02



#define CELLSTART_P1   0xa   // ���1������
#define CELLSTART_P2   0xb   // ���2������
#define CELLSTART_P3   0xc   // ���3������
#define CELLSTART_N1   0xd   // NPC1������
#define CELLSTART_N2   0xe   // NPC2������
#define CELLSTART_N3   0xf   // NPC3������
#define CELLSTART_N4   0x10  // NPC4������
#define CELLSTART_N5   0x11  // NPC5������
#define CELLSTART_N6   0x12  // NPC6������
#define CELLSTART_H1   0x13  // ��Ӫ1����
#define CELLSTART_H2   0x14  // ��Ӫ2����
#define CELLSTART_H3   0x15  // ��Ӫ3����
#define CELLSTART_H4   0x16  // ��ӪCAMP_NPC����

#define CAMP_1    0x0  // camp��Ӫ1(play1)
#define CAMP_2    0x1  // camp��Ӫ2(play2)
#define CAMP_3    0x2  // camp��Ӫ3(play3)
#define CAMP_NPC  0x3  // camp��ӪCAMP_NPC

#define VOLUME_NO   0x0  // ������ײ						volume��ײ���
#define VOLUME_YES  0x1  // ����ײ							volume��ײ���
#define VOLUME_HUGE 0x2  // ����ײ,�����ķ�Χ1���ڶ�����ײ  volume��ײ���

#define BLOOD_0		0x0		//����״̬	Ѫ��0
#define BLOOD_1		0x1		//����״̬  Ѫ��1
#define BLOOD_2		0x2		//����״̬  Ѫ��2
#define BLOOD_3		0x3		//��״̬	Ѫ��3 //����ʱ��Ѫ��
#define BLOOD_MAX	0x9		//���Ѫ��	Ѫ��9

// #define ISINVINCIBLE_0 0x0 //�Ƿ��޵� ��			//ͨ��tank
// #define ISINVINCIBLE_1 0x1 //�Ƿ��޵� ��

#define STRENGTH_1 0x1	 //ǿ��1,����>=1�ĵ���������˺�	//ǿ��(����),��������������Ӧ,����С�ڸ�ǿ�ȵ��ӵ��򲻶���ǽ��
#define STRENGTH_3 0x3	 //ǿ��3,����>=3�ĵ���������˺�   
#define STRENGTH_7 0x7	 //ǿ��7,����>=7�ĵ���������˺�

#define SHOWLEVEL_0 0x0	 //ͬһ��λ��,����һ��volume(���)=0ʱ��VOLUME_NOʱ,����������ص�,��ʱ���ȼ��ߵ���ʾ,���ȼ��͵ı�����
#define SHOWLEVEL_1 0x1	 //��ʾ���ȼ�
#define SHOWLEVEL_2 0x2	 //��ʾ���ȼ�          ���µ����ȼ�0,̹��,����,һ��ǽ��2,����3����4(������ʱ���ɸ���������ǽ����,Ϊ3,Ϊ4�ֽ׶�ûʲô����)
#define SHOWLEVEL_3 0x3	 //��ʾ���ȼ�
#define TANKSHOWLEVEL 0x1		 //̹����ʾ���ȼ�
#define MISSILESHOWLEVEL 0x1	 //������ʾ���ȼ�

#define ISSLOW_0 0x0	 //0,������ ͬһ��λ��,����һ��volume(���)=0ʱ��VOLUME_NOʱ,����������ص�,��ʱ�ж��Ƿ�Ӽ���
#define ISSLOW_1 0x1	 //1,����
#define ISFAST_0 0x0	 //0,������ ͬһ��λ��,����һ��volume(���)=0ʱ��VOLUME_NOʱ,����������ص�,��ʱ�ж��Ƿ�Ӽ���
#define ISFAST_1 0x1	 //1,����

#define ISALIVE_0 0x0	 //0,�����ƶ�
#define ISALIVE_1 0x1	 //1,�����ƶ�(�����ƶ�������,̹�˿��԰����ƶ�,���������ӵĹ���)

#define EFFECT_0 0x0	 //��Ч0 ����Ч
#define EFFECT_1 0x1	 //��Ч1 ����
#define EFFECT_2 0x2	 //��Ч2 ����	
#define EFFECT_3 0x3	 //��Ч3 ����(��ס̹�˲����ƶ�)
#define EFFECT_4 0x4	 //��Ч4 ���ӵ�
#define EFFECT_5 0x5	 //��Ч5 ��������
#define EFFECT_6 0x6	 //��Ч6 ��������
#define EFFECT_7 0x7	 //��Ч7 ����һ�δ��ܻ���

#define ISINVINCIBLE_0  0x0 //�Ƿ��޵� ��	(̹�˴����Դ���0�����޵�״̬,ͨ�������Լ����ﵽ����ʱ����)			
#define ISINVINCIBLE_1  0x1 //�Ƿ��޵� ��
#define ISINVINCIBLE_3  0x3 //�Ƿ��޵� ��				
#define ISINVINCIBLE_5  0x5 //�Ƿ��޵� ��
#define ISINVINCIBLE_10 0xa //�Ƿ��޵� ��
#define ISINVINCIBLE_15 0xf //�Ƿ��޵� ��

#define TANKID_NULL		0x0  //0		�õ�ͼ�����Ƿ����̹��,�����Ƕ���,0Ϊ��̹��,��Ӧ��ϵ(���=̹�������±�)
#define MISSILEID_NULL  0x0  //0		�õ���û�е���

/*******	̹����Ϣ����	************************/
#define TANKTYPE_1 0x1	 //�ͼ�̹��		��ҳ�������(Ĭ��tankType:TANKTYPE_1 , volume:VOLUME_YES , orientation:UP , color:F_GREEN(���1) F_YELLOW(���2) F_BLUE(���3) , blood:BLOOD_3 , speed:SPEED_0 , isInvincible:ISINVINCIBLE_3 , showLevel:SHOWLEVEL_2 , missile:MISSILETYPE_1 , life:LIFE_3 , skills:SKILLS_1 , bombs:BOMBS_P , isFrozen:ISFROZEN_0 , mines:MINES_P)
						 //�ͼ�̹��		�ͼ�CAMP_NPC��������(Ĭ��tankType:TANKTYPE_1 , volume:VOLUME_YES , orientation:DOWN , color:F_H_YELLOW , blood:BLOOD_3 , speed:SPEED_0 , isInvincible:ISINVINCIBLE_0 , showLevel:SHOWLEVEL_2 , missile:MISSILETYPE_1 , life:LIFE_1 ,  bombs:BOMBS_N , isFrozen:ISFROZEN_0 , mines:MINES_N)
//#define TANKTYPE_2 0x2	 //�м�̹��		 //̹������,ӳ��̹��ǿ��(����),����С�ڸ�ǿ�ȵ��ӵ��򲻶���̹��(�����,��Ҫ�Ȱѱ���ӹ�����������,�������û��о����Ѻ�,������)
#define TANKTYPE_3 0x2	 //�߼�̹��
#define TANKTYPE_4 0x3	 //�ƶ��Ǳ�
#define TANKTYPE_BOSS 0x4	 //�ƶ��Ǳ�

#define SPEED_0  0x0	//����
#define SPEED_1  0x1	//����

#define LIFE_0   0x0		//ʣ������ֵ	
#define LIFE_1   0x1
#define LIFE_2   0x2
#define LIFE_3   0x3
#define LIFE_4   0x4
#define LIFE_5   0x5
#define LIFE_6   0x6
#define LIFE_7   0x7

#define SKILLS_0  0x0		//ʣ�������
#define SKILLS_1  0x1
#define SKILLS_2  0x2
#define SKILLS_3  0x3

#define BOMBS_P 0xFF		//CAMP_NPC��ʼ��Ϊ255
#define BOMBS_N 0xFF		//CAMP_NPC��ʼ��Ϊ255

#define ISFROZEN_0	0x0		//�Ƿ񱻶�ס ��	(̹�˴����Դ���0�����޵�״̬,ͨ�������Լ����ﵽ����ʱ����)
#define ISFROZEN_1  0x1		//�Ƿ񱻶�ס ��
#define ISFROZEN_3  0x3		//�Ƿ񱻶�ס ��				
#define ISFROZEN_5  0x5		//�Ƿ񱻶�ס ��
#define ISFROZEN_10 0xa		//�Ƿ񱻶�ס ��
#define ISFROZEN_15 0xf		//�Ƿ񱻶�ס ��

#define MINES_0 0X0		//������,û��
#define MINES_1 0X1		
#define MINES_4 0X4		//��ҳ�ʼ��Ϊ4
#define MINES_7 0X7		//CAMP_NPC  ����:1,�м�:4,�߼�:8

#define TANK_BODY	      "��"      //���Ĭ��

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

public://�����������Ͷ���
	
public://�������ݶ���
	int m_tanksStyle[4][3][3];				//̹����ʽ
	//bool m_isOldData;

	//bool readData(char * filePath);			//����
	//bool writeData(char * filepath);		//�浵

};

