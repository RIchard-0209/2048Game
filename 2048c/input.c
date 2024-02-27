#include "input.h"


extern WINDOW* win_2048;

inputKey_e GetUserInput()
{
    keypad(win_2048,TRUE);
    int ret = wgetch(win_2048);
    keypad(win_2048,FALSE);

    if(ret == 'q' || ret == 'Q')
        return QUIT;
    else if(ret == KEY_UP || ret == 'w'|| ret == 'W')
        return UP;
    else if(ret == KEY_DOWN || ret == 's'|| ret == 'S')
        return DOWN;
    else if(ret == KEY_LEFT || ret == 'a' || ret == 'A')
        return LEFT;
    else if(ret == KEY_RIGHT || ret == 'd' || ret == 'D')
        return RIGHT;
    else if(ret == 'h' || ret == 'H')
        return AGAIN;
    else 
        return OTHER_CODE;
}

