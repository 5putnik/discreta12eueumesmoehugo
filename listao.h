#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

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

/* Lista de posicoes a serem passadas */
typedef struct passa_dados_st
{
    unsigned pos;
    struct passa_dados_st *prox;
}dados;

lugar *buscarLugarQtd(lugar *cabeca, unsigned x);
lugar *buscarLugarPos(lugar *cabeca, unsigned x);
lugar *buscarLugarQtdProx(lugar *cabeca, unsigned x);
lugar *buscarLugarPosProx(lugar *cabeca, unsigned x);
lugar *anteriorLugar(lugar *cabeca, lugar *r);
void inserirLugar(lugar **cabeca, unsigned i, unsigned x);
void removerLugar(lugar **cabeca, lugar *r);
void imprimirLugar(lugar *cabeca);

flecha *buscarFlechaAnd(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);
flecha *buscarFlechaOr(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);
flecha *buscarFlechaDe(flecha *cabeca, unsigned x);
flecha *buscarFlechaPara(flecha *cabeca, unsigned x);
flecha *buscarFlechaTk(flecha *cabeca, unsigned x);
flecha *buscarFlechaDeProx(flecha *cabeca, unsigned x);
flecha *buscarFlechaParaProx(flecha *cabeca, unsigned x);
flecha *buscarFlechaTkProx(flecha *cabeca, unsigned x);
flecha *anteriorFlecha(flecha *cabeca, flecha *r);
void inserirFlecha(flecha **cabeca, unsigned xde, unsigned xpara, unsigned xtk);
void removerFlecha(flecha **cabeca, flecha *r);
void imprimirFlechaLT(flecha *cabeca);
void imprimirFlechaTL(flecha *cabeca);
void inserirThread(l_thread **cabeca, pthread_t p);
void imprimirThread(l_thread *cabeca);

void inserirDados(dados **cabeca, unsigned x);
void limparDados(dados **cabeca);

float arctan(float x1, float y1, float x2, float y2);
