#include "screen.h"
#include <curses.h>


WINDOW* win_2048 = NULL;
WINDOW* win_score = NULL;


void OpenScreen()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    win_2048 = newwin(LINE_NUM,COLUMN_NUM,START_Y,START_X);
    win_score = newwin(LINE_NUM_, COLUMN_NUM, START_Y + LINE_NUM, START_X + 4);
}



void CloseScreen()
{
    delwin(win_score);
    delwin(win_2048);
    endwin();
}