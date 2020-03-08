#include"alien_lista.h"
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>

void inicializa_lista(t_lista *l){
    l->ini=l->fim=l->atual=NULL;
}

int inicializa_atual_ini(t_lista *l){
    l->atual=l->ini;
    if(l->atual==NULL)
        return 0;
    return 1;
}

int inicializa_atual_fim(t_lista *l){
    l->atual=l->fim;
    if(l->atual==NULL)
        return 0;
    return 1;
}

int inicializa_atual_prim_tipo(t_lista *l, int tipo){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo){
            l->atual=p;
            return 1;
        }
        p=p->prox;
    }
    return 0;
}

int incrementa_atual(t_lista *l){
    if(l->atual==NULL)
        return 0;
    l->atual=l->atual->prox;
    if(l->atual==NULL)
        return 0;
    return 1;
}

int decrementa_atual(t_lista *l){
    if(l->atual==NULL)
        return 0;
    l->atual=l->atual->prev;
    if(l->atual==NULL)
        return 0;
    return 1;
}

int retorna_atual_xy(t_lista *l, int *x, int *y){
    if(l->atual==NULL)
        return 0;
    *x=l->atual->x;
    *y=l->atual->y;
    return 1;
}
int retorna_atual_est_tipo(t_lista *l, int *estado, int *tipo){
    if(l->atual==NULL)
        return 0;
    *estado=l->atual->estado;
    *tipo=l->atual->tipo;
    return 1;
}
int retorna_atual_dimen(t_lista *l, int *altura, int *largura){
    if(l->atual==NULL)
        return 0;
    *altura=l->atual->altura;
    *largura=l->atual->largura;
    return 1;
}
int retorna_atual_sprite(t_lista *l, int *sprite){
    if(l->atual==NULL)
        return 0;
    *sprite=l->atual->sprite+1;
    return 1;
}

void mata_atual(t_lista *l){
    if(l->atual==NULL)
        return;
    l->atual->estado=MORTO;
}

int num_tipo(t_lista *l, int tipo){
    t_nodo *p;
    int contagem=0;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo)
            contagem++;
        p=p->prox;
    }
    return contagem;
}

int insere_elemento(t_lista *l,int tipo,int x, int y, int i, int j, int v, int sprites){
    t_nodo *new;
    new=(t_nodo *)malloc(sizeof(t_nodo));
    if(new==NULL)
        return 0;
    new->tipo=tipo;
    new->x=x;
    new->y=y;
    new->estado=VIVO;
    new->largura=j;
    new->altura=i;
    new->velocidade=v;
    new->velaux=0;
    new->sprite=0;
    new->death=0;
    new->numsprites=sprites;
    if(l->ini==NULL){
        new->prev=new->prox=NULL;
        l->ini=l->fim=new;
    }
    else{
        new->prox=NULL;
        new->prev=l->fim;
        l->fim->prox=new;
        l->fim=new;
    }
    return 1;
}

int checkcol2k(t_lista *l, int tipo1, int tipo2){
    t_nodo *p, *q;
    int colisoes=0;
    short sucesso=0;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo1 && p->estado!=MORTO){
            q=l->ini;
                while(q!=NULL){
                    if(q->tipo==tipo2 && q->estado!=MORTO){
                        sucesso=0;
                        if(p->x==q->x ||(p->x<q->x && p->x+p->largura>q->x))
                            sucesso++;
                        else if(p->x==q->x ||(q->x<p->x && q->x+q->largura>p->x))
                            sucesso++;
                        if(p->y==q->y ||(p->y<q->y && p->y+p->altura>q->y))
                            sucesso++;
                        else if(p->y==q->y ||(q->y<p->y && q->y+q->altura>p->y))
                            sucesso++;
                        if(sucesso==2){
                            p->estado=q->estado=MORTO;
                            colisoes++;
                        }
                    }
                    q=q->prox;
                }
        }
        p=p->prox;
    }
    return colisoes;
}

int checkcol1k(t_lista *l, int tipo1, int tipo2){
    t_nodo *p, *q;
    int colisoes=0;
    short sucesso=0;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo1 && p->estado!=MORTO){
            q=l->ini;
                while(q!=NULL){
                    if(q->tipo==tipo2 && q->estado!=MORTO){
                        sucesso=0;
                        if(p->x==q->x ||(p->x<q->x && p->x+p->largura>q->x))
                            sucesso++;
                        else if(q->x<p->x && q->x+q->largura>p->x)
                            sucesso++;
                        if(p->y==q->y ||(p->y<q->y && p->y+p->altura>q->y))
                            sucesso++;
                        else if(q->y<p->y && q->y+q->altura>p->y)
                            sucesso++;
                        if(sucesso==2){
                            q->estado=MORTO;
                            colisoes++;
                        }
                    }
                    q=q->prox;
                }
        }
        p=p->prox;
    }
    return colisoes;
}

