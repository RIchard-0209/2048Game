#include "2048.h"

#define N 4
int matrix2048[N][N] = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};


extern WINDOW*  win_2048;
void Game2048Logic()
{ 
    srandom(time(NULL));
    FillARandNum();
    DrawMatrix();
    while(1)
    {

    }
}

int GetZeroNum()
{
    int num = 0;
	for(int i = 0;i < N ;i++)
	{
		for(int j = 0; j < N;j++)
		{
            if(matrix2048[i][j] != 0)
                continue;
            num++;
        }
	}
    return num;
}


void DrawMatrix()
 {
	for(int i = 0;i < N ;i++)
	{
		for(int j = 0; j < N;j++)
		{
            wmove(win_2048,i,j*6);
            char tempArr[6] = {0};
            sprintf(tempArr,"%5d",matrix2048[i][j]);
            waddstr(win_2048,tempArr);
		}
	}
    wrefresh(win_2048);
    while(1);
}



void FillARandNum()
{
	int zeroNum = GetZeroNum();
	int pos = random() % zeroNum + 1;//ȡ1~zeroNum֮���һ�����ֵ��Ҳ��Ϊ����Ҫ���ֵ��һ�����λ��
	int cnt = 0;//ʵ�ʱ���ʱ��λ�ã�������pos���ʱ������Ӧ��i,j��Ϊ��������ֵ��λ��
	for(int i = 0;i < N ;i++)
	{
		for(int j = 0; j < N;j++)
		{
			if(matrix2048[i][j] == 0)
			{
				cnt++;
				if(cnt == pos)
				{
					int tempArr[] = {2,2,4,8};
					int index = random()%4;//��ȡ���ֵ���±꣬��������Ӧ��ֵ��䵽ĳλ��ȥ
					matrix2048[i][j] = tempArr[index];
					return ;
				}
			}
		}
	}
}



void MoveToLeft()
{

}

void MoveToRight()
{

}

void MoveToUp()
{

}

void MoveToDown()
{

}





int IsGameOver()
{

}


int IsChangeMatrix(inputKey_e inputKey)
{

}


