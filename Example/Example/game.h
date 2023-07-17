#pragma once
#include<Windows.h>

#define BSIZE 30
#define Ground_LeftX 200
#define Ground_RightX 500
#define GRAVITY 1.3 //�߷°��ӵ� ���

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
int x, y;
int num;
bool left, right;
#else
extern HWND hWndMain;
extern bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
extern int x, y;
extern int num;
extern bool left, right;
#endif

void Reset();
void Move();
void Gravity();
void Draw(HDC hdc);