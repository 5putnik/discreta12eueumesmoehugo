#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

/**
 * \file listao.h
 * \brief Header que contem funcoes auxiliares para o ex12.c 
 * \author Hugo Albuquerque de Fonsêca <<hugoalbuquerque0@gmail.com>>
 * \author Otacilio Saraiva Maia Neto <<otacilio.n97@gmail.com>>
 * \version 2.1
 * \date 2015-12-22
 */
/**
 * \
 * @{ */

/** 
 * Lista que descreve as caracteristicas da Flecha 
 */
typedef struct flecha_st
{
    unsigned de; /**< Ponto de partida da flecha */
    unsigned para; /**< Ponto de chegada da flecha */
    unsigned tk; /**< Quantidade de tokens necessaria para ativar a flecha */
    struct flecha_st * prox; /**< Proximo elemento da lista de flechas */
}flecha;

/**
 * Lista que descreve as caracteristicas dos Lugares
 */
typedef struct lugar_st
{
    unsigned pos; /**< Ordem do lugar (L0, L1, ...) */
    unsigned qtd; /**< Quantidade de tokens no lugar */
    int isBusy; /**< Flag se o lugar esta sendo modificado por uma transicao */
    struct lugar_st * prox; /**< Proximo elemento da lista de lugares */
}lugar;

/**
 * Descricao da rede de Petri sem as transicoes 
 */ 
typedef struct petri_st
{
    unsigned total_l, /**< Quantidade total de lugares */
             total_t; /**< Quantidade total de transicoes */
    lugar *l; /**< Lista de lugares */
    flecha *lt; /**< Lista de flechas Lugar -> Transicao */
    flecha *tl; /**< Lista de flechas Transicao -> Lugar */
}petri_t;

/**
 * Lista de threads ativas
 */
typedef struct thread_st
{
    pthread_t thr; /**< Endereco da thread */
    struct thread_st *prox; /**< Proximo elemento da lista de threads */
}l_thread;

/**
 * Lista de posicoes a serem passadas para a funcao transicao()
 */
typedef struct passa_dados_st
{
    unsigned pos; /**< Endereco da transicao */
    struct passa_dados_st *prox; /**< Proximo elemento da lista de dados */
}dados;

/**
 * Lista que conta o numero de ativacoes de uma transicao
 */
typedef struct conta_trans_st
{
    unsigned pos, /**< Endereco da transicao */
             x; /**< Contador de ativacoes */
    struct conta_trans_st *prox; /**< Proximo elemento da lista de ativacoes */
}conta_trans;

/**
 * \ingroup Header
 *
 * \brief Busca o primeiro lugar na lista que contenha aquela quantidade de tokens.
 *
 * \details Esta funcao se utiliza do ponto que o tipo lugar possui um comportamento de lista para procurar em todos os elementos dessa lista pelo primeiro que corresponda ao criterio de busca. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] x A variavel \a x representa a quantidade de tokens a ser procurada.
 *
 * \retval lugar a funcao retorna o elemento da lista que contenha aquela quantidade de tokens.
 *
 * \retval NULL a funcao retorna um ponteiro apontando para nada caso nao ache nenhum lugar.
 *
 */
lugar *buscarLugarQtd(lugar *cabeca, unsigned x);

/**
 * \ingroup Header
 *
 * \brief Busca na lista o lugar Lx.
 *
 * \details Esta funcao se utiliza do ponto que o tipo lugar possui um comportamento de lista para procurar em todos os elementos dessa lista pelo primeiro que corresponda ao criterio de busca. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] x A variavel \a x representa qual lugar sera' chamado.
 *
 * \retval lugar a funcao retorna o elemento da lista que tenha como argumento 'pos' o valor inserido.
 *
 * \retval NULL a funcao retorna um ponteiro apontando para nada caso nao ache nenhum lugar.
 *
 */
lugar *buscarLugarPos(lugar *cabeca, unsigned x);

lugar *buscarLugarQtdProx(lugar *cabeca, unsigned x);

lugar *buscarLugarPosProx(lugar *cabeca, unsigned x);

lugar *anteriorLugar(lugar *cabeca, lugar *r);

/**
 * \ingroup Header
 *
 * \brief Insere um lugar na lista.
 *
 * \details Esta funcao se utiliza do ponto que o tipo lugar possui um comportamento de lista e insere um elemento no final da mesma. Caso nao haja elemento nenhum, o "cabeca" da lista passa a ser o proprio elemento inserido. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] i A variavel \a i representa a posicao do lugar (L0, L1, ...).
 *
 * \param[in] x A variavel \a x representa a quantidade inicial de tokens daquele lugar.
 *
 * \param[in] b A variavel \a b e' uma variavel interna, que diz se este lugar pode doar tokens ou nao.
 *
 * \retval void a funcao retorna nada.
 *
 */
void inserirLugar(lugar **cabeca, unsigned i, unsigned x, int b);

/**
 * \ingroup Header
 *
 * \brief remove um lugar na lista.
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] r A variavel \a r representa o lugar que devera ser removido 
 *
 * \retval void a funcao retorna nada.
 *
 */
