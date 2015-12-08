/* ************************************************************************ *
 *    ex3.c, v0.1                                                           *
 *    Programa feito para simular uma rede de petri dado um arquivo de      *
 *    texto como entrada, utilizando paralelismo com threads e gerando uma  *
 *    imagem descritiva da rede                                             *
 *                                                                          *
 *    Copyright (C) 2015                                                    *
 *    Hugo Albuquerque de Fonseca                                           *
 *    Otacilio Saraiva Maia Neto                                            *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *    To contact the author, please write to:                               *
 *                                                                          *
 *    Hugo Albuquerque de Fonseca <hugoalbuquerque0@gmail.com>              *
 *    Phone: 55 (081) 9292-0944                                             *
 *                                                                          *
 *    Otacilio Saraiva Maia Neto <otacilio.n97@gmail.com>                   *
 *    Phone: 55 (819) 9959-7078                                             *                       
 *                                                                          *
 *                                                                          *       
 ************************************************************************** *
 *                                                
 */


/**
 * \file ex12.c
 * \brief programa que simula rede de petri. 
 * \author Hugo Albuquerque de Fonsêca <<hugoalbuquerque0@gmail.com>>
 * \author Otacilio Saraiva Maia Neto <<otacilio.n97@gmail.com>>
 * \version 0.2
 * \date 2015-12-02
 */
/**
 * \
 * @{ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listao.h"

#ifndef VMAX
#define VMAX 1000 /**< Tamanho maximo dos vetores */
#endif

#ifndef ITER
#define ITER 1000 /**< Total de iteracoes */
#endif

#ifndef PCT
#define PCT 50 /**< Porcentagem de chance de ativacao de cada transicao */
#endif

#ifndef DEBUG
#define DEBUG 0 /**< Ativa modo de debug */
#endif

void rlist(unsigned v[VMAX], unsigned n);
void printv(unsigned v[VMAX], unsigned n);
void printm(unsigned x[VMAX][VMAX], unsigned n, unsigned m);
void transicao(void *arg);
void desenha_rede(petri_t rede, const char *fname);

