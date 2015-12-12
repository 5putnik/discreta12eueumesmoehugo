#include "listao.h"

lugar *buscarLugarQtd(lugar *cabeca, unsigned x)
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

lugar *buscarLugarPos(lugar *cabeca, unsigned x)
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

lugar *anteriorLugar(lugar *cabeca, lugar *r)
{
    lugar *pl=cabeca, *plant=NULL;    
    if(r==NULL)
        return NULL;
    while(pl!=NULL && pl!=r)
    {
        plant=pl;
        pl=pl->prox;
    }

    return plant;
}

void inserirLugar(lugar **cabeca, unsigned i, unsigned x)
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

flecha *buscarFlechaAnd(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk)
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

flecha *buscarFlechaOr(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk)
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

flecha *buscarFlechaDe(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    while(pl != NULL)
    {
        if(pl -> de == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

flecha *buscarFlechaPara(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    while(pl != NULL)
    {
        if(pl -> para == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

flecha *buscarFlechaTk(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    while(pl != NULL)
    {
        if(pl -> tk == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}


flecha *anteriorFlecha(flecha *cabeca, flecha *r)
{
    flecha *pl=cabeca, *plant=NULL;    
    if(r==NULL)
        return NULL;
    while(pl!=NULL && pl!=r)
    {
        plant=pl;
        pl=pl->prox;
    }

    return plant;
}

void inserirFlecha(flecha **cabeca, unsigned xde, unsigned xpara, unsigned xtk)
{
    flecha *pl = *cabeca;
    flecha *plant = NULL;
    
    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }
    
    pl = malloc(sizeof(flecha));
    pl -> de = xde;
    pl -> para = xpara;
    pl -> tk = xtk;
    pl -> prox = NULL;
    
    if(plant != NULL)
        plant -> prox = pl;
    else
        *cabeca = pl;
}

void removerFlecha(flecha **cabeca, flecha *r)
{
    flecha *pl = *cabeca;
    flecha *plant = NULL;

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

void inserirThread(l_thread **cabeca, pthread_t p)
{
    l_thread *pl = *cabeca;
    l_thread *plant = NULL;
    
    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }
    
    pl = malloc(sizeof(l_thread));
    pl -> thr = p;
    pl -> prox = NULL;
    
    if(plant != NULL)
        plant -> prox = pl;
    else
        *cabeca = pl;
}

void imprimirFlechaLT(flecha *cabeca)
{
    flecha *p = cabeca;
    while(p != NULL)
    {
        printf("L%u ---(%u)---> T%u\n",p->de, p->tk, p->para);
        p = (p->prox);
    }
    return;
}

void imprimirFlechaTL(flecha *cabeca)
{
    flecha *p = cabeca;
    while(p != NULL)
    {
        printf("T%u ---(%u)---> L%u\n",p->de, p->tk, p->para);
        p = (p->prox);
    }
    return;
}

void imprimirThread(l_thread *cabeca)
{
    l_thread *p = cabeca;
    while(p != NULL)
    {
        printf("Thread: %p\n",&(p->thr));
        p = (p->prox);
    }
    return;
}

void imprimirLugar(lugar *cabeca)
{
    lugar *p = cabeca;
    while(p != NULL)
    {
        printf("L%u(%u)\n",p->pos, p->qtd);
        p = (p->prox);
    }
    return;
}
