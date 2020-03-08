#include"alien_lista.h"

#define CANHAO 0
#define ALIEN1 1
#define ALIEN2 2
#define ALIEN3 3
#define TIRO 4
#define BOMBA 5
#define NAVEMAE 6
#define BARREIRA 7

void imprime_perdeu(int score);

void imprime_ganhou(int score);

void imprime_sair();

void imprime_tela_inicial();

void imprime_new_wave(int limtiros, int velmax);

void imprime_pausa();

void imprime_score(int score, int level, int limtiros, int velocidade, int numaliens);

/*imprime todos os nodos*/
void imprime_jogo(t_lista *l, int score, int level, int limtiros, int velocidade, int numaliens);

/*move o canhao usando a entrada dada*/
void move_canhao(t_lista *l, char *entrada, int limtiros);

/*
  se tiver alguma alien ocupando a linha do canhao muda o estado dele para morto
  retorna 1 se o canhao ficar vivo e 0 caso contrario  
*/
int checa_canhao(t_lista *l);

/*
  move os aliens para direcao dir
  se houver algum alien na borda daql lado desce todos
  altera o dir caso necessario
*/
void move_aliens(t_lista *l, int *dir, int *velocidade);

/*remove todos os elementos que estao fora do jogo*/
void rmv_out(t_lista *l);

/*cade alien ter 1/1000 de chance de atirar*/
void alien_shoot(t_lista *l, int vel);