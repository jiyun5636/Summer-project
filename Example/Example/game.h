#pragma once
#include<Windows.h>

#define BSIZE 30
#define Ground_LeftX 200
#define Ground_RightX 500
#define GRAVITY 1.3 //중력가속도 계산

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
int x, y;
int num;
bool left, right;
#else
extern HWND hWndMain;
extern bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
extern int x, y;
extern int num;
extern bool left, right;
#endif

void Reset();
void Move();
void Gravity();
void Draw(HDC hdc);