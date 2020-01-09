#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <CommCtrl.h>//칼럼 구조체
#include "resource.h"
/*
a || A => 콤보박스컨트롤, 리스트박스컨트롤
b || B => 모덜리스 대화상자
c || C => 리스트 컨트롤, 칼럼
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
	HWND hdlg = NULL;//모덜리스는 이렇게 쓰는게 형식//다이얼로그에 만들어져 있는 핸들값 받아올 핸들
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
	static TCHAR *col_name[4] = { "이름", "전화번호", "성별", "출생연도" };
	LVCOLUMN lvcol = { 0 };//칼럼 구조체
	LVITEM item;
	static HWND hls, hb1;//다이얼로그에 만들어져 있는 핸들값 받아올 핸들
	LPNMHDR hdr;//lp가 붙어있으면 포인터. 
	LPNMLISTVIEW lv;
	TCHAR sex[2][5] = { { "남성" },{ "여성" } };
	int wid[4] = {80, 150, 60, 100};
	WCHAR tmp1[12], tmp2[10], tmp3[5];//전화번호(출력), 이름, 연도(출력)
	WCHAR *str = NULL;
	static int cnt = 0, select = 1;
	int i, phone[12], birth[5], sel;//전화번호(입력), 연도(출력);
	switch (iMsg) {
	case WM_INITDIALOG:
		hls = GetDlgItem(hdlg, IDC_LIST1);
		hb1 = GetDlgItem(hdlg, IDC_JOIN);
		lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//어떤 값이 들어있는지(LVCF_FMT:정렬방식 LVCF_WIDTH:폭 LVCF_TEXT:컬럼명 LVCF_SUBITEM:SUBITEM필드
		lvcol.fmt = LVCFMT_LEFT;
		for (i = 0; i < 4; i++) {
			lvcol.cx = wid[i];
			lvcol.pszText = col_name[i];
			lvcol.iSubItem = i;
			SendMessage(hls, LVM_INSERTCOLUMN, (WPARAM)i, (LPARAM)&lvcol);
		}
		EnableWindow(hb1, FALSE);
		break;
		
	case WM_NOTIFY://리스트컨트롤에 어떤 변화된 동작이 생기면 핸들값이 (command가 아니라) 여기로 들어옴
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
			item.iItem = cnt;//몇번째 아이템이냐
			item.iSubItem = 0;//몇번째 칼럼부터 넣어줄거냐
			item.pszText = "";//번호
			wsprintf(tmp1, "%d\n", phone);
			wsprintf(tmp3, "%d\n", birth);
			ListView_InsertItem(hls, &item);//삽입
			ListView_SetItemText(hls, cnt, 0, tmp2);//이름
			ListView_SetItemText(hls, cnt, 1, tmp1);//전화번호
			ListView_SetItemText(hls, cnt, 2, sex[select]);//성별
			ListView_SetItemText(hls, cnt, 3, tmp3);//연도
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