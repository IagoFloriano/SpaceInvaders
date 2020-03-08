#include"moveimprime.h"
#include<ncurses.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void imprime_perdeu(int score){
    mvprintw(15,29," __  __                          _       ");
    mvprintw(16,29,"|  \\/  |                        | |      ");
    mvprintw(17,29,"| \\  / | ___  _ __ _ __ ___  ___| |_ ___ ");
    mvprintw(18,29,"| |\\/| |/ _ \\| '__| '__/ _ \\/ __| __/ _ \\");
    mvprintw(19,29,"| |  | | (_) | |  | | |  __/\\__ \\ ||  __/");
    mvprintw(20,29,"|_|  |_|\\___/|_|  |_|  \\___||___/\\__\\___|");
    mvprintw(21,29,"            Aperte q para sair          ");
    mvprintw(22,29,"        pontuacao final:%d",score);
}

void imprime_ganhou(int score){
    mvprintw(15,29,"__      __                      _");
    mvprintw(16,29,"\\ \\    / /                     | |");
    mvprintw(17,29," \\ \\  / /__ _ __   ___ ___  ___| |_ ___");
    mvprintw(18,29,"  \\ \\/ / _ \\ '_ \\ / __/ _ \\/ __| __/ _ \\");
    mvprintw(19,29,"   \\  /  __/ | | | (_|  __/\\__ \\ ||  __/");
    mvprintw(20,29,"    \\/ \\___|_| |_|\\___\\___||___/\\__\\___|");
    mvprintw(21,29,"            Aperte q para sair         ");
    mvprintw(22,29,"           pontuacao final:%d",score);
}

void imprime_sair(){
    mvprintw(15,37,"  _____       _    ___  ");
    mvprintw(16,37," / ____|     (_)  |__ \\ ");
    mvprintw(17,37,"| (___   __ _ _ _ __ ) |");
    mvprintw(18,37," \\___ \\ / _` | | '__/ / ");
    mvprintw(19,37," ____) | (_| | | | |_|  ");
    mvprintw(20,37,"|_____/ \\__,_|_|_| (_) ");
    mvprintw(21,29,"Aperte q para sair e p para continuar");
}

void imprime_tela_inicial(){
    mvprintw(12,4,"  _|_|_|                                            ___     \\_/   /\\./\\");
    mvprintw(13,4,"_|        _|_|_|      _|_|_|    _|_|_|    _|_|     /o o\\   /d.b\\  |UwU|");
    mvprintw(14,4,"  _|_|    _|    _|  _|    _|  _|        _|_|_|_|   ~/^\\~   </^\\>  /_._\\");
    mvprintw(15,4,"      _|  _|    _|  _|    _|  _|        _|                   |");
    mvprintw(16,4,"_|_|_|    _|_|_|      _|_|_|    _|_|_|    _|_|_|           /_^_\\");
    mvprintw(17,4,"          _|                                               \\___/");
    mvprintw(19,4,"          _||_|_|                                        _|");
    mvprintw(20,4,"            _|    _|_|_|    _|      _|    _|_|_|    _|_|_|    _|_|    _|  _|_|    _|_|_|");
    mvprintw(21,4,"            _|    _|    _|  _|      _|  _|    _|  _|    _|  _|_|_|_|  _|_|      _|_|");
    mvprintw(22,4,"            _|    _|    _|    _|  _|    _|    _|  _|    _|  _|        _|            _|_|");
    mvprintw(23,4,"          _|_|_|  _|    _|      _|        _|_|_|    _|_|_|    _|_|_|  _|        _|_|_|");
    mvprintw(24,4,"    'a' ou <- para mover para esquerda   'd' ou -> para mover para direita");
    mvprintw(25,4,"                     \"espaco\" ou ^ ou 'w' para atirar");
    mvprintw(26,4,"                      aperte q para sair e p para pausar");
    mvprintw(27,4,"                     aperte qualquer botao para continuar");
}

