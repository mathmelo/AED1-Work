/* 
*	Algoritmos e Estruturas de Dados 1
*	Ciência da Computação
*
*	Desenvolvido por:
*			Matheus Melo da Costa
*   		Daniel Lopes Silva 
*
*  -------------------------------------
*	   -- GERENCIADOR DE ESTOQUE --
*  -------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#define LIMPA_TERMINAL system("cls")
#else
#define LIMPA_TERMINAL system("clear")
#endif

#define MAX_PRODUTO 1000
#define MAX_CATEGORIA 100
#define MAX_NOME 50

// --- Definição das Listas ---

typedef int TIPOCHAVE;

// Registro dos produtos
typedef struct {
	TIPOCHAVE chaveProduto;
	char nomeProduto[MAX_NOME];
	int quantidade;
	float valor;
} REGISTRO_PRODUTO;

// Registro das Categorias
typedef struct {
	TIPOCHAVE chaveCategoria;
	char nomeCategoria[MAX_NOME];
	
	REGISTRO_PRODUTO registroProduto[MAX_PRODUTO];
	int tamanhoListaProduto;
} REGISTRO_CATEGORIA;

// Registro da lista
typedef struct {
	REGISTRO_CATEGORIA registroCategoria[MAX_CATEGORIA];
	int tamanhoListaCategoria;
} LISTA;

// --- Funções de manipulação das Listas ---
void inicializarLista(LISTA* l); // COMPLETO
 int tamanho(LISTA* l); // COMPLETO
bool cadastrarProduto();
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i); // COMPLETO
bool deletarProduto();
bool deletarCategoria();
bool listarTodosOsProdutos();
bool listarProdutoEspecifico();
int listarCategorias(LISTA *l);
bool atualizarProduto();
void operacoesDeUsuario();
int confereIdCategoria(LISTA *l);
int confereIdProduto(REGISTRO_CATEGORIA *reg);

// --- Funções de projeções na tela ---
void printaTitulo();
void bemVindo();
void printaMenuPrincipal();

// --- Funções de leitura de dados ---
int leMenuPrincipal();
bool voltarRepetir();

// --- Sair ---
void sair(); 

int main() {
	// Registros e Listas
	LISTA l;
	REGISTRO_PRODUTO regProduto;
	REGISTRO_CATEGORIA regCategoria;
	
	// Variáveis e Arquivo
	bool a = true;
	int confereOpcao = 0;
	
	inicializarLista(&l);
	
	// Loop do Menu principal
	while(a) {
		printaTitulo();
		confereOpcao = leMenuPrincipal();
		
		if(confereOpcao == 1) {
			// INCOMPLETO
			LIMPA_TERMINAL;
			printaTitulo();
			printf("OPERACAO - CADASTRAR PRODUTO\n\n");
			getchar();
			printf("Digite o nome do novo produto: ");
			scanf("%[^\n]s", regProduto.nomeProduto);
			printf("\nDigite o id do novo produto: ");
			scanf("%d", &regProduto.chaveProduto);
			printf("\nDigite o valor do novo produto: ");
			scanf("%f", &regProduto.valor);
			printf("\nDigite a quantidade disponivel: ");
			scanf("%d", &regProduto.quantidade);
			cadastrarProduto(&l, regCategoria, tamanho(&l));
			cadastrarProduto();		
		}
			
		if(confereOpcao == 2) {
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				printf("OPERACAO - CADASTRAR CATEGORIA\n\n");
				getchar();
				printf("Digite o nome da nova categoria: ");
				scanf("%[^\n]s", regCategoria.nomeCategoria);
				printf("\nDigite o id da nova categoria: ");
				regCategoria.chaveCategoria = confereIdCategoria(&l);		
				cadastrarCategoria(&l, regCategoria, tamanho(&l));	
				regCategoria.nomeCategoria[0] = '\0';
				if(!(voltarRepetir())) break;				
			}
			LIMPA_TERMINAL;
		}

		if(confereOpcao == 3) deletarProduto();	
				
		if(confereOpcao == 4) deletarCategoria();

		if(confereOpcao == 5) listarTodosOsProdutos();
	
		if(confereOpcao == 6) listarProdutoEspecifico();

		if(confereOpcao == 7) atualizarProduto();
				
		if(confereOpcao == 8) operacoesDeUsuario();
				
		if(confereOpcao == 9) sair();	
	}
	
    return 0;
}


// --- Funções de projeção de menus na tela ---
void printaTitulo() {
	printf("\n-------------------------------------");
	printf("\n    -- GERENCIADOR DE ESTOQUE --\n");
 	printf("-------------------------------------\n\n");
 
}

void printaMenuPrincipal() {
	printf("OPERACOES:\n");
	printf("1 - Cadastrar um produto\n");
	printf("2 - Cadastrar categoria\n");
	printf("3 - Deletar produto\n");
	printf("4 - Deletar categoria\n");
	printf("5 - Listar produtos (todos)\n");
	printf("6 - Listar produto (especifico)\n");
	printf("7 - Atualizar produto\n");
	printf("8 - Operacoes de usuario\n");
	printf("9 - Sair\n");
}


// --- Funções de leitura de dados ---
int leMenuPrincipal() {
	int a = 0;
	bool confere = true;
	
	printaMenuPrincipal();
	
	while(confere) {
		printf("\nDigite um valor: ");
		scanf("%d", &a);
		
		if(a < 1 || a > 9) {
			printf("Opcao invalida!\n");
		} else confere = false;
	}
	
	return a;
}

bool voltarRepetir() {
	int temp;
	printf("1 - Voltar\n2 - Repetir Operacao\nDigite um valor: ");
	
	while(true) {
		scanf("%d", &temp);
		if (temp == 1 || temp == 2) {
			if (temp == 1) {
				return false;	
			}
			else return true;
		} else {
			printf("\nNumero invalido!\n");
		}
	}
}


// --- Funções de manipulação das Listas ---
int tamanho(LISTA* l) {
	return l->tamanhoListaCategoria;
}

void inicializarLista(LISTA* l) {
	l->tamanhoListaCategoria = 0;
}

bool cadastrarProduto() {
	return true;
}

bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i){
	int j;
	
	if ((l->tamanhoListaCategoria == MAX_CATEGORIA) || (i < 0) || (i > l->tamanhoListaCategoria)) {
		return false;	
	}
	
	for (j = l->tamanhoListaCategoria; j > i; j--) {
		l->registroCategoria[j] = l->registroCategoria[j-1];
	}
	
	l->registroCategoria[i] = reg;
	l->tamanhoListaCategoria++;
	
	printf("\nCategoria cadastrada com sucesso!\n");
	printf("Nome: %s, id: %d\n\n", l->registroCategoria[i].nomeCategoria,l->registroCategoria[i].chaveCategoria);
	
	return true;
}

bool deletarProduto() {
	return true;
}

bool deletarCategoria() {
	return true;
}

bool listarTodosOsProdutos() {
	return true;
}

bool listarProdutosPorCategoria() {
	return true;
}

bool listarProdutoEspecifico() {
	return true;
}

bool atualizarProduto() {
	return true;
}

void operacoesDeUsuario() {
	
}

int confereIdCategoria(LISTA *l) {
	int i;
	bool a = true, aux = true;
	TIPOCHAVE temp;
	
	while(a) {
		scanf("%d", &temp);
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			if (l->registroCategoria[i].chaveCategoria == temp) {
				printf("O id ja existe. Digite outro: ");
				aux = false;
				break;
			}
		}
		
		if (aux) break;		
		aux = true;
	}
	return temp;
}

int listarCategorias(LISTA *l) {
	
}

// --- Sair ---
void sair() {
	LIMPA_TERMINAL;
	printaTitulo();
	printf("Obrigado por usar nossos servicos!\n\n");
	exit(0);
}
