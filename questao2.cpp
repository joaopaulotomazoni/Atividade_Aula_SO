#include <iostream>
using namespace std;

#define HASH_SIZE 10 

struct HashNode {
    int num_pag;
    int frame;
    HashNode* prox;
};

HashNode* tabela_hash[HASH_SIZE];

void inicializar_tabela() {
    for (int i = 0; i < HASH_SIZE; i++) {
        tabela_hash[i] = NULL;
    }
}

int hash_func(int num_pag) {
    return num_pag % HASH_SIZE;
}

void inserir_pagina(int num_pag, int frame) {
    int indice = hash_func(num_pag);

    HashNode* novoNode = new HashNode();
    novoNode->num_pag = num_pag;
    novoNode->frame = frame;
    novoNode->prox = NULL;

    if (tabela_hash[indice] == NULL) {
        tabela_hash[indice] = novoNode;
    } else {
        novoNode->prox = tabela_hash[indice];
        tabela_hash[indice] = novoNode;
    }

    cout << "Página inserida: Num_Pag " << num_pag << " mapeada para Frame " << frame << " (Indice Hash: " << indice << ")\n";
}

int traduzir_endereco(int num_pag) {
    int indice = hash_func(num_pag);
    HashNode* atual = tabela_hash[indice];

    while (atual != NULL) {
        if (atual->num_pag == num_pag) {
            cout << "Frame encontrado! Pagina " << num_pag << " esta no Frame Fisico " << atual->frame << "\n";
            return atual->frame;
        }
        atual = atual->prox;
    }

    cout << "Page fault (Pagina " << num_pag << " nao encontrada na tabela hash)\n";
    return -1;
}

int main() {
    inicializar_tabela();

    cout << "Inserir:\n";
    inserir_pagina(105, 12); 
    inserir_pagina(250, 45);
    inserir_pagina(115, 13);

    cout << "\nTraduzir:\n";
    traduzir_endereco(105);
    traduzir_endereco(250);
    traduzir_endereco(115);

    cout << "\nSimular:\n";
    traduzir_endereco(999);
    traduzir_endereco(107);

    return 0;
}
