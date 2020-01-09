#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <CommCtrl.h>//Į�� ����ü
#include "resource.h"
/*
a || A => �޺��ڽ���Ʈ��, ����Ʈ�ڽ���Ʈ��
b || B => ������� ��ȭ����
c || C => ����Ʈ ��Ʈ��, Į��
*/

typedef struct gu {
	int num;
	char name[15];
}gu;

HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProc4(HWND hdlg, UINT iMsg,
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
	HWND hdlg = NULL;//��������� �̷��� ���°� ����//���̾�α׿� ������� �ִ� �ڵ鰪 �޾ƿ� �ڵ�
	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_CHAR:
		if (wParam == 'a' || wParam == 'A')
			DialogBox(hinst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc4);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK DlgProc4(HWND hdlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam) {
	static TCHAR *col_name[4] = { "�̸�", "��ȭ��ȣ", "����", "�������" };
	LVCOLUMN lvcol = { 0 };//Į�� ����ü
	LVITEM item;
	static HWND hls, hb1;//���̾�α׿� ������� �ִ� �ڵ鰪 �޾ƿ� �ڵ�
	LPNMHDR hdr;//lp�� �پ������� ������. 
	LPNMLISTVIEW lv;
	TCHAR sex[2][5] = { { "����" },{ "����" } };
	int wid[4] = {80, 150, 60, 100};
	WCHAR tmp1[12], tmp2[10], tmp3[5];//��ȭ��ȣ(���), �̸�, ����(���)
	WCHAR *str = NULL;
	static int cnt = 0, select = 1;
	int i, phone[12], birth[5], sel;//��ȭ��ȣ(�Է�), ����(���);
	switch (iMsg) {
	case WM_INITDIALOG:
		hls = GetDlgItem(hdlg, IDC_LIST1);
		hb1 = GetDlgItem(hdlg, IDC_JOIN);
		lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//� ���� ����ִ���(LVCF_FMT:���Ĺ�� LVCF_WIDTH:�� LVCF_TEXT:�÷��� LVCF_SUBITEM:SUBITEM�ʵ�
		lvcol.fmt = LVCFMT_LEFT;
		for (i = 0; i < 4; i++) {
			lvcol.cx = wid[i];
			lvcol.pszText = col_name[i];
			lvcol.iSubItem = i;
			SendMessage(hls, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvcol);
		}
		EnableWindow(hb1, FALSE);
		break;
		
	case WM_NOTIFY://����Ʈ��Ʈ�ѿ� � ��ȭ�� ������ ����� �ڵ鰪�� (command�� �ƴ϶�) ����� ����
		hdr = (LPNMHDR)lParam;
		lv = (LPNMLISTVIEW)lParam;
		if (hdr->hwndFrom == hls && hdr->code == LVN_ITEMCHANGING) {//?
			SetDlgItemText(hdlg, IDC_NAME, tmp2);
			SetDlgItemText(hdlg, IDC_PHONE, tmp1);
			SetDlgItemText(hdlg, IDC_BIRTH, tmp3);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_NEW:
			EnableWindow(hb1, TRUE);
			break;
		case IDC_WOMAN:
			select = 1;
			break;
		case IDC_MAN:
			select = 0;
			break;
		case IDC_JOIN:
			GetDlgItemText(hdlg, IDC_EDITPHONE, phone, 12);
			GetDlgItemText(hdlg, IDC_EDITNAME, tmp2, 10);
			GetDlgItemText(hdlg, IDC_EDITBIRTH, birth, 5);
			item.mask = LVIF_TEXT;
			cnt = ListView_GetItemCount(hls);
			item.iItem = cnt;//���° �������̳�
			item.iSubItem = 0;//���° Į������ �־��ٰų�
			item.pszText = "";//��ȣ
			wsprintf(tmp1, "%d\n", phone);
			wsprintf(tmp3, "%d\n", birth);
			ListView_InsertItem(hls, &item);//����
			ListView_SetItemText(hls, cnt, 0, tmp2);//�̸�
			ListView_SetItemText(hls, cnt, 1, tmp1);//��ȭ��ȣ
			ListView_SetItemText(hls, cnt, 2, sex[select]);//����
			ListView_SetItemText(hls, cnt, 3, tmp3);//����
			EnableWindow(hb1, FALSE);
			break;
		case IDC_OUT:
			sel = ListView_GetNextItem(hls, -1, LVNI_ALL | LVNI_SELECTED);
			if (sel != -1)
				ListView_DeleteItem(hls, sel);
			break;
		case IDC_EXIT:
			EndDialog(hdlg, 0);
			break;
		case IDOK:
			EndDialog(hdlg, 0);
			break;
		case IDCANCEL:
			EndDialog(hdlg, 0);
			break;
		}
		break;
	}
	return 0;
}