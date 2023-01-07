#ifndef GRAPH_H
#define GRAPH_H
typedef struct ArcNode
{
	int v;
	ArcNode *next;
}ArcNode;

typedef struct VexNode
{
	ArcNode *Head;
}VexNode;

typedef struct
{
	int vexnum;
	VexNode *V;
}Graph;

void CreateGraph(int n,Graph &G)
{
	G.vexnum = n;
	G.V = new VexNode[n+1];
	for (int i = 0; i <= n; ++i)
		G.V[i].Head = NULL;
}

void AddEdge(Graph &G,int u, int v)
{
	ArcNode *Arc = (ArcNode *)malloc(sizeof(ArcNode));
	Arc->v = v;
	Arc->next = G.V[u].Head;
	G.V[u].Head = Arc;
}

void DestroyGraph(Graph &G)
{
	for (int i = 1; i <= G.vexnum; ++i)
	{
		ArcNode *tmp;
		for (ArcNode *k = G.V[i].Head; k != NULL; k = tmp)
		{
			tmp = k->next;
			free(k);
		}
	}
	delete[] G.V;
}
#endif