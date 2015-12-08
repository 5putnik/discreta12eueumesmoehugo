#include "listao.h"

lugar *buscarLugarQtd(lugar *cabeca, int x)
{
    lugar *pl = cabeca;
    while(pl != NULL)
    {
        if(pl -> qtd == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

lugar *buscarLugarPos(lugar *cabeca, int x)
{
    lugar *pl = cabeca;
    while(pl != NULL)
    {
        if(pl -> pos == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

void inserirLugar(lugar **cabeca, int i, int x)
{
    lugar *pl = *cabeca;
    lugar *plant = NULL;
    
    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }
    
    pl = malloc(sizeof(lugar));
    pl -> pos = i;
    pl -> qtd = x;
    pl -> prox = NULL;
    
    if(plant != NULL)
        plant -> prox = pl;
    else
        *cabeca = pl;
}

void removerLugar(lugar **cabeca, lugar *r)
{
    lugar *pl = *cabeca;
    lugar *plant = NULL;

    if(r == NULL)
        return;
    
    while(pl != NULL && pl != r)
    {
        plant = pl;
        pl = pl -> prox;
    }

    if(pl == NULL)
        return;
    if(plant != NULL)
        plant -> prox = pl -> prox;
    else 
        *cabeca = pl -> prox;
    
    free(pl);
    return;
}

flecha *buscarFlechaAnd(flecha *cabeca, int xde, int xpara, int xtk)
{
    flecha *pl = cabeca;
    while(pl != NULL)
    {
        if((pl -> de == xde) && (pl -> para == xpara) && (pl -> tk == xtk))
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

flecha *buscarFlechaOr(flecha *cabeca, int xde, int xpara, int xtk)
{
    flecha *pl = cabeca;
    while(pl != NULL)
    {
        if((pl -> de == xde) || (pl -> para == xpara) || (pl -> tk == xtk))
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

void inserirFlecha(flecha **cabeca, int xde, int xpara, int xtk)
{
    flecha *pl = *cabeca;
    flecha *plant = NULL;
    
    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }
    
    pl = malloc(sizeof(lugar));
    pl -> de = xde;
    pl -> para = xpara;
    pl -> tk = xtk;
    pl -> prox = NULL;
    
    if(plant != NULL)
        plant -> prox = pl;
    else
        *cabeca = pl;
}
