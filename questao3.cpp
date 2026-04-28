#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int num_pag;
}TabelaInvertida;

TabelaInvertida Tabela_Global[1024];
int offset = 3;

void preencher_tabela(){
    for(int i=0; i<1024; i++){
        if(i%2 == 0){
            Tabela_Global[i].pid = rand() % 10000;
            Tabela_Global[i].num_pag = i;
        } else {
            Tabela_Global[i].pid = -1;
            Tabela_Global[i].num_pag = -1;
        }
    }
}

bool inserir_pagina(int pid, int num_pag){
    for(int i=0; i<1024; i++){
        if(Tabela_Global[i].pid == -1 && Tabela_Global[i].num_pag == -1){
            Tabela_Global[i].pid = pid;
            Tabela_Global[i].num_pag = num_pag;
            printf("\nPágina inserida: PID %d, Num_Pag %d alocada no Frame %d", pid, num_pag, i);
            return true;
        }
    }
    printf("\nErro: Memória física cheia (Page Replacement necessário).\n");
    return false;
}

void listar_tabela(int ini, int fim){
    for(int i = ini-1; i<fim; i++){
        printf("\n============================");
        printf("\n[%d] pid: %d", i, Tabela_Global[i].pid);
        printf("\n[%d] num_pag: %d", i, Tabela_Global[i].num_pag);
    }
}

int traduzir_endereco(int pid_b, int num_pag_b){

    for(int i=0; i<1024; i++){
        if(Tabela_Global[i].pid == pid_b && Tabela_Global[i].num_pag == num_pag_b){
            printf("\nFrame encontrado na posição %d, posição física: %d\n", i, i+offset);
            return i + offset;
        }
    }
    printf("\nPage fault\n");
    return -1;
}

int main(){

    preencher_tabela(); 
    listar_tabela(10, 20);

    traduzir_endereco(Tabela_Global[10].pid, Tabela_Global[10].num_pag);

    inserir_pagina(1234, 555);
    traduzir_endereco(1234, 555);

    traduzir_endereco(99999, 99999);

    return 0;
}
