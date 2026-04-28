#include <iostream>
using namespace std;

#define FILHOS 10

typedef struct PageTable PageTable;

typedef struct FilhoNode {
    PageTable *filho;
    struct FilhoNode *prox;
} FilhoNode;

struct PageTable {
    int id;
    int frame;
    PageTable *pai;
    FilhoNode *lista_filhos;
};

PageTable* criarPagina(int id){
    PageTable *novaPagina = new PageTable();
    novaPagina->id = id;
    novaPagina->frame = -1;
    novaPagina->pai=NULL;
    novaPagina->lista_filhos=NULL;

    return(novaPagina);
}

void adicionarFilho(PageTable *pai, PageTable *filho){
    FilhoNode *novoFilho = new FilhoNode();
    novoFilho->filho=filho;
    novoFilho->prox=pai->lista_filhos;
    pai->lista_filhos = novoFilho;
    filho->pai = pai;
}

PageTable* buscarFilho(PageTable *pai, int id) {
    FilhoNode *atual = pai->lista_filhos;
    while(atual != NULL) {
        if (atual->filho->id == id) return atual->filho;
        atual = atual->prox;
    }
    return NULL;
}

void inserir_pagina(PageTable *root, int num_pag, int frame) {
    int dir_id = num_pag / 100;
    int page_id = num_pag % 100;
    
    PageTable *diretorio = buscarFilho(root, dir_id);
    if (diretorio == NULL) {
        diretorio = criarPagina(dir_id);
        adicionarFilho(root, diretorio);
    }
    
    PageTable *pagina = buscarFilho(diretorio, page_id);
    if (pagina == NULL) {
        pagina = criarPagina(page_id);
        adicionarFilho(diretorio, pagina);
    }
    
    pagina->frame = frame;
    cout << "Página inserida: Num_Pag " << num_pag << " alocada no Frame " << frame << "\n";
}

int traduzir_endereco(PageTable *root, int num_pag) {
    int dir_id = num_pag / 100;
    int page_id = num_pag % 100;

    PageTable *diretorio = buscarFilho(root, dir_id);
    if (diretorio == NULL) {
        cout << "Page fault (Diretorio nao encontrado para a pagina " << num_pag << ")\n";
        return -1;
    }

    PageTable *pagina = buscarFilho(diretorio, page_id);
    if (pagina == NULL || pagina->frame == -1) {
        cout << "Page fault (Pagina nao mapeada para a pagina " << num_pag << ")\n";
        return -1;
    }

    cout << "Frame encontrado! Pagina " << num_pag << " esta no Frame Fisico " << pagina->frame << "\n";
    return pagina->frame;
}

int main(){
    PageTable *tabela_multinivel = criarPagina(0);

    cout << "Inserir:\n";
    inserir_pagina(tabela_multinivel, 105, 12);
    inserir_pagina(tabela_multinivel, 250, 45);
    inserir_pagina(tabela_multinivel, 106, 13);

    cout << "\nTraduzir:\n";
    traduzir_endereco(tabela_multinivel, 105);
    traduzir_endereco(tabela_multinivel, 250);
    
    cout << "\nSimular:\n";
    traduzir_endereco(tabela_multinivel, 999);
    traduzir_endereco(tabela_multinivel, 107);

    return 0;
}
