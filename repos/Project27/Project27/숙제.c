#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProc1(HWND hdlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG	 msg;
	WNDCLASS WndClass;
	hinst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "Window Class Name";
	RegisterClass(&WndClass);
	hwnd = CreateWindow("Window Class Name",
		"Window Title Name",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_LBUTTONDOWN:
		DialogBox(hinst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc1);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK DlgProc1(HWND hdlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam) {
	static char metro[7][11] = { 
		"����Ư����", "�λ걤����", "�뱸������", "��õ������", "����������", "���ֱ�����", "��걤����"}, 
		d1[3][7] = {"������", "���α�", "������"}, d2[3][7] = {"����", "����", "�ϱ�"}, d3[3][7]={"�޼���", "�߱�", "����"}, d4[3][7]={"����", "����", "����"}, d5[3][7]={"�߱�", "����", "����"}, d6[3][7]={"����", "����", "�ϱ�"}, d7[3][7]={"����", "�ϱ�", "����"};
	static char *temp[7] = {&d6, &d3, &d5, &d2, &d1, &d7, &d4};
	static HWND list, list2;
	static int select;
	int i;
	//temp[0] = d1, temp[1] = d2, temp[2] = d3, temp[3] = d4, temp[4] = d5, temp[5] = d6, temp[6] = d7;
	switch (iMsg) {
	case WM_INITDIALOG:
		list = GetDlgItem(hdlg, IDC_LIST1);
		list2 = GetDlgItem(hdlg, IDC_LIST2);
		for (i = 0; i < 7; i++) {
			SendMessage(list, LB_ADDSTRING, 0, (LPARAM)metro[i]);
		}
		//SetDlgItemText(list, IDC_LIST2, temp);	//?
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {		
		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE) {//����Ʈ�ڽ����� �� ������
				for(i=0;i<3;i++)
					SendMessage(list2, LB_DELETESTRING, i, 0);
				select = SendMessage(list, LB_GETCURSEL, 0, 0);//�ε�����ȣ�� SELECT�� ��
				for (i = 0; i < 3; i++) {
					MessageBox(hdlg, "aa", NULL, NULL);
					SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)(temp[select]+i));//���Ⱑ�̻�..?
				}
				//SendMessage(list , LB_GETTEXT, select, metro);//?
				SetDlgItemText(list, IDC_LIST1, temp[select]+i);
			}
			break;
		case IDCLOSE:
			EndDialog(hdlg, 0);
			break;
		}
		break;
	}
	return 0;
}