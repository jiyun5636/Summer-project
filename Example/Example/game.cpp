#include "game.h"
#include "Global.h"

void Reset() //�ʱ�ȭ
{
    x = 330; y = 370;
    isjump = false;
    isdown = false;
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

