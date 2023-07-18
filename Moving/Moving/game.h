#pragma once
#include<Windows.h>

#define BSIZE 30 //�� ������
#define SSize 20 //�簢�� ������
#define Ground_LeftX 0 
#define Ground_RightX 1000
#define GRAVITY 1.3 //�߷°��ӵ� ���

struct Obstacle //��ֹ�
{

};

struct Enemy //��
{

};

struct Floor //�ٴ�
{
	int floor_x;
	int floor_y;
};


#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
bool issilde;
int x, y;
int num;
bool isgrounded;
bool easy, normal, hard;
struct Floor f[10];
#else
extern HWND hWndMain;
extern bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
extern bool issilde;
extern int x, y;
extern int num;
extern bool easy, normal, hard;
extern struct Floor f[10];
#endif

void Reset(); //�ʱ�ȭ
void Move(); //���� Ű �Լ�
void Gravity(); //�߷� �����ϴ� �Լ�
void MapDraw(HDC hdc); //��
void Draw(HDC hdc); //�⺻ �ڼ�
void SlideDraw(HDC hdc); //�����̵� �ڼ