#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX 40
#define INVALIDO -1
#define false -1
#define true 1

typedef struct
{
    int id;
    char nome[MAX];
    char user[MAX];
    int paginas;
    char hora[MAX];
}
TIPOCHAVE;

typedef struct  
{
    TIPOCHAVE chave;
}
REGISTRO;

typedef struct aux
{
REGISTRO reg;
struct aux * PROX;
}
ELEMENTO;

typedef ELEMENTO * PONT;

typedef struct
{
PONT topo;
}
EstruturaDeDados;

void initP (EstruturaDeDados* p);
int sizeP (EstruturaDeDados* p);
void showP (EstruturaDeDados* p);
int pushP (EstruturaDeDados* p, REGISTRO reg);
int popP (EstruturaDeDados* p, REGISTRO* reg);
void reinitP (EstruturaDeDados* p);
int isemptyP (EstruturaDeDados* p);
REGISTRO whatInit (void);
void prePush (EstruturaDeDados* p);
void prePop (EstruturaDeDados* p);
void insereDefault (EstruturaDeDados* p);
void addP (EstruturaDeDados* p);
int proximoId(EstruturaDeDados* p);

void initP (EstruturaDeDados* p)
{
    p->topo = NULL;
}

int sizeP (EstruturaDeDados* p)
{ 
    PONT end = p->topo;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->PROX;
    }

    return tam;
}

int isemptyP(EstruturaDeDados* p)
{
    if (p->topo == NULL)
    return true;
    return false;
}

void showP (EstruturaDeDados* p)
{
    PONT end = p->topo;
    system ("cls");
    printf("\nEstruturaDeDados: \" ");
    while (end != NULL)
    {
        printf("\n %d\t\t%s\t\t%s\t%d\t%s", end->reg.chave.id, end->reg.chave.nome, end->reg.chave.user, end->reg.chave.paginas, end->reg.chave.hora);
        end = end->PROX;
    }

    printf("\"\n");
}

int pushP(EstruturaDeDados* p, REGISTRO reg)
{
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL)
    {
        return false;
    }

    novo->reg = reg;

    if (p->topo == NULL || reg.chave.paginas >= p->topo->reg.chave.paginas)
    {
        novo->PROX = p->topo;
        p->topo = novo;
        return true;
    }

    else 
    {
        PONT atual = p->topo;

        while (atual->PROX != NULL && atual->PROX->reg.chave.paginas >= reg.chave.paginas)
        {
            atual = atual->PROX;
        }

        novo->PROX = atual->PROX;
        atual->PROX = novo;
        return true;
    }

}

int popP(EstruturaDeDados* p, REGISTRO* reg)
{
    if ( p->topo == NULL)
    {
        return false; 
    }

    *reg = p->topo->reg;
    PONT apagar = p->topo;
    p->topo = apagar->PROX;
    free(apagar);

    return true;
}

void reinitP (EstruturaDeDados* p)
{
    PONT apagar;
    PONT posicao = p->topo;
    while (posicao != NULL)
    {
        apagar = posicao;
        posicao = posicao->PROX;
        free(apagar);
    }

    p->topo = NULL;
}

int pesquisa (EstruturaDeDados* p)
{
    char qual[MAX];

    printf("\nDigite o nome do documento a ser encontrado: ");
    fflush(stdin);
    fgets(qual, MAX, stdin);
    qual[strcspn(qual, "\n")] = 0;

    PONT atual = p->topo;

    while (atual != NULL)
    {
        if (strcmp(atual->reg.chave.nome, qual) == 0)
        {
            printf("\nDocumento encontrado:");
            printf("\n %d\t\t%s\t\t%s\t%d\t%s", atual->reg.chave.id, atual->reg.chave.nome, atual->reg.chave.user, atual->reg.chave.paginas, atual->reg.chave.hora);
            return true;            
        }

        atual = atual->PROX;
    }

    printf("\nArquivo não encontrado. Voltando ao menu");
}

