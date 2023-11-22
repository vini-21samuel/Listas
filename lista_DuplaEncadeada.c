#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó na lista duplamente encadeada
struct No {
    int dado;
    struct No* proximo;
    struct No* anterior;
};

// Função para criar um novo nó com o dado fornecido
struct No* criarNo(int dado) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

// Função para inserir um nó no início da lista
void inserirNoInicio(struct No** cabeca, int dado) {
    // Cria um novo nó com o dado fornecido
    struct No* novoNo = criarNo(dado);

    // Configura os ponteiros do novo nó
    novoNo->proximo = *cabeca;
    if (*cabeca != NULL) {
        (*cabeca)->anterior = novoNo;
    }

    // Atualiza a cabeça da lista para apontar para o novo nó
    *cabeca = novoNo;
}

// Função para inserir um nó no final da lista
void inserirNoFim(struct No** cabeca, int dado) {
    // Cria um novo nó com o dado fornecido
    struct No* novoNo = criarNo(dado);

    // Caso especial: lista vazia
    if (*cabeca == NULL) {
        *cabeca = novoNo;
        return;
    }

    // Encontra o último nó na lista
    struct No* temp = *cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }

    // Configura os ponteiros do novo nó
    temp->proximo = novoNo;
    novoNo->anterior = temp;
}

// Função para inserir um nó em uma posição específica da lista
void inserirNaPosicao(struct No** cabeca, int dado, int posicao) {
    // Verifica se a posição é válida
    if (posicao < 1) {
        printf("Posição inválida\n");
        return;
    }

    // Caso especial: inserção no início
    if (posicao == 1) {
        inserirNoInicio(cabeca, dado);
        return;
    }

    // Cria um novo nó com o dado fornecido
    struct No* novoNo = criarNo(dado);

    // Encontra o nó na posição anterior à posição desejada
    struct No* temp = *cabeca;
    for (int i = 1; i < posicao - 1 && temp != NULL; ++i) {
        temp = temp->proximo;
    }

    // Verifica se a posição é válida
    if (temp == NULL) {
        printf("Posição inválida\n");
        return;
    }

    // Configura os ponteiros do novo nó
    novoNo->proximo = temp->proximo;
    novoNo->anterior = temp;
    if (temp->proximo != NULL) {
        temp->proximo->anterior = novoNo;
    }
    temp->proximo = novoNo;
}

// Função para excluir o nó do início da lista
void excluirDoInicio(struct No** cabeca) {
    // Verifica se a lista está vazia
    if (*cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }

    // Armazena o nó a ser removido
    struct No* temp = *cabeca;

    // Atualiza a cabeça da lista para o próximo nó
    *cabeca = (*cabeca)->proximo;

    // Atualiza o ponteiro anterior do novo nó da cabeça para NULL
    if (*cabeca != NULL) {
        (*cabeca)->anterior = NULL;
    }

    // Libera a memória do nó removido
    free(temp);
}

// Função para excluir o nó do final da lista
void excluirDoFim(struct No** cabeca) {
    // Verifica se a lista está vazia
    if (*cabeca == NULL) {
        printf("Lista vazia\n");
        return;
    }

    // Encontra o último nó na lista
    struct No* temp = *cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }

    // Caso especial: remoção do único nó na lista
    if (temp->anterior == NULL) {
        *cabeca = NULL;
    } else {
        // Atualiza o ponteiro próximo do nó anterior para NULL
        temp->anterior->proximo = NULL;
    }

    // Libera a memória do nó removido
    free(temp);
}

// Função para excluir o nó de uma posição específica da lista
void excluirDaPosicao(struct No** cabeca, int posicao) {
    // Verifica se a lista está vazia ou se a posição é inválida
    if (*cabeca == NULL || posicao < 1) {
        printf("Posição inválida\n");
        return;
    }

    // Encontra o nó na posição desejada
    struct No* temp = *cabeca;
    for (int i = 1; i < posicao && temp != NULL; ++i) {
        temp = temp->proximo;
    }

    // Verifica se a posição é válida
    if (temp == NULL) {
        printf("Posição inválida\n");
        return;
    }

    // Caso especial: remoção do primeiro nó
    if (temp->anterior == NULL) {
        *cabeca = temp->proximo;
    } else {
        // Atualiza o ponteiro próximo do nó anterior para o próximo nó
        temp->anterior->proximo = temp->proximo;
    }

    // Atualiza o ponteiro anterior do próximo nó para o nó anterior
    if (temp->proximo != NULL) {
        temp->proximo->anterior = temp->anterior;
    }

    // Libera a memória do nó removido
    free(temp);
}

// Função para buscar um nó com dado valor na lista
struct No* buscarNo(struct No* cabeca, int dado) {
    // Percorre a lista procurando pelo nó com o dado fornecido
    while (cabeca != NULL) {
        if (cabeca->dado == dado) {
            return cabeca;
        }
        cabeca = cabeca->proximo;
    }

    // Retorna NULL se o nó não for encontrado
    return NULL;
}

// Função para exibir os nós da lista
void exibirNos(struct No* cabeca) {
    // Percorre a lista exibindo cada nó
    while (cabeca != NULL) {
        printf("%d <-> ", cabeca->dado);
        cabeca = cabeca->proximo;
    }

    // Indica o fim da lista
    printf("NULL\n");
}

// Função principal
int main() {
    // Inicializa a cabeça da lista como NULL
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
        printf("0 - Sair                        |\n");
        printf("________________________________|");

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

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
