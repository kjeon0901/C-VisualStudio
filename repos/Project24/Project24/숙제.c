#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <math.h>
#include "resource.h"
#include <stdio.h>
#define R 20
#define size 100
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
double selec(int x, int y, int x1, int y1);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG	 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	static HMENU hmenu, hsub;
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT pt[3][size];
	static int count[3] = { 1 }, click = 1, mx, my;
	int i;
	switch (iMsg)
	{
	case WM_CREATE:
		memset(pt[0], 0, size * sizeof(POINT));
		pt[0][0].x = pt[0][0].y = 50;
		hmenu = GetMenu(hwnd);
		hsub = GetSubMenu(hmenu, 4);
		EnableMenuItem(hsub, ID_COPY, MF_GRAYED);
		EnableMenuItem(hsub, ID_PASTE, MF_GRAYED);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (click) {
			for (i = 0; i < count[0]; i++) {
				if (selec(pt[0][i].x, pt[0][i].y, mx, my) < R) {
					click = 1 - click;
					EnableMenuItem(hsub, ID_COPY, MF_ENABLED);
					break;
				}
			}
		}
		else {
			EnableMenuItem(hsub, ID_PASTE, MF_ENABLED);
			click = 1 - click;
		}

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COPY:

			break;
		case ID_PASTE:
			pt[0][count[0]].x = mx;
			pt[0][count[0]].y = my;
			count[0]++;
			InvalidateRgn(hwnd, NULL, TRUE);
			EnableMenuItem(hsub, ID_COPY, MF_GRAYED);
			EnableMenuItem(hsub, ID_PASTE, MF_GRAYED);
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < count[0]; i++) {
			Ellipse(hdc, pt[0][i].x - R, pt[0][i].y - R, pt[0][i].x + R, pt[0][i].y + R);

		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

double selec(int x, int y, int x1, int y1) {
	return(sqrt((float)((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y))));
}