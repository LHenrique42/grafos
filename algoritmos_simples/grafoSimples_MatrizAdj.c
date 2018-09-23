/*
	As seguintes implementações não é para grafos
	valorados e/ou direcionados. Apenas grafos simples, implementados
	utilizanto matriz de adjacencias.

*/

#include <stdlib.h>
#include <stdio.h>

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
void insereAresta(Grafo *, int , int);
void removeAresta(Grafo *, int, int);
void imprimeGrafo(Grafo *);
int verificaAdjacencia(Grafo *, int, int);
int grauVertice(Grafo *, int);
void imprimeAdjacentes(Grafo *, int);

// Fim Protótipos

void main(int argc, int **argv)
{
	Grafo *G = criaGrafo(4);
	insereAresta(G, 0, 1);
	insereAresta(G, 0, 2);
	insereAresta(G, 0, 3);
	insereAresta(G, 1, 2);
	insereAresta(G, 1, 3);
	insereAresta(G, 2, 1);
	insereAresta(G, 2, 3);
	removeAresta(G, 2, 3);
	imprimeGrafo(G);
	printf("%2d\n", verificaAdjacencia(G, 2, 3));
	printf("%2d\n", verificaAdjacencia(G, 0, 1));
	printf("%2d\n", grauVertice(G, 0));
	imprimeAdjacentes(G, 0);
	puts("");
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

void insereAresta(Grafo *G, int v, int w)
{
	if(v != w && G->adj[v][w] == 0)
	{
		G->adj[v][w] = 1;
		G->adj[w][v] = 1;
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
	for(int v = 0; v < G->V; v++)
	{
		printf("%2d:", v);
		for(int w = 0; w < G->V; w++)
		{
			if(G->adj[v][w] == 1)
				printf(" %2d", w);
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