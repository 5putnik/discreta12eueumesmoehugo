#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Tipo que descreve as caracteristicas da Flecha */
typedef struct flecha_st
{
    int de;
    int para;
    int tk;
    struct flecha_st * prox;
}flecha;

/* Tipo que descreve as caracteristicas dos Lugares */
typedef struct lugar_st
{
    int pos;
    int qtd;
    struct lugar_st * prox;
}lugar;

/* Descricao da rede de Petri sem as transicoes */ 
typedef struct petri_st
{
    lugar *l;
    flecha *lt;
    flecha *tl;
}petri_t;

/* Lista de threads */
typedef struct thread_st
{
    pthread_t thr;
    struct thread_st *prox;
}l_thread;

lugar *buscarLugarQtd(lugar *cabeca, int x);
lugar *buscarLugarPos(lugar *cabeca, int x);
lugar *anteriorLugar(lugar *cabeca, lugar *r);
void inserirLugar(lugar **cabeca, int i, int x);
void removerLugar(lugar **cabeca, lugar *r);
void imprimirLugar(lugar *cabeca);

flecha *buscarFlechaAnd(flecha *cabeca, int xde, int xpara, int xtk);
flecha *buscarFlechaOr(flecha *cabeca, int xde, int xpara, int xtk);
flecha *buscarFlechaDe(flecha *cabeca, int x);
flecha *buscarFlechaPara(flecha *cabeca, int x);
flecha *buscarFlechaTk(flecha *cabeca, int x);
void inserirFlecha(flecha **cabeca, int xde, int xpara, int xtk);
void removerFlecha(flecha **cabeca, flecha *r);
void imprimirFlecha(flecha *cabeca);
void inserirThread(l_thread **cabeca, pthread_t p);
void imprimirThread(l_thread *cabeca);
