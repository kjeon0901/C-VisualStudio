//_T 쓰지 말고, 프로젝트 속성 => 문자집합 => 설정안함

#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam);
//CALLBACK: 도돌이표. WHILE문으로 돌아감과 동시에 자신이 실행했던 MESSAGE값을 보내줌
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {//다 구조체임. 구조체 이름은 바꿔도 상관없음. 
	HWND hwnd;//HANDLE: 자원의 번호가 정수값으로 저장됨 - 마우스 커서, 아이콘, 이미지 등등. window창에 뭐든 하나 추가할 때마다 HANDLE 써줘야 함. 
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;//WINDOW의 EVENT를 처리하기 위한 함수
	WndClass.cbClsExtra = 0;//메모리를 얼마나 쓸거냐 한계치를 담는 변수
	WndClass.cbWndExtra = 0;//메모리를 얼마나 쓸거냐 한계치를 담는 변수
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//그 프로그램의 아이콘을 담아두는 곳
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//커서의 모양을 담아두는 곳
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색을 담아두는 곳
																 //앞에 LP가 붙어있으면 모두 포인터, 즉 주소라고 생각하면 됨. 
	WndClass.lpszMenuName = NULL;//이 프로그램에 MENU가 있다면 그 주소를 담아두는 곳
	WndClass.lpszClassName = _T("Window Class Name");//윈도우의 고유한 이름 하나를 담아두는 곳
	RegisterClass(&WndClass);//위의 설계도를 가지고 윈도우 운영체제에 "나 이렇게 프로그램 만들거야!"라고 등록시킴

	hwnd = CreateWindow(_T("Window Class Name"),//CREATEWINDOW라는 함수를 통해 방금 설계한 프로그램을 만듦. 대신 LPSZCLASSNAME에 등록된 이름과 일치해야 함.
		_T("Window Title Name"),//프로그램 위에 써있는 이름
		WS_OVERLAPPEDWINDOW,//지금 실행되고 있는 모든 프로그램 위에 창이 뜨도록 함
		CW_USEDEFAULT,//윈도우 창이 뜨는 위치
		CW_USEDEFAULT,//윈도우 창이 뜨는 위치
		CW_USEDEFAULT,//윈도우 창의 크기
		CW_USEDEFAULT,//윈도우 창의 크기
		NULL,//윈도우 창 여러개 뜨도록 할 경우 부모 윈도우가 누군지 알려주는 부분
		NULL,//메뉴를 연결시켜주는 부분
		hInstance,
		NULL//나중에 DIALOGE(창이 뜨면 그 창 안쪽만 선택할 수 있는 창)랑 MODAL(창이 뜨더라도 창 밖의 부분을 선택할 수 있는 창) 쓰게 될 때 사용하는 부분
	);

	ShowWindow(hwnd, nCmdShow);//여기까지 잘 실행됐다면 WINDOW 흰색 창은 무조건 뜨게 되어 있음. 창이 안뜨는 경우 위쪽에서 문제가 생긴 것. 
	UpdateWindow(hwnd);//현재 나의 모니터 화면에 뜨도록 다른 화면과 합쳐서 다시 그림.(뭔가 움직일때마다 계속 다시 그려주는 것임)
					   //EVENT가 발생했을 경우 MSG로 WHILE문에 들어감!!
	while (GetMessage(&msg, NULL, 0, 0)) { //무한루프. MESSAGE QUEUE에서 (자신이 보낸 이벤트에 해당하는) 메세지를 보내올 때까지 계속 기다림.
		TranslateMessage(&msg);
		DispatchMessage(&msg);//WINDOW에게 이 EVENT는 잘 처리가 되었습니다 라고 알려줌. 
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	//WPARAM, LPARAM: 윈도우 메시지와 함께 가져오는 부가적인 내용 담음.(SHIFT키 누르고 대문자 입력한 거냐 소문자 입력한 거냐,,,등등)

	HDC hdc, gdc, idc;//DC 만들기 위해 꼭 필요함
	PAINTSTRUCT ps;//DC 만들기 위해 꼭 필요함
	static RECT rect;//사각형 만드는 함수 끝나고 "happy" 넣는 함수 들어가고.. 계속 남아있어야 하니까 지역변수인 rect 앞에 static 붙여줌.
	static char str[10][1000];
	static int cnt[10] = { 0 }, line = 0, k;
	char rrr[11] = { "I love you" }; //NULL까지 합쳐서 11임.

	switch (iMsg) {//메세지가 올 때마다 CASE를 하나씩 추가시킬 것임.
	case WM_CREATE://WINDOW MESSAGE CREATE: EVENT를 가져와서 윈도우가 가장 처음 (무조건) 실행하는 부분. 값에 대한 초기화를 해주는 부분.
				   //rect.left = 50;
				   //rect.top = 50;
				   //rect.right = 200;
				   //rect.bottom = 200;
		break;
	case WM_LBUTTONDOWN://왼쪽 마우스 클릭 누를 때, RBUTTONDOWN은 오른쪽.
		gdc = GetDC(hwnd);
		TextOut(gdc, 150, 150, "birthday", 8);//이렇게 쓸 땐 NULL 빼고 8임.
		ReleaseDC(hwnd, gdc);
		break;
	case WM_LBUTTONUP://왼쪽 마우스 클릭 뗄 때, RBUTTONDOWN은 오른쪽.
		idc = GetDC(hwnd);
		TextOut(idc, 100, 100, rrr, strlen(rrr));//위에서 문자열 넣고 이렇게 써도 됨. strlen은 문자열 크기 구해주는 함수.
		ReleaseDC(hwnd, idc);
		break;
	case WM_CHAR://문자키만 누르는 거니까
		if (wParam == VK_BACK)//만약 BACKSPACE를 눌렀다면
			cnt[line]--;
		else if (wParam == VK_RETURN)
			line++;
		else {
			str[line][cnt[line]++] = wParam;//++ 가 뒤에 있으니가 실행 후 증가.
		}
		str[line][cnt[line]] = "\0"; //문자열이니까 문자열 뒤에 null값 계속 넣어줘야 함. 
		InvalidateRgn(hwnd, NULL, TRUE);//강제로 MESSAGE QUEUE에 넣어 WM_PAINT 실행시키는 함수 => 화면을 재구성하고 싶을 때 사용.
										//NULL: 윈도우 영역 전체를 다시 실행시키고 싶을 때.
										//TRUE: 잔상을 없애는 대신 깜박임이 생김. 
										//깜박임도 없애려면 TRUE=>PALSE로 바꾸고 NULL대신 영역을 지정해줘야 함.
		break;
	case WM_PAINT://윈도우창 전체를 그릴 때마다 실행 (예> 테트리스 할 때는 창을 가만히 내버려두기 때문에 함수를 통해 여기로 계속 와야 함)
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 50, 50, "happy", 5);//이렇게 쓸 땐 NULL 빼고 5임.
		DrawText(hdc, "happy", 5, &rect, DT_CENTER | DT_VCENTER);
		for (k = 0; k <= line; k++) {
			TextOut(hdc, 30, 80 + (20 * k), str[k], cnt[k]);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY://WINDOW MESSAGE DESTROY: 윈도우 창 닫기를 누르는 것도 EVENT라서 그때 실행되는 부분.
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}