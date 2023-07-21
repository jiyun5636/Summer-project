#include <windows.h>
#include "Global.h"
#include "resource.h"
#include"game.h"

void Initialize()
{
	hField = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND));
	SetTimer(hWndMain, 2, 50, NULL);
	HDC hdc = GetDC(hWndMain);
	hBackBit = CreateCompatibleBitmap(hdc, 2000, 700);
	ReleaseDC(hWndMain, hdc);
}
void MemoryPaint()
{
	HDC hdc = GetDC(hWndMain);
	HDC hMemDC = CreateCompatibleDC(hdc);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBackBit);
	// 배경 그림
	HDC hMemDC2 = CreateCompatibleDC(hdc);
	HBITMAP hOldbit1 = (HBITMAP)SelectObject(hMemDC2, hField);
	int w = min(2000 - goundx, 2000);
	BitBlt(hMemDC, 0, 0,w, 700, hMemDC2, goundx, 0, SRCCOPY);
	if (w < 2000) {
		BitBlt(hMemDC, w, 0, 2000 - w, 700, hMemDC2, 0, 0, SRCCOPY);
	}

	SelectObject(hMemDC2, hOldbit1);
	DeleteDC(hMemDC2);
	// 캐릭터 그림
	
	Ellipse(hMemDC, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
	MoveToEx(hMemDC, Ground_LeftX, 400, NULL); //y축은 고정
	LineTo(hMemDC, Ground_RightX, 400);


	// 완성된 그림 전송
	BitBlt(hdc, 0, 0, 2000, 700, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hdc);
}

void OnTimer()
{
	goundx+=10;
	if (goundx > 2048) goundx = 0;
	for (int i = 0; i < tCnt; i++)
	{
		tp[i].x += 10;
		if (tp[i].x > 2000)
		{
			for (int j = i; j < tCnt - 1; j++)
			{
				tp[j].x = tp[j + 1].x;
				tp[j].y = tp[j + 1].y;
			}
			tCnt--;
			i--;
		}
	}

	if (GetKeyState(VK_UP) & 0x5000)
	{
		SetTimer(hWndMain, 1, 20, NULL);//점프용
	}
	if (GetKeyState(VK_LEFT) & 0x5000)
	{
		goundx += 100;
	}

	MemoryPaint();

	InvalidateRect(hWndMain, NULL, FALSE);
}

void TransBlt(HDC hdc, int x, int y, HBITMAP hbitmap, COLORREF clrMask)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC		hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT	ptSize;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hbitmap);
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem = CreateCompatibleDC(hdc);
	hdcSave = CreateCompatibleDC(hdc);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, clrMask);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, x, y, SRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
	BitBlt(hdc, x, y, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
