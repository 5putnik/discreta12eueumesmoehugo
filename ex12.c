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
 ************************************************************************** *
 *
 */

/**
 * \file ex12.c
 * \brief programa que simula rede de petri. 
 * \author Hugo Albuquerque de Fonsêca <<hugoalbuquerque0@gmail.com>>
 * \author Otacilio Saraiva Maia Neto <<otacilio.n97@gmail.com>>
 * \version 1.0
 * \date 2015-12-14
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

#define A 1
#define B 2
#define C 3
#define D 4
#define LIVRE 0
#define OCUPADO 1


#ifndef ITER
    #define ITER 1000 /**< Total de iteracoes */
#endif

#ifndef DEBUG
    #define DEBUG 0 /**< Ativa modo de debug */
#endif

#ifndef GIF
    #define GIF 0 /**< Ativa modo GIF (Ainda nao implementado) */
#endif

#ifndef IMG_X
    #define IMG_X 800
#endif

#ifndef IMG_Y
    #define IMG_Y 600
#endif

#define M_LIN if(DEBUG == A || DEBUG == D) printf("-------------------------------------------------------\n")
#define CORBRANCO (makecol(255,255,255))
#define CORPRETO 1
#define CORCINZA (makecol(160,160,160))
#define CORAZUL (makecol(0, 0, 255))
#define CORVERDE (makecol(0, 255, 0))
#define CORAMARELO (makecol(255,255,100))
#define CORVERMELHO (makecol(255, 0, 0))

void *transicao(void *arg);
void desenha_rede(petri_t *rede, const char *fname);

unsigned it_escape;                             /* Flag condicional da iteracao */

/* Rede de petri propriamente dita */
petri_t *rede;

conta_trans *contador;

