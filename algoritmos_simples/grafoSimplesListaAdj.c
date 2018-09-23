#include <stdio.h>
#include <stdlib.h>

typedef struct vertice
{
    int no;
    struct vertice *prox;
} Vertice;

typedef struct grafo
{
    int V;
    int E;
    Vertice *adj;
} Grafo;

Grafo *criaGrafo(int v);
Vertice *novoVertice(int x);
void insereAresta(Grafo *G, int v, int w);
void removeAresta(Grafo *G, int v, int w);
void imprimeGrafo(Grafo *G);
int grauVertice(Grafo *G, int v);
int GrafosGrausVerticesIguais(Grafo *A, Grafo *B);


void main()
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
    printf("%2d\n", grauVertice(G, 0));

    Grafo *A = criaGrafo(4);
    insereAresta(A, 0, 1);
	insereAresta(A, 0, 2);
	insereAresta(A, 0, 3);
	insereAresta(A, 1, 2);
	insereAresta(A, 1, 3);
	insereAresta(A, 2, 1);
	insereAresta(A, 2, 3);
	removeAresta(A, 2, 3);

    printf("%2d\n", GrafosGrausVerticesIguais(G, A));
}

Grafo *criaGrafo(int v)
{
    Grafo *G = (Grafo  *)malloc(sizeof(Grafo));
    G->V = v;
    G->E = 0;
    G->adj = (Vertice *)calloc(v, sizeof(Vertice));
    return G;
}

Vertice *novoVertice(int x)
{
    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
    if(novo == NULL ) {printf("ERRO!\n"); exit(1);}
    novo->no = x;
    novo->prox = NULL;
    return novo;
}

void insereAresta(Grafo *G, int v, int w)
{
    if( v != w )
    {
        Vertice *p = G->adj[v].prox;
        while( p != NULL )
        {
            if( p->no == w ) break;
            p = p->prox;
        }
        if( p == NULL ) // nao existe aresta (v,w)
        {
            Vertice *novo = novoVertice(w);
            novo -> prox = G->adj[v].prox;
            G->adj[v].prox = novo;
            G->E++;
        }
        p = G->adj[w].prox;
        while( p != NULL )
        {
            if( p -> no == v ) break;
            p = p->prox;
        }
        if(p == NULL) // nao existe aresta (w,v)
        {
            Vertice *novo = novoVertice(v);
            novo -> prox = G->adj[w].prox;
            G->adj[w].prox = novo;
            G->E++;           
        }
    }
}

void removeAresta(Grafo *G, int v, int w)
{
    if(G->adj[v].prox != NULL)
    {
        Vertice *aux = G->adj[v].prox;
        Vertice *preaux = &(G->adj[v]);
        while(aux != NULL)
        {
            if(aux -> no == w) break;
            preaux = aux;
            aux = aux->prox;
        }
        if(aux != NULL)
        {
            G->E--;
            preaux -> prox = aux->prox;
            free(aux);
        }
    }
    if(G->adj[w].prox != NULL)
    {
        Vertice *aux = G->adj[w].prox;
        Vertice *preaux = &(G->adj[w]);
        while(aux != NULL)
        {
            if(aux -> no == v) break;
            preaux = aux;
            aux = aux->prox;
        }
        if(aux != NULL)
        {
            G->E--;
            preaux -> prox = aux->prox;
            free(aux);
        }        
    }
}

void imprimeGrafo(Grafo *G)
{
    if(G ==  NULL) exit(1);
    Vertice *aux = NULL;
    for(int i = 0; i < G->V; i++)
    {
        aux = G->adj[i].prox;
        printf("%2d:", i);
        while( aux != NULL )
        {
            printf(" %2d", aux->no);
            aux = aux -> prox;
        }
        puts("");
    }
}

int grauVertice(Grafo *G, int v)
{
    if(G == NULL) return 0;
    Vertice *aux = G->adj[v].prox;
    int grau = 0;
    while(aux != NULL)
    {
        aux = aux -> prox;
        grau++;
    }
    return grau;
}

int GrafosGrausVerticesIguais(Grafo *A, Grafo *B)
{
    if(A->V != B->V) return 0;
    for( int i = 0; i < A->V; i++)
    {
        if( grauVertice(A, i) != grauVertice(B, i)) return 0;
    }
    return 1;
}