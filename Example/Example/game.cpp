#include "game.h"

void Reset() //�ʱ�ȭ
{
    x = 330; y = 370;
    isjump = false;
    isdown = false;
    left = false;
    right = false;
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
    InvalidateRect(hWndMain, NULL, TRUE);
}

void Draw(HDC hdc)
{
    Ellipse(hdc, x - BSIZE, y - BSIZE, x + BSIZE, y + BSIZE);
    MoveToEx(hdc, Ground_LeftX, 400, NULL); //y���� ����
    LineTo(hdc, Ground_RightX, 400);
}