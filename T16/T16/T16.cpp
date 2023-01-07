//城市巡游赛
#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include"UnDirect.h"
#define MAX_V 2010
#define MAX_I 12
int n,ans;
int F[MAX_V][15],dep[MAX_V];
int Low[MAX_V], DFN[MAX_V];
int Bel[MAX_V],Siz[MAX_V];
int Index;
int scc;
bool Instack[MAX_V];
int ind[MAX_V], dp[MAX_V];
Graph T, G,IG;

void DFS(Graph &G, int u, int fa)
{
	F[u][0] = fa; dep[u] = dep[fa] + 1;
	for (int i = 1; i <= MAX_I; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	for (ArcNode* k = G.V[u].Head; k != NULL; k = k->next)
	{
		int v = k->point;
		if (v == fa)
			continue;
		DFS(G, v, u);
	}
}

int LCA(int u, int v)
{
	if (dep[u] > dep[v])
		std::swap(u, v);
	int hu = dep[u], hv = dep[v];
	int tu = u, tv = v;
	for (int det = hv - hu, i = 0; det; det >>= 1, ++i)
	{
		if (det & 1)
			tv = F[tv][i];
	}
	if (tu == tv)
		return tu;
	for (int i = MAX_I; ~i; --i)
	{
		if (F[tu][i] == F[tv][i])
			continue;
		tu = F[tu][i];
		tv = F[tv][i];
	}
	return F[tu][0];
}

void Tarjan(Graph &G, int u,std::stack<int> &Stack)
{
	int v;
	Low[u] = DFN[u] = ++Index;
	Stack.push(u);
	Instack[u] = true;
	for (ArcNode* k = G.V[u].Head; k != NULL; k = k->next)
	{
		v = k->point;
		if (!DFN[v])
		{
			Tarjan(G, v, Stack);
			if (Low[u] > Low[v])
				Low[u] = Low[v];
		}
		else if (Instack[v] && Low[u] > DFN[v])
			Low[u] = DFN[v];
	}
	if (Low[u] == DFN[u])
	{
		++scc;
		do
		{
			v = Stack.top();
			Stack.pop();
			Instack[v] = false;
			Bel[v] = scc;
			++Siz[scc];
		} while (v != u);
	}
}

int main()
{
	std::cin >> n;
	CreateGraph(T, n);
	CreateGraph(G, n);
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		std::cin >> u >> v;
		AddEdge(T, u, v);
		AddEdge(T, v, u);
	}
	for (int i = 1; i <= n; ++i)
		std::cin >> T.V[i].A;
	DFS(T, 1, 0);
	for(int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (i == j)
				continue;
			int length = dep[i] + dep[j] - 2 * dep[LCA(i, j)];
			if (length == T.V[i].A)
				AddEdge(G, i, j);
		}
	std::stack<int> S;
	for (int i = 1; i <= n; ++i)
		if (!DFN[i])
			Tarjan(G, i, S);
	CreateGraph(IG, scc);
	for (int i = 1; i <= n; ++i)
	{
		for (ArcNode *k = G.V[i].Head; k != NULL; k = k->next)
		{
			int v = k->point;
			if (Bel[i] == Bel[v])
				continue;
			AddEdge(IG, Bel[i], Bel[v]);
			++ind[Bel[v]];
		}
	}
	std::queue<int> Q;
	for (int i = 1; i <= scc; ++i)
		if (!ind[i])
			Q.push(i);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		dp[u] += Siz[u];
		for (ArcNode *k = IG.V[u].Head; k != NULL; k = k->next)
		{
			int v = k->point;
			dp[v] = std::max(dp[v], dp[u]);
			--ind[v];
			if (!ind[v])
				Q.push(v);
		}
		ans = std::max(ans, dp[u]);
	}
	std::cout << ans;
	return 0;
}