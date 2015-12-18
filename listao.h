#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

/* Tipo que descreve as caracteristicas da Flecha */
typedef struct flecha_st
{
    unsigned de;
    unsigned para;
    unsigned tk;
    struct flecha_st * prox;
}flecha;

/* Tipo que descreve as caracteristicas dos Lugares */
typedef struct lugar_st
{
    unsigned pos;
    unsigned qtd;
    int isBusy;
    struct lugar_st * prox;
}lugar;

/* Descricao da rede de Petri sem as transicoes */ 
typedef struct petri_st
{
    unsigned total_l,
             total_t;
    lugar *l;
    flecha *lt;
    flecha *tl;
}petri_t;

/* Lista de threads */
typedef struct thread_st
{
    pthread_t thr;
    struct thread_st *prox;
}l_thread;

/* Lista de posicoes a serem passadas */
typedef struct passa_dados_st
{
    unsigned pos;
    struct passa_dados_st *prox;
}dados;

typedef struct conta_trans_st
{
    unsigned pos,
             x;
    struct conta_trans_st *prox;
}conta_trans;

/**
 * \ingroup Listao
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
 * \ingroup Listao
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
void inserirLugar(lugar **cabeca, unsigned i, unsigned x, int b);
void removerLugar(lugar **cabeca, lugar *r);
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
void imprimirFlechaLT(flecha *cabeca);
void imprimirFlechaTL(flecha *cabeca);
void inserirThread(l_thread **cabeca, pthread_t p);
void imprimirThread(l_thread *cabeca);

void inserirDados(dados **cabeca, unsigned x);
void limparDados(dados **cabeca);

/**
 * \ingroup Listao
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
 * \ingroup Listao
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
 * \ingroup Listao
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
