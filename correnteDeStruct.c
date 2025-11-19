#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct
{
   int      chave;
   char       NOME[100+1];
   char       DATANASC [10+1];
}
REGISTRO;

typedef struct aux
{
   REGISTRO   reg;
   struct     aux * PROX;
}
ELEMENTO;

ELEMENTO* removerElemento(ELEMENTO* inicio, int qual)
{
    ELEMENTO* atual = inicio;
    ELEMENTO* anterior = NULL;
    ELEMENTO* proximo = NULL;
    ELEMENTO* novo = NULL;

    while (atual != NULL)
    {
        if (atual->reg.chave == qual && anterior == NULL)
        {
            novo = atual->PROX;
            printf(" Liberando nó: Chave %d (%s)\n", atual->reg.chave, atual->reg.NOME);
            free(atual);
            return novo;
        }
        else if (atual->reg.chave == qual && anterior != NULL)
        {
            anterior->PROX = atual->PROX;
            printf(" Liberando nó: Chave %d (%s)\n", atual->reg.chave, atual->reg.NOME);
            free(atual);
            return inicio;
        }

        anterior = atual;
        atual = atual->PROX;
    }

    printf("\nCódigo não encontrado");
    return inicio;
}

void liberarLista(ELEMENTO* inicio) 
{
    ELEMENTO* atual = inicio;
    ELEMENTO* proximo;

    while (atual != NULL)
    {
        proximo = atual->PROX;
        printf(" Liberando nó: Chave %d (%s)\n", atual->reg.chave, atual->reg.NOME);
        free(atual);

        atual = proximo;
    }
}

ELEMENTO* inserirNoInicio(ELEMENTO* inicio, int nova_chave, char* novo_nome, char* nova_data)
{
    ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    novo->reg.chave = nova_chave;
    strcpy(novo->reg.NOME, novo_nome);
    strcpy(novo->reg.DATANASC, nova_data);
    novo->PROX = inicio;

    return novo;
}

void imprimirLista(ELEMENTO* inicio)
{
    ELEMENTO* p = inicio;

    while (p != NULL)
    {
        printf("\n Chave: %d, Nome: %s\n", p->reg.chave, p->reg.NOME);
        p = p->PROX;
    }
}

int main()
{
    setlocale(0, "Portuguese");

    int qual;

    ELEMENTO* minhaLista = NULL; 
    imprimirLista(minhaLista);

    minhaLista = inserirNoInicio(minhaLista, 1, "Ana", "01/01/2000");
    minhaLista = inserirNoInicio(minhaLista, 2, "Bruno", "02/02/2001");
    minhaLista = inserirNoInicio(minhaLista, 3, "Carla", "03/03/2002");
    minhaLista = inserirNoInicio(minhaLista, 4, "Maria", "04/04/2003");
    minhaLista = inserirNoInicio(minhaLista, 5, "José", "05/05/2004");

    imprimirLista(minhaLista);

    printf("\nDigite o código para excluir:\n");
    scanf("%d", &qual);

    minhaLista = removerElemento(minhaLista, qual);

    imprimirLista(minhaLista);

    liberarLista(minhaLista);

    minhaLista = NULL;

    return 0;
}