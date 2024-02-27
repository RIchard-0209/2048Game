#include "2048.h"
#include "input.h"
#include "screen.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>

extern WINDOW* win_2048;
extern inputKey_e GetUserInput();
extern WINDOW* win_score;
// extern int LINE_NUM;
// extern int COLUMN_NUM;

int matrix2048[N][N] = { 0 };

// int  matrix2048[][4] = 
//     {
//         {0, 2, 2, 8},
//         {8, 8, 4, 4},
//         {4, 8, 2, 4},
//         {16, 8, 8, 32}
//     };


int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void Game2048Logic()
{
    srandom(time(NULL));

    FillARandNum();

    DrawMatrix();
    
    while(1)
    {
        inputKey_e gesture = GetUserInput();
        
        if (QUIT == gesture)
        {
            break;
        }
        else if (AGAIN == gesture)
        {
            memset(matrix2048, 0, sizeof matrix2048);
            
            FillARandNum();
            ClearScreen();
            score = 0;
            tmp = 0;
            DrawMatrix();   
        }
        
        else if (OTHER_CODE == gesture)
        {
            DrawInputError();
        }
        else 
        {   if(IsChange(gesture))
            {
                ClearScore();
                FillARandNum();
                DrawMatrix();
            }
        }

        if (IsGameOver() == 1)
        {
            score = 0;
            tmp = 0;
            DisPlayGameOver();
        }
    }
}
//???4*4???????§Ø????0
int GetZeroNum()
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix2048[i][j] == 0)
            {
                ans ++;
            }
        }
    }
    
    return ans;
}

//??????????????§Ö???? 4 * 6 + 1
void DrawScore()
{
    wmove(win_score, 0, 0);
    char buff[15] = "score: ";
    char num[10] = { 0 };
    sprintf(num, "%d", score);
    strcat(buff, num);
    waddstr(win_score, buff);
    wrefresh(win_score);
}

void DrawInputError()
{
    wmove(win_score, 1, 0);
    char buff[] = "Press Button Error";
    waddstr(win_score, buff);
    wrefresh(win_score);
}

//??4*4?????§Ö??????§Õ???????????
void DrawMatrix()
{
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < N; j ++)
        {
            wmove(win_2048, i, j * 6);
            char buff[6] = { 0 };
            sprintf(buff, "%5d", matrix2048[i][j]);
            waddstr(win_2048, buff);
            wrefresh(win_2048);
        }
    }

    // wmove(win_2048, 0, 6 * 4 + 1);
    // char buff[10];
    // sprintf(buff, "%d", tmp);
    // waddstr(win_2048, buff);
    // wrefresh(win_2048);
    DrawScore();
    
}


//??4*4?????????¦Ë????????????
//???¦Ë?¨°????????????¦Ë???
void FillARandNum()
{
	int zeroNum = GetZeroNum();
    if (zeroNum == 0)
        return ;
	int pos = random() % zeroNum + 1;//?1~zeroNum??????????????????????????????????¦Ë??
	int cnt = 0;//?????????¦Ë?????????pos?????????????i,j??????????????¦Ë??
	for (int i = 0; i < N ;i ++)
	{
		for (int j = 0; j < N; j ++)
		{
			if (matrix2048[i][j] == 0)
			{
				cnt ++;
				if (cnt == pos)
				{
					int tempArr[] = {2, 2, 4, 8};
					int index = random() % 4;//??????????¡À?????????????????¦Ë???
					matrix2048[i][j] = tempArr[index];
					return ;
				}
			}
		}
	}
}


//?????????????????????????????????????????????????????????????§Ö?????????????
//???????????
void MoveToLeft(int matrix[][N])
{
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0, k = 0; j < N && k < N; j ++)
        {
            if (matrix[i][k] == 0)   k++;
            if (matrix[i][j] == 0)   continue;
            else if (j != k && matrix[i][j] == matrix[i][k])
            {
                matrix[i][k] += matrix[i][j];
                matrix[i][j] = 0;
                tmp += matrix[i][k];
                k = i + 1;
            }
            else if (matrix[i][j] != 0 && matrix[i][j] != matrix[i][k])
            {
                k ++;
            }
        }

        for (int j = 0, k = 0; j < N; j ++)
        {
            while(k < j && matrix[i][k] != 0) k ++;
            if (matrix[i][k] == 0)
                Swap(&matrix[i][j], &matrix[i][k]);
        }
    }
}

void MoveToRight(int matrix[][N])
{
        // for (int j = N- 1, k = N - 1; j >= 0; j --)
        // {
        //     while(j < k && matrix[i][k] != 0) k --;
        //     if (matrix[i][k] == 0)
        //         Swap(&matrix[i][j], &matrix[i][k]);
        // }

    for (int i = 0; i < N; i ++)
    {
        for (int j = N - 1, k = N - 1; j >= 0 && k >= 0; j --)
        {
            if (matrix[i][k] == 0)   k--;
            if (matrix[i][j] == 0)   continue;
            else if (j != k && matrix[i][j] == matrix[i][k])
            {
                matrix[i][k] += matrix[i][j];
                matrix[i][j] = 0;
                tmp += matrix[i][k];
                k = i - 1;
            }
            else if (matrix[i][j] != 0 && matrix[i][j] != matrix[i][k])
            {
                k --;
            }
        }

        for (int j = N - 1, k = N - 1; j >= 0; j --)
        {
            while(j < k && matrix[i][k] != 0) k --;
            if (matrix[i][k] == 0)
                Swap(&matrix[i][j], &matrix[i][k]);
        }
    }
}

