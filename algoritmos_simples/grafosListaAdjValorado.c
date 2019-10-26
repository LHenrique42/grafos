/*
	Autor: Hadamo Egito
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct vert
{
	int val,peso;
	struct vertice *prox;
}vertice;
//estrutura do grafo com num de vertices e arestas e lista de adj
typedef struct grafo
{
	int v,e;
	vertice *adj;
}Grafo;
//função para criar grafo, dado numero de vertices v
Grafo* criaGrafo(int v)
{
	Grafo *g = (Grafo*) malloc(sizeof(Grafo));
	if (g!=NULL)
	{
		g->v  = v;
		g->e = 0;
		g->adj = (vertice*)calloc(v,sizeof(vertice));
		//todas as adjacencias estarao vazias neste momento
		for (int i = 0; i <v; ++i)
		{
			g->adj[i].prox = NULL;
		}
	}
	return g;
}
//função para criar vertice dado valor do vertice v
vertice* novoVertice(int v, int peso)
{
	vertice *novo = (vertice*)malloc(sizeof(vertice));
	if(novo == NULL)
	{
		printf("Algo de errado não está certo, vertice não criado!\n");
	}else
	{
		novo -> val = v;
		novo -> peso = peso;
		novo -> prox = NULL;
	}
	return novo;
}
//função para criar aresta entre dois vertices distintos num grafo
void insereAresta(Grafo *g, int v1, int v2,int peso)
{
	if(v1!=v2)//se nao for laco
	{
		vertice *p = g->adj[v1].prox;
		while(p!=NULL)
		{
			if(p->val == v2) break; //verifica se o vertice ja esta ligado
			p = p->prox;
		}
		/*se terminou de percorrer lista e não achou ocorrencia
		do novo vertice, insere o vertice na lista
		so verifica uma vez pois se trata de grafo simples
		*/
		if(p==NULL)
		{
			//insere novo vertice na adj de v1
			vertice *novo = novoVertice(v2,peso);
			novo->prox = g -> adj[v1].prox;
			g->adj[v1].prox = novo;
			//incrementa num de arestas do grafo
			g->e++;
			// repete o processo para v2
			novo = novoVertice(v1,peso);
			novo->prox = g->adj[v2].prox;
			g->adj[v2].prox = novo;
		}
	}
}

void imprimeGrafo(Grafo *g)
{
	if(g!=NULL)
	{
		int i;
		vertice *w;
		printf("\nGrafo com %d vertices e %d arestas",g -> v, g -> e );
		for(i=0 ; i < g->v ; ++i)
		{
			printf("\nv%d ->",i);
			w = g -> adj[i].prox;
			while(w != NULL)
			{
				printf(" ( %d|%d )",w -> val,w->peso);
				w = w -> prox;
			}
			printf("¬");
		}
	}
}
//funcao que remove arestas de um grafo simples valorado entre dois vertices e retorna o grafo
Grafo *removerAresta(Grafo *g, int v, int w)
{
	//pega primeiro elem da lista de v
	vertice *p, *q = g->adj[v].prox;
	if(q != NULL)
	{
		//se elem nao for null, percorre lista até o fim ou até achar w como adj
		p = &g->adj[v];
		while(q!= NULL)
		{
			//achado w como adj, sai do laço, caso contrario continua percorrendo
			if(q->val == w )break;
			p = q;
			q = q -> prox;
		}
		//se nao chegou ate o final, achou o w, retire ele e diminui g->e
		if(q != NULL)
			{
				p -> prox = q-> prox;
				free(q);
				g -> e--;
			}
	}
	//repete o processo para w
	q = g->adj[w].prox;
	if(q != NULL)
	{
		p = &g->adj[v];
		while(q!= NULL)
		{
			if(q->val == v )break;
			p = q;
			q = q -> prox;
		}
		if(q != NULL)
		{
			p -> prox = q-> prox;
			free(q);
		}
	}
	return g;
}

