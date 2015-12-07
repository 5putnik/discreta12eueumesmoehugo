#include "listao.h"

lugar *buscarLugar(lugar *cabeca, int x)
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

void inserirLugar(lugar **cabeca, int x)
{
    lugar *pl = *cabeca;
    lugar *plant = NULL;
    
    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }
    
    pl = malloc(sizeof(lugar));
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

flecha *buscarLugar(flecha *cabeca, int xde, intxpara, int xtk)
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

flecha *buscarLugar(flecha *cabeca, int xde, intxpara, int xtk)
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