void MoveToUp(int matrix[][N])
{
    for (int j = 0; j < N; j ++)
    {
        for (int i = 0, k = 0; i < N && k < N; i ++)
        {
            if (matrix[k][j] == 0)   k++;
            if (matrix[i][j] == 0)   continue;
            else if (i != k && matrix[i][j] == matrix[k][j])
            {
                matrix[k][j] += matrix[i][j];
                matrix[i][j] = 0;
                tmp += matrix[k][j];
                k = i + 1;
            }
            else if (matrix[i][j] != 0 && matrix[i][j] != matrix[k][j])
            {
                k ++;
            }
        }

        for (int i = 0, k = 0; i < N; i ++)
        {
            while(k < i && matrix[k][j] != 0) k ++;
            if (matrix[k][j] == 0)
                Swap(&matrix[i][j], &matrix[k][j]);
        }
        // Print();
        // for (int i = 0, k = 1; k < N; i ++, k ++)
        // {
        //     if ( matrix[k][j] == matrix[i][j])
        //     {
        //         matrix[i][j] += matrix[k][j];
        //         matrix[k][j] = 0;
        //         tmp += matrix[i][j];
        //     }
        //     if (matrix[i][j] == 0)
        //     {
        //         Swap(&matrix[i][j], &matrix[k][j]);
        //     }
        // }
    }
}

void MoveToDown(int matrix[][N])
{
    for (int j = 0; j < N; j ++)
    {

        for (int i = N - 1, k = N - 1; i >= 0 && k >= 0; i --)
        {
            if (matrix[k][j] == 0)   k--;
            if (matrix[i][j] == 0)   continue;
            else if (i != k && matrix[i][j] == matrix[k][j])
            {
                matrix[k][j] += matrix[i][j];
                matrix[i][j] = 0;
                tmp += matrix[k][j];
                k = i - 1;
            }
            else if (matrix[i][j] != 0 && matrix[i][j] != matrix[k][j])
            {
                k --;
            }
        }

        for (int i = N- 1, k = N - 1; i >= 0; i --)
        {
            while(i < k && matrix[k][j] != 0) k --;
            if (matrix[k][j] == 0)
                Swap(&matrix[i][j], &matrix[k][j]);
        }
    }
}
//?§Ø??????????(????????????1.???§Ö?????????0??2.???§Ú??????????????????)
//return 0??????¦Ä????
int IsGameOver()
{
    if (GetZeroNum() > 0)
    {
        return 0;
    }
    /*
    ????????
    2 4 8     2: 2(???) + 1 + 1; 4: 1(???) + 1 + 1 + 1;
    4 2 2     2: 2(4) + 1(8)
    2 8 4
    */

    int ans = 0; //?????¦¶?§Ó???????
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < N; j ++)
        {
            int flag = 0; //?????????????????
            for (int k = 0; k < 4; k ++)
            {
                //int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
                int x = i + d[k][1];
                int y = j + d[k][0];
                if (x == -1 || y == -1 || y == N || x == N)
                {
                    flag ++;
                }
                //???????????????????
                else if (matrix2048[x][y] != matrix2048[i][j])
                {
                    flag ++;
                }
            }
            //???????????,????????
            if (flag == 4)
            {
                ans ++; 
            }
        }
    }
    return ans == 16 ? 1 : 0;
    // return ans;
}

//?§Ø???????????????????????
int IsChange(int inputKey)
{
    // //????????????,?????4????eg?????4?????????????
    // if (GetZeroNum() >= 12)
    // {
    //     return 1;
    // }
    int matrix[N][N];
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < N; j ++)
            matrix[i][j] = matrix2048[i][j];
    }
    if (LEFT == inputKey)
    {
        MoveToLeft(matrix);
    }
    else if (RIGHT == inputKey)
    {
        MoveToRight(matrix);
    }
    else if (UP == inputKey)
    {
        MoveToUp(matrix);
    }
    else if (DOWN == inputKey)
    {
        MoveToDown(matrix);
    }
    if (IsSame(matrix))
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < N; i ++)
        {
            for (int j = 0; j < N; j ++)
            {
                matrix2048[i][j] = matrix[i][j];
            }
        }
        score = tmp;
        return 1;
    }
}

//Return: ???True 
int IsSame(int matrix[][N])
{
    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < N; j ++)
            if (matrix2048[i][j] != matrix[i][j])
                return 0;
    }
    tmp = score;
    return 1;
}


void DisPlayGameOver()
{
    char buff[1024];
    ClearScreen();
    wmove(win_2048, 0, 0);
    
    strcpy(buff, "Game Over!");
    waddstr(win_2048, buff);
    wrefresh(win_2048);
    wmove(win_2048, 1, 0);

    strcpy(buff, "Press H button Again");
    waddstr(win_2048, buff);
    wrefresh(win_2048);

}

void ClearScreen()
{
    char buff[2];
    strcpy(buff, " ");
    for (int i = 0; i < LINE_NUM; i ++)
    {
        for (int j = 0; j < COLUMN_NUM; j++)
        {
            wmove(win_2048, i, j);
            waddstr(win_2048, buff);    
            wrefresh(win_2048);
        }   
    }
    ClearScore();
    
}

void ClearScore()
{
    char buff[2];
    strcpy(buff, " ");
    for (int i = 0; i < LINE_NUM_; i ++)
    {
        for (int j = 0; j < COLUMN_NUM; j ++)
        {
            wmove(win_score, i, j);
            waddstr(win_score, buff);    
            wrefresh(win_score);
        }
    }
}
void Swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