void imprime_new_wave(int limtiros, int velmax){
    mvprintw(13,35," _   _");
    mvprintw(14,35,"| \\ | |");
    mvprintw(15,35,"|  \\| | _____      __ ");
    mvprintw(16,35,"| . ` |/ _ \\ \\ /\\ / /");
    mvprintw(17,35,"| |\\  |  __/\\ V  V /  ");
    mvprintw(18,35,"|_|_\\_|\\___| \\_/\\_/");
    mvprintw(19,35,"  \\ \\        / /");
    mvprintw(20,35,"   \\ \\  /\\  / /_ ___   _____ ");
    mvprintw(21,35,"    \\ \\/  \\/ / _` \\ \\ / / _ \\");
    mvprintw(22,35,"     \\  /\\  / (_| |\\ V /  __/");
    mvprintw(23,35,"      \\/  \\/ \\__,_| \\_/ \\___|");
    mvprintw(24,35,"como aumentar a dificuldade:");
    mvprintw(25,35,"'t' para ter um tiro a menos");
    mvprintw(26,35,"'r' para os aliens acelerarem");
    mvprintw(27,35,"tiros atuais:%d",limtiros);
    if(velmax>1)
        mvprintw(28,35,"velocidade dos aliens:%d",8-((velmax-1)/2));
    else
        mvprintw(28,35,"velocidade dos aliens:MAX");
}

void imprime_pausa(){
    mvprintw(15,34," _____");
    mvprintw(16,34,"|  __ \\");
    mvprintw(17,34,"| |__) |_ _ _   _ ___  __ _ ");
    mvprintw(18,34,"|  ___/ _` | | | / __|/ _` |");
    mvprintw(19,34,"| |  | (_| | |_| \\__ \\ (_| |");
    mvprintw(20,34,"|_|   \\__,_|\\__,_|___/\\__,_|");
    mvprintw(21,34,"  aperte 'p' para despausar");
    mvprintw(22,34,"       ou 'q' para sair     ");
}

void imprime_score(int score, int level, int limtiros, int velocidade, int numaliens){
    int x;
    x=getmaxx(stdscr);
    mvhline(0,0,0,99);
    mvhline(37,0,0,99);
    mvvline(0,0,0,37);
    mvvline(0,99,0,37);
    mvaddch(37,0,ACS_LLCORNER);
    mvaddch(0,0,ACS_ULCORNER);
    if(x<111){
        mvaddch(0,99,ACS_URCORNER);
        mvaddch(37,99,ACS_LRCORNER);
        attron(A_STANDOUT);
        mvprintw(0,45,"%7d",score);
        attroff(A_STANDOUT);
        attron(COLOR_PAIR(1));
        mvprintw(37,93,"level:%d",level);
        attroff(COLOR_PAIR(1));
    }
    else{
        mvhline(0,100,0,11);
        mvhline(37,100,0,11);
        mvvline(0,111,0,37);
        mvaddch(0,99,ACS_TTEE);
        mvaddch(37,99,ACS_BTEE);
        mvaddch(0,111,ACS_URCORNER);
        mvaddch(37,111,ACS_LRCORNER);
        attron(COLOR_PAIR(5));
        mvprintw(1,100,"level:");
        mvprintw(2,100,"%10d",level);
        mvprintw(4,100,"score:");
        mvprintw(5,100,"%10d",score);
        mvprintw(7,100,"limite");
        mvprintw(8,100,"tiros:");
        mvprintw(9,100,"%10d",limtiros);
        mvprintw(11,100,"velocidade");
        mvprintw(12,100,"aliens:");
        if(velocidade!=1)
            mvprintw(13,100,"%10d",8-(velocidade/2));
        else
            mvprintw(13,100,"    MAX");
        mvprintw(14,100,"numero");
        mvprintw(15,100,"aliens:");
        mvprintw(16,100,"%10d",numaliens);
        attroff(COLOR_PAIR(5));
    }
}

