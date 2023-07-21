#include "game.h"
#include "Global.h"

void Reset() //초기화
{
    x = 200; y = 370;
    isjump = false;
    isdown = false;
    isslide = false;

    easy = true;
    normal = false;
    hard = false;
    num = 0;
}

void Move() //모든 플레이어 이동
{
    if (GetKeyState(VK_UP) & 0x8000)
    {
        if (!isjump && !isdown)
        {
            isjump = true;
            num = 0; //점프할때 필요한 (연산?) 변수
        }
    }
}

void Gravity() //점프시 모든 중력
{
    if (isjump) //점프가 가능한가? (스페이스바가 눌렸나?)
    {
        num = 20;
        num--; //점프, 하강할때 고정값 가지고 계산
        y -= GRAVITY * num; //***수정 등가속도 / 수가 점점
        if (y < 260) //정해둔 거리만큼 점프를 다 뛰었나?
        {
            y = 260; //원하는 좌표만큼 점프하면 좌표고정
            isjump = false; //점프 불가능
            isdown = true; //하강 시작
        }
    }
    if (isdown) //하강이 가능한가? (일정 거리만큼 점프했나?)
    {
        y += GRAVITY * num; //중력가속도 계산해서 하강
        num++; //떨어질때마다 num이 줄어듬으로서 더 빠르게 하강시킴
        if (y > 370) //원의 반지름이 30임으로  직선의 y좌표(400)에서 -30만큼 해서 370임
        {
            y = 370; //원하는 좌표만큼 하강하면 좌표고정 (최초 좌표)
            isdown = false; //하강 불가능

        }
        if (num < 0) y = 370;
    }

   // InvalidateRect(hWndMain, NULL, FALSE);
}

void MapDraw(HDC hdc) //맵
{
    if (easy)
    {
        f[0].floor_x = 0;
        f[0].floor_y = 400;
        f[1].floor_x = 500;
        f[1].floor_y = 400;
        for (int i = 0; i < 2; i++)
        {
            MoveToEx(hdc, f[i].floor_x, f[i].floor_y, NULL); //y축은 고정
            LineTo(hdc, f[i].floor_x + 300, f[i].floor_y);
        }
    }
}

void Draw(HDC hdc) //기본 자세 (임시)
{
    Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
}

void SlideDraw(HDC hdc) //슬라이드 자세 (임시)
{
    Rectangle(hdc, x - SSize, y - SSize + 10, x + SSize, y + SSize + 10);
}