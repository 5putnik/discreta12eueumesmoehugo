#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Tipo que descreve as caracteristicas da Flecha */
typedef struct flecha_st
{
    unsigned de;
    unsigned para;
    unsigned tk;
    struct flecha_st * prox;
}flecha;

/* Tipo que descreve as caracteristicas dos Lugares */
typedef struct lugar_st
{
    unsigned pos;
    unsigned qtd;
    struct lugar_st * prox;
}lugar;

/* Descricao da rede de Petri sem as transicoes */ 
typedef struct petri_st
{
    unsigned total_l,
             total_t;
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

lugar *buscarLugarQtd(lugar *cabeca, unsigned x);
lugar *buscarLugarPos(lugar *cabeca, unsigned x);
lugar *anteriorLugar(lugar *cabeca, lugar *r);
void inserirLugar(lugar **cabeca, unsigned i, unsigned x);
void removerLugar(lugar **cabeca, lugar *r);
void imprimirLugar(lugar *cabeca);

flecha *buscarFlechaAnd(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);
flecha *buscarFlechaOr(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);
flecha *buscarFlechaDe(flecha *cabeca, unsigned x);
flecha *buscarFlechaPara(flecha *cabeca, unsigned x);
flecha *buscarFlechaTk(flecha *cabeca, unsigned x);
flecha *anteriorFlecha(flecha *cabeca, flecha *r);
void inserirFlecha(flecha **cabeca, unsigned xde, unsigned xpara, unsigned xtk);
void removerFlecha(flecha **cabeca, flecha *r);
void imprimirFlecha(flecha *cabeca);
void inserirThread(l_thread **cabeca, pthread_t p);
void imprimirThread(l_thread *cabeca);
