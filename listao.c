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
    lugar *pl = cabeca;
    lugar *plant = NULL;
    
    while(pl != NULL)
    {
        plant -> pl;
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
