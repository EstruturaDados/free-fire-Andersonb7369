#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura da mochila
typedef struct {
    Item itens[MAX_ITENS];
    int nItens;
} Mochila;

// inicializando funções
void InicializaMochila(Mochila *mochila);
void InserirItem(Mochila *mochila, const char* nome, const char* tipo, int quantidade);
void RemoverItem(Mochila *mochila, const char* nome);
void ListarItens(Mochila *mochila);
void BuscarItem(Mochila *mochila, const char* nome);

int main() {
    Mochila mochila;
    InicializaMochila(&mochila);

    int opcao;
    char nome[30], tipo[20];
    int quantidade;

    do {
        printf("\n==============================================");
        printf("\n  MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA");
        printf("\n==============================================");
        printf("\nITENS NA MOCHILA: %d/%d\n", mochila.nItens, MAX_ITENS);
        printf("\n1. ADICIONAR ITEM");
        printf("\n2. REMOVER ITEM");
        printf("\n3. LISTAR ITENS");
        printf("\n4. BUSCAR ITEM");
        printf("\n0. SAIR");
        printf("\n----------------------------------------------");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                if (mochila.nItens < MAX_ITENS) {
                    printf("Nome do item: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    printf("Tipo do item: ");
                    fgets(tipo, sizeof(tipo), stdin);
                    tipo[strcspn(tipo, "\n")] = 0;

                    printf("Quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();

                    InserirItem(&mochila, nome, tipo, quantidade);
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2:
                printf("Nome do item para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                RemoverItem(&mochila, nome);
                break;

            case 3:
                ListarItens(&mochila);
                break;

            case 4:
                printf("Nome do item para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                BuscarItem(&mochila, nome);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Inicializa a mochila
void InicializaMochila(Mochila *mochila) {
    mochila->nItens = 0;
}

// Insere um item na mochila
void InserirItem(Mochila *mochila, const char* nome, const char* tipo, int quantidade) {
    strcpy(mochila->itens[mochila->nItens].nome, nome);
    strcpy(mochila->itens[mochila->nItens].tipo, tipo);
    mochila->itens[mochila->nItens].quantidade = quantidade;
    mochila->nItens++;
    printf("Item inserido com sucesso!\n");
}

// Remove um item da mochila
void RemoverItem(Mochila *mochila, const char* nome) {
    int pos = -1;
    for (int i = 0; i < mochila->nItens; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Item não encontrado.\n");
        return;
    }
    for (int i = pos; i < mochila->nItens - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }
    mochila->nItens--;
    printf("Item removido com sucesso!\n");
}

// Lista todos os itens da mochila
void ListarItens(Mochila *mochila) {
    printf("\n--------- ITENS NA MOCHILA -------------\n");
    printf("NOME           | TIPO         | QUANTIDADE\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < mochila->nItens; i++) {
        printf("%-14s | %-12s | %d\n", 
            mochila->itens[i].nome, 
            mochila->itens[i].tipo, 
            mochila->itens[i].quantidade);
    }
    printf("----------------------------------------\n");
}

// Busca um item pelo nome
void BuscarItem(Mochila *mochila, const char* nome) {
    for (int i = 0; i < mochila->nItens; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            printf("Item encontrado: %s | %s | %d\n", 
                mochila->itens[i].nome, 
                mochila->itens[i].tipo, 
                mochila->itens[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado.\n");
}