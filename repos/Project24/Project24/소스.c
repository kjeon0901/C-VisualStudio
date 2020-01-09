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
	static COLORREF clbr, clpen, temp[16]; //글자 색깔 표현할 변수
	HPEN hpen, oldpen;
	HBRUSH hbr, oldbr;
	static HMENU hmenu, hsub; //메뉴의 핸들값 가짐
	static BOOL drag = FALSE;
	static int firstX[3][10], firstY[3][10], endX[3][10], endY[3][10], x[3][10], y[3][10], select = -1, copy = 0, draw = 0, paste = 0, count[3] = { 0 }, pick[3] = { -1 };
	int i, k, r1 = 25, len = r1 + 1;

	switch (iMsg) {
	case WM_CREATE:
		hmenu = GetMenu(hwnd); //우리가 만든 api의 핸들값을 통해 메뉴의 핸들값을 얻어와야 함
		hsub = GetSubMenu(hmenu, 2); //hmenu의 핸들값을 통해 hsub 핸들값을 얻어와야 함		//숫자 1은 메뉴(서브메뉴X)라는 배열에서 인덱스번호
		EnableMenuItem(hsub, ID_BRUSH, MF_GRAYED); //MF_GRAYED : 비활성화, MF_ENABLED : 활성화
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
		if (copy == 0 && select!=-1 && draw == 1) {//어떤거 그릴지 선택한 뒤에 도형 그릴 공간 선택
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
		 if (copy == 1 && paste==0 && pick[select]!=-1) {//도형내부선택
			 paste = 1;
			EnableMenuItem(hsub, ID_COPY, MF_ENABLED);
		}
		 if (paste==1 && pick[select]!=-1) {//도형외부선택(붙여넣기)
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
		if (drag) {//TRUE일 때만 동작
			
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
				SetROP2(hdc, R2_XORPEN); //래스터연산을 사용할 것이며, 그중 사용할 것은 R2_XORPEN이다!!
				SelectObject(hdc, GetStockObject(WHITE_PEN));//내가 띄우는 창이 하얀색이니까 하얀색 펜을 덮음으로써 검정색을 만들어냄.
				MoveToEx(hdc, x[select][count[select]], y[select][count[select]], NULL);
				LineTo(hdc, firstX[select][count[select]], firstY[select][count[select]]); //이전 라인 지운 다음에 다음 라인 그려야 하니까, 이전 라인에 하얀색 다시 씌워서 없어진것처럼 보이게(검+흰=흰)
				MoveToEx(hdc, x[select][count[select]], y[select][count[select]], NULL);
				LineTo(hdc, endX[select][count[select]], endY[select][count[select]]); //mousemove에 의해 움직여진 좌표값으로 새로 그려줌(흰+흰=검)
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