#include<vector>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<string>
#include<fstream>
#include<cassert>
#include"Graph.h"
#define AtriKawaii 2333

std::map<std::string, int> M;
std::map<int, int> N;
std::vector<std::string> A[666];
std::vector<int> AA[666];
std::vector<int> B[6666];
std::string C[6666];

int _used,bus_cnt;

Graph G1, G2;

void ReadIn()
{
	std::fstream FILE("bus.txt", std::ios::in);
	std::string str,_str;
	while (std::getline(FILE, str))
	{
		int num = 0;
		++bus_cnt;
		auto it = str.begin();
		while (*it <= '9' && *it >= '0')
			num = num * 10 + *it++ - '0';
		N[bus_cnt] = num;
		int i = str.find(' '),j;
		while (str[i] == ' ') ++i;
		int _size = str.size();
		for (j = i + 1; j < _size; ++j)
		{
			if (str[j] != ',')
				continue;
			_str = str.substr(i, j - i);
			A[bus_cnt].push_back(_str);
			if (!M.count(_str))
				M[_str] = ++_used;
			AA[bus_cnt].push_back(M[_str]);
			C[M[_str]] = _str;
			B[M[_str]].push_back(bus_cnt);
			i = j + 1;
		}
		_str = str.substr(i, j - i);
		A[bus_cnt].push_back(_str);
		if (!M.count(_str))
			M[_str] = ++_used;
		AA[bus_cnt].push_back(M[_str]);
		C[M[_str]] = _str;
		B[M[_str]].push_back(bus_cnt);
	}
	FILE.close();
}

void CreateG1()
{
	std::fstream outputFile("G1.txt", std::ios::out);
	for (int i = 1; i <= bus_cnt; ++i)
	{
		for (int j = i + 1; j <= bus_cnt; ++j)
			for (auto it = AA[i].begin(); it < AA[i].end(); ++it)
			{
				auto it2 = std::find(AA[j].begin(), AA[j].end(), *it);
				if (it2 == AA[j].end())
					continue;
				outputFile << i << " " << j << std::endl;
				break;
			}
	}
	outputFile.close();
}

void CreateG11()
{
	std::fstream outputFile("G1.txt", std::ios::out);
	for (int i = 1; i <= bus_cnt; ++i)
	{
		for (int j = i + 1; j <= bus_cnt; ++j)
			for (auto p1:AA[i])
			{
				bool pd = false;
				for (auto p2 : AA[j])
				{
					if (p1 == p2)
					{
						outputFile << i << " " << j << std::endl;
						pd = true;
						break;
					}
				}
				if(pd)
					break;
			}
	}
	outputFile.close();
}

void InitGraph()
{
	std::fstream outputFile("G1.txt", std::ios::in);
	while (!outputFile.eof())
	{
		int u, v;
		outputFile >> u >> v;
		AddEdge(G1, u, v);
		AddEdge(G1, v, u);
		if (outputFile.fail())
			break;
	}
	CreateGraph(_used, G2);
	for (int i = 1; i <= bus_cnt; ++i)
	{
		for (int j = 0; j < A[i].size() - 1; ++j)
		{
			AddEdge(G2, M[A[i][j]], M[A[i][j + 1]]);
			AddEdge(G2, M[A[i][j + 1]], M[A[i][j]]);
		}
	}
}

void Solve1(std::string from,std::string to)
{
	if (!M.count(from))
	{
		puts("���󣺳����ز����ڣ�");
		return;
	}
	if (!M.count(to))
	{
		puts("����Ŀ�ĵز����ڣ�");
		return;
	}
	if (from == to)
	{
		puts("�����ؼ�ΪĿ�ĵأ������������ӳ����ǲ�����Ǯ������������vivo50(bushi");
		return;
	}
	bool *vis = new bool[bus_cnt + 1];
	int *dis = new int[bus_cnt + 1];
	int *F = new int[bus_cnt + 1];
	std::queue<int> Q;
	int des = -1;
	for (int i = 1; i <= bus_cnt; ++i)
	{
		vis[i] = false;
		dis[i] = 0x3f3f3f3f;
		if (std::find(A[i].begin(), A[i].end(), from) != A[i].end())
		{
			Q.push(i);
			vis[i] = true;
			dis[i] = F[i] = 0;
		}
	}
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if (std::find(A[u].begin(), A[u].end(), to) != A[u].end())
		{
			des = u;
			break;
		}
		for (ArcNode *k = G1.V[u].Head; k != NULL; k = k->next)
		{
			int v = k->v;
			if (vis[v])
				continue;
			vis[v] = true;
			dis[v] = dis[u] + 1;
			F[v] = u;
			Q.push(v);
		}
	}
	if (des == -1)
	{
		puts("δ�ҵ�·�ߣ�");
		delete[] vis;
		delete[] F;
		delete[] dis;
		return;
	}
	if (dis[des] == 0)
	{
		std::cout << "ֻ����� " << N[des] << " ·�������� " << from << " �� " << to << " ���ɣ����軻�ˣ�";
	}
	else
	{
		printf("�˳�·�����£���ת��%d�Σ���\n",dis[des]);
		int *cache = new int[dis[des] + 1];
		int u = des;
		int cnt = 0;
		while (u)
			cache[++cnt] = u,
			u = F[u];
		std::string nowSta = from;
		for (int i = cnt; i > 1; --i)
		{
			int a = cache[i], b = cache[i - 1];
			for (auto it = A[a].begin(); it < A[a].end(); ++it)
			{
				if (std::find(A[b].begin(), A[b].end(), *it) != A[b].end())
				{
					if (i == cnt)
						std::cout << "����";
					else 
						std::cout << "Ȼ��";
					std::cout << "�� " << nowSta << " ���� " << N[a] << " ·���������� " << *it << " �³���\n";
					nowSta = *it;
					break;
				}
			}
		}
		std::cout << "����� " << nowSta << " ���� " << N[cache[1]] << " ·���������� " << to << " �³���\n";
	}
	delete[] vis;
	delete[] F;
	delete[] dis;
}

