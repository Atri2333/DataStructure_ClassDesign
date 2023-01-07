//���ܵ���dev-C++����֪��Ϊʲô��VS�ܵ�����
#include<string>
#include<map>
#include<unordered_map>
#include<fstream>
#include<iostream>
#include<queue>
#include<set>
#include<unordered_set>
int n;
std::map<std::string, int> M;
std::string FM[666666];
int F[666666], L[666666],A[666666];
std::queue<int> Q;
std::set<std::string> s[50];
std::string S, T;

void Init()
{
	std::fstream FILE("words.txt", std::ios::in);
	std::string str;
	while (!FILE.eof())
	{
		FILE >> str;
		s[str.size()].insert(str);
	}
	FILE.close();
}

int main()
{
	Init();
	puts("������ʼ���ʣ�");
	std::cin >> S;
	puts("������ֹ���ʣ�");
	std::cin >> T;
	if (S.size() != T.size())
	{
		puts("���ʳ��Ȳ���ͬ��");
		return 0;
	}
	if (S == T)
	{
		puts("����������ͬ��");
		return 0;
	}
	if (s[S.size()].find(S) == s[S.size()].end())
	{
		puts("��ʼ���ʲ����ڣ�");
		return 0;
	}
	if (s[T.size()].find(T) == s[T.size()].end())
	{
		puts("��ֹ���ʲ����ڣ�");
		return 0;
	}
	M[S] = ++n; F[n] = 0; L[n] = -1;
	FM[n] = S;
	Q.push(n);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		std::string us = FM[u];
	//	std::cout << "F[" << us << "]=" << F[u] << std::endl;
		if (us == T)
			break;
		for (int i = 0; i < us.size(); ++i)
		{
			char CH = us[i];
			std::string str = us;
			for (char ch = 65; ch <= 122; ++ch)
			{
				if (ch == CH)
					continue;
				str[i] = ch;
			//	if (str == T) printf("%d!\n", us.size());
				if (s[us.size()].find(str) != s[us.size()].end())
				{
					if (!M.count(str))
					{
						M[str] = ++n;
						F[n] = F[u] + 1;
						L[n] = u;
						FM[n] = str;
						Q.push(n);
					}
				}
			}
		}
	}
	if (!M.count(T))
	{
		puts("���ݲ����ڣ�");
		return 0;
	}
	int id = M[T];
	int u = id;
	for (int i = 1; i <= F[id]; ++i)
	{
		A[i] = u;
		u = L[u];
	}
	puts("����Ϊ��");
	std::cout << S;
	for (int i = F[id]; i; --i)
		std::cout << "->" << FM[A[i]];
	return 0;
}