int main(void)
{
    unsigned t = time(NULL);                    /* Temporizador da simulacao */
    unsigned qt,                                /* Quantidade de transicoes */
             ql;                                /* Quantidade de lugares */
    unsigned i,                                 /* Variavel geral de laco */
             j,                                 /* Variavel geral de laco */
             k,                                 /* Variavel geral de laco */
             it_escape,                         /* Flag condicional da iteracao */
             lctk,                              /* Variavel temporaria de insercao */
             alt,                               /* Total de arcos lugar -> transicao */
             atl;                               /* Total de arcos transicao -> lugar */
    petri_t *rede = malloc(sizeof(petri_t));    /* Rede de petri propriamente dita */
    rede -> l = NULL;
    rede -> tl = NULL;
    rede -> lt = NULL;
    /* Parametros a serem passados para a funcao de transicao */
    struct passa_dados_st
    {
        petri_t net;
        int pos;
    }dados;

    srand(time(NULL));
    /* Escaneando a quantidade de lugares */
    scanf("%u",&ql);
    /* Escaneando a quantidade de transicoes */
    scanf("%u",&qt); 
    if(DEBUG) printf("Quantidade de lugares: %u\n",ql);
    /*if(ql>VMAX)
    {
        printf("Erro linha 1: quantidade de lugares acima do maximo. \n");
        return -1;
    }*/
    if(DEBUG) printf("Quantidade de transicoes: %u\n",qt);
    /*if(qt>VMAX)
    {
        printf("Erro linha 2: quantidade de transicoes acima do maximo. \n");
        return -1;
    }*/
    /* Escaneando total de lugares com pelo menos um token */
    scanf("%u",&lctk);
    /* Escaneando total de arcos lugar -> transicao */
    scanf("%u",&alt);
    /* Escaneando total de arcos transicao -> lugar */
    scanf("%u",&atl);

    for(k=0;k<lctk;k++)
    {
        scanf("%u %u", &i, &j);
        if(i>=ql)
        {
            printf("Erro linha %u: lugar maior que o definido. \n", 6+k);
            return -1;
        }
        inserirLugar(&(rede->l), i, j);
        if(DEBUG) printf("li lugar L%u = %u tokens\n",i, j);
    }
    for(k=0;k<alt;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=ql||j>=qt)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k);
            return -1;
        }
        if(DEBUG) printf("li flecha L%u---(%u)--->T%u\n",i, lctk, j);
        inserirFlecha(&(rede->lt), i, j, lctk);
        /* lt[i][j]= lctk; <<<<< SUBSTITUIR */
    }
    for(k=0;k<atl;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=qt||j>=ql)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k+alt);
            return -1;
        }
        if(DEBUG) printf("li flecha T%u---(%u)--->L%u\n",i, lctk, j);
        inserirFlecha(&(rede->tl), i, j, lctk);
        /* tl[i][j] = lctk; <<<<<< SUBSTITUIR */
    }
    lugar *pl = rede->l;
    if(DEBUG) while(pl != NULL)
    {
        printf("inseri lugar L[%u] = %u tokens\n",pl->pos, pl->qtd);
        pl = pl->prox;
    }
    flecha *pt = rede->tl;
    if(DEBUG) while(pt != NULL)
    {
        printf("inseri flecha T[%u]---(%u)--->L[%u]\n",pt->de, pt->tk, pt->para);
        pt = (pt->prox);
    }
    pt = rede->lt;
    if(DEBUG) while(pt != NULL)
    {
        printf("inseri flecha L[%u]---(%u)--->T[%u]\n",pt->de, pt->tk, pt->para);
        pt = (pt->prox);
    }
    printf("======= INICIO DA SIMULACAO =======\n");
    /* Este trecho sera retirado quanto a simulacao estiver pronta */
    printf("Under construction. WE APOLOGISE FOR THE INCONVENIENCE\n");
    return 0;
    /* Fim do trecho temporario */
    k = 0;
    do
    {
        k++;
        it_escape = 0;
        it_escape = 1;
        if(k>ITER)
        {
            printf("Atencao! Apos %u iteracoes, a rede de petri nao estabilizou! Finalizando a simulacao. \nPara aumentar a quantidade maxima de iteracoes, verifique o manual de utilizacao do programa.\n",ITER);
            break;
        }
    }while(it_escape);
    /* Esta parte do codigo servira apenas para auxiliar no desenvolvimento do codigo */
    /* for(k=0;k<ITER;k++)
    {
        if(DEBUG) printf("\nInteracao %u:\n",k+1);
        rlist(chosen,qt);
        it_escape = 0;
        if(DEBUG) printf("Ordem de tentativa:");
        if(DEBUG) printv(chosen,qt);
        if(DEBUG) printf("\n");
        for(m=0;m<qt;m++)
        {
            i = chosen[m]; //sorteio i
            if(DEBUG) printf("Tentativa %u: numero sorteado: [%u]\n",m+1,i);
            flag = 1;
            for(j=0;j<ql;j++)
                if(lt[j][i] != 0)
                    if(l[j] < lt[j][i])
                    {
                        flag = 0;
                        break;
                    }
            if(flag)
            {
                it_escape = 1; //alguma transicao ativou
                if((rand()%100 + 1) <= PCT)
                {
                    if(DEBUG) printf("Transicao %u ativou!\n",i);
                    for(j=0;j<ql;j++)
                        if(lt[j][i] != 0)
                        {
                            l[j] -= lt[j][i];
                            if(DEBUG) printf("Transicao %u consumiu %u token(s) do lugar %u \n", i, lt[j][i], j);
                        }
                    for(j=0;j<ql;j++)
                        if(tl[i][j] != 0)
                        {
                            l[j] += tl[i][j];
                            v[i]++;     
                            if(DEBUG) printf("Transicao %u produziu %u token(s) \n", i, tl[i][j]);   
                        }
                    if(DEBUG) printf("Token em cada lugar:[");
                    if(DEBUG) printv(l,ql);
                    if(DEBUG) printf(" ]\n");
                }
                else
                    if(DEBUG) printf("Transicao %u decidiu nao ativar.\n",i);               
            }
        }
        if(it_escape == 0) //se nada aconteceu com nenhuma transicao
            break;
    }*/
    printf("======= FIM DA SIMULACAO ==========\n");
    t = time(NULL) - t;
    printf("Tempo de reprodução do programa: %u segundo(s).\n",t);
    if(k==0)
        printf("Aviso: nenhuma transicao foi disparada! \n");
    printf("Numero de iteracoes: %u.\n",k);
    printf("Lugares com token: \n");
    /* Imprimir "LX = Y" se Y > 0 */
    /* for(j=0;j<ql;j++)
        if(l[j] != 0)
            printf("Lugar %u: %u tokens \n",j,l[j]); */

    printf("Transicoes disparadas: \n");
    /* Imprimir "TX: Y vezes" se Y > 0 */
    /* for(j=0;j<ql;j++)
        if(v[j] != 0)
            printf("Transicao %u: disparada %u vezes \n",j,v[j]); */


    return EXIT_SUCCESS;
}

