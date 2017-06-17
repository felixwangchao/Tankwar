#pragma once
#include "Data.h"

//�������йصĽ���
class CDraw :virtual public CData
{
public:
	CDraw();
	~CDraw();

	//���ô������,��С
	bool setCmdWindowsInfo(wchar_t* pszWindowTitle, int width, int high);

	//ָ��λ�û��ַ���
	void writeChar(int row, int col, char* pszChar, WORD wArr);
	
	//��Ϣѭ��
	void messageLoop();

	//�����Ļ
	void clsConsole();
private:
	//����������
	void outputPos(int row, int col);

	//�����¼�������
	bool keyEventProc(KEY_EVENT_RECORD ker);

	//����¼�������
	bool mouseEventProc(MOUSE_EVENT_RECORD mer);

private:
	HANDLE m_hStdIn;
	HANDLE m_hStdOut;
	int m_WallType;

};