REGISTRO whatInit (void)
{ 
    REGISTRO r;
    printf ("\nTIPOCHAVE : ");
    fflush (stdin); 
    gets(r.chave.nome);

    return r;
}

void prePush (EstruturaDeDados* p)
{
    REGISTRO elem;
    elem = whatInit();
    if ( pushP(p, elem) == true )
    {
        printf ("\nPush [%s] com sucesso.", elem.chave.nome );
    }

    else
    {
        printf ("\nPush [%s] sem sucesso!", elem.chave.nome );
    }
}

void prePop (EstruturaDeDados* p)
{ 
    REGISTRO regPop;

    if ( popP(p, &regPop) == true )
    {
        printf ("\nPop [%s] com sucesso.", regPop.chave.nome );
    }

    else
    {
        printf ("\nPop sem sucesso!");
    }
}

int proximoId(EstruturaDeDados* p)
{
    
    int qualProximo = 0;

    PONT atual = p->topo;

    while (atual != NULL)
    {
        if (qualProximo < atual->reg.chave.id)
        {
            qualProximo = atual->reg.chave.id;
        }

        atual = atual->PROX;
    }

    if (qualProximo == 0)
    {
        return 1;
    }

    return qualProximo;
}


void insereDefault (EstruturaDeDados* p)
{
    REGISTRO r;

    r.chave.id = 201;
    strcpy(r.chave.nome, "Relatorio_Financeiro.pdf");
    strcpy(r.chave.user, "Ana C.");
    r.chave.paginas = 55;
    strcpy(r.chave.hora, "10:00:00");
    pushP(p, r);

    r.chave.id = 202;
    strcpy(r.chave.nome, "Proposta_Marketing.docx");
    strcpy(r.chave.user, "João S.");
    r.chave.paginas = 12;
    strcpy(r.chave.hora, "10:00:15");
    pushP(p, r);

    r.chave.id = 203;
    strcpy(r.chave.nome, "Foto_Capa.jpg");
    strcpy(r.chave.user, "Maria B.");
    r.chave.paginas = 1;
    strcpy(r.chave.hora, "10:00:30");
    pushP(p, r);

    r.chave.id = 204;
    strcpy(r.chave.nome, "Contrato_Novo.pdf");
    strcpy(r.chave.user, "Ana C.");
    r.chave.paginas = 98;
    strcpy(r.chave.hora, "10:00:45");
    pushP(p, r);

    r.chave.id = 205;
    strcpy(r.chave.nome, "Rascunho_Ideias.txt");
    strcpy(r.chave.user, "Pedro P.");
    r.chave.paginas = 5;
    strcpy(r.chave.hora, "10:01:00");
    pushP(p, r);

    r.chave.id = 206;
    strcpy(r.chave.nome, "Apresentacao_Vendas.pptx");
    strcpy(r.chave.user, "João S.");
    r.chave.paginas = 35;
    strcpy(r.chave.hora, "10:01:15");
    pushP(p, r);

    r.chave.id = 207;
    strcpy(r.chave.nome, "Memo_Interno.pdf");
    strcpy(r.chave.user, "Maria B.");
    r.chave.paginas = 3;
    strcpy(r.chave.hora, "10:01:30");
    pushP(p, r);

    r.chave.id = 208;
    strcpy(r.chave.nome, "Folha_de_Rosto.doc");
    strcpy(r.chave.user, "Pedro P.");
    r.chave.paginas = 1;
    strcpy(r.chave.hora, "10:01:45");
    pushP(p, r);

    r.chave.id = 209;
    strcpy(r.chave.nome, "Balanco_Anual.xls");
    strcpy(r.chave.user, "Ana C.");
    r.chave.paginas = 150;
    strcpy(r.chave.hora, "10:02:00");
    pushP(p, r);

    r.chave.id = 210;
    strcpy(r.chave.nome, "Lista_de_Precos.pdf");
    strcpy(r.chave.user, "João S.");
    r.chave.paginas = 22;
    strcpy(r.chave.hora, "10:02:15");
    pushP(p, r);

    r.chave.id = 211;
    strcpy(r.chave.nome, "Relatorio_Semestral.doc");
    strcpy(r.chave.user, "Eub");
    r.chave.paginas = 550;
    strcpy(r.chave.hora, "10:30:15");
    pushP(p, r);

    printf("\nTrabalhos inseridos e Organizados\n");
} 

