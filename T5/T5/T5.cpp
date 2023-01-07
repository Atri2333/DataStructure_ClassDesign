#include<queue>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HufTree;

HufTree HT;

bool vis[150];
int C[150];
char H[150]; int RH[150],ccnt;
std::string Code[150];

char tag[6000000];

std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > Q;

void ReadIn()
{
	std::fstream FILE("source.txt", std::ios::in);
	std::string str;
	while (FILE.good())
	{
		std::getline(FILE, str);
		for (auto it = str.begin(); it != str.end(); ++it)
			++C[*it], vis[*it] = true;
		++C['\n'], vis['\n'] = true;
	}
	FILE.close();
}

void EnCode()
{
	std::fstream FILE("code.dat",std::ios::out | std::ios::binary);
	std::fstream SRC("source.txt", std::ios::in);
	std::string str;
	int len = 0;
	while (SRC.good())
	{
		std::getline(SRC, str);
		
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			for (auto it2 = Code[RH[*it]].begin(); it2 != Code[RH[*it]].end(); ++it2)
				tag[len++] = *it2;
		}
		if(SRC.good())
		for (auto it2 = Code[RH['\n']].begin(); it2 != Code[RH['\n']].end(); ++it2)
			tag[len++] = *it2;
	}
	for (auto it2 = Code[RH[128]].begin(); it2 != Code[RH[128]].end(); ++it2)
		tag[len++] = *it2;
	SRC.close();
	int l = 0;
	while (true)
	{
		unsigned char buf = 0;
		for (int i = l, j = 0; j < 8; ++i, ++j)
		{
			if(i < len)
				buf = (buf << 1) | (tag[i] - '0');
			else buf <<= 1;
		}
		FILE.write((char *)&buf, sizeof(buf));
		l += 8;
		if (l >= len)
			break;
	}
	FILE.close();
}

void DeCode()
{
	std::fstream FILE("code.dat", std::ios::in | std::ios::binary);
	std::fstream TGT("recode.txt", std::ios::out);
	int len = 0;

	while (!FILE.eof())
	{
		unsigned char t = 0;
		FILE.read((char *)&t, sizeof(unsigned char));
		if (FILE.fail())
			break;
		for (int i = 7; ~i; --i)
			tag[len++] = (((1<<i) & t) > 0) + '0';
		
	}
	std::string mod;
	std::string zero, one;
	zero.append("0");
	one.append("1");
	for (int i = 0; i < len; ++i)
	{
		bool end = false;
		if (tag[i] == '0')
			mod.append(zero);
		else
			mod.append(one);
		for(int j = 0; j < ccnt; ++j)
			if (Code[j] == mod)
			{
				if (j == RH[128])
				{
					end = true;
					break;
				}
				mod.clear();
				TGT << H[j];
				break;
			}
		if (end) break;
	}
	TGT.close();
	FILE.close();
}

void HufCode()
{
	HT = (HufTree)malloc(sizeof(HTNode) * 256);
	int cnt = 0;
	C[128] = 1; vis[128] = true; //128±íÊ¾½áÊø·ûºÅ
	while (!Q.empty()) Q.pop();
	for (int i = 0; i <= 128; ++i)
		if (vis[i])
		{
			HT[cnt].lchild = HT[cnt].rchild = -1;
			HT[cnt].weight = C[i];
			H[cnt] = i; RH[i] = cnt;
			Q.push(std::make_pair(C[i], cnt++));
		}
	ccnt = cnt;
	while (Q.size() > 1)
	{
		std::pair<int, int> a, b;
		a = Q.top(); Q.pop();
		b = Q.top(); Q.pop();
		HT[a.second].parent = HT[b.second].parent = cnt;
		HT[cnt].lchild = a.second;
		HT[cnt].rchild = b.second;
		HT[cnt].parent = -1;
		HT[cnt].weight = a.first + b.first;
		Q.push(std::make_pair(a.first + b.first, cnt++));
	}
	for (int i = 0; i < ccnt; ++i)
	{
		int s = 0;
		int c, f;
		for (c = i, f = HT[c].parent; f != -1; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				Code[i].append("0");
			else
				Code[i].append("1");
		}
		std::reverse(Code[i].begin(), Code[i].end());
		std::cout << H[i] << ":" << Code[i] << std::endl;
	}
	free(HT);
	EnCode();
}

int main()
{
	ReadIn();
	HufCode();
	DeCode();

	return 0;
}