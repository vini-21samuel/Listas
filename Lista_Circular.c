#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista circular
struct No {
    int dado;
    struct No* proximo;
};

// Função para criar um novo nó
struct No* criarNo(int dado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inserir um nó no início da lista circular
void inserirNoInicio(struct No** cabeca, int dado) {
    // Cria um novo nó
    struct No* novoNo = criarNo(dado);

    if (*cabeca == NULL) {
        // Se a lista estiver vazia, o nó aponta para ele mesmo
        novoNo->proximo = novoNo;
        *cabeca = novoNo;
    } else {
        // Se a lista não estiver vazia, ajusta os ponteiros para incluir o novo nó
        struct No* temp = *cabeca;
        while (temp->proximo != *cabeca) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
        novoNo->proximo = *cabeca;
        *cabeca = novoNo;
    }
}

// Função para inserir um nó no final da lista circular
void inserirNoFim(struct No** cabeca, int dado) {
    // Cria um novo nó
    struct No* novoNo = criarNo(dado);

    if (*cabeca == NULL) {
        // Se a lista estiver vazia, o nó aponta para ele mesmo
        novoNo->proximo = novoNo;
        *cabeca = novoNo;
    } else {
        // Se a lista não estiver vazia, ajusta os ponteiros para incluir o novo nó
        struct No* temp = *cabeca;
        while (temp->proximo != *cabeca) {
            temp = temp->proximo;
        }
        temp->proximo = novoNo;
        novoNo->proximo = *cabeca;
    }
}

// Função para inserir um nó em uma posição específica da lista circular
void inserirNaPosicao(struct No** cabeca, int dado, int posicao) {
    if (posicao < 1) {
        printf("Posição inválida\n");
        return;
    }

    if (posicao == 1) {
        // Se a posição for 1, insere no início
        inserirNoInicio(cabeca, dado);
        return;
    }

    // Cria um novo nó
    struct No* novoNo = criarNo(dado);
    struct No* temp = *cabeca;

    for (int i = 1; i < posicao - 1 && temp != NULL; ++i) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Posição inválida\n");
        return;
    }

    // Ajusta os ponteiros para incluir o novo nó
    novoNo->proximo = temp->proximo;
    temp->proximo = novoNo;
}

// Função para excluir o nó do início da lista circular
void excluirDoInicio(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }

    struct No* temp = *cabeca;
    while (temp->proximo != *cabeca) {
        temp = temp->proximo;
    }

    if (*cabeca == temp) {
        // Se houver apenas um nó na lista, remove o nó
        *cabeca = NULL;
    } else {
        // Ajusta os ponteiros para excluir o nó do início
        temp->proximo = (*cabeca)->proximo;
        *cabeca = (*cabeca)->proximo;
    }

    free(temp);
}

// Função para excluir o nó do final da lista circular
void excluirDoFim(struct No** cabeca) {
    if (*cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }

    struct No* temp = *cabeca;
    while (temp->proximo->proximo != *cabeca) {
        temp = temp->proximo;
    }

    struct No* ultimoNo = temp->proximo;
    temp->proximo = *cabeca;
    free(ultimoNo);
}

// Função para excluir o nó de uma posição específica da lista circular
void excluirDaPosicao(struct No** cabeca, int posicao) {
    if (*cabeca == NULL || posicao < 1) {
        printf("Posição inválida\n");
        return;
    }

    if (posicao == 1) {
        // Se a posição for 1, exclui do início
        excluirDoInicio(cabeca);
        return;
    }

    struct No* temp = *cabeca;

    for (int i = 1; i < posicao - 1 && temp != NULL; ++i) {
        temp = temp->proximo;
    }

    if (temp == NULL || temp->proximo == *cabeca) {
        printf("Posição inválida\n");
        return;
    }

    // Ajusta os ponteiros para excluir o nó da posição específica
    struct No* noParaExcluir = temp->proximo;
    temp->proximo = temp->proximo->proximo;
    free(noParaExcluir);
}

// Função para buscar um nó com dado valor na lista circular
struct No* buscarNo(struct No* cabeca, int dado) {
    struct No* temp = cabeca;
    if (temp != NULL) {
        do {
            if (temp->dado == dado) {
                return temp;
            }
            temp = temp->proximo;
        } while (temp != cabeca);
    }
    return NULL;
}

// Função para exibir os nós da lista circular
void exibirNos(struct No* cabeca) {
    struct No* temp = cabeca;
    if (temp != NULL) {
        do {
            printf("%d -> ", temp->dado);
            temp = temp->proximo;
        } while (temp != cabeca);
    }
    printf("NULL\n");
}

// Função para liberar a memória de todos os nós na lista circular
void limparLista(struct No** cabeca) {
    struct No* temp = *cabeca;
    while (temp != NULL) {
        struct No* proximo = temp->proximo;
        free(temp);
        temp = proximo;
        if (temp == *cabeca) {
            break;
        }
    }
    *cabeca = NULL;
}

// Função principal
int main() {
    struct No* cabeca = NULL;

    // Variáveis para armazenar a escolha do usuário, dado e posição
    int opcao, dado, posicao;

    // Loop principal do programa
    do {
        // Exibe o menu de opções
        
        printf("________________________________");
        printf("\n1 - Inserir no Inicio           |\n");
        printf("2 - Inserir no Fim              |\n");
        printf("3 - Inserir em uma posicao      |\n");
        printf("4 - Excluir do Inicio           |\n");
        printf("5 - Excluir do Fim              |\n");
        printf("6 - Excluir de uma Posicao      |\n");
        printf("7 - Buscar No                   |\n");
        printf("8 - Exibir Lista                |\n");
        printf("9 - Limpar Lista                |\n");
        printf("0 - Sair                        |\n");
        printf("________________________________|\n");
        

        // Solicita a escolha do usuário
        printf("\nEscolha a opção: ");
        scanf("%d", &opcao);

        // Executa a operação correspondente à escolha do usuário
        switch (opcao) {
            case 1:
                printf("Digite o dado a ser inserido: ");
                scanf("%d", &dado);
                inserirNoInicio(&cabeca, dado);
                break;

            case 2:
                printf("Digite o dado a ser inserido: ");
                scanf("%d", &dado);
                inserirNoFim(&cabeca, dado);
                break;

            case 3:
                printf("Digite o dado a ser inserido: ");
                scanf("%d", &dado);
                printf("Digite a posição: ");
                scanf("%d", &posicao);
                inserirNaPosicao(&cabeca, dado, posicao);
                break;

            case 4:
                excluirDoInicio(&cabeca);
                break;

            case 5:
                excluirDoFim(&cabeca);
                break;

            case 6:
                printf("Digite a posição: ");
                scanf("%d", &posicao);
                excluirDaPosicao(&cabeca, posicao);
                break;

            case 7:
                printf("Digite o dado a ser buscado: ");
                scanf("%d", &dado);
                struct No* resultadoBusca = buscarNo(cabeca, dado);
                if (resultadoBusca != NULL) {
                    printf("Nó encontrado: %d\n", resultadoBusca->dado);
                } else {
                    printf("Nó não encontrado\n");
                }
                break;

            case 8:
                exibirNos(cabeca);
                break;

            case 9:
                limparLista(&cabeca);
                printf("Lista limpa.\n");
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