void imprime_jogo(t_lista *l, int score, int level, int limtiros, int velocidade, int numaliens){
    erase();
    int x,y,tipo,estado,sprite;
    char string[28];
    if(inicializa_atual_ini(l)){
        do{
            retorna_atual_xy(l,&x,&y);
            retorna_atual_est_tipo(l,&estado,&tipo);
            retorna_atual_sprite(l,&sprite);
            if(estado==VIVO){
                switch(tipo){
                    case CANHAO:
                        attron(COLOR_PAIR(1));
                        switch(sprite){
                            case 1:
                                mvprintw(y,x,"/_^_\\");
                                mvprintw(y+1,x,"\\___/");
                                break;
                            case 2:
                                mvprintw(y,x,"|_^_|");
                                mvhline(y+1,x,0,5);
                                mvaddch(y+1,x,ACS_LLCORNER);
                                mvaddch(y+1,x+4,ACS_LRCORNER);
                                break;
                        }
                        attroff(COLOR_PAIR(1));
                        break;
                    case ALIEN3:
                        attron(COLOR_PAIR(2));
                        switch(sprite){
                            case 1:
                                mvprintw(y,x,"/\\./\\");
                                mvprintw(y+1,x,"|UwU|");
                                mvprintw(y+2,x,"/_._\\");
                                break;
                            case 2:
                                mvprintw(y,x,"/\\./\\");
                                mvprintw(y+1,x,"|OvO|");
                                mvprintw(y+2,x,"_/.\\_");
                                break;
                        }
                        break;
                    case ALIEN2:
                        switch(sprite){
                            case 1:
                                mvprintw(y,x," \\_/ ");
                                mvprintw(y+1,x,"/d.b\\");
                                mvprintw(y+2,x,"</^\\>");
                                break;
                            case 2:
                                mvprintw(y,x," _^_ ");
                                mvprintw(y+1,x,"/q.p\\");
                                mvprintw(y+2,x,">|^|<");
                                break;
                        }
                        break;
                    case ALIEN1:
                        switch(sprite){
                            case 1:
                                mvprintw(y,x," ___ ");
                                mvprintw(y+1,x,"/o o\\");
                                mvprintw(y+2,x,"~/^\\~");
                                break;
                            case 2:
                                mvprintw(y,x," ___");
                                mvprintw(y+1,x,"/o o\\");
                                mvprintw(y+2,x,"-|^|-");
                                break;
                        }
                        break;
                    case TIRO:
                        attron(COLOR_PAIR(1));
                        switch(sprite){
                            case 1:
                                mvaddch(y,x,ACS_LARROW);
                                break;
                            case 2:
                                mvaddch(y,x,ACS_UARROW);
                                break;
                            case 3:
                                mvaddch(y,x,ACS_RARROW);
                                break;
                            case 4:
                                mvaddch(y,x,'v');
                                break;
                        }
                        attroff(COLOR_PAIR(1));
                        break;
                    case BOMBA:
                        switch(sprite){
                            case 1:
                                mvaddch(y,x,ACS_BULLET);
                                break;
                            case 2:
                                mvaddch(y,x,'o');
                                break;
                            case 3:
                                mvaddch(y,x,'O');
                                break;
                            case 4:
                                mvaddch(y,x,'o');
                                break;
                        }
                        break;
                    case NAVEMAE:
                        attron(COLOR_PAIR(3));
                        switch(sprite){
                            case 1:
                                strcpy(string," _______ /|_|_|_|\\\\WWWWWWW/");
                                break;
                            case 2:
                                strcpy(string," _______ /_|_|_|_\\\\WWWWWWW/");
                                break;
                        }
                        int i, j;
                        for(i=0;i<3;i++){
                            if(i+y>0 && i+y<37)
                                for(j=0;j<9;j++){
                                    if(j+x>0 && j+x<99)
                                        mvaddch(i+y,j+x,string[(i*9)+j]);
                            }
                        }
                        attroff(COLOR_PAIR(3));
                        break;
                    case BARREIRA:
                        attron(COLOR_PAIR(1));
                        if(sprite>0 && sprite<5)
                            mvaddch(y,x,ACS_DIAMOND);
                        else if(sprite>4 && sprite<9)
                            mvaddch(y,x,ACS_CKBOARD);
                        attroff(COLOR_PAIR(1));
                        break;
                }
            }
            else{
                if(tipo==NAVEMAE){
                    attron(COLOR_PAIR(3));
                    mvprintw(y,x+2,"\\ | /");
                    mvprintw(y+1,x+2,"- 0 -");
                    mvprintw(y+2,x+2,"/ | \\");
                    attroff(COLOR_PAIR(3));
                }
                else if(tipo==ALIEN1 || tipo==ALIEN2 || tipo==ALIEN3){
                    attron(COLOR_PAIR(2));
                    mvprintw(y,x,"\\ | /");
                    mvprintw(y+1,x,"- 0 -");
                    mvprintw(y+2,x,"/ | \\");
                    attroff(COLOR_PAIR(2));
                }
                else if(tipo==CANHAO){
                    attron(COLOR_PAIR(1));
                    mvprintw(y,x," \\ / ");
                    mvprintw(y+1,x," / \\ ");
                    attroff(COLOR_PAIR(1));
                }
            }
        } while(incrementa_atual(l));
    }
    imprime_score(score,level,limtiros,velocidade,numaliens);
    refresh();
}

