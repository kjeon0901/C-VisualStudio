#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
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
	HBRUSH hbr, old;
	static POINT cat, step;
	static int mx, my, select = 0, cnt = 0;
	float len;
	switch (iMsg)
	{
	case WM_CREATE:
		cat.x = 100;
		cat.y = 100;
		break;
	case WM_TIMER:
		cnt++;
		cat.x += step.x;
		cat.y += step.y;

		if (cnt == 10) {
			step.x = 0;
			step.y = 0;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		my = HIWORD(lParam);
		mx = LOWORD(lParam);
		select = 1;
		cnt = 0;
		SetTimer(hwnd, 1, 100, NULL);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		select = 0;
		KillTimer(hwnd, 1);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		my = HIWORD(lParam);
		mx = LOWORD(lParam);
		step.x = (mx - cat.x) / 10;
		step.y = (my - cat.y) / 10;
		cnt = 0;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, cat.x, cat.y, "∞ÌæÁ¿Ã", 6);
		if (select)
			TextOut(hdc, mx, my, "¡„", 2);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}