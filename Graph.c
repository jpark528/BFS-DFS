/*********************************************************************************
*Juyeon Park, jpark528
* 2019 Summer CMPS101 PA4
* Graph.c
* Graph ADT file
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define WHITE 0
#define BLACK 2
#define GRAY 1

typedef struct GraphObj{
	List* neighbor;
	int* color;
	int* parent;
	int* discover;
	int* finish;
	//int* distance;
	int order;
	int size;
	//int source;
	int time;
}GraphObj;

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbor = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
    //G->distance = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    //G->source = NIL;
	G->time = UNDEF;
	for(int i = 1; i <=n; i++){
		G->neighbor[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
		G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        //G->distance[i] = INF;
	}
	return G;
}
void freeGraph(Graph* pG){
	//Graph pointer = *pG;
	if(*pG != NULL && pG != NULL){
		for(int i = 1; i <= (*pG)->order; i++){
			freeList(&((*pG)->neighbor[i]));}


			free((*pG)->neighbor);
			free((*pG)->parent);
			//free((*pG)->distance);
			free((*pG)->color);
			free((*pG)->discover);
			free((*pG)->finish);
			free(*pG);
			*pG = NULL;

	}
}

/*** Access functions ***/
int getOrder(Graph G){
	if(G==NULL){
		exit(1);
	}
	else
		return G->order;
}
int getSize(Graph G){
	if(G==NULL){
		exit(1);
	}
	else
		return G->size;
}
/*
int getSource(Graph G){
	if(G==NULL){
		exit(1);
	}
	else
		return G->source;
}
*/
int getParent(Graph G, int u){
	if(G==NULL){
		exit(1);
	}
	if(u<=0 && u>getOrder(G)){
		exit(1);
	}
	else{
		return G->parent[u];
	}
}
int getDiscover(Graph G, int u){
	if(G == NULL){
		exit(1);
	}
	else{
		if(u<=0 && u>getOrder(G)){
			exit(1);
		}
	}
	return G->discover[u];

}
int getFinish(Graph G, int u){
	if(G == NULL){
		exit(1);
	}
	else{
		if(u<=0 && u>getOrder(G)){
			exit(1);
		}
	}
	return G->finish[u];
}
/*
int getDist(Graph G, int u){
	if(G==NULL){
		exit(1);
	}
	else if(G!=NULL){
		if(u<=0 && u>getOrder(G)){
			exit(1);
		}
		if(getSource(G)==NIL){
			return INF;
		}
	}
	return G->distance[u];
}

void getPath(List L, Graph G, int u){
	if(G==NULL || getSource(G)==NIL){
		exit(1);
	}
	else if(G!=NULL){
		if(u<=0 && u>getOrder(G)){
			exit(1);
		}
		if(u == getSource(G)){
			append(L,getSource(G));
		}
		else if(G->parent[u] == NIL){
			append(L,NIL);
		}
		else{
			getPath(L,G,G->parent[u]);
			append(L,u);
		}
	}
}
*/

void makeNull(Graph G){
	if(G==NULL){
		exit(1);
	}
	for(int i = 1; i <=getOrder(G); i++){
		clear(G->neighbor[i]);
	}
	G->size = 0;
}


void addEdge(Graph G, int u, int v){
	if(G==NULL){
		exit(1);
	}
	else if(G!=NULL){
		if((u<=0 && u>getOrder(G)) && (v<=0 && v>getOrder(G))){
			exit(1);
		}
		/*if(v<=0 && v>getOrder(G)){
			exit(1);
		}*/
	}
	addArc(G,u,v);
	addArc(G,v,u);
	(G->size)--;
}

