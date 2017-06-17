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

//���ô������,��С
bool CDraw::setCmdWindowsInfo(wchar_t* pszWindowTitle, int width, int high)
{
	//1.���������б���
	SetConsoleTitle(L"TankWar");

	//2.��ȡ��������д��ڴ�С
	COORD pos = GetLargestConsoleWindowSize(m_hStdOut);	//�����õĴ��ڴ�СҪ��������ֵС1
	COORD bufferSize = { pos.X, pos.Y };				//�������Ĵ�С�����������ã�Ϊ�˱������ô���ʧ�ܣ��Ȱѻ���������Ϊ���
	//3.���������л�������С
	if (!SetConsoleScreenBufferSize(m_hStdOut, bufferSize)){
		//ʧ��
		printf("���������л�������С ʧ�ܣ�errID��%d��", GetLastError());
		return false;
	}
	//4.���������д�С
	SMALL_RECT srctMaxWindow = { 0, 0, pos.X - 1, pos.Y - 1 };
	SMALL_RECT srctUserWindow = { 0, 0, (short)width, (short)high };
	if (!SetConsoleWindowInfo(m_hStdOut, true, &srctUserWindow)){
		//ʧ��
		printf("���������д��ڴ�С ʧ�ܣ�errID��%d��", GetLastError());
		//ʧ��������Ϊ��󴰿�
		SetConsoleWindowInfo(m_hStdOut, true, &srctMaxWindow);
		return false;
	}
	else{
		//�ɹ�,��ѻ�������С�������ػ���
		bufferSize.X = srctUserWindow.Right + 1;
		bufferSize.Y = srctUserWindow.Bottom + 1;
		SetConsoleScreenBufferSize(m_hStdOut, bufferSize);
	}
	return true;
}

// ������������Ҫ������ַ�������ɫ
void CDraw::writeChar(int row, int col, char* pszChar, WORD wArr){
	// ���ù������
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;	// �Ƿ���ʾ���
      	SetConsoleCursorInfo(m_hStdOut, &cci);
	// ��������
	COORD loc;
	loc.X = row * 2; // x��ֵ��Wide��2��
	loc.Y = col;
	SetConsoleCursorPosition(m_hStdOut, loc);
	// �����ı�����
	SetConsoleTextAttribute(m_hStdOut, wArr);
	printf(pszChar); //��ӡʱ��Ҫע����Щ�����ַ���ռ�����ֽ�
}


//��ӡ���λ��
void CDraw::outputPos(int row, int col){
	char szBuf[100] = { 0 };
	sprintf_s(szBuf, sizeof(szBuf), "x=%2d,y=%2d ", col / 2, row);
	SetConsoleTitleA(szBuf);
}


//�����¼�������
bool CDraw::keyEventProc(KEY_EVENT_RECORD ker){
	if (ker.bKeyDown){
		writeChar(0, 0, "���̰���", 0x50);	
	}
	else{
		writeChar(0, 0, "���̵���", 0x50);
	}

	//ker.wVirtualKeyCode
	//���ݲ�ͬ��������룬����ͬ�Ĳ�����
	//����ֵȷ���Ƿ��˳����������¼�
	return false;
}

//����¼�������
bool CDraw::mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch (mer.dwEventFlags){
	case 0:
		
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){	
			writeChar(0, 0, "�������", 0x50);
			m_WallType = WALL_A1;
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED){
			writeChar(0, 0, "�Ҽ�����", 0x50);
	
		}
		break;
	case DOUBLE_CLICK:
		writeChar(0, 0, "˫��", 0x50);
		break;
	case MOUSE_MOVED:
		outputPos(mer.dwMousePosition.X, mer.dwMousePosition.Y);
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
			writeChar(0, 0, "��������϶�", 0x50);

		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED){
			writeChar(0, 0, "�Ҽ������϶�", 0x50);
		}
		break;
	default:
		
		break;
	}

	
	return false;
}

//��Ϣѭ��
void CDraw::messageLoop(){
	INPUT_RECORD stdRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(m_hStdIn, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	bool isExit = false; //�Ƿ��˳�
	while (1){
		//�ȴ��¼�
		ReadConsoleInput(m_hStdIn, &stdRecord, 1, &dwRead);
		//�����¼�
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

//�����Ļ
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


