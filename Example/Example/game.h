#pragma once
#include<Windows.h>

#define BSIZE 30
#define SSize 20 //�簢�� ������
#define Ground_LeftX 200
#define Ground_RightX 500
#define GRAVITY 1.3 //�߷°��ӵ� ���

struct Floor //�ٴ�
{
	int floor_x;
	int floor_y;
};

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
int x, y;
int num;
bool isslide;
bool isgrounded;
bool easy, normal, hard;
struct Floor f[10];
#else
extern HWND hWndMain;
extern bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
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
void MapDraw(HDC hdc); //��
void Draw(HDC hdc); //�⺻ �ڼ�
void SlideDraw(HDC hdc); //�����̵� �ڼ