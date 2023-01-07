#define _CRT_SECURE_NO_WARNINGS
#include"AVL.h"
#include<cstdlib>
#include<string>
#include<iostream>
#include<fstream>

int main()
{
	AVLTree T = NULL;
	puts("正在从文件读取数据...");
	std::fstream FILE("data.txt", std::ios::in);
	while (!FILE.eof())
	{
		int x = 0;
		FILE >> x;
		Insert(T, x);
		if (FILE.good() == false)
			break;
	}
	puts("已读取完毕！现输出结果：");
	DFS(T);
	printf("\n现进行手动操作\n");
	system("pause");
	while (1)
	{
		system("cls");
		int input = -1,x;
		bool pd;
		printf("请选择以下操作：\n[1]插入数\n[2]删除数\n[3]查找数\n[0]退出\n");
		scanf("%d", &input);
		switch (input)
		{

			case 1:
				printf("请输入插入的数：");
				scanf("%d", &x);
				pd = Insert(T,x);
				if (!pd)
					puts("数已存在！");
				else
					puts("插入成功！");
				break;
			case 2:
				printf("请输入删除的数：");
				scanf("%d", &x);
				pd = Remove(T,x);
				if (!pd)
					puts("该数不存在！");
				else
					puts("删除成功！");
				break;
			case 3:
				printf("请输入查找的数：");
				scanf("%d", &x);
				pd = Find(T,x);
				if (!pd)
					puts("该数不存在！");
				else
					puts("该数存在！");
				break;
			case 0:
				return 0;
			default:
				printf("请输入正确的指令！\n");
		}
		puts("按任意键输出AVL内存储结果：");
		system("pause");
		DFS(T); puts("");
		system("pause");
		
	}
	return 0;
}