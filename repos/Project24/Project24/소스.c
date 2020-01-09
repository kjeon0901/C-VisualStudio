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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	CHOOSECOLOR color;
	static COLORREF clbr, clpen, temp[16]; //���� ���� ǥ���� ����
	HPEN hpen, oldpen;
	HBRUSH hbr, oldbr;
	static HMENU hmenu, hsub; //�޴��� �ڵ鰪 ����
	static BOOL drag = FALSE;
	static int firstX[3][10], firstY[3][10], endX[3][10], endY[3][10], x[3][10], y[3][10], select = -1, copy = 0, draw = 0, paste = 0, count[3] = { 0 }, pick[3] = { -1 };
	int i, k, r1 = 25, len = r1 + 1;

	switch (iMsg) {
	case WM_CREATE:
		hmenu = GetMenu(hwnd); //�츮�� ���� api�� �ڵ鰪�� ���� �޴��� �ڵ鰪�� ���;� ��
		hsub = GetSubMenu(hmenu, 2); //hmenu�� �ڵ鰪�� ���� hsub �ڵ鰪�� ���;� ��		//���� 1�� �޴�(����޴�X)��� �迭���� �ε�����ȣ
		EnableMenuItem(hsub, ID_BRUSH, MF_GRAYED); //MF_GRAYED : ��Ȱ��ȭ, MF_ENABLED : Ȱ��ȭ
		EnableMenuItem(hsub, ID_PEN, MF_GRAYED);
		hsub = GetSubMenu(hmenu, 4);
		EnableMenuItem(hsub, ID_COPY, MF_GRAYED);
		EnableMenuItem(hsub, ID_PASTE, MF_GRAYED);
		for (i = 0; i < 3; i++) {
			for(k=0;k<10;k++)
				firstX[i][k] = endX[i][k] = firstY[i][k] = endY[i][k] = -500;
		}
		break;
	case WM_LBUTTONDOWN:
		if (copy == 0 && select!=-1 && draw == 1) {//��� �׸��� ������ �ڿ� ���� �׸� ���� ����
			firstX[select][count[select]] = LOWORD(lParam);
			firstY[select][count[select]] = HIWORD(lParam);
			for (i = 0; i < count[0]; i++) {
				if(x[select][i]<firstX[select][count[select]]<endX[i] && y[select][i]<firstY[select][count[select]]<endY[i])
					pick[select] = i;
			}
			x[select][count[select]] = LOWORD(lParam);
			y[select][count[select]] = HIWORD(lParam);
			drag = TRUE;
			copy = 1;
			paste = 0;
		}
		 if (copy == 1 && paste==0 && pick[select]!=-1) {//�������μ���
			 paste = 1;
			EnableMenuItem(hsub, ID_COPY, MF_ENABLED);
		}
		 if (paste==1 && pick[select]!=-1) {//�����ܺμ���(�ٿ��ֱ�)
			count[select]++;
			pick[select] = -1;
			copy = 0;
			//pt[0][count[0]].x = mpt.x;
			//pt[0][count[0]].y = mpt.y;

			
			EnableMenuItem(hsub, ID_PASTE, MF_ENABLED);
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		drag = FALSE;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (drag) {//TRUE�� ���� ����
			
			endX[select][count[select]] = LOWORD(lParam);
			endY[select][count[select]] = HIWORD(lParam);
			if (select == 0) {
				Ellipse(hdc, x[select][count[select]], y[select][count[select]], firstX[select][count[select]], firstY[select][count[select]]);
				Ellipse(hdc, x[select][count[select]], y[select][count[select]], endX[select][count[select]], endY[select][count[select]]);
			}
			else if (select == 1) {
				Rectangle(hdc, x[select][count[select]], y[select][count[select]], firstX[select][count[select]], firstY[select][count[select]]);
				Rectangle(hdc, x[select][count[select]], y[select][count[select]], endX[select][count[select]], endY[select][count[select]]);
			}
			else if (select == 2) {
				SetROP2(hdc, R2_XORPEN); //�����Ϳ����� ����� ���̸�, ���� ����� ���� R2_XORPEN�̴�!!
				SelectObject(hdc, GetStockObject(WHITE_PEN));//���� ���� â�� �Ͼ���̴ϱ� �Ͼ�� ���� �������ν� �������� ����.
				MoveToEx(hdc, x[select][count[select]], y[select][count[select]], NULL);
				LineTo(hdc, firstX[select][count[select]], firstY[select][count[select]]); //���� ���� ���� ������ ���� ���� �׷��� �ϴϱ�, ���� ���ο� �Ͼ�� �ٽ� ������ ��������ó�� ���̰�(��+��=��)
				MoveToEx(hdc, x[select][count[select]], y[select][count[select]], NULL);
				LineTo(hdc, endX[select][count[select]], endY[select][count[select]]); //mousemove�� ���� �������� ��ǥ������ ���� �׷���(��+��=��)
			}
			firstX[select][count[select]] = endX[select][count[select]];
			firstY[select][count[select]] = endY[select][count[select]];
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_COMMAND:
		for (i = 0; i < 3; i++) {
			if (ID_ELLIPSE + i == LOWORD(wParam)) {
				clbr = RGB(255, 255, 255); clpen = RGB(0, 0, 0);
				draw = 1;
				pick[i] = 0;
				count[i]++;
				select = i;
			}
		}
		switch (LOWORD(wParam)) {
		
		case ID_COPY:
			select = -1;
			EnableMenuItem(hsub, ID_COPY, MF_GRAYED);
			break;
		case ID_PASTE:
			select = -1;
			EnableMenuItem(hsub, ID_PASTE, MF_GRAYED);
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		if (draw) {
			for (i = 0; i < count[0]; i++) {
				Ellipse(hdc, x[0][count[0]], y[0][count[0]], endX[0][count[0]], endY[0][count[0]]);
				break;
			}
			for (i = 0; i < count[1]; i++){
				Rectangle(hdc, x[1][count[1]], y[1][count[1]], endX[1][count[1]], endY[1][count[1]]);
				break;
			}
			for (i = 0; i < count[2]; i++) {
				MoveToEx(hdc, x[2][count[2]], y[2][count[2]], NULL);
				LineTo(hdc, endX[2][count[2]], endY[2][count[2]]);
				break;
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