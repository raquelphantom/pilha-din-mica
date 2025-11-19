/* --------------------------------------- Bibliotecas -------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>


/* ------------------------------- Constantes pré-definidas --------------------------------- */
#define INVALIDO -1
#define false    -1  
#define true      1

/* --------------------- Tipos de dados definidos pelo programador -------------------------- */

/* definição do tipo booleano */
typedef int 	bool;

/* definição do tipo chave utilizado:  a chave da nossa implementação será um número inteiro */
typedef int TIPOCHAVE;

/* definição do registro*/
typedef struct   
{         
   TIPOCHAVE  chave; 
   /* campos do registro */        
   char       NOMEPROD[100+1];
   char       DATAVENC [10+1]; 
} 
REGISTRO;

typedef struct ELEMENTO
{  
	REGISTRO 	reg;
	struct 		ELEMENTO	* PROX; // prox APONTA para o endereço de memória  
}                           // de um elemento com essa mesma estrutura 
ELEMENTO;

typedef ELEMENTO * PONT;  

typedef struct 
{
	PONT topo; /* topo APONTA para o endereço do ELEMENTO do TOPO da PILHA */
} 
PILHA;

/* --------------------------- Protótipos das funções --------------------------------------- */
void 		inicializarPilha (PILHA* p);
int 		tamanho (PILHA* p);
bool 		estaVazia(PILHA* p); 
void 		exibirPilha (PILHA* p); 
void 		reinicializarPilha (PILHA* p);
void 		insereNaPilha (PILHA* p);
void 		excluiDaPilha (PILHA* p);
bool 		inserirElemPilha(PILHA* p, REGISTRO reg); 
bool 		excluirElemPilha(PILHA* p, REGISTRO* reg); 
REGISTRO 	oqueInserir (void);
int 		main (void);

/* ----------------------- Rotinas de gerenciamento da Pilha -------------------------------- */

/* 
Para inicializar uma pilha já criada pelo usuário,  precisamos apenas acertar o valor do 
campo topo.
Já que o topo conterá o endereço do elemento que está no topo da pilha e apilha está vazia,  
iniciaremos esse campo com valor NULL. 
*/
void inicializarPilha (PILHA* p)
{
  p->topo = NULL;
}

/* Já que não temos um campo com o número de elementos na pilha, 
   precisaremos percorrer todos os elementos para contar quantos são.
*/
int tamanho (PILHA* p) 
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

/* Se topo está  armazenando o endereço NULL, significa que a pilha está vazia. */
bool estaVazia(PILHA* p) 
{
   if (p->topo == NULL) 
      return true;  
   return false;
}

/* Para exibir os elementos da estrutura precisaremos  percorrer os elementos
(iniciando pelo elemento do topo da pilha) e, por exemplo, imprimir suas chaves. */
void exibirPilha (PILHA* p) 
{  
   PONT end = p->topo;  
   system ("cls");
   printf("Pilha: \n[");  
   while (end != NULL) 
   {
		printf("\n%i - %s - %s", end->reg.chave, end->reg.NOMEPROD, end->reg.DATAVENC);  
		end = end->PROX;
   }
   printf("]");
}
/* 
Inserção de um elemento (push)
O usuário passa como parâmetro um registro a ser inserido na pilha
O elemento será inserido no topo da pilha, ou  melhor, 
“acima” do elemento que está no topo da  pilha.
O novo elemento irá apontar para o elemento que estava no topo da pilha
*/
bool inserirElemPilha(PILHA* p, REGISTRO reg) 
{  
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO)); 
   if (novo==NULL)
   {
      printf ("\nErro ao alocar memória para novo elemento.");
      printf ("\nNão foi possível inserir na pilha!");
      getch();
      return false;
   } 
   novo->reg  = reg;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}