void addP(EstruturaDeDados* p)
{
    REGISTRO seiLa;
    int addId, addPaginas;
    char addNome[MAX], addUser[MAX], addHora[MAX];

    addId = 0;

    addId = proximoId(p);
    seiLa.chave.id = addId;

    printf("\nDigite o nome do arquivo para adicionar: \n");
    fflush(stdin);
    fgets(addNome, MAX, stdin);
    addNome[strcspn(addNome, "\n")] = 0;
    strcpy(seiLa.chave.nome, addNome);

    printf("\nDigite o nome do usuário: \n");
    fflush(stdin);
    fgets(addUser, MAX, stdin);
    addUser[strcspn(addUser, "\n")] = 0;
    strcpy(seiLa.chave.user, addUser);

    printf("\nQuantidade de Páginas: \n");
    fflush(stdin);
    scanf("%d", &addPaginas);
    seiLa.chave.paginas = addPaginas;

    printf("\nDigite o horário nesse modelo (0h:0m:0s) \n");
    fflush(stdin);
    fgets(addHora, MAX, stdin);
    addHora[strcspn(addHora, "\n")] = 0;
    strcpy(seiLa.chave.hora, addHora);

    pushP(p, seiLa);
}


int main()
{
    setlocale(0, "portuguese");

    EstruturaDeDados *ed;
    int *ant;
    char opc;

    ed = (EstruturaDeDados *) malloc (sizeof(EstruturaDeDados));
    if ( ed==NULL)
    {
        printf ("\nErro em malloc!");
        printf("\nAperte enter para sair");
        getchar();
        exit(0);
    }

    do
    {
        //system ("color e0"); //cor feia
        system ("cls");
        printf ("\n TESTANDO A ESTRUTURA DE DADOS ");
        printf ("\n------------------------------------");
        printf ("\n 1. initP ");
        printf ("\n 2. sizeP ");
        printf ("\n 3. showP ");
        printf ("\n 4. isemptyP ");
        printf ("\n 5. pushP ");
        printf ("\n 6. popP ");
        printf ("\n 7. reinitP ");
        printf ("\n 8. buscaP ");
        printf ("\n 9. Encerra o programa ");
        printf ("\n a. addP");
        printf ("\n------------------------------------");
        printf ("\n Escolha: "); fflush (stdin); 
        scanf(" %c", &opc);

        switch (opc)
        {
            case '1': {initP(ed); insereDefault(ed);} break;
            case '2': printf("\n\nSize = %i", sizeP(ed) ); break;
            case '3': showP (ed); break;
            case '4': if ( isemptyP (ed) == true ) 
                      {
                          printf ("\nSIM");
                      }

                      else
                      { 
                          printf ("\nNAO"); break;
                      }

            case '5': prePush (ed); break;
            case '6': prePop  (ed); break;
            case '7': reinitP (ed); break;
            case '8': pesquisa(ed); break;
            case 'a': addP    (ed); break;
            case '9': exit(0); break;
            default : 
            { 
                printf ("\nERRO"); 
                printf("\nAperte enter para continuar");
                getchar(); 
            } 
            break;
        }

        printf ("\n\nNovo teste? [n/N = NEGATIVO]");    
        fflush (stdin);
        scanf("%c", &opc);

    } while ( opc != 'n' && opc != 'N');

    return 0;
}