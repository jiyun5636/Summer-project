#define MAIN
#include <windows.h>                           // 윈도우 헤더파일
#include <stdlib.h>
#include"game.h"
#include "Global.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   //CALLBACK 매크로
//HINSTANCE g_hInst;                              //인스턴스 핸들
//LPCTSTR lpszClass = TEXT("김지윤_21031007");            //제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam,
    int nCmdShow)
{
    HWND hWnd;                                 //윈도우 핸들 선언
    MSG Message;                              //메세지 구조체 변수 선언
    WNDCLASS WndClass;                           //Windows Class 구조체 변수 선언
    g_hInst = hInstance;                        //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

    WndClass.cbClsExtra = 0;                     //예약 영역. 지금은 사용X
    WndClass.cbWndExtra = 0;                     //예약 영역
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // 윈도우의 배경 색상을 지정
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //윈도우의 마우스포인터 모양을 지정
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //윈도우의 커서 아이콘 모양 지정
    WndClass.hInstance = hInstance;                  //윈도우 클래스를 등록하는 프로그램 번호
    WndClass.lpfnWndProc = WndProc;                  //윈도우 메세지 처리 함수 지정
    WndClass.lpszClassName = lpszClass;               //윈도우 클래스의 이름 지정
    WndClass.lpszMenuName = NULL;                  //메뉴 지정
    WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;         //윈도우의 스타일을 정의

    RegisterClass(&WndClass);                     //WNDCLASS 구조체의 번지를 전달


    hWnd = CreateWindow(lpszClass, lpszClass,         //윈도우를 생성
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //메세지 루프를 실행
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue에 있는 메세지를 읽어들인다
        TranslateMessage(&Message);                  //키보드 입력 메세지를 가공하여 프로그램에서 쉽게 
                                            //  사용할 수 있도록
        DispatchMessage(&Message);                  //메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
    }
    return (int)Message.wParam;                     //탈출 코드. 프로그램 종료
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static bool flag = false;
    switch (iMessage)
    {
    case WM_CREATE:
        hWndMain = hWnd;
        Initialize();
        Reset(); //초기화
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawBitmap(hdc, 0, 0, hBackBit);
        MapDraw(hdc); //기본적으로 맵을 그림
        if (isslide) //슬라이드가 가능할 때
        {
            SlideDraw(hdc); //슬라이드 이미지를 내보냄 (충돌 범위 줄어듬)
        }
        else Draw(hdc); //슬라이드를 누르지 않는 모든 상황엔 기본 이미지
        EndPaint(hWnd, &ps);
       return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            SetTimer(hWndMain, 1, 40, NULL);
            break;
        case VK_DOWN:
            isslide = true; //아래키를 눌렀을 때 슬라이드 가능메세지를 보냄 (WM_PAINT에)
            InvalidateRect(hWndMain, NULL, true);
            break;
        default:
            break;
        }
        break;

    case WM_KEYUP:
        switch (wParam)
        {
        case VK_DOWN:
            isslide = false;
            break;
        default:
            break;
        }
        InvalidateRect(hWndMain, NULL, true);
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case 1:
                Move();
                Gravity();

              if(y==370)
                    KillTimer(hWnd, 1);
             // InvalidateRect(hWnd, NULL, TRUE);
            break;
        case 2:
            OnTimer();
          
            break;
        default:
            break;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        PostQuitMessage(0);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//test