#include "screen.h"
#include "input.h"
#include "2048.h"



int main()
{
    //��ʼ���ַ�����
    OpenScreen();
    //2048��Ϸ���߼�
    Game2048Logic();
    //�رմ���
    CloseScreen();

    return 0;
}