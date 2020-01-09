#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"

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
#define size 20
//int wormx[1000], wormy[1000];��� �����Ҵ����� �غ�����...
int*wormx, *wormy, wsize = 10;
int board[22][22] = { 0 };
int len = 2, ctx, cty;
int level = 1;
int score = 0, food = 0, speed = 100, endgame = 1;

void make_food() {
	int i, x, y;
	for (i = 0; i < 10; i++) {//�������� �ٲ� ������ ��� ���� �Ŵϱ� ���� �Լ��� ��.
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		if (board[y][x] == 0) {
			board[y][x] = 2;
			food++;//���̰� 10�� �������
		}
		else {
			i--;
			continue;
		}
	}
}
void init() {
	int i;
	wormx = (int*)malloc(sizeof(int) * 12);//12���� ���� �Ҵ�
	wormy = (int*)malloc(sizeof(int) * 12);
	for (i = 0; i < 22; i++) {
		board[i][0] = -1;
		board[i][21] = -1;
		board[0][i] = -1;
		board[21][i] = -1;
	}
	wormx[0] = 2; wormy[0] = 1;
	wormx[1] = 1; wormy[1] = 1;
	board[wormy[0]][wormx[0]] = 3;
	board[wormy[1]][wormx[1]] = 3;
	make_food();
}
void draw(HDC hdc) {
	int i, j;
	char str[100];
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 22; j++) {
			if (board[j][i] == -1)
				Rectangle(hdc, i*size, j*size, (i + 1)*size, (j + 1)*size);
			if (board[j][i] == 2) {
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				Ellipse(hdc, i*size, j*size, (i + 1)*size, (j + 1)*size);
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			}
		}
	}
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
	Ellipse(hdc, wormx[0] * size, wormy[0] * size, (wormx[0] + 1)*size, (wormy[0] + 1) * size);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 255)));
	for (i = 1; i < len; i++)
		Ellipse(hdc, wormx[i] * size, wormy[i] * size, (wormx[i] + 1)*size, (wormy[i] + 1) * size);
	wsprintf(str, "Stage %d", level);
	TextOut(hdc, 480, 50, str, strlen(str));
	wsprintf(str, "����: %d", score);
	TextOut(hdc, 480, 80, str, strlen(str));
}
void ctrl(WPARAM wParam) {
	switch (wParam) {
	case VK_LEFT:
		if (ctx == 1)break;
		ctx = -1;
		cty = 0;
		break;
	case VK_RIGHT:
		if (ctx == -1)break;
		ctx = 1;
		cty = 0;
		break;
	case VK_UP:
		if (cty == 1)break;
		ctx = 0;
		cty = -1;
		break;
	case VK_DOWN:
		if (cty == -1)break;
		ctx = 0;
		cty = 1;
		break;
	}
}
void move(HWND hwnd) {
	int tempx, tempy, i;
	tempx = wormx[0];
	tempy = wormy[0];

	wormx[0] += ctx;
	wormy[0] += cty;
	if (board[wormy[0]][wormx[0]] == -1 || board[wormy[0]][wormx[0]] == 3) {
		wormx[0] = tempx;
		wormy[0] = tempy;
		KillTimer(hwnd, 1);
		MessageBox(hwnd, "GAME OVER", NULL, NULL);
		PostQuitMessage(0);//â �ݾ��ִ� ���� => ����ٰ� �θ� ���� endgame �� �ǹ̰� ������
		endgame = 0;
	}
	else {
		//  -> ������ ���� ������
		if (board[wormy[0]][wormx[0]] == 2) {
			len++;
			score += 10;
			food--;
			if (food == 0) {//���� �ٸ������
				level++;//���� ����
				wormx = (int*)realloc(wormx, sizeof(int) * (wsize*level + 2));
				wormy = (int*)realloc(wormy, sizeof(int) * (wsize*level + 2));
				make_food();//���̴ٽø����

				speed -= 10;
				KillTimer(hwnd, 1);
				SetTimer(hwnd, 1, speed, NULL);
			}
			board[wormy[0]][wormx[0]] = 0;
		}
		else
			board[wormy[len - 1]][wormx[len - 1]] = 0;
		// -> �̵� �ϸ鼭 ������ ���� ���󰡰�
		for (i = len - 1; i > 1; i--) {
			wormx[i] = wormx[i - 1];
			wormy[i] = wormy[i - 1];
		}
		wormx[1] = tempx;
		wormy[1] = tempy;
		board[wormy[0]][wormx[0]] = 3;
	}




}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i, j;
	srand((int)time(NULL));
	switch (iMsg)
	{
	case WM_CREATE:
		init();
		break;
	case WM_COMMAND:

		break;
	case WM_KEYDOWN:
		if (endgame) {//endgame�� 0�� �Ǹ� �ƿ� ����� ���ϵ���
			SetTimer(hwnd, 1, speed, NULL);
			ctrl(wParam);
		}
		break;
	case WM_TIMER:
		move(hwnd);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		draw(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}