#pragma once
#include "Data.h"

//跟界面有关的交互
class CDraw :virtual public CData
{
public:
	CDraw();
	~CDraw();

	//设置窗体标题,大小
	bool setCmdWindowsInfo(wchar_t* pszWindowTitle, int width, int high);

	//指定位置画字符串
	void writeChar(int row, int col, char* pszChar, WORD wArr);
	
	//消息循环
	void messageLoop();

	//清除屏幕
	void clsConsole();
private:
	//输出鼠标坐标
	void outputPos(int row, int col);

	//键盘事件处理函数
	bool keyEventProc(KEY_EVENT_RECORD ker);

	//鼠标事件处理函数
	bool mouseEventProc(MOUSE_EVENT_RECORD mer);

private:
	HANDLE m_hStdIn;
	HANDLE m_hStdOut;
	int m_WallType;

};

