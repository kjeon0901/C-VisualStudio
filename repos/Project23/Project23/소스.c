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
//int wormx[1000], wormy[1000];대신 동적할당으로 해보겠음...
int*wormx, *wormy, wsize = 10;
int board[22][22] = { 0 };
int len = 2, ctx, cty;
int level = 1;
int score = 0, food = 0, speed = 100, endgame = 1;
int start = 0, pause = 0;

void make_food() {
	int i, x, y;
	for (i = 0; i < 10; i++) {//스테이지 바뀔 때마다 계속 사용될 거니까 따로 함수로 뺌.
		x = rand() % 20 + 1;
		y = rand() % 20 + 1;
		if (board[y][x] == 0) {
			board[y][x] = 2;
			food++;//먹이가 10개 만들어짐
		}
		else {
			i--;
			continue;
		}
	}
}
void init() {
	int i;
	wormx = (int*)malloc(sizeof(int) * 12);//12개의 공간 할당
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
	wsprintf(str, "점수: %d", score);
	TextOut(hdc, 480, 80, str, strlen(str));
	wsprintf(str, "이동시간: %d / 1000(초)", speed);
	TextOut(hdc, 480, 110, str, strlen(str));
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
		//PostQuitMessage(0);	//창 닫아주는 역할 => 여기다가 두면 변수 endgame 의 의미가 없어짐
		endgame = 0;
	}
	else {
		//  -> 검은색 원을 먹으면
		if (board[wormy[0]][wormx[0]] == 2) {
			len++;
			score += 10;
			food--;
			if (food == 0) {//먹이 다먹은경우
				level++;//레벨 증가
				wormx = (int*)realloc(wormx, sizeof(int) * (wsize*level + 2));
				wormy = (int*)realloc(wormy, sizeof(int) * (wsize*level + 2));
				make_food();//먹이다시만들기

				speed -= 10;
				KillTimer(hwnd, 1);
				SetTimer(hwnd, 1, speed, NULL);
			}
			board[wormy[0]][wormx[0]] = 0;
		}
		else
			board[wormy[len - 1]][wormx[len - 1]] = 0;
		// -> 이동 하면서 꼬리도 같이 따라가게
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
		init();//안없애도 되나?
		break;
	case WM_KEYDOWN:
		if (endgame && start && !pause) {//endgame이 0이 되면 아예 재시작 못하도록	//&& 쓰는 게 맞나?
				SetTimer(hwnd, 1, speed, NULL);
				ctrl(wParam);
		}
		break;
	case WM_TIMER:
		move(hwnd);
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		for (i = 0; i < 4; i++) {
			if (ID_SPEED100 + i == LOWORD(wParam)) {
				speed = 100-(10*i); break;
			}
		}
		for (i = 0; i < 6; i++) {
			if (ID_LV1 + i == LOWORD(wParam)) {
				level = i + 1; 
				if (speed != 105 - (5 * level)) {//속도설정안했으면
					speed = 105-(5*level);
				}
				break;
			}
		}

		switch (LOWORD(wParam)) {
		case ID_START:
			if(start)
				KillTimer(hwnd, 1);
			wsize = 10, len = 2, level = 1, score = 0, food = 0, speed = 100, endgame = 1;
			start = 1;
			for (i = 0; i < 22; i++) {
				for (j = 0; j < 22; j++) {
					board[j][i] = 0;
				}
			}
			init();
			break;
		case ID_PAUSE:
			KillTimer(hwnd, 1);
			pause = 1;
			break;
		case ID_RESTART:
			if (pause == 1) {
				pause = 0;
				SetTimer(hwnd, 1, speed, NULL);
			}
			break;
		case ID_CLOSE:
			KillTimer(hwnd, 1);
			MessageBox(hwnd, "종료합니다", "GAME CLOSE", NULL);
			PostQuitMessage(0);
			break;
		}
		
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		if (start) {
			hdc = BeginPaint(hwnd, &ps);
			draw(hdc);
			EndPaint(hwnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}