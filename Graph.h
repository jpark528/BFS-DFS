/*********************************************************************************
*Juyeon Park, jpark528
* 2019 Summer CMPS101 PA4
* Graph.h
* Header file of Graph.c
*********************************************************************************/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
//#define INF -1
#define UNDEF -1
#define NIL 0
#include "List.h"

typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
//int getDist(Graph G, int u);
//void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
//void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
//void BFS(Graph G, int s);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
