#include "screen.h"
#include "input.h"
#include "2048.h"



int main()
{
    //初始化字符窗口
    OpenScreen();
    //2048游戏的逻辑
    Game2048Logic();
    //关闭窗口
    CloseScreen();

    return 0;
}