int main(void)
{
    rede = malloc(sizeof(petri_t));
    contador = malloc(sizeof(conta_trans));
    unsigned t = time(NULL);                    /* Temporizador da simulacao */
    unsigned qt,                                /* Quantidade de transicoes */
             ql;                                /* Quantidade de lugares */
    unsigned i,                                 /* Variavel geral de laco */
             j,                                 /* Variavel geral de laco */
             k,                                 /* Variavel geral de laco */
             lctk,                              /* Variavel temporaria de insercao */
             alt,                               /* Total de arcos lugar -> transicao */
             atl;                               /* Total de arcos transicao -> lugar */
    dados *d = malloc(sizeof(dados)),           /* Lista de transicoes */
          *pd = d;                              /* Ponteiro auxiliar da lista de transicoes */
    l_thread *lthr = NULL;                      /* Lista de threads */
    pthread_t temp_thr;                         /* Variavel auxiliar da lista de threads */

    rede -> l = NULL;
    rede -> tl = NULL;
    rede -> lt = NULL;
    srand(time(NULL));

    /* Escaneando a quantidade de lugares */
    scanf("%u",&ql);
    rede->total_l = ql;
    /* Escaneando a quantidade de transicoes */
    scanf("%u",&qt); 
    rede->total_t = qt;
    /*********** EasterEgg v1.0 BirthDay version **************/ 
    /*********** Only programmers will now, it needs recompilate with the MACRO ***************/
#ifdef EASTEREGGV1
    printf("14/12/2015 The first day of the Petri Simulator, tagged v1.0 one day ago at 22:00 PM\n");
    printf("It is also the day of the birthday of the co-developer Otacilio Neto\n");
    printf("So congratulations to both!!!\n");
    printf("\"Twenty years from now you will be more disappointed by the things that you didnt do than by the ones you did do. So throw off the bowlines. Sail away from the safe harbor. Catch the trade winds in your sails\"\n");
    printf("Explore! Dream! Discover!\n");
#endif
    /********** End EasterEgg v1.0 ******************/ 

    if(DEBUG == A || DEBUG == D) printf("Quantidade de lugares: %u\n",ql);
    /*if(ql>VMAX)
      {
      printf("Erro linha 1: quantidade de lugares acima do maximo. \n");
      return -1;
      }*/
    if(DEBUG == A || DEBUG == D) printf("Quantidade de transicoes: %u\n",qt);
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
        inserirLugar(&(rede->l), i, j, LIVRE);
    }
    for(k=0;k<rede->total_l;k++)
    {
        if(buscarLugarPos((rede->l), k) == NULL)
            inserirLugar(&(rede->l), k, 0, LIVRE);
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
    if(DEBUG == A || DEBUG == D) imprimirLugar(rede->l);
    if(DEBUG == A || DEBUG == D) imprimirFlechaTL(rede->tl);
    if(DEBUG == A || DEBUG == D) imprimirFlechaLT(rede->lt);
    desenha_rede(rede, "inicio.bmp");
    printf("======= INICIO DA SIMULACAO =======\n");
    printf("(execucao pode demorar dependendo do tamanho da rede...)\n");
    k = 0;
    do
    {
        k++;
        it_escape = 0;
        /* d->net = rede; */
        M_LIN;
        for(i=0;i<qt;i++)
        {
            inserirDados(&d, i);
            if(pd->prox != NULL)
                pd = pd->prox;
            if(pthread_create(&temp_thr, NULL, transicao, (void *)pd))
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
        if(DEBUG == A || DEBUG == D) imprimirLugar(rede->l);
        M_LIN;
        if(k>ITER)
        {
            printf("Atencao! Apos %u iteracoes, a rede de petri nao estabilizou! Finalizando a simulacao. \nPara aumentar a quantidade maxima de iteracoes, verifique o manual de utilizacao do programa.\n",ITER);
            break;
        }
    }while(it_escape);
    printf("======= FIM DA SIMULACAO ==========\n");
    desenha_rede(rede, "fim.bmp");
    t = time(NULL) - t;
    printf("Tempo de reprodução do programa: %u segundo(s).\n",t);
    if(k==0)
        printf("Aviso: nenhuma transicao foi disparada! \n");
    if(k<ITER)
        printf("Numero de iteracoes necessarias pra convergir: %u.\n",k);
    printf("Lugares com token: \n");
    imprimirLugar(rede->l);

    printf("Transicoes disparadas: \n");
    conta_trans *ct = contador;
    while(ct != NULL)
    {
        printf("T%u: %u vez(es)\n", ct->pos, ct->x);
        ct = ct->prox;
    }

    return EXIT_SUCCESS;
}

/**
 * \ingroup Main
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
    unsigned i = n->pos;
    /* petri_t *r = n->net; */
    petri_t *r = rede;
    if(r == NULL)
    {
        printf("ERRO: passando nada pra transicao!!\n");
        return NULL;
    }

    flecha *tlt = r -> lt; // Cabeca da lista LugarTransicao
    flecha *ttl = r -> tl; // Cabeca da lista TransicaoLugar
    lugar *tp = r -> l; // Cabeca da lista Lugar
    flecha *x = NULL; // Flecha atual
    lugar *y = NULL; // Lugar atual

    unsigned xde,
             xtk,
             xpara,
             yqtd,
             d,
             dd,
             c;

    /********************** Codigo reestruturado ****************/
    
    c = 0; // Para saber se entrou pelo menos 1x no loop
    d = dd = 0; // Inicia os contadores de lugares existentes e lugares disponivels para tirar em 0
    x = buscarFlechaPara(tlt, i); // Procura uma flecha 'lt' que aponte para a transicao atual 'i'

    /********************* CHECKS DA TRANSICAO **************************/
    while(x != NULL) // Enquanto houverem flechas 
    {
        c = 1; // Marca que entrou no loop
        xtk = x -> tk; // armazena a qtd de tokens que a flecha pede
        xde = x -> de; // armazena o lugar de origem dessa flecha 
   
        if(DEBUG == B || DEBUG == D) printf("[thread %u] Precisa remover %d tokens do lugar %d\n", i, xtk, xde);
        y = buscarLugarPos(tp, xde); // Procura o lugar em que a flecha parte

        if(y != NULL) // Se o lugar de origem da flecha existir
        {
            d++; // Marca que encontrou mais uma flecha
            if( y -> isBusy == LIVRE)
            {
                y -> isBusy = OCUPADO; // Marca que o lugar esta ocupado pela Thread
                yqtd = y -> qtd; // Armazena a qntd de tokens desponivels no local
            
                if(xtk <= yqtd) // Se a qntd de tokens que a flecha pede for disponiveis no local
                {
                    dd++; // Marca que o local ta disponivel
                    if(DEBUG == B || DEBUG == D) printf("[thread %u] Lugar com tokens suficientes\n", i);
                }
                else
                    if(DEBUG == B || DEBUG == D) printf("[thread %u] Lugar com tokens insuficientes\n", i);
            }
        }
        else 
            if(DEBUG == C || DEBUG == D) printf("[thread %u]Erro: lugar inexistente\n", i);

        x = buscarFlechaParaProx(x, i); // Procura uma nova flecha
    }

    if((DEBUG == C || DEBUG == D) && !c) printf("[thread %u] Erro: transicao fantasma, nenhum lugar aponta para ela\n", i); //Um else pro while
    c = 0; // Reseta a variavel de controle
    
    /**************************** ACOES DA TRANSICAO ***********************/
    if(d == dd && d && dd) // Se a transicao estiver apta a disparar 
    {
        if(DEBUG == B || DEBUG == D) printf("Transicao %u disparou\n", i);
        it_escape = 1;
        x = buscarFlechaPara(tlt, i); // Busca novamente as flechas que apontam para a transicao
        incrementaTrans(&contador, i);
        
        while(x != NULL) // Repetindo a pesquisa de flechas
        {
            c = 1;
            xtk = x -> tk;
            xde = x -> de;
     
            y = buscarLugarPos(tp, xde);
            if(y != NULL)
            {
                y -> qtd = (y -> qtd) - xtk; // Subtrai os tokens, condicao de corrida pode bugar essa parte deixando negativo
                y -> isBusy = LIVRE;
            }
            else
                if(DEBUG == C || DEBUG == D) printf("[thread %u]Erro: lugar inexistente na 2 pesquisa\n", i);

            x = buscarFlechaParaProx(x, i); // procura uma nova flecha
        }

        if(DEBUG == C || DEBUG == D) printf("[thread %u] Erro: transicao fantasma, nenhum lugar aponta para ela 2 pesq\n", i);
        c = 0; // Reseta a variavel de controle
    
        /* Inicio da busca das flechas tl */
        x = buscarFlechaDe(ttl, i); // Busca uma flecha que parta da transicao

        while(x != NULL)
        {
            c = 1;
            xtk = x -> tk; // Armazena a qntd de tokens que deverao ser depositados indicados pela flecha
            xpara = x -> para; // Armazena em que lugar deve depositar o token

            y = buscarLugarPos(tp, xpara);

            if(y != NULL)
            {
                y -> qtd = (y -> qtd) + xtk; // adiciona os tokens ao lugar de saida
            }
            else 
                if(DEBUG == C || DEBUG == D) printf("[thread %u] Erro: nao existe lugar de chegada da flecha\n", i);

            x = buscarFlechaDeProx(x, i); // Busca uma nova flecha
        }
        if((DEBUG == C || DEBUG == D) && !c) printf("[thread %u] Erro: transicao fantasma, nenhum lugar e' apontado por ela\n", i);
    }

    return NULL;
}

