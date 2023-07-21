#pragma once
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Initialize();
void MemoryPaint();
void OnTimer();
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask);

struct TPOINT
{
	int x;
	int y;
};

#ifdef MAIN

HINSTANCE g_hInst;
//HWND hWndMain;
LPCTSTR lpszClass = TEXT("FieldScroll");
HBITMAP hField, hBaby, hToilet;
int goundx = 0;
int bx = 100, by = 100, ty;
TPOINT tp[100];
int tCnt;
HBITMAP hBackBit, hOldBitmap;
#else
extern HINSTANCE g_hInst;
extern HWND hWndMain;
extern LPCTSTR lpszClass;
extern HBITMAP hField, hBaby, hToilet;
extern int goundx;
extern int bx, by, ty;
extern TPOINT tp[100];
extern int tCnt;
extern HBITMAP hBackBit, hOldBitmap;
#endif
