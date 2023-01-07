#ifndef UNDIRECT_H
#define UNDIRECT_H

typedef struct ArcNode
{
	int point;
	ArcNode *next;
}ArcNode;

typedef struct
{
	ArcNode *Head;
	int A;
}VexNode;

typedef struct
{
	int n;
	VexNode *V;
}Graph;

void CreateGraph(Graph &G,int n)
{
	G.n = n;
	G.V = new VexNode[n + 1];
	for (int i = 1; i <= n; ++i)
		G.V[i].Head = NULL;
}

void AddEdge(Graph &G,int u, int v)
{
	ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
	p->point = v;
	p->next = G.V[u].Head;
	G.V[u].Head = p;
}

void DestroyGraph(Graph &G)
{
	delete[] G.V;
}
#endif