int checa_coluna(t_lista *l, int tipo, int x){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && (p->x==x || (p->x<x && p->x+p->largura>x)))
            return 1;
        p=p->prox;
    }
    return 0;
}

int checa_linha(t_lista *l, int tipo, int y){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && (p->y==y || (p->y<y && p->y+p->altura>y)))
            return 1;
        p=p->prox;
    }
    return 0;
}

void addvh(t_lista *l, int tipo, int direcao){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo){
            if(p->velaux==0){
                p->x+=direcao;
                p->sprite=(p->sprite+1)%p->numsprites;
            }
            p->velaux=(p->velaux+1)%p->velocidade;
        }
        p=p->prox;
    }
}

void addvv(t_lista *l, int tipo, int direcao){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo){
            if(p->velaux==0){
                p->y+=direcao;
                p->sprite=(p->sprite+1)%p->numsprites;
            }
            p->velaux=(p->velaux+1)%p->velocidade;
        }
        p=p->prox;
    }
}

void mvh(t_lista *l, int tipo, int direcao){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo){
            p->x+=direcao;
            p->sprite=(p->sprite+1)%p->numsprites;
        }
        p=p->prox;
    }
}

void mvv(t_lista *l, int tipo, int direcao){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo){
            p->y+=direcao;
            p->sprite=(p->sprite+1)%p->numsprites;
        }
        p=p->prox;
    }
}

void addvsprite(t_lista *l, int tipo){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo)
            p->sprite=(p->sprite+1)%p->numsprites;
        p=p->prox;
    }
}

void incrsdead(t_lista *l){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->estado==MORTO)
            p->death++;
        p=p->prox;
    }
}

void rmvdead(t_lista *l, int tipo, int dead){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && p->death>dead){
            if(p==l->ini && p==l->fim){
                l->ini=l->fim=NULL;
            }
            else if(p==l->ini){
                l->ini=p->prox;
                l->ini->prev=NULL;
            }
            else if(p==l->fim){
                l->fim=p->prev;
                l->fim->prox=NULL;
            }
            else{
                p->prev->prox=p->prox;
                p->prox->prev=p->prev;
            }
            free(p);
            p=l->ini;
        }
        else
            p=p->prox;
    }
}

void rmvx(t_lista *l, int tipo, int x){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && p->x==x){
            if(p==l->ini && p==l->fim){
                l->ini=l->fim=NULL;
            }
            else if(p==l->ini){
                l->ini=p->prox;
                l->ini->prev=NULL;
            }
            else if(p==l->fim){
                l->fim=p->prev;
                l->fim->prox=NULL;
            }
            else{
                p->prev->prox=p->prox;
                p->prox->prev=p->prev;
            }
            free(p);
            p=l->ini;
        }
        else
            p=p->prox;
    }
}

void rmvy(t_lista *l, int tipo, int y){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && p->y==y){
            if(p==l->ini && p==l->fim){
                l->ini=l->fim=NULL;
            }
            else if(p==l->ini){
                l->ini=p->prox;
                l->ini->prev=NULL;
            }
            else if(p==l->fim){
                l->fim=p->prev;
                l->fim->prox=NULL;
            }
            else{
                p->prev->prox=p->prox;
                p->prox->prev=p->prev;
            }
            free(p);
            p=l->ini;
        }
        else
            p=p->prox;
    }
}

void rmvxy(t_lista *l, int tipo, int x, int y){
    t_nodo *p;
    p=l->ini;
    while(p!=NULL){
        if(p->tipo==tipo && p->x==x && p->y==y){
            if(p==l->ini && p==l->fim){
                l->ini=l->fim=NULL;
            }
            else if(p==l->ini){
                l->ini=p->prox;
                l->ini->prev=NULL;
            }
            else if(p==l->fim){
                l->fim=p->prev;
                l->fim->prox=NULL;
            }
            else{
                p->prev->prox=p->prox;
                p->prox->prev=p->prev;
            }
            free(p);
            p=l->ini;
        }
        else
            p=p->prox;
    }
}

void destroi_lista(t_lista *l){
    if(l->ini==l->fim){
        free(l->ini);
        l->ini=l->fim=l->atual=NULL;
        return;
    }
    t_nodo *p, *q;
    p=l->ini;
    q=p->prox;
    while(q!=NULL){
        free(p);
        p=q;
        q=q->prox;
    }
    free(p);
}

void chvel(t_lista *l, int tipo, int vel){
    t_nodo *p;
    p=l->ini;
    if(vel<1)
        vel=1;
    while(p!=NULL){
        if(p->tipo==tipo)
            p->velocidade=vel;
        p=p->prox;
    }
}