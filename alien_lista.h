#define VIVO 1
#define MORTO 0
#define DIREITA 1
#define ESQUERDA -1
#define CIMA -1
#define BAIXO 1


struct t_nodo {
    int tipo;       /*numero para saber qual objeto eh*/
    int x;          /*x da parte mais a esquerda do objeto*/
    int y;          /*y da pate mais a cima do objeto*/
    int estado;     /*estado do objeto*/
    int largura;
    int altura;
    int velocidade; /*velocidade com que o objeto percorre a tela(quanto menor o numero mais rapido, 1 eh o minimo)*/
    int velaux;     /*auxiliar para velocidade ser usada*/
    int sprite;     /*variavel para controle das "animacoes"*/
    int numsprites;
    int death;      /*contador de quantos frames o objeto ficou morto usado para explosoes poderem ficar mais tempo na tela*/
    struct t_nodo *prox;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *fim;
    t_nodo *atual;
};
typedef struct t_lista t_lista;

/*
  muda todos os int de contagem da lista para zero
  todos os apontadores apontam para NULL
  e a direcao para direita
*/
void inicializa_lista(t_lista *l);

/*
  inicializa atual no primeiro elemento da lista
  se a lista estiver vazia atual sera=NULL
  retorna 0 com lista vazia e 1 caso contrario
*/
int inicializa_atual_ini(t_lista *l);

/*
  inicializa atual no ultimo elemento da lista
  se a lista estiver vazia atual sera=NULL
  retorna 0 com lista vazia e 1 caso contrario
*/
int inicializa_atual_fim(t_lista *l);

/*
  inicializa atual no primeiro elemento com tipo tipo
  retorna 0 com lista vazia ou n tenha nenhum elemento com aql tipo
  retorna 1 caso contrario
*/
int inicializa_atual_prim_tipo(t_lista *l, int tipo);

/*
  incrementa o atual da lista
  retorna 0 caso atual seja NULL antes de incrementar
  retorna 0 caso atual saia da lista depois de incrementar
  retorna 1 caso contrario
*/
int incrementa_atual(t_lista *l);

/*
  decrementa o atual da lista
  retorna 0 caso atual seja NULL antes de decrementar
  retorna 0 caso atual saia da lista depois de decrementar
  retorna 1 caso contrario
*/
int decrementa_atual(t_lista *l);

/*
  retorna x e y de atual nos ponteiros
  retorn 1 em caso de sucesso e 0 caso contrario
*/
int retorna_atual_xy(t_lista *l, int *x, int *y);

/*
  retorna estado e tipo de atual nos ponteiros
  retorn 1 em caso de sucesso e 0 caso contrario
*/
int retorna_atual_est_tipo(t_lista *l, int *estado, int *tipo);

/*
  retorna altura e largura de atual nos ponteiros
  retorn 1 em caso de sucesso e 0 caso contrario
*/
int retorna_atual_dimen(t_lista *l, int *altura, int *largura);

/*
  retorna o sprite de atual no ponteiro
  retorn 1 em caso de sucesso e 0 caso contrario
*/
int retorna_atual_sprite(t_lista *l, int *sprite);

/*muda o estado de atual para morto*/
void mata_atual(t_lista *l);

/*
  retorna quantos elementos tem tipo tipo
*/
int num_tipo(t_lista *l, int tipo);

/*
  insere um elemento do tipo tipo na lista
  insere ele com canto superior esquerdo em x y
  insere ele com altura i e largura j
  insere com velocidade v, quanto menor a velocidade mais rapido
  tera sprites sprites
*/
int insere_elemento(t_lista *l,int tipo,int x, int y, int i, int j, int v, int sprites);

/*
  testa as colisoes da lista entre todos os elementos de tipo1 com tipo2
  muda para MORTO os dois que colidiram
  retorna quantas colisoes foram detectadas
*/
int checkcol2k(t_lista *l, int tipo1, int tipo2);

/*
  testa as colisoes da lista entre todos os elementos de tipo1 com tipo2
  muda para MORTO quando o colide
  muda apenas o tipo2 para MORTO
  retorna quantas colisoes foram detectadas
*/
int checkcol1k(t_lista *l, int tipo1, int tipo2);

/*retorna 1 se ha algum tipo ocupando o a coluna x*/
int checa_coluna(t_lista *l, int tipo, int x);

/*retorna 1 se ha algum tipo ocupando a linha y*/
int checa_linha(t_lista *l, int tipo, int y);

/*
  mexe todos os tipos tipo na direcao horizontal direcao
  leva em consideracao a velocidade
  avanca o sprite caso o elemento se mexeu
*/
void addvh(t_lista *l, int tipo, int direcao);

/*
  mexe todos os tipos tipo na direcao vertical direcao
  leva em consideracao a velocidade
  avanca o sprite caso o elemento se mexeu
*/
void addvv(t_lista *l, int tipo, int direcao);

/*
  mexe todos os tipos tipo na direcao horizontal direcao
  sem levar em consideracao a velocidade
  avanca o sprite caso o elemento se mexeu
*/
void mvh(t_lista *l, int tipo, int direcao);

/*
  mexe todos os tipos tipo na direcao vertical direcao
  sem levar em consideracao a velocidade
  avanca o sprite caso o elemento se mexeu
*/
void mvv(t_lista *l, int tipo, int direcao);

/*
  avanca o sprites de todos os tipos de tipo tipo
*/
void addvsprite(t_lista *l, int tipo);

/*incrementa death de todos os elementos mortos*/
void incrsdead(t_lista *l);

/*
  remove todos os elementos de tipo tipo q estao mortos a dead passadas da funcao incrsdead
  pode arruinar o atual
*/
void rmvdead(t_lista *l, int tipo, int dead);

/*remove todos os elementos de tipo tipo que tem x igual ao passado*/
void rmvx(t_lista *l, int tipo, int x);

/*remove todos os elementos de tipo tipo que tem y igual ao passado*/
void rmvy(t_lista *l, int tipo, int y);

/*remove todos os elementos de tipo tipo que tem x  e y igual aos passados*/
void rmvxy(t_lista *l, int tipo, int x, int y);

/*da free em todos os nodos da lista*/
void destroi_lista(t_lista *l);

/*
  altera a velocidade de todos os elementos de tipo tipo para vel
  se vel for menor que um a velocidade sera mudada para um
*/
void chvel(t_lista *l, int tipo, int vel);
