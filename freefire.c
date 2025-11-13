#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_ITENS 10

typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} item;

struct itemEncadeado
{
    char nome[30];
    char tipo[20];
    int quantidade;
    struct itemEncadeado *proximo;
};

// Função para cadastrar itens no array de itens.
// Parâmetros:
//   itens: ponteiro para o array de itens a ser preenchido.
//   contador: ponteiro para o contador de itens cadastrados.
void cadastrarItem(item *itens, int *contador)
{

    while (*contador < MAX_ITENS)
    {
        // ler nome (com espaços)
        printf("Digite o nome do item: ");
        if (fgets(itens[*contador].nome, sizeof(itens[*contador].nome), stdin))
        {
            itens[*contador].nome[strcspn(itens[*contador].nome, "\r\n")] = '\0'; // remove newline
        }
        // ler tipo (com fgets) ou usar scanf("%19s") se não quiser espaços

        printf("Digite o tipo do item: ");
        if (fgets(itens[*contador].tipo, sizeof(itens[*contador].tipo), stdin))
        {
            itens[*contador].tipo[strcspn(itens[*contador].tipo, "\r\n")] = '\0';
        }
        printf("Digite a quantidade do item: ");
        while (scanf("%d", &itens[*contador].quantidade) != 1)
        {
            printf("Entrada inválida. Digite um número inteiro para a quantidade: ");
            while (getchar() != '\n')
                ; // Limpa o buffer de entrada
        }
        // Limpa o buffer após ler o inteiro
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
        (*contador)++;
    }
}

void removerItem(item *itens, int *qtdItens, const char *nomeRemover)
{

    // loop para percorrer o array de itens
    for (int i = 0; i < *qtdItens; i++)
    {
        // se o nome do item atual for igual ao nome a ser removido
        if (strcmp(itens[i].nome, nomeRemover) == 0)
        {
            // desloca os itens seguintes para preencher o espaço do item removido, ou seja, sobrescreve o item a ser removido
            // item na posição i é substituído pelo item na posição i+1, e assim por diante
            for (int j = i; j < *qtdItens - 1; j++)
            {
                itens[j] = itens[j + 1];
            }
            (*qtdItens)--;
            printf("Item '%s' removido com sucesso.\n", nomeRemover);
            return;
        }
    }
    printf("Item '%s' não encontrado.\n", nomeRemover);
}

