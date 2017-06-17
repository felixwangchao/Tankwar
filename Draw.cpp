#include <iostream>
#include<windows.h>
#include "Draw.h"


CDraw::CDraw()
{
	m_hStdIn  = GetStdHandle(STD_INPUT_HANDLE);
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}



CDraw::~CDraw()
{
}

//设置窗体标题,大小
bool CDraw::setCmdWindowsInfo(wchar_t* pszWindowTitle, int width, int high)
{
	//1.设置命令行标题
	SetConsoleTitle(L"TankWar");

	//2.获取最大命令行窗口大小
	COORD pos = GetLargestConsoleWindowSize(m_hStdOut);	//能设置的窗口大小要比这个最大值小1
	COORD bufferSize = { pos.X, pos.Y };				//缓存区的大小可以随意设置，为了避免设置窗口失败，先把缓冲器设置为最大
	//3.设置命令行缓冲区大小
	if (!SetConsoleScreenBufferSize(m_hStdOut, bufferSize)){
		//失败
		printf("设置命令行缓冲区大小 失败（errID：%d）", GetLastError());
		return false;
	}
	//4.设置命令行大小
	SMALL_RECT srctMaxWindow = { 0, 0, pos.X - 1, pos.Y - 1 };
	SMALL_RECT srctUserWindow = { 0, 0, (short)width, (short)high };
	if (!SetConsoleWindowInfo(m_hStdOut, true, &srctUserWindow)){
		//失败
		printf("设置命令行窗口大小 失败（errID：%d）", GetLastError());
		//失败则设置为最大窗口
		SetConsoleWindowInfo(m_hStdOut, true, &srctMaxWindow);
		return false;
	}
	else{
		//成功,则把缓冲区缩小，以隐藏滑块
		bufferSize.X = srctUserWindow.Right + 1;
		bufferSize.Y = srctUserWindow.Bottom + 1;
		SetConsoleScreenBufferSize(m_hStdOut, bufferSize);
	}
	return true;
}

// 行数，列数，要输出的字符串，颜色
void CDraw::writeChar(int row, int col, char* pszChar, WORD wArr){
	// 设置光标属性
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;	// 是否显示光标
      	SetConsoleCursorInfo(m_hStdOut, &cci);
	// 设置坐标
	COORD loc;
	loc.X = row * 2; // x的值是Wide的2倍
	loc.Y = col;
	SetConsoleCursorPosition(m_hStdOut, loc);
	// 设置文本属性
	SetConsoleTextAttribute(m_hStdOut, wArr);
	printf(pszChar); //打印时需要注意有些特殊字符是占两个字节
}


//打印鼠标位置
void CDraw::outputPos(int row, int col){
	char szBuf[100] = { 0 };
	sprintf_s(szBuf, sizeof(szBuf), "x=%2d,y=%2d ", col / 2, row);
	SetConsoleTitleA(szBuf);
}


//键盘事件处理函数
bool CDraw::keyEventProc(KEY_EVENT_RECORD ker){
	if (ker.bKeyDown){
		writeChar(0, 0, "键盘按下", 0x50);	
	}
	else{
		writeChar(0, 0, "键盘弹起", 0x50);
	}

	//ker.wVirtualKeyCode
	//根据不同的虚拟键码，做不同的操作。
	//返回值确定是否退出继续监听事件
	return false;
}

//鼠标事件处理函数
bool CDraw::mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch (mer.dwEventFlags){
	case 0:
		
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){	
			writeChar(0, 0, "左键单击", 0x50);
			m_WallType = WALL_A1;
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED){
			writeChar(0, 0, "右键单击", 0x50);
	
		}
		break;
	case DOUBLE_CLICK:
		writeChar(0, 0, "双击", 0x50);
		break;
	case MOUSE_MOVED:
		outputPos(mer.dwMousePosition.X, mer.dwMousePosition.Y);
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
			writeChar(0, 0, "左键按下拖动", 0x50);

		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED){
			writeChar(0, 0, "右键按下拖动", 0x50);
		}
		break;
	default:
		
		break;
	}

	
	return false;
}

//消息循环
void CDraw::messageLoop(){
	INPUT_RECORD stdRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(m_hStdIn, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	bool isExit = false; //是否退出
	while (1){
		//等待事件
		ReadConsoleInput(m_hStdIn, &stdRecord, 1, &dwRead);
		//处理事件
		if (stdRecord.EventType == KEY_EVENT){
			isExit = keyEventProc(stdRecord.Event.KeyEvent);
		}
		else if (stdRecord.EventType == MOUSE_EVENT){
			isExit = mouseEventProc(stdRecord.Event.MouseEvent);
		}
		if (isExit){
			break;
		}
	}

}

//清除屏幕
void CDraw::clsConsole()
{
	system("color 0A");
	system("cls");
	DWORD    dummy;
	COORD    Home = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(m_hStdOut, &csbiInfo);
	FillConsoleOutputCharacter(m_hStdOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);

	SetConsoleCursorPosition(m_hStdOut, Home);
}


