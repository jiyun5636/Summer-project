#include "game.h"

void Reset() //�ʱ�ȭ
{
    x = 200; y = 370;
    isjump = false;
    isdown = false;
    issilde = false;

    easy = true;
    normal = false;
    hard = false;
    num = 0;
}

void Move() //��� �÷��̾� �̵�
{
    if (GetKeyState(VK_LEFT) & 0x8000)
    {
        x -= 10;
    }
    if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        x += 10;
    }
    if (GetKeyState(VK_UP) & 0x8000) //ȭ��ǥ ���� Ű
    {
        if (!isjump && !isdown)
        {
            isjump = true;
            issilde = false;
            num = 0; //�����Ҷ� �ʿ��� (����?) ����
        }
    }
    InvalidateRect(hWndMain, NULL, TRUE);
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
        for (int i = 0; i < 10; i++) //���������� ��� �ϰ�
        {
            if (y-30 > f[i].floor_y) //���� �������� 30������  ������ y��ǥ(400)���� -30��ŭ �ؼ� 370��
            {
                y++; //���ϴ� ��ǥ��ŭ �ϰ��ϸ� ��ǥ���� (���� ��ǥ)
            }
            else  isdown = false; //�ϰ� �Ұ���
        }
    }
    InvalidateRect(hWndMain, NULL, TRUE);
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
            LineTo(hdc, f[i].floor_x+300, f[i].floor_y);
        }
    }
}

void Draw(HDC hdc) //�⺻ �ڼ� (�ӽ�)
{
    Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
}

void SlideDraw(HDC hdc) //�����̵� �ڼ� (�ӽ�)
{
    Rectangle(hdc,x-SSize,y- SSize+10,x+ SSize,y+ SSize+10);
}