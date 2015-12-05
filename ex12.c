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

/* Parametros a serem passados para a funcao de transicao */
struct passaTrans
{
    petri_t rede;
    int pos;
}x;

void rlist(unsigned v[VMAX], unsigned n);
void printv(unsigned v[VMAX], unsigned n);
void printm(unsigned x[VMAX][VMAX], unsigned n, unsigned m);
void transicao(void *arg);
void desenhaPetri(petri_t p, const char*c);

int main(void)
{
    unsigned t = time(NULL);
    unsigned l[VMAX] = {0}, 
             lt[VMAX][VMAX] = {0}, 
             tl[VMAX][VMAX] = {0}, 
             qt, 
             ql, 
             chosen[VMAX], 
             v[VMAX] = {0};
    unsigned i, 
             j, 
             k, 
             m, 
             flag, 
             it_escape, 
             lctk, 
             alt, 
             atl;
    struct passa_dados_st
    {
        petri_t rede;
        int pos;
    }dados;
    srand(time(NULL));
    scanf("%u",&ql);
    scanf("%u",&qt); 
    if(DEBUG>1) printf("Quantidade de lugares: %u\n",ql);
    if(ql>VMAX)
    {
        printf("Erro linha 1: quantidade de lugares acima do maximo. \n");
        return -1;
    }
    if(DEBUG>1) printf("Quantidade de transicoes: %u\n",qt);
    if(qt>VMAX)
    {
        printf("Erro linha 2: quantidade de transicoes acima do maximo. \n");
        return -1;
    }
    scanf("%u",&lctk);
    scanf("%u",&alt);
    scanf("%u",&atl);
    for(k=0;k<lctk;k++)
    {
        scanf("%u %u", &i, &j);
        if(i>=ql)
        {
            printf("Erro linha %u: lugar maior que o definido. \n", 6+k);
            return -1;
        }
        l[i]=j;
    }
    for(k=0;k<alt;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=ql||j>=qt)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k);
            return -1;
        }
        lt[i][j]= lctk;
    }
    for(k=0;k<atl;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=qt||j>=ql)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k+alt);
            return -1;
        }
        tl[i][j] = lctk;
    }
    if(DEBUG>1) printf("Token em cada lugar:[");
    if(DEBUG>1) printv(l,ql);
    if(DEBUG>1) printf(" ]\n");
    if(DEBUG>1) printf("Matriz lt:");
    if(DEBUG>1) printm(lt,ql,qt);
    if(DEBUG>1) printf("\nMatriz tl:");
    if(DEBUG>1) printm(tl,qt,ql);
    if(DEBUG>1) printf("\n");
    printf("======= INICIO DA SIMULACAO =======\n");
    for(k=0;k<ITER;k++)
    {
        if(DEBUG>1) printf("\nInteracao %u:\n",k+1);
        rlist(chosen,qt);
        it_escape = 0;
        if(DEBUG>1) printf("Ordem de tentativa:");
        if(DEBUG>1) printv(chosen,qt);
        if(DEBUG>1) printf("\n");
        for(m=0;m<qt;m++)
        {
            i = chosen[m]; //sorteio i
            if(DEBUG>0) printf("Tentativa %u: numero sorteado: [%u]\n",m+1,i);
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
                    if(DEBUG>0) printf("Transicao %u ativou!\n",i);
                    for(j=0;j<ql;j++)
                        if(lt[j][i] != 0)
                        {
                            l[j] -= lt[j][i];
                            if(DEBUG>1) printf("Transicao %u consumiu %u token(s) do lugar %u \n", i, lt[j][i], j);
                        }
                    for(j=0;j<ql;j++)
                        if(tl[i][j] != 0)
                        {
                            l[j] += tl[i][j];
                            v[i]++;     
                            if(DEBUG>1) printf("Transicao %u produziu %u token(s) \n", i, tl[i][j]);   
                        }
                    if(DEBUG>0) printf("Token em cada lugar:[");
                    if(DEBUG>0) printv(l,ql);
                    if(DEBUG>0) printf(" ]\n");
                }
                else
                    if(DEBUG>0) printf("Transicao %u decidiu nao ativar.\n",i);               
            }
        }
        if(it_escape == 0) //se nada aconteceu com nenhuma transicao
            break;
    }
    printf("======= FIM DA SIMULACAO ==========\n");
    t = time(NULL) - t;
    printf("Tempo de reprodução do programa: %u segundo(s).\n",t);
    if(k==0)
        printf("Aviso: nenhuma transicao foi disparada! \n");
    printf("Numero de iteracoes: %u.\n",k);
    printf("Lugares com token: \n");
    for(j=0;j<ql;j++)
        if(l[j] != 0)
            printf("Lugar %u: %u tokens \n",j,l[j]);

    printf("Transicoes disparadas: \n");
    for(j=0;j<ql;j++)
        if(v[j] != 0)
            printf("Transicao %u: disparada %u vezes \n",j,v[j]);


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
        if(DEBUG>4) printf("Vetor[%u]: %u (",n-i,v[n-i]);
        f = 1;
        for(j=0;j<(n-i);j++)
            if(v[j] == v[n-i])
                f = 0;
        if(f)
        {
            if(DEBUG>4) printf("OK)\n");
            i--;
        }
        else
            if(DEBUG>4) printf("Falhou)\n");
    }
    if(DEBUG>4) printf("retorno do rlist: [");
    if(DEBUG>4) printv(v,n);
    if(DEBUG>4) printf(" ]\n");
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

/* 
 * Funcao transicao;
 * Que devera checkar as flechas de entrada;
 * Checkar os lugares para ver se existe quantidade de tokens suficientes para disparar indicadas pelas flechas;
 * Checkar as flechas de saida;
 * Depositar nos lugares a quantidade de tokens indidicados pelas flechas
 * */
void transicao(void *arg)
{
    return;
}

void desenhaPetri(petri_t p, const char*c)
{
    break;
}
