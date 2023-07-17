#pragma once
#include<Windows.h>

#define BSIZE 30 //�� ������
#define SSize 20 //�簢�� ������
#define Ground_LeftX 200 
#define Ground_RightX 500
#define GRAVITY 1.3 //�߷°��ӵ� ���

#ifdef MAIN
HWND hWndMain;
bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
bool issilde;
int x, y;
int num;
bool isgrounded;
#else
extern HWND hWndMain;
extern bool isjump, isdown; //������ ��������, ������ �� �پ���(�ϰ�)
extern bool issilde;
extern int x, y;
extern int num;
#endif

void Reset(); //�ʱ�ȭ
void Move(); //���� Ű �Լ�
void Gravity(); //�߷� �����ϴ� �Լ�
void MapDraw(HDC hdc); //��
void Draw(HDC hdc); //�⺻ �ڼ�
void SlideDraw(HDC hdc); //�����̵� �ڼ