void addArc(Graph G, int u, int v){
	List L;
	int n;
	n = G->order;
	L = G->neighbor[u];
	if(G==NULL){
		exit(1);
	}
	if((v <1 || v >n) && (u < 1 || u >n)){
		exit(1);
	}

	/*if(u < 1 || u >n){
		exit(1);
	}*/
	if(length(L) <=0){
		append(L,v);
	}
	else{
		moveFront(L);
		while(get(L) < v){
			moveNext(L);
			if(index(L) == -1){
				break;
			}
		}
		if(index(L) == -1){
			append(L,v);
		}
		else{
			insertBefore(L,v);
		}

	}
	(G->size)++;
}
void Visit(Graph G, List S, int x){
	List L;
	if(G == NULL || S == NULL){
		exit(1);
	}
	G->color[x] = GRAY;
	G->discover[x] = ++(G->time);
	L = G->neighbor[x];
	if(length(L) > 0){
		moveFront(L);
		while(index(L) != -1){
			int temp = get(L);
			if(G->color[temp] == WHITE){
				G->parent[temp] = x;
				Visit(G,S,temp);
			}
			moveNext(L);
		}
	}
	G->color[x] = BLACK;
	G->finish[x] = ++(G->time);
	prepend(S,x);
	/*
	int i;
	G->discover[get(S)] = (++time);
	G->color[get(S)] = GRAY;
	for(i = 1; i < (getOrder(G)+1); i++){
		while(length(S) > 0){
			int f = front(S);
			deleteFront(S);
			if(length(G->neighbor[f]) >0){
				moveFront(G->neighbor[f]);
			}
			while(index(S) != -1){
				if(G->color[get(G->neighbor[f])] == WHITE){
					G->parent[get(G->neighbor[f])] = f;
					Visit(G,get(G->neighbor[f]));
					append(S,(get(G->neighbor[f])));
				}
				moveNext(G->neighbor[f]);
			}
			G->color[f] = BLACK;

		}
		freeList(&S);
	}
*/
}



void DFS(Graph G, List S){
	//S = newList();
	if(G == NULL || S == NULL){
		exit(1);
	}
	//int time;
	int number = G->order;
	if(length(S) != number){
		exit(1);
	}
	else{
		for(int i = 1; i <= getOrder(G); i++){
			G->parent[i] = NIL;
			G->color[i] = WHITE;
			G->discover[i] = UNDEF;
			G->finish[i] = UNDEF;
		}
		//int time = 0;
		//G->source = NIL;
		G->time = 0;
		moveFront(S);
		while(index(S) != -1){
			int x = get(S);
			if(G->color[get(S)] == WHITE){
				Visit(G,S,x);
			}
			moveNext(S);
		}
		for(int i = 1; i <= getOrder(G); i++){
			deleteBack(S);
		}
	}
	//freeList(&S);
}
/*
void BFS(Graph G, int s){
	List L = newList();
	if(G==NULL){
		exit(1);
	}
	if(s<=0 && s>getOrder(G)){
		exit(1);
	}
	else {
		for(int i = 1; i <=getOrder(G); i++){
			G->parent[i] = NIL;
			G->distance[i] = INF;
			G->color[i] = WHITE;
		}
		G->source = s;
		G->color[s] = GRAY;
		G->distance[s] = 0;
		append(L,s);

		while(length(L) >0)
		{
			int f = front(L);
			deleteFront(L);

			// check length
			if(length(G->neighbor[f]) >0){
				moveFront(G->neighbor[f]);
			}

			while(index(G->neighbor[f]) != -1){
				if(G->color[get(G->neighbor[f])] == WHITE){
					G->color[get(G->neighbor[f])] = GRAY;
					G->distance[get(G->neighbor[f])] = G->distance[f] +1;
					G->parent[get(G->neighbor[f])] = f;
					append(L,(get(G->neighbor[f])));
				}
				moveNext(G->neighbor[f]);

			}
			G->color[f] = BLACK;
		}
		freeList(&L);
	}
}

*/
Graph transpose(Graph G){
	Graph Transpose = newGraph(getOrder(G));
	if(G==NULL){
		exit(1);
	}
	else{
		for(int i = 1; i <= getOrder(G); i++){

				moveFront(G->neighbor[i]);
				while(index(G->neighbor[i])>=0){
					addArc(Transpose,get(G->neighbor[i]),i);
					moveNext(G->neighbor[i]);
				}
			}

	}
	return Transpose;
}
Graph copyGraph(Graph G){
	Graph Copy = newGraph(getOrder(G));
	if(G == NULL){
		exit(1);
	}
	else{
		for(int i = 1; i <= getOrder(G); i++){

				moveFront(G->neighbor[i]);
				while(index(G->neighbor[i])>=0){
					addArc(Copy,i,get(G->neighbor[i]));
					moveNext(G->neighbor[i]);
				}

		}
	}
	return Copy;
}
void printGraph(FILE* out, Graph G){
	if(G==NULL){
		exit(1);
	}

	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		//moveFront(G->neighbor[i]);
		printList(out, G->neighbor[i]);
		//moveNext(G->neighbor[i]);
		fprintf(out, "\n");
	}

}