void listarItens(const item *itens, int contador)
{
    printf("Lista de Itens:\n");
    for (int i = 0; i < contador; i++)
    {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
}

void buscarItem(const item *itens, int qtdItens, const char *nomeBuscar)
{
    for (int i = 0; i < qtdItens; i++)
    {
        if (strcmp(itens[i].nome, nomeBuscar) == 0)
        {
            printf("Item encontrado: Nome: %s, Tipo: %s, Quantidade: %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
            return;
        }
    }
    printf("Item '%s' não encontrado.\n", nomeBuscar);
}

void buscaBinariaItem(const item *itens, int qtdItens, const char *nomeBuscar)
{
    int esquerda = 0;
    int direita = qtdItens - 1;

    while (esquerda <= direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(itens[meio].nome, nomeBuscar);

        if (cmp == 0)
        {
            printf("Item encontrado: Nome: %s, Tipo: %s, Quantidade: %d\n", itens[meio].nome, itens[meio].tipo, itens[meio].quantidade);
            return;
        }
        else if (cmp < 0)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }
    printf("Item '%s' não encontrado.\n", nomeBuscar);
}

void bubbleSortItemsPorNome(item *itens, int qtdItens)
{
    int i, j;

    // definindo variável auxiliar para troca
    item aux;
    // j começa em 1 porque a cada iteração o maior elemento "sobe" para o final do array
    for (j = 1; j < qtdItens; j++)
    {
        // loop para comparar elementos adjacentes, ou seja itens[i] e itens[i+1], qtdItens-1 para evitar acessar fora do array
        for (i = 0; i < qtdItens - 1; i++)
        {
            // comparando os nomes dos itens adjacentes
            if (strcmp(itens[i].nome, itens[i + 1].nome) > 0)
            {
                // auxiliar recebe o atual
                aux = itens[i];
                // atual recebe o próximo
                itens[i] = itens[i + 1];
                // próximo recebe o atual do auxiliar
                itens[i + 1] = aux;
            }
        }
    }
    for (i = 0; i < qtdItens; i++)
    {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", itens[i].nome, itens[i].tipo, itens[i].quantidade);
    }
}

void cadastrarItemEncadeado(struct itemEncadeado **inicio, int *contador)
{
    char novoNome[30];
    char novoTipo[20];
    int novaQuantidade;
    while (*contador < MAX_ITENS)
    {
        struct itemEncadeado *novo = (struct itemEncadeado *)malloc(sizeof(struct itemEncadeado));
        if (!novo)
        {
            printf("Erro ao alocar memória para novo item.\n");
            return;
        }
        printf("digite o nome do item: ");
        if (fgets(novoNome, sizeof(novoNome), stdin))
        {
            novoNome[strcspn(novoNome, "\r\n")] = '\0'; // remove newline
            strcpy(novo->nome, novoNome);
        }
        printf("digite o tipo do item: ");
        if (fgets(novoTipo, sizeof(novoTipo), stdin))
        {
            novoTipo[strcspn(novoTipo, "\r\n")] = '\0'; // remove newline
            strcpy(novo->tipo, novoTipo);
        }
        printf("digite a quantidade do item: ");
        scanf("%d", &novaQuantidade);
        novo->quantidade = novaQuantidade;
        novo->proximo = *inicio;
        *inicio = novo;
        (*contador)++;
        // Limpa o buffer após ler o inteiro
        while (getchar() != '\n')
            ;
    }
}

void listarItensEncadeados(struct itemEncadeado *inicio)
{
    struct itemEncadeado *atual = inicio;
    printf("Lista de Itens Encadeados:\n");
    while (atual != NULL)
    {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", atual->nome, atual->tipo, atual->quantidade);
        atual = atual->proximo;
    }
}

void removerItemEncadeado(struct itemEncadeado *inicio)
{
    struct itemEncadeado *atual = inicio;
    if (inicio != NULL)
    {
        inicio = inicio->proximo;
        free(atual);
        printf("Item removido com sucesso.\n");
    }
    else
    {
        printf("Lista vazia. Nenhum item para remover.\n");
    }
}

void buscaPorNomeEncadeado(struct itemEncadeado *inicio, const char *nomeBuscar)
{
    struct itemEncadeado *atual = inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nomeBuscar) == 0)
        {
            printf("Item encontrado: Nome: %s, Tipo: %s, Quantidade: %d\n", atual->nome, atual->tipo, atual->quantidade);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item '%s' não encontrado.\n", nomeBuscar);
}

void escolherStructMenu()
{
    printf("Escolha a estrutura de dados:\n");
    printf("1. Array Estático\n");
    printf("2. Lista Encadeada\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

void menu()
{
    printf("Menu de Opções - Lista Estática:\n");
    printf("1. Cadastrar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item\n");
    printf("5. Ordenar Itens por Nome\n");
    printf("6. Buscar Item (Busca Binária)\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

void menuEncadeado()
{
    printf("Menu de Opções - Lista Encadeada:\n");
    printf("1. Cadastrar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    system("cls || clear");
    item itens[MAX_ITENS];
    struct itemEncadeado *inicio = NULL;
    int contador = 0;
    int escolhaEstrutura;
    int opcao;
    int opcaoEncadeado;
    // int qtdItens = sizeof(itens) / sizeof(itens[0]);
    do
    {
        escolherStructMenu();
        char linhaOpcao[32];
        if (fgets(linhaOpcao, sizeof(linhaOpcao), stdin))
        {
            if (sscanf(linhaOpcao, "%d", &escolhaEstrutura) != 1)
            {
                escolhaEstrutura = -1; /* entrada inválida */
            }
        }
        else
        {
            escolhaEstrutura = 0; /* EOF / erro de leitura: sair */
        }
        switch (escolhaEstrutura)
        {
        case 0:
            /* code */
            break;
        case 1:
            system("cls || clear");
            do
            {

                menu();
                /* Ler a opção como linha para evitar deixar '\n' no stdin
                   (misturar scanf e fgets causa o problema observado). */
                char linhaOpcao[32];
                if (fgets(linhaOpcao, sizeof(linhaOpcao), stdin))
                {
                    if (sscanf(linhaOpcao, "%d", &opcao) != 1)
                    {
                        opcao = -1; /* entrada inválida */
                    }
                }
                else
                {
                    opcao = 0; /* EOF / erro de leitura: sair */
                }
                switch (opcao)
                {
                case 0:
                    printf("Saindo do programa.\n");
                    system("cls || clear");
                    break;
                case 1:
                    cadastrarItem(itens, &contador);
                    break;
                case 2:
                {
                    char nomeRemover[30];
                    printf("Digite o nome do item a ser removido: ");
                    if (fgets(nomeRemover, sizeof(nomeRemover), stdin))
                    {
                        nomeRemover[strcspn(nomeRemover, "\r\n")] = '\0'; // remove newline
                    }
                    removerItem(itens, &contador, nomeRemover);
                    break;
                }
                case 3:
                    listarItens(itens, contador);
                    break;
                case 4:
                {
                    char nomeBuscar[30];
                    printf("Digite o nome do item a ser buscado: ");
                    if (fgets(nomeBuscar, sizeof(nomeBuscar), stdin))
                    {
                        nomeBuscar[strcspn(nomeBuscar, "\r\n")] = '\0'; // remove newline
                    }
                    buscarItem(itens, contador, nomeBuscar);
                    break;
                }
                case 5:
                    bubbleSortItemsPorNome(itens, contador);
                    break;
                case 6:
                {
                    char nomeBuscar[30];
                    printf("Digite o nome do item a ser buscado (Busca Binária): ");
                    if (fgets(nomeBuscar, sizeof(nomeBuscar), stdin))
                    {
                        nomeBuscar[strcspn(nomeBuscar, "\r\n")] = '\0'; // remove newline
                    }
                    buscaBinariaItem(itens, contador, nomeBuscar);
                    break;
                }
                default:
                    break;
                }
            } while (opcao != 0);
            break;
        case 2:
            system("cls || clear");
            do
            {

                menuEncadeado();
                /* Ler a opção como linha para evitar deixar '\n' no stdin
                   (misturar scanf e fgets causa o problema observado). */
                char linhaOpcaoEnc[32];
                if (fgets(linhaOpcaoEnc, sizeof(linhaOpcaoEnc), stdin))
                {
                    if (sscanf(linhaOpcaoEnc, "%d", &opcaoEncadeado) != 1)
                    {
                        opcaoEncadeado = -1; /* entrada inválida */
                    }
                }
                else
                {
                    opcaoEncadeado = 0; /* EOF / erro de leitura: sair */
                }
                switch (opcaoEncadeado)
                {
                case 0:
                    printf("Saindo do programa.\n");
                    system("cls || clear");
                    break;
                case 1:

                    cadastrarItemEncadeado(&inicio, &contador);
                    break;
                case 2:
                    removerItemEncadeado(&inicio);
                    break;
                case 3:
                    listarItensEncadeados(inicio);
                    break;
                case 4:
                {
                    char nomeBuscar[30];
                    printf("Digite o nome do item a ser buscado: ");
                    if (fgets(nomeBuscar, sizeof(nomeBuscar), stdin))
                    {
                        nomeBuscar[strcspn(nomeBuscar, "\r\n")] = '\0'; // remove newline
                    }
                    buscaPorNomeEncadeado(inicio, nomeBuscar);
                    break;
                }
                default:
                    break;
                }
            } while (opcaoEncadeado != 0);
            break;
        default:
            break;
        }

    } while (escolhaEstrutura != 0);
}