void move_canhao(t_lista *l, char *entrada, int limtiros){
    int x,y;
    inicializa_atual_prim_tipo(l,CANHAO);
    retorna_atual_xy(l,&x,&y);
    if(*entrada=='w' || *entrada=='W' ||
    *entrada=='k' || *entrada=='K' ||
    *entrada==(char)KEY_UP || *entrada==' '){
        if(num_tipo(l,TIRO)<limtiros)
            insere_elemento(l,TIRO,x+2,y,1,1,4,4);
    }
    else if(*entrada=='d' || *entrada=='D' ||
    *entrada=='l' || *entrada=='L' ||
    *entrada==(char)KEY_RIGHT){
        if(x<94)
            mvh(l,CANHAO,DIREITA);
    }
    else if(*entrada=='a' || *entrada=='A' ||
    *entrada=='h' || *entrada=='H' ||
    *entrada==(char)KEY_LEFT){
        if(x>1)
            mvh(l,CANHAO,ESQUERDA);
    }
    else if(*entrada=='q'){
        nodelay(stdscr,FALSE);
        attron(COLOR_PAIR(5));
        imprime_sair();
        attroff(COLOR_PAIR(5));
        *entrada=getch();
        while(*entrada!='q' && *entrada!='p')
            *entrada=getch();
        nodelay(stdscr,TRUE);
    }
    else if(*entrada=='p'){
        nodelay(stdscr,FALSE);
        attron(COLOR_PAIR(5));
        imprime_pausa();
        attroff(COLOR_PAIR(5));
        *entrada=getch();
        while(*entrada!='q' && *entrada!='p')
            *entrada=getch();
        nodelay(stdscr,TRUE);
    }
}

int checa_canhao(t_lista *l){
    if(!inicializa_atual_prim_tipo(l,CANHAO))
        return 0;
    int x, y, tipo, estado;
    retorna_atual_est_tipo(l,&estado,&tipo);
    if(tipo==CANHAO && estado==MORTO)
        return 0;
    retorna_atual_xy(l,&x,&y);
    if(checa_linha(l,ALIEN1,y)||
    checa_linha(l,ALIEN2,y)||
    checa_linha(l,ALIEN3,y))
        return 0;
    return 1;
}

void move_aliens(t_lista *l, int *dir, int *velocidade){
    int diraux=(*dir);
    if(*dir==DIREITA){
        if(checa_coluna(l,ALIEN1,98) ||
        checa_coluna(l,ALIEN2,98) ||
        checa_coluna(l,ALIEN3,98)){
            *dir=ESQUERDA;
        }
    }
    else if(*dir==ESQUERDA){
        if(checa_coluna(l,ALIEN1,1) ||
        checa_coluna(l,ALIEN2,1) || 
        checa_coluna(l,ALIEN3,1)){
            *dir=DIREITA;
        }
    }
    if(*dir==diraux){
        addvh(l,ALIEN1,*dir);
        addvh(l,ALIEN2,*dir);
        addvh(l,ALIEN3,*dir);
    }
    else{
        mvv(l,ALIEN1,BAIXO);
        mvv(l,ALIEN2,BAIXO);
        mvv(l,ALIEN3,BAIXO);
        (*velocidade)--;
        chvel(l,ALIEN1,*velocidade);
        chvel(l,ALIEN2,*velocidade);
        chvel(l,ALIEN3,*velocidade);
    }
}

void rmv_out(t_lista *l){
    rmvx(l,NAVEMAE,-8);
    rmvy(l,TIRO,0);
    rmvy(l,BOMBA,37);
}

void alien_shoot(t_lista *l, int vel){
    if(!inicializa_atual_ini(l))
        return;
    int tipo, x, y, estado;
    do{
        retorna_atual_est_tipo(l,&estado,&tipo);
        if(tipo>CANHAO && tipo<TIRO && estado==VIVO){
            if((rand()%1000)==1){
                retorna_atual_xy(l,&x,&y);
                insere_elemento(l,BOMBA,x+2,y+2,1,1,vel,4);
            }
        }
    }while(incrementa_atual(l));
}