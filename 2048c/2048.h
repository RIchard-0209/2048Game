#ifndef __2048_H__
#define __2048_H__

#define N 4

	//得分
	static int score = 0;
	//临时得分
	static int tmp = 0;

	//游戏的主逻辑
    void Game2048Logic();
	//获取数组中零个数
	int	GetZeroNum();
	
	//写一个4*4的数组
	void DrawMatrix();
	
	
	//随机数
	void FillARandNum();
	
	
	//上下左右移动
	void MoveToLeft(int matrix[][N]);

	void MoveToRight(int matrix[][N]);

	void MoveToUp(int matrix[][N]);

	void MoveToDown(int matrix[][N]);

	
	//判断游戏是否结束
	int IsGameOver();
	
	//是否改变
	/*
		通过一个新的数组，按方向运行后形成的新数组
		调用IsSame函数
	*/
	int IsChange(int inputKey);

	//展示游戏结束界面
	void DisPlayGameOver();
    
	//
	/*
		将新数组与游戏的数组比较，如果相同则没有改变
		不相同，则将新数组的值赋给游戏的数组
	*/
    int IsSame(int matrix[][N]);
    
	//交换函数
    void Swap(int* a, int* b);

	//清除主游戏界面
	void ClearScreen();

	//清楚分数界面
	void ClearScore();

	//写分数
	void DrawScore();

	//写按键无效
	void DrawInputError();


#endif