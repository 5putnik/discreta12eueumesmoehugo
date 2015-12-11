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
#include <pthread.h>
#include <allegro.h>
#include <unistd.h>
#include "listao.h"

#ifndef ITER
    #define ITER 5 /**< Total de iteracoes */
#endif

#ifndef DEBUG
    #define DEBUG 0 /**< Ativa modo de debug */
#endif

#define M_LIN printf("-------------------------------------------------------\n")

void *transicao(void *arg);
void desenha_rede(petri_t rede, const char *fname);

unsigned it_escape;                             /* Flag condicional da iteracao */

typedef struct passa_dados_st
{
    petri_t *net;
    unsigned pos;
}dados;

int main(void)
{
    unsigned t = time(NULL);                    /* Temporizador da simulacao */
    unsigned qt,                                /* Quantidade de transicoes */
             ql;                                /* Quantidade de lugares */
    unsigned i,                                 /* Variavel geral de laco */
             j,                                 /* Variavel geral de laco */
             k,                                 /* Variavel geral de laco */
             lctk,                              /* Variavel temporaria de insercao */
             alt,                               /* Total de arcos lugar -> transicao */
             atl;                               /* Total de arcos transicao -> lugar */
    petri_t *rede = malloc(sizeof(petri_t));    /* Rede de petri propriamente dita */
    dados *d = malloc(sizeof(dados));
    l_thread *lthr = NULL;
    pthread_t temp_thr;
    rede -> l = NULL;
    rede -> tl = NULL;
    rede -> lt = NULL;
    /* Parametros a serem passados para a funcao de transicao */

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
    }
    if(rede->l == NULL)
    {
        printf("Erro: lugar nao pode ser lido no documento de texto.\n");
        return -1;
    }
    for(k=0;k<alt;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=ql||j>=qt)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k);
            return -1;
        }
        inserirFlecha(&(rede->lt), i, j, lctk);
    }
    if(rede->lt == NULL)
    {
        printf("Erro: flecha lugar->transicao nao pode ser lido no documento de texto.\n");
        return -1;
    }
    for(k=0;k<atl;k++)
    {
        scanf("%u %u %u", &i, &lctk, &j);
        if(i>=qt||j>=ql)
        {
            printf("Erro linha %u: lugar ou transicao acima do definido. \n", 6+lctk+k+alt);
            return -1;
        }
        inserirFlecha(&(rede->tl), i, j, lctk);
    }
    if(rede->tl == NULL)
    {
        printf("Erro: flecha transicao->lugar nao pode ser lido no documento de texto.\n");
        return -1;
    }
    if(DEBUG) imprimirLugar(rede->l);
    if(DEBUG) imprimirFlecha(rede->tl);
    if(DEBUG) imprimirFlecha(rede->lt);
    printf("======= INICIO DA SIMULACAO =======\n");
    k = 0;
    do
    {
        k++;
        it_escape = 0;
        d->net = rede;
        M_LIN;
        for(i=0;i<qt;i++)
        {
            printf("Passando %u\n",i);
            d->pos = i;
            if(pthread_create(&temp_thr, NULL, transicao, (void *)d))
            {
                printf("Erro criando thread %u!\n",i);
                exit(1);
            }
            inserirThread(&lthr, temp_thr);
        }
        while(lthr != NULL)
        {
            temp_thr = lthr->thr;
            if(pthread_join(temp_thr, NULL))
            {
                printf("Erro juntando thread!\n");
                exit(1);
            }
            lthr = lthr->prox;
        }
        M_LIN;
        it_escape = 1;
        if(k>ITER)
        {
            printf("Atencao! Apos %u iteracoes, a rede de petri nao estabilizou! Finalizando a simulacao. \nPara aumentar a quantidade maxima de iteracoes, verifique o manual de utilizacao do programa.\n",ITER);
            break;
        }
    }while(it_escape);
    /* Este trecho sera retirado quanto a simulacao estiver pronta */
    printf("Under construction. WE APOLOGISE FOR THE INCONVENIENCE\n");
    return 0;
    /* Fim do trecho temporario */

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
 * \brief Funcao que executa a transicao da rede.
 *
 * \details Esta funcao deve checar as flechas de entrada, checar os lugares para ver se existe quantidade de tokens suficientes para disparar indicadas pelas flechas, checar as flechas de saida e depositar nos lugares a quantidade de token indicados pelas flechas
 *
 * \param[in] arg A variavel \a arg seria na realidade uma struct que recebeu um cast para ser passada atraves de uma pthread. Ela deve conter a rede de petri e o indice da transicao.
 *
 * \retval void a funcao retorna nada.
 *
 */
void *transicao(void *arg)
{
    dados *n = (dados *)(arg);
    petri_t *r = n->net;
    unsigned i = n->pos,
             j;

    flecha *t = r -> lt;
    flecha *x = NULL;
    int xde, xtk;

    printf("[transicao, thread %u] Me passou a variavel net de endereco %p\n", i, r);
    for(j=0;j<5;j++)
    {
        
        x = buscarFlechaPara(t, i);
        if(x != NULL)
        {
            xtk = x -> tk;
            xde = x -> de;
            printf("Precisa remover %d tokens do lugar %d", xtk, xde);
        }
        else
            printf("Erro transicao fantasma, nenhum lugar aponta para ela");


        printf("[transicao, thread %u] Rodei %u vezes.\n", i, j);
        sleep(1);
    }
    return NULL;
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
    printf("[desenha_rede] Me passou a variavel rede de endereco %p\n[desenha_rede] Me passou a variavel fname de nome %s\n", &rede, fname);
    return;
}
