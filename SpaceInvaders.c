#include"moveimprime.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>


void coloca_navemae(t_lista *l){
	if(num_tipo(l,NAVEMAE)==0 && (rand()%500)==0)
        insere_elemento(l,NAVEMAE,98,1,3,9,20,2);
}

void inicializa_jogo(t_lista *l, int vel){
    int i, j;
    destroi_lista(l);
    insere_elemento(l,CANHAO,45,35,2,5,1,2);
    /* colocar aliens */
	for(j=3;j<75;j=j+7){
		insere_elemento(l,ALIEN3,j,6,3,5,vel,2);
	}
	for(j=3;j<75;j=j+7){
		insere_elemento(l,ALIEN2,j,10,3,5,vel,2);
	}
	for(j=3;j<75;j=j+7){
		insere_elemento(l,ALIEN2,j,14,3,5,vel,2);
	}
	for(j=3;j<75;j=j+7){
		insere_elemento(l,ALIEN1,j,18,3,5,vel,2);
	}
	for(j=3;j<75;j=j+7){
		insere_elemento(l,ALIEN1,j,22,3,5,vel,2);
	}

    /* colocar a barreira */
	for(j=14;j<78;j=j+21){
		insere_elemento(l,BARREIRA,j,30,1,1,vel,8);
	}
	for(j=18;j<82;j=j+21){
		insere_elemento(l,BARREIRA,j,30,1,1,vel,8);
	}
	for(i=15;i<81;i=i+21){
		for(j=0;j<3;j++){
			insere_elemento(l,BARREIRA,i+j,30,1,1,vel,8);
		}
	}

	for(j=13;j<77;j=j+21){
		insere_elemento(l,BARREIRA,j,31,1,1,vel,8);
	}
	for(j=19;j<83;j=j+21){
		insere_elemento(l,BARREIRA,j,31,1,1,vel,8);
	}
	for(i=14;i<81;i=i+21){
		for(j=0;j<5;j++){
			insere_elemento(l,BARREIRA,i+j,31,1,1,vel,8);
		}
	}

	for(i=13;i<77;i=i+21){
			insere_elemento(l,BARREIRA,i,32,1,1,vel,8);
			insere_elemento(l,BARREIRA,i+1,32,1,1,vel,8);
	}
	for(i=18;i<82;i=i+21){
			insere_elemento(l,BARREIRA,i,32,1,1,vel,8);
			insere_elemento(l,BARREIRA,i+1,32,1,1,vel,8);
    }
}

void set_all_speed(t_lista *l, int alien, int tiro, int bomba){
    chvel(l,ALIEN1,alien);
    chvel(l,ALIEN2,alien);
    chvel(l,ALIEN3,alien);
    chvel(l,TIRO,tiro);
    chvel(l,BOMBA,bomba);
    chvel(l,NAVEMAE,alien/2);
}

void mvandcol(t_lista *l, int *dir, int *score, int *velocidade){
    *score+=(checkcol2k(l,TIRO,ALIEN1))*10;
    *score+=(checkcol2k(l,TIRO,ALIEN2))*20;
    *score+=(checkcol2k(l,TIRO,ALIEN3))*30;

    *score+=checkcol2k(l,TIRO,BOMBA);
    addvv(l,BOMBA,BAIXO);
    *score+=checkcol2k(l,TIRO,BOMBA);
    addvv(l,TIRO,CIMA);

    *score+=(checkcol2k(l,TIRO,NAVEMAE)*100);

    checkcol1k(l,ALIEN1,BARREIRA);
    checkcol1k(l,ALIEN2,BARREIRA);
    checkcol1k(l,ALIEN3,BARREIRA);

    checkcol2k(l,TIRO,BARREIRA);
    checkcol2k(l,BOMBA,BARREIRA);
    checkcol2k(l,BOMBA,CANHAO);


    alien_shoot(l,6);

    move_aliens(l,dir,velocidade);
    addvh(l,NAVEMAE,ESQUERDA);

    addvsprite(l,BARREIRA);

    incrsdead(l);
    rmv_out(l);
    rmvdead(l,ALIEN1,4);
    rmvdead(l,ALIEN2,4);
    rmvdead(l,ALIEN3,4);
    rmvdead(l,NAVEMAE,4);
    rmvdead(l,TIRO,0);
    rmvdead(l,BOMBA,0);
}

int main(){
    int maxx, maxy;
    initscr();
    getmaxyx(stdscr,maxy,maxx);
    if(maxx<99 || maxy<37){
        printf("Terminal muito pequeno, terminal deve ter no minimo 38 linhas e 100 colunas.\n");
        endwin();
        return 1;
    }
    noecho();
    keypad(stdscr,TRUE);

    clear();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_BLACK,COLOR_WHITE);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    attron(A_BOLD);

    attron(COLOR_PAIR(5));
    curs_set(0);
    imprime_tela_inicial();
    getch();
    attroff(COLOR_PAIR(5));  
    nodelay(stdscr,TRUE);

    int limtiros=7, velmax=15, velocidade=velmax, level=0, score=0, dir=DIREITA, numaliens;
    t_lista jogo;
    inicializa_lista(&jogo);
    inicializa_jogo(&jogo,velmax);
    char entrada=' ';
    while(entrada!='q' && level!=10 && checa_canhao(&jogo)){

        entrada=getch();
        move_canhao(&jogo,&entrada, limtiros);
        coloca_navemae(&jogo);
        mvandcol(&jogo,&dir,&score,&velocidade);


        numaliens=num_tipo(&jogo,ALIEN1);
        numaliens+=(num_tipo(&jogo,ALIEN2));
        numaliens+=(num_tipo(&jogo,ALIEN3));
        set_all_speed(&jogo,velocidade,4,6);

        imprime_jogo(&jogo,score,level,limtiros,velocidade,numaliens);
        if(numaliens==0 && level<10){
            destroi_lista(&jogo);
            nodelay(stdscr,FALSE);
            attron(COLOR_PAIR(5));
            imprime_new_wave(limtiros,velmax);
            attroff(COLOR_PAIR(5));
            entrada=getch();
            while(entrada!='t' && entrada!='r')
                entrada=getch();
            if(entrada=='r'){
                velmax-=2;
                velocidade=velmax;
            }
            else
                limtiros--;
            nodelay(stdscr,TRUE);
            inicializa_lista(&jogo);
            inicializa_jogo(&jogo,velmax);
            level++;
        }
        usleep(16666);
    }
    nodelay(stdscr,FALSE);
    attron(COLOR_PAIR(5));
    if(entrada=='q'){
        endwin();
        destroi_lista(&jogo);
        return 1;
    }
    else if(level<10)
        imprime_perdeu(score);
    else
        imprime_ganhou(score);
    entrada=getch();
    while(entrada!='q' && entrada!='r')
        entrada=getch();
    destroi_lista(&jogo);
    attroff(COLOR_PAIR(5));
    attroff(A_BOLD);
    endwin();
    if(entrada=='r')
        main();
    return 1;
}