void Solve2(std::string from,std::string to)
{
	if (!M.count(from))
	{
		puts("���󣺳����ز����ڣ�");
		return;
	}
	if (!M.count(to))
	{
		puts("����Ŀ�ĵز����ڣ�");
		return;
	}
	if (from == to)
	{
		puts("�����ؼ�ΪĿ�ĵأ������������ӳ����ǲ�����Ǯ������������vivo50(bushi");
		return;
	}
	int Dis[6666],f[6666];
	memset(Dis, 0x3f, sizeof Dis);
	Dis[M[from]] = 0; f[M[from]] = 0;
	std::queue<int> Q;
	Q.push(M[from]);
	while (!Q.empty())
	{
		int u = Q.front();
		if (u == M[to])
			break;
		Q.pop();
		for (auto *k = G2.V[u].Head; k != NULL; k = k->next)
		{
			int v = k->v;
			if (Dis[v] < 0x3f3f3f3f)
				continue;
			Dis[v] = Dis[u] + 1;
			f[v] = u;
			Q.push(v);
		}
	}
	if (Dis[M[to]] == 0x3f3f3f3f)
	{
		puts("δ�ҵ�·�ߣ�");
		return;
	}
	std::vector<int> W,Ans;
	Ans.push_back(0);
	for (int i = M[to]; i; i = f[i])
		W.push_back(i);
	std::reverse(W.begin(), W.end());
	int l = 0, r = W.size() - 1,ll,rr;
	while (l < W.size() - 1)
	{
		ll = l, rr = W.size() - 1;
		while (ll < rr)
		{
			int mid = ll + rr >> 1; ++mid;
			bool pd = false;
			for(auto it = B[W[l]].begin(); it != B[W[l]].end(); ++it)
				for(auto it2 = B[W[mid]].begin(); it2 != B[W[mid]].end(); ++it2)
					if (*it == *it2)
					{
						pd = true;
						break;
					}
			if (pd) ll = mid;
			else rr = mid - 1;
		}
		Ans.push_back(ll);
		l = ll;
	}
	for (int i = 0; i < Ans.size() - 1; ++i)
	{
		l = Ans[i], r = Ans[i + 1]; bool pd = false;
		for (auto it = B[W[l]].begin(); it != B[W[l]].end(); ++it)
		{
			for (auto it2 = B[W[r]].begin(); it2 != B[W[r]].end(); ++it2)
				if (*it == *it2)
				{
					pd = true;
					if (!i)
						printf("����");
					else if (W[r] == M[to])
						printf("���");
					else printf("Ȼ��");
					std::cout << "�� " << C[W[l]] << " ���� " << N[*it] << " ·���������� " << C[W[r]] << " �³�";
					if (W[r] == M[to]) puts("��");
					else puts("��");
					break;
				}
			if (pd) break;
		}
		assert(pd);
	}
	std::cout << "�ܾ���վ�㣺" << Dis[M[to]] + 1 << std::endl;
}

int main()
{
	ReadIn();
	CreateGraph(bus_cnt, G1);
//	CreateG11(); return 0;
	InitGraph();
	
	while (AtriKawaii)
	{
		system("cls");
		std::cout << "��ѡ��\n����ת������·��[1]\n���پ���վ��·��[2]\n�˳�[3]\n���������(1-3)��";
		char _id[AtriKawaii];
		std::cin.getline(_id, AtriKawaii - 1);
		if (std::strlen(_id) == 1)
		{
			if (_id[0] == '1')
			{
				std::string to, from;
				std::cout << "��������أ�\n";
				std::cin >> from;
				std::cout << "����Ŀ�ĵأ�\n";
				std::cin >> to;
				Solve1(from, to);
			}
			else if (_id[0] == '2')
			{
				std::string to, from;
				std::cout << "��������أ�\n";
				std::cin >> from;
				std::cout << "����Ŀ�ĵأ�\n";
				std::cin >> to;
				Solve2(from, to);
			}
			else if (_id[0] == '3')
			{
				break;
			}
			else 
			{
			//	puts("�������ʲô���ˣ�");
			}
		}
		else
		{
			//puts("�������ʲô���ˣ�");
		}
		system("pause");
	}
	DestroyGraph(G1);
	DestroyGraph(G2);

	return 0;
}