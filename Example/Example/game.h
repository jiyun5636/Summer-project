#pragma once
#include<Windows.h>

#define BSIZE 30
#define SSize 20 //사각형 사이즈
#define Ground_LeftX 200
#define Ground_RightX 500
#define GRAVITY 1.3 //중력가속도 계산

struct Floor //바닥
{
	int floor_x;
	int floor_y;
};

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
int x, y;
int num;
bool isslide;
bool isgrounded;
bool easy, normal, hard;
struct Floor f[10];
#else
extern HWND hWndMain;
extern bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
extern int x, y;
extern int num;
extern bool isslide;
extern bool isgrounded;
extern bool easy, normal, hard;
extern struct Floor f[10];
#endif

void Reset();
void Move();
void Gravity();
void MapDraw(HDC hdc); //맵
void Draw(HDC hdc); //기본 자세
void SlideDraw(HDC hdc); //슬라이드 자세