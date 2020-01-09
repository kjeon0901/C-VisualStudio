//_T ���� ����, ������Ʈ �Ӽ� => �������� => ��������

#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam);
//CALLBACK: ������ǥ. WHILE������ ���ư��� ���ÿ� �ڽ��� �����ߴ� MESSAGE���� ������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {//�� ����ü��. ����ü �̸��� �ٲ㵵 �������. 
	HWND hwnd;//HANDLE: �ڿ��� ��ȣ�� ���������� ����� - ���콺 Ŀ��, ������, �̹��� ���. windowâ�� ���� �ϳ� �߰��� ������ HANDLE ����� ��. 
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;//WINDOW�� EVENT�� ó���ϱ� ���� �Լ�
	WndClass.cbClsExtra = 0;//�޸𸮸� �󸶳� ���ų� �Ѱ�ġ�� ��� ����
	WndClass.cbWndExtra = 0;//�޸𸮸� �󸶳� ���ų� �Ѱ�ġ�� ��� ����
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//�� ���α׷��� �������� ��Ƶδ� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//Ŀ���� ����� ��Ƶδ� ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//������ ��Ƶδ� ��
																 //�տ� LP�� �پ������� ��� ������, �� �ּҶ�� �����ϸ� ��. 
	WndClass.lpszMenuName = NULL;//�� ���α׷��� MENU�� �ִٸ� �� �ּҸ� ��Ƶδ� ��
	WndClass.lpszClassName = _T("Window Class Name");//�������� ������ �̸� �ϳ��� ��Ƶδ� ��
	RegisterClass(&WndClass);//���� ���赵�� ������ ������ �ü���� "�� �̷��� ���α׷� ����ž�!"��� ��Ͻ�Ŵ

	hwnd = CreateWindow(_T("Window Class Name"),//CREATEWINDOW��� �Լ��� ���� ��� ������ ���α׷��� ����. ��� LPSZCLASSNAME�� ��ϵ� �̸��� ��ġ�ؾ� ��.
		_T("Window Title Name"),//���α׷� ���� ���ִ� �̸�
		WS_OVERLAPPEDWINDOW,//���� ����ǰ� �ִ� ��� ���α׷� ���� â�� �ߵ��� ��
		CW_USEDEFAULT,//������ â�� �ߴ� ��ġ
		CW_USEDEFAULT,//������ â�� �ߴ� ��ġ
		CW_USEDEFAULT,//������ â�� ũ��
		CW_USEDEFAULT,//������ â�� ũ��
		NULL,//������ â ������ �ߵ��� �� ��� �θ� �����찡 ������ �˷��ִ� �κ�
		NULL,//�޴��� ��������ִ� �κ�
		hInstance,
		NULL//���߿� DIALOGE(â�� �߸� �� â ���ʸ� ������ �� �ִ� â)�� MODAL(â�� �ߴ��� â ���� �κ��� ������ �� �ִ� â) ���� �� �� ����ϴ� �κ�
	);

	ShowWindow(hwnd, nCmdShow);//������� �� ����ƴٸ� WINDOW ��� â�� ������ �߰� �Ǿ� ����. â�� �ȶߴ� ��� ���ʿ��� ������ ���� ��. 
	UpdateWindow(hwnd);//���� ���� ����� ȭ�鿡 �ߵ��� �ٸ� ȭ��� ���ļ� �ٽ� �׸�.(���� �����϶����� ��� �ٽ� �׷��ִ� ����)
					   //EVENT�� �߻����� ��� MSG�� WHILE���� ��!!
	while (GetMessage(&msg, NULL, 0, 0)) { //���ѷ���. MESSAGE QUEUE���� (�ڽ��� ���� �̺�Ʈ�� �ش��ϴ�) �޼����� ������ ������ ��� ��ٸ�.
		TranslateMessage(&msg);
		DispatchMessage(&msg);//WINDOW���� �� EVENT�� �� ó���� �Ǿ����ϴ� ��� �˷���. 
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	//WPARAM, LPARAM: ������ �޽����� �Բ� �������� �ΰ����� ���� ����.(SHIFTŰ ������ �빮�� �Է��� �ų� �ҹ��� �Է��� �ų�,,,���)

	HDC hdc, gdc, idc;//DC ����� ���� �� �ʿ���
	PAINTSTRUCT ps;//DC ����� ���� �� �ʿ���
	static RECT rect;//�簢�� ����� �Լ� ������ "happy" �ִ� �Լ� ����.. ��� �����־�� �ϴϱ� ���������� rect �տ� static �ٿ���.
	static char str[10][1000];
	static int cnt[10] = { 0 }, line = 0, k;
	char rrr[11] = { "I love you" }; //NULL���� ���ļ� 11��.

	switch (iMsg) {//�޼����� �� ������ CASE�� �ϳ��� �߰���ų ����.
	case WM_CREATE://WINDOW MESSAGE CREATE: EVENT�� �����ͼ� �����찡 ���� ó�� (������) �����ϴ� �κ�. ���� ���� �ʱ�ȭ�� ���ִ� �κ�.
				   //rect.left = 50;
				   //rect.top = 50;
				   //rect.right = 200;
				   //rect.bottom = 200;
		break;
	case WM_LBUTTONDOWN://���� ���콺 Ŭ�� ���� ��, RBUTTONDOWN�� ������.
		gdc = GetDC(hwnd);
		TextOut(gdc, 150, 150, "birthday", 8);//�̷��� �� �� NULL ���� 8��.
		ReleaseDC(hwnd, gdc);
		break;
	case WM_LBUTTONUP://���� ���콺 Ŭ�� �� ��, RBUTTONDOWN�� ������.
		idc = GetDC(hwnd);
		TextOut(idc, 100, 100, rrr, strlen(rrr));//������ ���ڿ� �ְ� �̷��� �ᵵ ��. strlen�� ���ڿ� ũ�� �����ִ� �Լ�.
		ReleaseDC(hwnd, idc);
		break;
	case WM_CHAR://����Ű�� ������ �Ŵϱ�
		if (wParam == VK_BACK)//���� BACKSPACE�� �����ٸ�
			cnt[line]--;
		else if (wParam == VK_RETURN)
			line++;
		else {
			str[line][cnt[line]++] = wParam;//++ �� �ڿ� �����ϰ� ���� �� ����.
		}
		str[line][cnt[line]] = "\0"; //���ڿ��̴ϱ� ���ڿ� �ڿ� null�� ��� �־���� ��. 
		InvalidateRgn(hwnd, NULL, TRUE);//������ MESSAGE QUEUE�� �־� WM_PAINT �����Ű�� �Լ� => ȭ���� �籸���ϰ� ���� �� ���.
										//NULL: ������ ���� ��ü�� �ٽ� �����Ű�� ���� ��.
										//TRUE: �ܻ��� ���ִ� ��� �������� ����. 
										//�����ӵ� ���ַ��� TRUE=>PALSE�� �ٲٰ� NULL��� ������ ��������� ��.
		break;
	case WM_PAINT://������â ��ü�� �׸� ������ ���� (��> ��Ʈ���� �� ���� â�� ������ �������α� ������ �Լ��� ���� ����� ��� �;� ��)
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 50, 50, "happy", 5);//�̷��� �� �� NULL ���� 5��.
		DrawText(hdc, "happy", 5, &rect, DT_CENTER | DT_VCENTER);
		for (k = 0; k <= line; k++) {
			TextOut(hdc, 30, 80 + (20 * k), str[k], cnt[k]);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY://WINDOW MESSAGE DESTROY: ������ â �ݱ⸦ ������ �͵� EVENT�� �׶� ����Ǵ� �κ�.
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}