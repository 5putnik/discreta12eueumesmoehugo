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
#include <math.h>
#include "listao.h"

#ifndef ITER
    #define ITER 5 /**< Total de iteracoes */
#endif

#ifndef DEBUG
    #define DEBUG 1 /**< Ativa modo de debug */
#endif

#ifndef GIF
    #define GIF 0 /**< Ativa modo GIF (Ainda nao implementado) */
#endif

#define M_LIN printf("-------------------------------------------------------\n")

void *transicao(void *arg);
void desenha_rede(petri_t *rede, const char *fname);

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
    rede->total_l = ql;
    /* Escaneando a quantidade de transicoes */
    scanf("%u",&qt); 
    rede->total_t = qt;
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
    if(DEBUG) imprimirFlechaTL(rede->tl);
    if(DEBUG) imprimirFlechaLT(rede->lt);
    desenha_rede(rede, "inicio");
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
    desenha_rede(rede, "fim");
    /* Este trecho sera retirado quanto a simulacao estiver pronta */
    printf("Under construction. WE APOLOGISE FOR THE INCONVENIENCE\n");
    return 0;
    /* Fim do trecho temporario */
    printf("======= FIM DA SIMULACAO ==========\n");
    t = time(NULL) - t;
    printf("Tempo de reprodução do programa: %u segundo(s).\n",t);
    if(k==0)
        printf("Aviso: nenhuma transicao foi disparada! \n");
    printf("Numero de iteracoes: %u.\n",k);
    printf("Lugares com token: \n");
    /* Imprimir "LX = Y" se Y > 0 */

    printf("Transicoes disparadas: \n");
    /* Imprimir "TX: Y vezes" se Y > 0 */


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
    unsigned i = n->pos;
    if(r == NULL)
    {
        printf("ERRO: passando nada pra transicao!!\n");
        return NULL;
    }

    flecha *t = r -> lt;
    flecha *tp = r -> tl; 
    flecha *x = NULL;
    flecha *xx = NULL;
    lugar *tpp = r -> l;
    lugar *tppp = r -> l;
    lugar *y = NULL;
    lugar *yy = NULL;

    unsigned xde,
             xtk,
             xxpara,
             xxtk,
             yqtd,
             d,
             dd,
             c,
             cc;

    /* Codido paralelo 2 */
    x = buscarFlechaPara(t, i);
    c = 0;
    cc = 0;
    d = 0;
    dd = 0;
    while(x != NULL)
    {
        c = 1;
        xtk = x -> tk;
        xde = x -> de;
        if(DEBUG) printf("[thread %u] Precisa remover %d tokens do lugar %d\n", i, xtk, xde);
        y = buscarLugarPos(tpp, xde);
        while(y != NULL)
        {
            d++;
            yqtd = y -> qtd;
            if(xtk <= yqtd)
            {
                if(DEBUG) printf("[thread %u] Lugar com tokens suficientes\n", i);
                dd++;
            }
            else
                if(DEBUG) printf("[thread %u] Lugar com tokens insuficientes\n", i);

            y = y -> prox; 
            tpp = tpp -> prox; 
            y = buscarLugarPos(tpp, xde);
        }
        t = t -> prox;
        x = buscarFlechaPara(t, i);
    }
    printf("Passei daqui 4\n");

    if(DEBUG && !c) printf("[thread %u] Erro: transicao fantasma, nenhum lugar aponta para ela\n", i);

    if(d == dd && d && dd)
    {
        if(DEBUG) printf("Transicao %u disparou\n", i);
        /* Devido a condicao de corrida a qtd pode ficar negativa */

        /* Enquanto houver elementos em Y subtrair os tokens da qtd */
        while(y != NULL) 
        {
            y -> qtd = (y -> qtd) - xtk;
            y = y -> prox;
        }

        /*Inicio deposito de token no lugar de saida */
        xx = buscarFlechaDe(tp, i);
        while(xx != NULL)
        {
            cc = 1;
            xxtk = xx -> tk;
            xxpara = xx -> para;
            if(DEBUG) printf("[thread %u] Precisa adicionar %d tokens no lugar %d\n", i, xxtk, xxpara);
            yy = buscarLugarPos(tppp, xxpara);

            if(yy != NULL)
            {
                /*Achou o lugar que deve despejar os tokens */
                yy -> qtd = (yy -> qtd) + xxtk;        
            }
            else
                if(DEBUG) printf("[thread %u] Erro: nao existe lugar de chegada da flecha\n", i);

            tp = tp -> prox;
            xx = buscarFlechaDe(tp, i);
        }

        if(DEBUG && !cc) printf("[thread %u] Erro: transicao fantasma, nenhum lugar e' apontado por ela\n", i);
    }
    /* FIM Codigo paralelo 2 */

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
void desenha_rede(petri_t *rede, const char *fname)
{
    float ang;
    unsigned i, q;
    lugar *a_l = rede->l;
    BITMAP *buff;
    PALETTE pal;
    /*flecha *a_tl = rede->tl;
      flecha *a_lt = rede->lt;*/
    /* Inicializacao Allegro */
    if(install_allegro(SYSTEM_NONE, &errno, atexit)!=0)
        exit(EXIT_FAILURE);
    set_color_depth(16);
    get_palette(pal);
    buff = create_bitmap(800,600);
    if(buff == NULL)
    {
        printf("Could not create buffer!\n");
        exit(EXIT_FAILURE);
    }
    /* Desenho propriamente dito */

    if(rede->total_l > rede->total_t)
        ang = M_PI/rede->total_l;
    else
        ang = M_PI/rede->total_t;
    if(DEBUG) printf("Desenhando %u lugares e %u transicoes espacados entre si %.2fº...\n", rede->total_l, rede->total_t, ang*180.0/M_PI);

    for(i=0;i<rede->total_l;i++)
    {
        a_l = buscarLugarPos(rede->l, i);
        q = 0;
        if(a_l != NULL)
            q = a_l->qtd;
        if(DEBUG) printf("L%u(%u) (posicionada %.2fº)\n", i, q, ang*(2*i)*180.0/M_PI);
    }
    for(i=0;i<rede->total_t;i++)
        if(DEBUG) printf("T%u (posicionado %.2fº)\n", i, ang*(2*i+1)*180.0/M_PI);
    /* Salvando Imagem */
    save_bitmap(IMAGENAME, buff, pal);
    destroy_bitmap(buff);
    allegro_exit();
    if(!GIF) printf("Imagem %s salva com sucesso!\n", fname);
    return;
}
