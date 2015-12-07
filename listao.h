#include <stdlib.h>

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
    int qtd;
    struct lugar_st * prox;
}lugar;

/* Descricao da rede de Petri sem as transicoes */ 
typedef struct petri_st
{
    lugar l;
    flecha lt;
    flecha tl;
}petri_t;

lugar *buscarLugar(lugar *cabeca, int x);
void inserirLugar(lugar **cabeca, int x);
void removerLugar(lugar **cabeca, lugar *r);
flecha *buscarFlechaAnd(flecha *cabeca, int xde, int xpara, int xtk);
flecha *buscarFlechaOr(flecha *cabeca, int xde, int xpara, int xtk);