void removerLugar(lugar **cabeca, lugar *r);
/**
 * \ingroup Header
 *
 * \brief imprime os lugares de uma lista.
 *
 * \details A funcao basicamente lista todos os lugares contidos em uma lista e os imprime da seguinte forma: LX(Y), sendo X o lugar e Y a quantidade de tokens. Caso o DEBUG esteja ativo e o lugar estiver ocupado, sera adicionado ao fim tambem a mensagem (OCUPADO).
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void imprimirLugar(lugar *cabeca);

flecha *buscarFlechaAnd(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);

flecha *buscarFlechaOr(flecha *cabeca, unsigned xde, unsigned xpara, unsigned xtk);

flecha *buscarFlechaDe(flecha *cabeca, unsigned x);

flecha *buscarFlechaPara(flecha *cabeca, unsigned x);

flecha *buscarFlechaTk(flecha *cabeca, unsigned x);

flecha *buscarFlechaDeProx(flecha *cabeca, unsigned x);

flecha *buscarFlechaParaProx(flecha *cabeca, unsigned x);

flecha *buscarFlechaTkProx(flecha *cabeca, unsigned x);

flecha *anteriorFlecha(flecha *cabeca, flecha *r);

void inserirFlecha(flecha **cabeca, unsigned xde, unsigned xpara, unsigned xtk);

void removerFlecha(flecha **cabeca, flecha *r);

/**
 * \ingroup Header
 *
 * \brief Imprime uma lista de flechas LT.
 *
 * \details Esta funcao se utiliza do ponto que o tipo flecha se comporta como uma lista para imprimir elemento a elemento passando apenas uma unica variavel. Por se tratar de um tipo L->T, ela imprimira todos os elementos da seguinte forma: LX---(Y)--->TZ, sendo X o lugar, Y a quantidade de tokens passados e Z a transicao. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void imprimirFlechaLT(flecha *cabeca);

/**
 * \ingroup Header
 *
 * \brief Imprime uma lista de flechas TL.
 *
 * \details Esta funcao se utiliza do ponto que o tipo flecha se comporta como uma lista para imprimir elemento a elemento passando apenas uma unica variavel. Por se tratar de um tipo T->L, ela imprimira todos os elementos da seguinte forma: TX---(Y)--->LZ, sendo X a transicao, Y a quantidade de tokens passados e Z o lugar. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void imprimirFlechaTL(flecha *cabeca);

/**
 * \ingroup Header
 *
 * \brief Insere uma thread na lista.
 *
 * \details Esta funcao se utiliza do ponto que o tipo l_thread possui um comportamento de lista e insere um elemento no final da mesma. Caso nao haja elemento nenhum, o "cabeca" da lista passa a ser o proprio elemento inserido. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da lista.
 *
 * \param[in] p A variavel \a b e' a thread a ser inserida na lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void inserirThread(l_thread **cabeca, pthread_t p);

/**
 * \ingroup Header
 *
 * \brief Imprime os enderecos de uma lista de threads.
 *
 * \details Esta funcao se utiliza do ponto que o tipo l_thread possui um comportamento de lista e imprime o endereco de todos os seus elementos. 
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void imprimirThread(l_thread *cabeca);


/**
 * \ingroup Header
 *
 * \brief Isere elementos na lista dados
 *
 * \details Esta funcao insere o valor X dentro da lista do tipo dados.
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] x Valor a ser inserido.
 *
 * \retval void a funcao retorna nada.
 *
 */
void inserirDados(dados **cabeca, unsigned x);

/**
 * \ingroup Header
 *
 * \brief Limpa a lista de dados lista.
 *
 * \details Esta funcao limpa igualando os ponteiros a NULL
 * 
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \retval void a funcao retorna nada.
 *
 */
void limparDados(dados **cabeca);

/**
 * \ingroup Header
 *
 * \brief Calcula o cosseno de um segmento de reta.
 *
 * \details Dados dois pontos P1(x1,y1) e P2(x2,y2), a funcao calcula o cosseno do segmento de reta P1P2, evitando absolutamente qualquer erro de quadrante no calculo de angulos. 
 *
 * \param[in] x1 A variavel \a x1 representa o valor no eixo X do ponto P1.
 *
 * \param[in] y1 A variavel \a y1 representa o valor no eixo Y do ponto P1.
 *
 * \param[in] x2 A variavel \a x2 representa o valor no eixo X do ponto P2.
 *
 * \param[in] y2 A variavel \a y2 representa o valor no eixo Y do ponto P2.
 *
 * \retval float a funcao retorna o cosseno do segmento de reta.
 *
 */
float lcos(float x1, float y1, float x2, float y2);

/**
 * \ingroup Header
 *
 * \brief Calcula o seno de um segmento de reta.
 *
 * \details Dados dois pontos P1(x1,y1) e P2(x2,y2), a funcao calcula o seno do segmento de reta P1P2, evitando absolutamente qualquer erro de quadrante no calculo de angulos. 
 *
 * \param[in] x1 A variavel \a x1 representa o valor no eixo X do ponto P1.
 *
 * \param[in] y1 A variavel \a y1 representa o valor no eixo Y do ponto P1.
 *
 * \param[in] x2 A variavel \a x2 representa o valor no eixo X do ponto P2.
 *
 * \param[in] y2 A variavel \a y2 representa o valor no eixo Y do ponto P2.
 *
 * \retval float a funcao retorna o seno do segmento de reta.
 *
 */
float lsin(float x1, float y1, float x2, float y2);

/**
 * \ingroup Header
 *
 * \brief Incrementa 1 num contador inserido numa lista.
 *
 * \details Esta funcao se utiliza do ponto que o tipo conta_trans possui um comportamento de lista para procurar em todos os elementos dessa lista pelo primeiro que corresponda ao criterio de busca.
 * Apos isso ela incrementara 1 no valor que corresponde ao numero de ativacoes que aquela transicao executou. Caso nao ache nenhuma transicao que corresponda a que foi buscada, uma nova sera criada 
 * e seu valor inicial sera' 1.
 *
 * \param[in] cabeca A variavel \a cabeca seria o primeiro elemento da busca na lista.
 *
 * \param[in] pos A variavel \a pos representa qual transicao sera' incrementada.
 *
 * \retval void a funcao retorna nada.
 *
 */
void incrementaTrans(conta_trans **cabeca, unsigned pos);
