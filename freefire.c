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

// Fun√ß√£o para cadastrar itens no array de itens.
// Par√¢metros:
//   itens: ponteiro para o array de itens a ser preenchido.
//   contador: ponteiro para o contador de itens cadastrados.
void cadastrarItem(item *itens, int *contador)
{

    while (*contador < 2)
    {
        // ler nome (com espaÁos)
        printf("Digite o nome do item: ");
        if (fgets(itens[*contador].nome, sizeof(itens[*contador].nome), stdin))
        {
            itens[*contador].nome[strcspn(itens[*contador].nome, "\r\n")] = '\0'; // remove newline
        }
        // ler tipo (com fgets) ou usar scanf("%19s") se n„o quiser espaÁos
        
        printf("Digite o tipo do item: ");
        if (fgets(itens[*contador].tipo, sizeof(itens[*contador].tipo), stdin))
        {
            itens[*contador].tipo[strcspn(itens[*contador].tipo, "\r\n")] = '\0';
        }
        printf("Digite a quantidade do item: ");
        while (scanf("%d", &itens[*contador].quantidade) != 1)
        {
            printf("Entrada inv·lida. Digite um n˙mero inteiro para a quantidade: ");
            while (getchar() != '\n')
                ; // Limpa o buffer de entrada
        }
        // Limpa o buffer apÛs ler o inteiro
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
        (*contador)++;
    }
}

void removerItem(item *itens, int *qtdItens, const char *nomeRemover)
{
    
    //loop para percorrer o array de itens
    for (int i = 0; i < *qtdItens; i++)
    {
        //se o nome do item atual for igual ao nome a ser removido
        if (strcmp(itens[i].nome, nomeRemover) == 0)
        {
            // desloca os itens seguintes para preencher o espaÁo do item removido, ou seja, sobrescreve o item a ser removido
            // item na posiÁ„o i È substituÌdo pelo item na posiÁ„o i+1, e assim por diante
            for (int j = i; j < *qtdItens - 1; j++)
            {
                itens[j] = itens[j + 1];
            }
            (*qtdItens)--;
            printf("Item '%s' removido com sucesso.\n", nomeRemover);
            return;
        }
    }
    printf("Item '%s' n„o encontrado.\n", nomeRemover);
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
    printf("Item '%s' n„o encontrado.\n", nomeBuscar);
}

void menu()
{
    printf("Menu de OpÁıes:\n");
    printf("1. Cadastrar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item\n");
    printf("0. Sair\n");
    printf("Escolha uma opÁ„o: ");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    system("cls || clear");
    item itens[MAX_ITENS];
    int contador = 0;
    int opcao;
    int qtdItens = sizeof(itens) / sizeof(itens[0]);

    do{
        menu();
        /* Ler a opÁ„o como linha para evitar deixar '\n' no stdin
           (misturar scanf e fgets causa o problema observado). */
        char linhaOpcao[32];
        if (fgets(linhaOpcao, sizeof(linhaOpcao), stdin)) {
            if (sscanf(linhaOpcao, "%d", &opcao) != 1) {
                opcao = -1; /* entrada inv·lida */
            }
        } else {
            opcao = 0; /* EOF / erro de leitura: sair */
        }
        switch (opcao)
        {
        case 0:
            printf("Saindo do programa.\n");
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
        default:
            break;
        }
    } while (opcao != 0);
}