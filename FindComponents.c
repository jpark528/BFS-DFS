/*********************************************************************************
*Juyeon Park, jpark528
* 2019 Summer CMPS101 PA4
* FindComponents.c
* Print Graph.c's output
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
//#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int len, discover, finish, i =0;
   FILE *in, *out;
   List L = newList();
   Graph G=NULL;
   //char tokenlist[MAX_LEN];
   //char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   if( fscanf(in, " %d", &len) != 1 ){
      exit(1);
   }
   G = newGraph(len);
   for(i=1; i<=len; i++) {
	   append(L, i);
   }

   // read graph edges and build graph
   i=2;
   if( fscanf(in, " %d %d", &discover, &finish) != 2 ){
      exit(1);
   }
   while( discover!= 0 && finish != 0 ){
      addArc(G, discover, finish);
      i++;
      if( fscanf(in, " %d %d", &discover, &finish) != 2 ){
         exit(1);
      }
   }
	
	DFS(G,L);
	Graph Transpose = transpose(G);
	DFS(Transpose,L);
	moveFront(L);
	// print adjacency list representation of G 
   fprintf(out, "\n");
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
	// count the number of strong components in G 
	List* C;
   int count = 0;
   while(index(L)>=0) {
      if( getParent(Transpose, get(L))==NIL ){
		  count++;
	  }
	  moveNext(L);
   }

   // allocate an array of Lists to store the strong components
   C = calloc(count, sizeof(List));
   for(int i=0; i<count; i++) {
      C[i] = newList();
   }

   // assemble Lists representing the strong components
   i = count;
   for(moveFront(L); index(L)>=0; moveNext(L)){
      int u = get(L);
      if(getParent(Transpose,u)==NIL) i--;
	  if(i == count) break;
      append(C[i], u); // or prepend(C[i], u)
   }
   
   fprintf(out, "\nG contains %d strongly connected components:", count);
	//C = calloc(count, sizeof(List));
   // print out the strong components
   for(i=0; i<count; i++){
      fprintf(out, "\nComponent %d: ", i+1);
      printList(out, C[i]);
   }
    fprintf(out, "\n");

   // free all heap memory
   for(i=0; i<count; i++) {
      freeList(&C[i]);
   }
   
   freeGraph(&Transpose);
   freeGraph(&G);
   free(C);
   freeList(&L);
   fclose(in);
   fclose(out);
   return(0);
}