/*
Exclusão de um elemento (pop)
O usuário solicita a exclusão do elemento do topo da pilha:
Se a pilha não estiver vazia, além de excluir esse elemento da pilha 
iremos copiá-lo para um local indicado pelo usuário.
*/
bool excluirElemPilha(PILHA* p, REGISTRO* reg) 
{  
   if ( p->topo == NULL) 
      return false;
   *reg        = p->topo->reg;  
   PONT apagar = p->topo;
   p->topo     = apagar->PROX; 
   free(apagar);
   return true;
}
/* 
Só tem sentido, se a pilha foi inicializada alguma vez.
Para reinicializar a pilha, precisamos excluir todos os seus elementos 
e colocar NULL no campo topo 
*/
void reinicializarPilha (PILHA* p) 
{  /*
   PONT apagar;
   PONT posicao = p->topo;  
   while (posicao != NULL) 
   {
      apagar  = posicao;  
      posicao = posicao->PROX;  
      free(apagar);
   }
   p->topo = NULL;
   */
   REGISTRO regExcluido;
   bool     flag;
   do
   {
   	 flag = excluirElemPilha(p, &regExcluido); 
   }
   while (  flag != false );
}
/*------------------*/
/* Funções de apoio */
/*------------------*/
REGISTRO oqueInserir (void)
{	REGISTRO r;
	printf ("\nTIPOCHAVE        : "); fflush (stdin); scanf("%i", &r.chave);
	printf ("\nNOME DO PRODUTO  : "); fflush (stdin); gets(r.NOMEPROD);
	printf ("\nDATA DE VALIDADE : "); fflush (stdin); gets(r.DATAVENC);
	return r;
}

void insereNaPilha (PILHA* p)
{
	REGISTRO	elem;
	elem  = oqueInserir();
	if ( inserirElemPilha(p, elem) == true )
	   printf ("\nChave [%i] inserida com sucesso.", elem.chave );
	else
	   printf ("\nChave [%i] NÃO inserida!", elem.chave );
}

void excluiDaPilha (PILHA* p)
{	REGISTRO regExcluido;
 	if ( excluirElemPilha(p, &regExcluido) == true )
	   printf ("\nRegistro: [%i][%s][%s] excluído com sucesso.", regExcluido.chave, regExcluido.NOMEPROD, regExcluido.DATAVENC );
	else
	   printf ("\nNão foi possivel excluir o registro.");
}

/* ---------------------------------- CORPO DO PROGRAMA ------------------------------------ */
int main (void)
{
   PILHA pil; 
   
   char opc;
   setlocale(LC_ALL, "");
   do
   {    system ("color e0");
   		system ("cls");
   		printf ("\n       TESTE COM PILHA  DINÂMICA    ");
   		printf ("\n------------------------------------");
   		printf ("\n 1. Inicializar Pilha               ");
   		printf ("\n 2. Exibir tamanho da Pilha         ");
   		printf ("\n 3. Exibir Pilha                    ");
   		printf ("\n 4. Verificar se a pilha está vazia ");
   		printf ("\n 5. Inserir elemento na Pilha (push)");
   		printf ("\n 6. Excluir elemento da Pilha (pop) ");
   		printf ("\n 7. Reinicializa Pilha              ");
   		printf ("\n------------------------------------");
   		printf ("\n    Escolha: "); fflush (stdin); opc = getche();
   		
		switch (opc)
   	    {
   	    	case '1': inicializarPilha(&pil); 								break;
   	    	case '2': printf("\n\nTamanho da Pilha = %i", tamanho(&pil) ); 	break;								
			case '3': exibirPilha (&pil);									break;			
   	    	case '4': if ( estaVazia (&pil) == true ) 
			               printf ("\nPilha vazia");	
					  else printf ("\nPilha NÃO vazia");		            break;
   	    	case '5': insereNaPilha (&pil);									break;
   	    	case '6': excluiDaPilha (&pil);									break;
   	    	case '7': reinicializarPilha (&pil);							break;
		}

		printf ("\n\nNovo teste? [n/N = não]"); fflush (stdin); opc = getche();
   }
   while ( opc != 'n' && opc != 'N');
   return 0;
}