/**
 * \ingroup Main
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
    float ang,      /* Angulacao antre cada elemento na imagem */
          r_lugar,  /* Raio da circunferencia que representa o lugar */
          smaller,  /* A menor das dimensoes da imagem */
          x,        /* Variavel geral para representar coordenada X */
          y,        /* Variavel geral para representar coordenada Y */
          x1,       /* Variavel geral para representar coordenada X */
          y1,       /* Variavel geral para representar coordenada Y */
          x2,       /* Variavel geral para representar coordenada X */
          y2,       /* Variavel geral para representar coordenada Y */
          x3,       /* Variavel geral para representar coordenada X */
          y3,       /* Variavel geral para representar coordenada Y */
          co,       /* Variavel geral para representar cosseno */
          si;       /* Variavel geral para representar seno */

    unsigned i, q;
    lugar *a_l = rede->l;
    BITMAP *buff;
    PALETTE pal;
    flecha *a_tl = rede->tl,
           *a_lt = rede->lt;
    /* Inicializacao Allegro */
    if(install_allegro(SYSTEM_NONE, &errno, atexit)!=0)
        exit(EXIT_FAILURE);
    set_color_depth(16);
    get_palette(pal);
    buff = create_bitmap(IMG_X,IMG_Y);
    smaller = (float)IMG_X;
    if(smaller > (float)IMG_Y)
        smaller = (float)IMG_Y;
    r_lugar = smaller/4.0*(M_PI/(M_PI+(float)rede->total_l));
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
    if(DEBUG == B || DEBUG == D) printf("Desenhando %u lugares e %u transicoes espacados entre si %.2fº...\n", rede->total_l, rede->total_t, ang*180.0/M_PI);

    /* Desenhando os lugares  */
    for(i=0;i<rede->total_l;i++)
    {
        a_l = buscarLugarPos(rede->l, i);
        q = 0;
        if(a_l != NULL)
            q = a_l->qtd;
        x = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos(2*i*ang);
        y = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin(2*i*ang);
        circle(buff, x, y, r_lugar, CORBRANCO);
        textprintf_ex(buff, font, x, y, CORVERDE, CORPRETO, "%u", q);
        if(DEBUG == B || DEBUG == D) printf("L%u(%u) (posicionada %.2fº)\n", i, q, ang*(2*i)*180.0/M_PI);
        textprintf_ex(buff, font, x, y - r_lugar, CORVERDE, CORPRETO, "L%u", i);
    }

    /* Desenhando as transicoes  */
    for(i=0;i<rede->total_t;i++)
    {
        x = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos((2*i+1)*ang);
        y = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin((2*i+1)*ang);
        line(buff, x, y+r_lugar, x, y-r_lugar, CORBRANCO);
        if(DEBUG == B || DEBUG == D) printf("T%u (posicionado %.2fº)\n", i, ang*(2*i+1)*180.0/M_PI);
        textprintf_ex(buff, font, x, y - r_lugar, CORVERDE, CORPRETO, "T%u", i);
    }

    /* Desenhando as flechas */
    while(a_tl != NULL)
    {
        i = a_tl->de;
        x1 = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos((2*i+1)*ang);
        y1 = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin((2*i+1)*ang);
        i = a_tl->para;
        x = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos(2*i*ang);
        y = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin(2*i*ang);
        co = lcos(x1,y1,x,y);
        si = lsin(x1,y1,x,y);
        x -= r_lugar*co;
        y -= r_lugar*si;
        line(buff, x1, y1, x, y, CORBRANCO);
        textprintf_ex(buff, font, (x+x1)/2, (y+y1)/2, CORVERDE, CORPRETO, "%u", a_tl->tk);
        x2 = x - (r_lugar / 4) * (si + co);
        y2 = y + (r_lugar / 4) * (co - si);
        x3 = x + (r_lugar / 4) * (si - co);
        y3 = y - (r_lugar / 4) * (si + co);
        triangle(buff, x, y, x2, y2, x3, y3, CORBRANCO);
        a_tl = a_tl->prox;
    }
    while(a_lt != NULL)
    {
        i = a_lt->de;
        x1 = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos(2*i*ang);
        y1 = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin(2*i*ang);
        i = a_lt->para;
        x = IMG_X/2.0 + (IMG_X/2.0 - r_lugar)*cos((2*i+1)*ang);
        y = IMG_Y/2.0 + (IMG_Y/2.0 - r_lugar)*sin((2*i+1)*ang);
        co = lcos(x1,y1,x,y);
        si = lsin(x1,y1,x,y);
        x1 += r_lugar*co;
        y1 += r_lugar*si;
        line(buff, x1, y1, x, y, CORBRANCO);
        textprintf_ex(buff, font, (x+x1)/2, (y+y1)/2, CORVERDE, CORPRETO, "%u", a_lt->tk);
        x2 = x - (r_lugar / 4) * (si + co);
        y2 = y + (r_lugar / 4) * (co - si);
        x3 = x + (r_lugar / 4) * (si - co);
        y3 = y - (r_lugar / 4) * (si + co);
        triangle(buff, x, y, x2, y2, x3, y3, CORBRANCO);
        a_lt = a_lt->prox;
    }
    /* Salvando Imagem */
    save_bitmap(fname, buff, pal);
    destroy_bitmap(buff);
    allegro_exit();
    if(!GIF) printf("Imagem %s salva com sucesso!\n", fname);
    return;
}
