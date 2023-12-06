#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

typedef struct No {
    Produto produto;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
} ListaEstoque;

ListaEstoque* inicializarLista() {
    ListaEstoque* lista = (ListaEstoque*)malloc(sizeof(ListaEstoque));
    lista->inicio = NULL;
    return lista;
}

void adicionarProduto(ListaEstoque* lista) {
    Produto novoProduto;
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);
    fflush(stdin);
    printf("Digite a descricao do produto: ");
    scanf("%s", novoProduto.descricao);
    fflush(stdin);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);
    fflush(stdin);
    printf("Digite o valor do produto: ");
    scanf("%f", &novoProduto.valor);
    fflush(stdin);

    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->produto = novoProduto;
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;

    printf("Produto adicionado com sucesso!\n");
}

void imprimirRelatorio(ListaEstoque* lista) {
    No* atual = lista->inicio;

    printf("\nRelatorio de Produtos:\n");
    while (atual != NULL) {
        printf("Codigo: %d\n", atual->produto.codigo);
        printf("Descricao: %s\n", atual->produto.descricao);
        printf("Quantidade: %d\n", atual->produto.quantidade);
        printf("Valor: %.2f\n\n", atual->produto.valor);

        atual = atual->proximo;
    }
}

void pesquisarProduto(ListaEstoque* lista) {
    int codigo;
    printf("Digite o codigo do produto a ser pesquisado: ");
    scanf("%d", &codigo);
    fflush(stdin);

    No* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", atual->produto.codigo);
            printf("Descricao: %s\n", atual->produto.descricao);
            printf("Quantidade: %d\n", atual->produto.quantidade);
            printf("Valor: %.2f\n\n", atual->produto.valor);
            return;
        }
        atual = atual->proximo;
    }

    printf("\nProduto nao encontrado.\n");
}

void removerProduto(ListaEstoque* lista) {
    int codigo;
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);
    fflush(stdin);

    No* atual = lista->inicio;
    No* anterior = NULL;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            if (anterior == NULL) {
                
                lista->inicio = atual->proximo;
            } else {
                
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("\nProduto removido com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nProduto nao encontrado.\n");
}

void liberarLista(ListaEstoque* lista) {
    No* atual = lista->inicio;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int main() {
    ListaEstoque* estoque = inicializarLista();
    int escolha;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Imprimir Relatório\n");
        printf("3. Pesquisar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        fflush(stdin);

        switch (escolha) {
            case 1:
                adicionarProduto(estoque);
                break;
            case 2:
                imprimirRelatorio(estoque);
                break;
            case 3:
                pesquisarProduto(estoque);
                break;
            case 4:
                removerProduto(estoque);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (escolha != 0);

    // Liberar a memória alocada para a lista
    liberarLista(estoque);

    return 0;
}