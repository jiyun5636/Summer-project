#define MAIN
#include <windows.h>                           // ������ �������
#include <stdlib.h>
#include"game.h"
#include "Global.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   //CALLBACK ��ũ��
//HINSTANCE g_hInst;                              //�ν��Ͻ� �ڵ�
//LPCTSTR lpszClass = TEXT("������_21031007");            //���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam,
    int nCmdShow)
{
    HWND hWnd;                                 //������ �ڵ� ����
    MSG Message;                              //�޼��� ����ü ���� ����
    WNDCLASS WndClass;                           //Windows Class ����ü ���� ����
    g_hInst = hInstance;                        //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

    WndClass.cbClsExtra = 0;                     //���� ����. ������ ���X
    WndClass.cbWndExtra = 0;                     //���� ����
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // �������� ��� ������ ����
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //�������� ���콺������ ����� ����
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //�������� Ŀ�� ������ ��� ����
    WndClass.hInstance = hInstance;                  //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
    WndClass.lpfnWndProc = WndProc;                  //������ �޼��� ó�� �Լ� ����
    WndClass.lpszClassName = lpszClass;               //������ Ŭ������ �̸� ����
    WndClass.lpszMenuName = NULL;                  //�޴� ����
    WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;         //�������� ��Ÿ���� ����

    RegisterClass(&WndClass);                     //WNDCLASS ����ü�� ������ ����


    hWnd = CreateWindow(lpszClass, lpszClass,         //�����츦 ����
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //�޼��� ������ ����
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue�� �ִ� �޼����� �о���δ�
        TranslateMessage(&Message);                  //Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� 
                                            //  ����� �� �ֵ���
        DispatchMessage(&Message);                  //�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
    }
    return (int)Message.wParam;                     //Ż�� �ڵ�. ���α׷� ����
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
        Reset(); //�ʱ�ȭ
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        DrawBitmap(hdc, 0, 0, hBackBit);
        MapDraw(hdc); //�⺻������ ���� �׸�
        if (isslide) //�����̵尡 ������ ��
        {
            SlideDraw(hdc); //�����̵� �̹����� ������ (�浹 ���� �پ��)
        }
        else Draw(hdc); //�����̵带 ������ �ʴ� ��� ��Ȳ�� �⺻ �̹���
        EndPaint(hWnd, &ps);
       return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            SetTimer(hWndMain, 1, 40, NULL);
            break;
        case VK_DOWN:
            isslide = true; //�Ʒ�Ű�� ������ �� �����̵� ���ɸ޼����� ���� (WM_PAINT��)
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