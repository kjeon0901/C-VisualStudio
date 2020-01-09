#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"
HINSTANCE hinst;
void calc();
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
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
	static HDC hdc, memdc1, memdc2;
	PAINTSTRUCT ps;
	static HBITMAP hbit, old;
	static RECT rect, image[25];
	static int x, select;
	int i, k, w, h, num[25];
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		hbit = (HBITMAP)LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	case WM_COMMAND:
		for (i = 0; i < 3; i++) {
			if (LOWORD(wParam) == ID_3X3 + i) {
				select = 3 + i;
			}
		}
		if (LOWORD(wParam) == ID_SHOW) {
			hdc = GetDC(hwnd);//paint�޼��� ���� getdc�� �ѹ� �� ���� => ������ �ٽ� paint�޼��� ���༭ �ܻ� ����
			memdc1 = CreateCompatibleDC(hdc);
			old = (HBITMAP)SelectObject(memdc1, hbit);
			StretchBlt(hdc, 0, 0, rect.right, rect.bottom, memdc1, 0, 0, 240, 224, SRCCOPY);
			SelectObject(memdc2, old);
			DeleteDC(memdc1);
			ReleaseDC(hwnd, hdc);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		w = rect.right / select, h = rect.bottom / select;
		//�̹��� ���� ��ǥ�� image[]�� ������� ����ֱ�
		for (i = 0; i < select; i++) {
			for (k = 0; k < select; k++) {
				image[select * i + k].left = k * w;
				image[select * i + k].top = i * h;
				image[select * i + k].right = (k + 1)*w;
				image[select * i + k].bottom = (i + 1)*h;
			}
		}
		//�������� ���� ��� num[]�� ����ֱ�
		for (i = 0; i < select*select; i++) {
			num[i] = rand() % (select*select);
			for (k = 0; k < i; k++) {
				if (num[i] == num[k]) {
					num[i] = rand() % (select*select);
					k--;
				}
			}
		}
		//num �� ����ִ� ���ڿ� image �� �ε��� ��ȣ�� ���� �� image �����ֱ�
		for (i = 0; i < select; i++) {
			for (k = 0; k < select; k++) {
				StretchBlt(hdc, image[num[select*i + k]].left, image[num[select*i + k]].top, w, h, memdc1, image[num[select*i + k]].left, image[num[select*i + k]].top, 240, 224, SRCCOPY);//�������
				//StretchBlt(hdc, , w, h, memdc1, image[num[select*i + k]].left, image[num[select*i + k]].top, 240, 224, SRCCOPY)//�������

			}
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}