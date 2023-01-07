#define _CRT_SECURE_NO_WARNINGS
#include"AVL.h"
#include<cstdlib>
#include<string>
#include<iostream>
#include<fstream>

int main()
{
	AVLTree T = NULL;
	puts("���ڴ��ļ���ȡ����...");
	std::fstream FILE("data.txt", std::ios::in);
	while (!FILE.eof())
	{
		int x = 0;
		FILE >> x;
		Insert(T, x);
		if (FILE.good() == false)
			break;
	}
	puts("�Ѷ�ȡ��ϣ�����������");
	DFS(T);
	printf("\n�ֽ����ֶ�����\n");
	system("pause");
	while (1)
	{
		system("cls");
		int input = -1,x;
		bool pd;
		printf("��ѡ�����²�����\n[1]������\n[2]ɾ����\n[3]������\n[0]�˳�\n");
		scanf("%d", &input);
		switch (input)
		{

			case 1:
				printf("��������������");
				scanf("%d", &x);
				pd = Insert(T,x);
				if (!pd)
					puts("���Ѵ��ڣ�");
				else
					puts("����ɹ���");
				break;
			case 2:
				printf("������ɾ��������");
				scanf("%d", &x);
				pd = Remove(T,x);
				if (!pd)
					puts("���������ڣ�");
				else
					puts("ɾ���ɹ���");
				break;
			case 3:
				printf("��������ҵ�����");
				scanf("%d", &x);
				pd = Find(T,x);
				if (!pd)
					puts("���������ڣ�");
				else
					puts("�������ڣ�");
				break;
			case 0:
				return 0;
			default:
				printf("��������ȷ��ָ�\n");
		}
		puts("����������AVL�ڴ洢�����");
		system("pause");
		DFS(T); puts("");
		system("pause");
		
	}
	return 0;
}