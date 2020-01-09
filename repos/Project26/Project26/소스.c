#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define r 10
#define wh 20
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
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
POINT box[10], circle[10];
int sel = -1, num[10];
void check(HWND hwnd, int x, int y);
void move(HWND hwnd, WPARAM wParam, RECT rect);
void check(HWND hwnd, int x, int y) {
	int i, k, j;
	float len[10];
	for (i = 0; i < 10; i++) {
		if (box[i].x - wh <= x && x <= box[i].x + wh && box[i].y - wh <= y && y <= box[i].y + wh) {
			sel = i;
			for (k = 0; k < 10; k++) {
				len[k] = sqrt((x - circle[k].x)*(x - circle[k].x) + (y - circle[k].y)*(y - circle[k].y));
				for (j = 0; j < k; j++) {
					if (len[k] < len[j]) num[i] = j;
				}
			}
			SetTimer(hwnd, sel, 40, NULL);
			break;
		}
	}
}
void move(HWND hwnd, WPARAM wParam, RECT rect) {
	int i, k, j, chk = 0, cnt[10] = { 0 }, right[10] = { 0 };
		if (box[sel].x - wh <= circle[num[sel]].x - r && circle[num[sel]].x + r <= box[sel].x + wh && box[sel].y - wh <= circle[num[sel]].y - r && circle[num[sel]].y + r <= box[sel].y + wh) {
			cnt[sel] = 1;
			if (cnt[0]==cnt[1]==cnt[2]==cnt[3]==cnt[4]==cnt[5]==cnt[6]==cnt[7]==cnt[8]==cnt[9]==1) {
				MessageBox(hwnd, "¼º°ø!", "Game Clear", NULL);
				PostQuitMessage(0);
			}
		}
		if (wParam == sel){
			if (!right[sel]) {
				if (box[sel].x < circle[num[sel]].x)  box[sel].x += 10;
				else if (box[sel].x > circle[num[sel]].x) box[sel].x -= 10;
				if (box[sel].x - wh <= circle[num[sel]].x - r && circle[num[sel]].x + r <= box[sel].x + wh)right[sel] = 1;
			}
			else if(right[sel]){
				if (box[sel].y < circle[num[sel]].y)  box[sel].y += 10;
				else if (box[sel].y > circle[num[sel]].y) box[sel].y -= 10;
				if (box[sel].y - wh <= circle[num[sel]].y - r && circle[num[sel]].y + r <= box[sel].y + wh)right[sel] = 1;
			}
		}
	}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hbr, oldbr;
	static RECT rect;
	int x, y, i, k;
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		for (i = 0; i < 10; i++) {
			box[i].x = rand() % rect.right;
			box[i].y = rand() % rect.bottom;
			circle[i].x = rand() % rect.right;
			circle[i].y = rand() % rect.bottom;
			if (box[i].x == circle[i].x && box[i].y == circle[i].y) {
				i--;
			}
			for (k = 0; k < i; k++) {
				if ((box[i].x == box[k].x && box[i].y == box[k].y) || (circle[i].x == circle[k].x && circle[i].y == circle[k].y)) {
					i--;
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		check(hwnd, x, y);
		break;
	case WM_TIMER:
		move(hwnd, wParam, rect);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hbr = CreateSolidBrush(RGB(0, 0, 255));
		oldbr = (HBRUSH)SelectObject(hdc, hbr);
		for (i = 0; i < 10; i++)
			Ellipse(hdc, circle[i].x - r, circle[i].y - r, circle[i].x + r, circle[i].y + r);

		hbr = CreateSolidBrush(RGB(255, 0, 0));
		oldbr = (HBRUSH)SelectObject(hdc, hbr);
		for (i = 0; i < 10; i++)
			Rectangle(hdc, box[i].x - wh, box[i].y - wh, box[i].x + wh, box[i].y + wh);

		SelectObject(hdc, oldbr);
		DeleteObject(hbr);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}