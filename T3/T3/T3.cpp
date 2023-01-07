#include"Graph.h"
#include<iostream>
Graph G;
int n,R,ans,now;

void DFS(Graph &G, int u, int down, int up,int fa)
{
	if (u < down) down = u;
	if (u > up) up = u;
	if (down > now || up < now)
		return;
	if (u != now && (up == u && down == now || up == now && down == u))
		++ans;
	for (auto *k = G.V[u].head; k != NULL; k = k->next)
		if(k->to != fa) 
			DFS(G, k->to, down, up,u);
}

int main()
{
	std::cin >> n;
	CreateGraph(G, n, n - 1);
	for (int i = 1; i <= n; ++i)
	{
		int fa; std::cin >> fa;
		if (!fa) R = i;
		else AddEdge(G, fa, i), AddEdge(G, i, fa);
	}
	for (int i = 1; i <= n; ++i)
		now = i, DFS(G, i, 0x3f3f3f3f, 0,0);
	std::cout << (ans >> 1);
	DestroyGraph(G);
	return 0;
}