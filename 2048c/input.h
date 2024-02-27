#ifndef __INPUT_H__
#define __INPUT_H__


#include <curses.h>



typedef enum inputKey
{
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4,
    QUIT = 5,
    OTHER_CODE = 6,
    AGAIN = 7,
}inputKey_e;


/*
    GetUserInput:
*/
inputKey_e GetUserInput();




#endif