/**
 * \ingroup GroupUnique
 *
 * \brief Gera uma lista aleatoria.
 *
 * \details Esta funcao faz uma lista de 0 a n, porem numa ordem aleatoria. 
 *
 * \param[out] v A variavel \a v sera a lista numa ordem aleatoria.
 *
 * \param[in] n A variavel \a n representa o tamanho do vetor \a v.
 *
 * \retval void a funcao retorna nada.
 *
 */
void rlist(unsigned v[VMAX], unsigned n)
{
    unsigned i = n, j, f;
    while(i)
    {
        v[n-i] = rand()%n;
        if(DEBUG>1) printf("Vetor[%u]: %u (",n-i,v[n-i]);
        f = 1;
        for(j=0;j<(n-i);j++)
            if(v[j] == v[n-i])
                f = 0;
        if(f)
        {
            if(DEBUG>1) printf("OK)\n");
            i--;
        }
        else
            if(DEBUG>1) printf("Falhou)\n");
    }
    if(DEBUG>1) printf("retorno do rlist: [");
    if(DEBUG>1) printv(v,n);
    if(DEBUG>1) printf(" ]\n");
    return;
}

/**
 * \ingroup GroupUnique
 *
 * \brief Imprime os valores de um vetor.
 *
 * \details Esta funcao imprime valores de um vetor, em uma ordem crescente. 
 *
 * \param[in] v A variavel \a v e um vetor que sera impresso.
 *
 * \param[in] n A variavel \a n representa o numero de impressoes \a v.
 *
 * \retval void a funcao retorna nada.
 *
 */
void printv(unsigned v[VMAX], unsigned n)
{
    unsigned i;
    for(i=0;i<n;i++)
        printf(" %u",v[i]);
    return;
}

/**
 * \ingroup GroupUnique
 *
 * \brief Imprime os valores de uma matriz.
 *
 * \details Esta funcao imprime valores de uma matriz,em numa ordem crescente. 
 *
 * \param[in] x A variavel \a x e uma matriz que sera impressa.
 *
 * \param[in] n A variavel \a n representa a linha da matriz a ser impressa \a x.
 *
 * \param[in] m A variavel \a m representa a coluna da matriz a ser impressa \a x.
 *
 * \retval void a funcao retorna nada.
 *
 */
void printm(unsigned x[VMAX][VMAX], unsigned n, unsigned m)
{
    unsigned i, j;
    for(i=0;i<n;i++)
    {
        printf("\n");
        for(j=0;j<m;j++)
            printf("%u ",x[i][j]);
    }
    return;
}

/**
 * \ingroup GroupUnique
 *
 * \brief Funcao que executa a transicao da rede.
 *
 * \details Esta funcao deve checar as flechas de entrada, checar os lugares para ver se existe quantidade de tokens suficientes para disparar indicadas pelas flechas, checar as flechas de saida e depositar nos lugares a quantidade de token indicados pelas flechas
 *
 * \param[in] arg A variavel \a arg seria na realidade uma struct que recebeu um cast para ser passada atraves de uma pthread. Ela deve conter a rede de petri e o indice da transicao.
 *
 * \retval void a funcao retorna nada.
 *
 */
void transicao(void *arg)
{
    return;
}

/**
 * \ingroup GroupUnique
 *
 * \brief Desenha uma rede no Allegro e imprime num arquivo de imagem.
 *
 * \details Esta funcao utiliza a biblioteca grafica Allegro para imprimir uma rede de Petri. 
 *
 * \param[in] rede A variavel \a rede seria a rede de Petri.
 *
 * \param[in] fname A variavel \a fname representa o nome do arquivo que sera gerado.
 *
 * \retval void a funcao retorna nada.
 *
 */
void desenha_rede(petri_t rede, const char *fname)
{
    return;
}
