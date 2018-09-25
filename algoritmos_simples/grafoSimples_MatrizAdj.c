/*
	As seguintes implementações não é para grafos
	valorados e/ou direcionados. Apenas grafos simples, implementados
	utilizanto matriz de adjacencias.

*/

/*
	TODO: Algoritimo PRIM
	FIXME: Verificar se funcoes estao tratando peso corretamente
*/
#include <stdlib.h>
#include <stdio.h>

#define INFINITO 9999999999;
// Estrutura para Grafo
typedef struct grafo
{
	int V;
	int E;
	int **adj;
	
} Grafo;

// Protótipos de funções

Grafo *criaGrafo(int );
int **alocaMatrizInt(int, int, int);
void insereAresta(Grafo *, int , int, int);
void removeAresta(Grafo *, int, int);
void imprimeGrafo(Grafo *);
int verificaAdjacencia(Grafo *, int, int);
int grauVertice(Grafo *, int);
void imprimeAdjacentes(Grafo *, int);
int verticeProx(Grafo *G, int v);
// Fim Protótipos

void main(int argc, int **argv)
{
	Grafo *G = criaGrafo(4);
	insereAresta(G, 0, 1, 3);
	insereAresta(G, 0, 2, 2);
	insereAresta(G, 0, 3, 4);
	insereAresta(G, 1, 2, 5);
	insereAresta(G, 1, 3, 7);
	insereAresta(G, 2, 1, 8);
	insereAresta(G, 2, 3, 1);
//	removeAresta(G, 2, 3);
	imprimeGrafo(G);
//	printf("%2d\n", verificaAdjacencia(G, 2, 3));
//	printf("%2d\n", verificaAdjacencia(G, 0, 1));
//	printf("%2d\n", grauVertice(G, 0));
//	imprimeAdjacentes(G, 0);
	puts("");
}

int verticeProx(Grafo *G, int v)
{
	if(G == NULL) return -1;
	int vertice = -1;
	int i = 0;
	for(i = 0; i < G->V; i++){
		if( i == v ) continue;
		if(G->adj[v][i] > 0 && vertice == -1) vertice = i;		 
		else if(G->adj[v][i] < G->adj[v][vertice]) vertice = i;		 
	}
	return vertice;
}

Grafo* prim(Grafo *G)
{
	// TODO: Terminando
	// Grafo a ser retornado
	Grafo *arvMin = criaGrafo(G->V);
	arvMin->E = G->V - 1;
	// vetor para armazenar vertices ja no grafo
	int vertices[G->V];
	int qtdVertices = 0;
	while(qtdVertices < G->V)
	{
		
	}
	
}

int **alocaMatrizInt(int m, int n, int valorInicial)
{
	int **matriz = (int **)malloc(m * sizeof(int *));
	for(int i = 0; i < n; i++) matriz[i] = (int *)malloc(n * sizeof(int ));
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++) matriz[i][j] = valorInicial;
	}
	return matriz;
}

Grafo *criaGrafo(int v)
{
	Grafo *G = (Grafo *)malloc(1 * sizeof(Grafo));
	G->V = v;
	G->E = 0;
	G->adj = alocaMatrizInt(v, v, 0);
	return G;
}

void insereAresta(Grafo *G, int v, int w, int weight)
{
	if(v != w && G->adj[v][w] == 0 && weight > 0)
	{
		G->adj[v][w] = weight;
		G->adj[w][v] = weight;
		G->E++;
	}
}

void removeAresta(Grafo *G, int v, int w)
{
	if(G->adj[v][w] == 1)
	{
		G->adj[v][w] = 0;
		G->adj[w][v] = 0;
		G->E--;
	}
}

void imprimeGrafo(Grafo *G)
{
	printf("Legenda\nVertice X: A(Vertice, Peso).\n\n");
	for(int v = 0; v < G->V; v++)
	{
		printf("Vertice %2d: ", v);
		for(int w = 0; w < G->V; w++)
		{
			if(G->adj[v][w] > 0)
				printf("(%d, %d) ", w, G->adj[v][w]);
		}
		puts("");
	}
}

int verificaAdjacencia(Grafo *G, int v, int w)
{
	if(G == NULL) return 0;
	if(G->adj[v][w] == 1 && G->adj[w][v] == 1)
		return 1;
	return 0;
}

int grauVertice(Grafo *G, int v)
{
	if(G == NULL) return 0;
	int grau = 0;
	for(int i = 0; i < G->V; i++) grau += G->adj[v][i];
	return grau;
}

void imprimeAdjacentes(Grafo *G, int v)
{
	printf("%2d:", v);
	for(int i = 0; i < G->V; i++)
	{
		if(G->adj[v][i] == 1) printf(" %2d", i);
	}
}