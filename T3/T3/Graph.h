#ifndef GRAPH_H
#define GRAPH_H
#define MAX_V 2010
#define OK 1
#define ERROR 0
#include<iostream>

typedef int Status;
typedef struct ArcNode
{
	int to;
	ArcNode *next;
}ArcNode;

typedef struct
{
	ArcNode *head;
}VexNode;

typedef struct
{
	VexNode *V;
	int n, m;
}Graph;

Status CreateGraph(Graph &G, int n, int m)
{
	G.n = n;
	G.m = m;
	G.V = new VexNode[n + 1];
	if (G.V == NULL)
		return ERROR;
	for (int i = 0; i <= n; ++i)
		G.V[i].head = NULL;
	return OK;
}

Status AddEdge(Graph &G, int u, int v)
{
	ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
	if (p == NULL)
		return ERROR;
	p->to = v;
	p->next = G.V[u].head;
	G.V[u].head = p;
	return OK;
}

Status DestroyGraph(Graph &G)
{
	delete[] G.V;
	return OK;
}

#endif // !GTAPH_H
