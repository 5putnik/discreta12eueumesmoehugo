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

lugar *buscarLugarQtdProx(lugar *cabeca, unsigned x)
{
    lugar *pl = cabeca;
    pl = pl -> prox;

    while(pl != NULL)
    {
        if(pl -> qtd == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

lugar *buscarLugarPosProx(lugar *cabeca, unsigned x)
{
    lugar *pl = cabeca;
    pl = pl -> prox;

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

void inserirLugar(lugar **cabeca, unsigned i, unsigned x, int b)
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
    pl -> isBusy = b;
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

flecha *buscarFlechaDeProx(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    pl = pl -> prox; 

    while(pl != NULL)
    {
        if(pl -> de == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

flecha *buscarFlechaParaProx(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    pl = pl -> prox;

    while(pl != NULL)
    {
        if(pl -> para == x)
            return pl;
        pl = pl -> prox;
    }
    return NULL;
}

flecha *buscarFlechaTkProx(flecha *cabeca, unsigned x)
{
    flecha *pl = cabeca;
    pl = pl -> prox;

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
        printf("L%u(%u) ",p->pos, p->qtd);
        if(p->isBusy)
            printf("(OCUPADO)\n");
        else
            printf("(LIVRE)\n");
        p = (p->prox);
    }
    return;
}

void inserirDados(dados **cabeca, unsigned x)
{
    dados *pl = *cabeca;
    dados *plant = NULL;

    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
    }

    pl = malloc(sizeof(dados));
    pl -> pos = x;
    pl -> prox = NULL;

    if(plant != NULL)
        plant -> prox = pl;
    else
        *cabeca = pl;
    return;
}

void limparDados(dados **cabeca)
{
    dados *pl = *cabeca;
    dados *plant = NULL;

    while(pl != NULL)
    {
        plant = pl;
        pl = pl -> prox;
        free(plant);
    }

    return;
}

float lcos(float x1, float y1, float x2, float y2)
{
    if(x1==0 && x2 == 0 && y1 == 0 && y2 == 0)
        return ~0;
    return ((x2-x1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

float lsin(float x1, float y1, float x2, float y2)
{
    if(x1==0 && x2 == 0 && y1 == 0 && y2 == 0)
        return ~0;
    return ((y2-y1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

void incrementaTrans(conta_trans **cabeca, unsigned pos)
{
    conta_trans *pl = *cabeca;
    conta_trans *plant = NULL;

    while(pl != NULL)
    {
        plant = pl;
        if(pl->pos == pos)
            break;
        pl = pl->prox;
    }


    if(pl == NULL) /* Se contador de transicao nao existe, cria */
    {
        pl = malloc(sizeof(lugar));
        pl->pos = pos;
        pl->x = 1;
        pl->prox = NULL;

        if(plant != NULL)
            plant -> prox = pl;
        else
            *cabeca = pl;
    }
    else /* Caso contrario, incrementa um */
        pl->x++;
}
