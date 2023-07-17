#pragma once
#include<Windows.h>

#define BSIZE 30 //원 사이즈
#define SSize 20 //사각형 사이즈
#define Ground_LeftX 200 
#define Ground_RightX 500
#define GRAVITY 1.3 //중력가속도 계산

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
bool issilde;
int x, y;
int num;
bool isgrounded;
#else
extern HWND hWndMain;
extern bool isjump, isdown; //점프가 가능한지, 점프를 다 뛰었나(하강)
extern bool issilde;
extern int x, y;
extern int num;
#endif

void Reset(); //초기화
void Move(); //위쪽 키 함수
void Gravity(); //중력 적용하는 함수
void MapDraw(HDC hdc); //맵
void Draw(HDC hdc); //기본 자세
void SlideDraw(HDC hdc); //슬라이드 자세