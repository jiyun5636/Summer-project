#include "game.h"
#include "Global.h"

void Reset() //�ʱ�ȭ
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

void Move() //��� �÷��̾� �̵�
{
    if (GetKeyState(VK_UP) & 0x8000)
    {
        if (!isjump && !isdown)
        {
            isjump = true;
            num = 0; //�����Ҷ� �ʿ��� (����?) ����
        }
    }
}

void Gravity() //������ ��� �߷�
{
    if (isjump) //������ �����Ѱ�? (�����̽��ٰ� ���ȳ�?)
    {
        num = 20;
        num--; //����, �ϰ��Ҷ� ������ ������ ���
        y -= GRAVITY * num; //***���� ��ӵ� / ���� ����
        if (y < 260) //���ص� �Ÿ���ŭ ������ �� �پ���?
        {
            y = 260; //���ϴ� ��ǥ��ŭ �����ϸ� ��ǥ����
            isjump = false; //���� �Ұ���
            isdown = true; //�ϰ� ����
        }
    }
    if (isdown) //�ϰ��� �����Ѱ�? (���� �Ÿ���ŭ �����߳�?)
    {
        y += GRAVITY * num; //�߷°��ӵ� ����ؼ� �ϰ�
        num++; //������������ num�� �پ�����μ� �� ������ �ϰ���Ŵ
        if (y > 370) //���� �������� 30������  ������ y��ǥ(400)���� -30��ŭ �ؼ� 370��
        {
            y = 370; //���ϴ� ��ǥ��ŭ �ϰ��ϸ� ��ǥ���� (���� ��ǥ)
            isdown = false; //�ϰ� �Ұ���

        }
        if (num < 0) y = 370;
    }

   // InvalidateRect(hWndMain, NULL, FALSE);
}

void MapDraw(HDC hdc) //��
{
    if (easy)
    {
        f[0].floor_x = 0;
        f[0].floor_y = 400;
        f[1].floor_x = 500;
        f[1].floor_y = 400;
        for (int i = 0; i < 2; i++)
        {
            MoveToEx(hdc, f[i].floor_x, f[i].floor_y, NULL); //y���� ����
            LineTo(hdc, f[i].floor_x + 300, f[i].floor_y);
        }
    }
}

void Draw(HDC hdc) //�⺻ �ڼ� (�ӽ�)
{
    Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
}

void SlideDraw(HDC hdc) //�����̵� �ڼ� (�ӽ�)
{
    Rectangle(hdc, x - SSize, y - SSize + 10, x + SSize, y + SSize + 10);
}