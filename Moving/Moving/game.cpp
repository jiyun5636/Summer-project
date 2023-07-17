#include "game.h"

void Reset() //�ʱ�ȭ
{
    x = 330; y = 370;
    isjump = false;
    isdown = false;
    issilde = false;
    num = 0;
}

void Move() //��� �÷��̾� �̵�
{
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
        if (y > 370) //���� �������� 30������  ������ y��ǥ(400)���� -30��ŭ �ؼ� 370��
        {
            y = 370; //���ϴ� ��ǥ��ŭ �ϰ��ϸ� ��ǥ���� (���� ��ǥ)
            isdown = false; //�ϰ� �Ұ���
        }
    }
    InvalidateRect(hWndMain, NULL, TRUE);
}

void MapDraw(HDC hdc) //��
{
    MoveToEx(hdc, Ground_LeftX, 400, NULL); //y���� ����
    LineTo(hdc, Ground_RightX, 400);
}

void Draw(HDC hdc) //�⺻ �ڼ� (�ӽ�)
{
    Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
}

void SlideDraw(HDC hdc) //�����̵� �ڼ� (�ӽ�)
{
    Rectangle(hdc,x-SSize,y- SSize+10,x+ SSize,y+ SSize+10);
}