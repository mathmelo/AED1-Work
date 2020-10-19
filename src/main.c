/* 
*	Algoritmos e Estruturas de Dados 1
*	Ciência da Computação
*
*	Desenvolvido por:
*			Matheus Melo da Costa
*			Daniel Lopes Silva 
*
*	-------------------------------------
*		-- GERENCIADOR DE ESTOQUE --
*	-------------------------------------
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
bool cadastrarProduto(LISTA *l, int idCategoria, REGISTRO_PRODUTO reg); // COMPLETO
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i); // COMPLETO
bool deletarProduto();
bool deletarCategoria();
bool listarTodosOsProdutos(); // COMPLETO
bool listarProdutoEspecifico();
void listarCategorias(LISTA *l); // COMPLETO
bool atualizarProduto();
void operacoesDeUsuario();
int confereIdProduto(LISTA *l);

// --- Funções de projeções na tela ---
void printaTitulo(); // COMPLETO
void printaMenuPrincipal(); // COMPLETO

// --- Funções de leitura de dados ---
int leMenuPrincipal(); // COMPLETO
bool voltarRepetir(); // COMPLETO
int confereIdCategoria(LISTA *l); // COMPLETO

// --- Sair ---
void sair(); // COMPLETO

int main() {
	// Registros e Listas
	LISTA l;
	REGISTRO_PRODUTO regProduto;
	REGISTRO_CATEGORIA regCategoria;
	
	// Variáveis e Arquivo
	bool a = true;
	int confereOpcao = 0;
	int idTemporarioCategoria;
	
	inicializarLista(&l);
	
	// Loop do Menu principal
	while(a) {
		printaTitulo();
		confereOpcao = leMenuPrincipal();
		
		// CADASTRAR UM PRODUTO
		if(confereOpcao == 1) {
			while(true) {
				if(tamanho(&l) == 0) {
					printf("\nNao foram cadastradas categorias, crie uma antes.\n");
					if(!(voltarRepetir())) {
						LIMPA_TERMINAL;
						break;
					}
				} else {
					LIMPA_TERMINAL;
					printaTitulo();
					printf("OPERACAO - CADASTRAR PRODUTO\n\n");
					getchar();
					
					printf("Digite o nome do novo produto: ");
					scanf("%[^\n]s", regProduto.nomeProduto);
					
					printf("Digite o valor do novo produto: ");
					scanf("%f", &regProduto.valor);
					
					printf("Digite a quantidade disponivel: ");
					scanf("%d", &regProduto.quantidade);
					
					printf("Digite o id da Categoria que quer vincular o produto (-1 para cancelar): ");
					scanf("%d", &idTemporarioCategoria);
					
					if(idTemporarioCategoria == -1) {
						regProduto.nomeProduto[0] = '\0';
						if(!(voltarRepetir())) {
							LIMPA_TERMINAL;
							break;
						}
					} else {
						if(cadastrarProduto(&l, idTemporarioCategoria, regProduto)) {
							printf("\n\nProduto cadastrado com sucesso\n\n");							
						}
						
						if(!(voltarRepetir())) {
							LIMPA_TERMINAL;
							break;
						}
					}
				}
			}
		}
			
		// CADASTRAR UMA CATEGORIA
		if(confereOpcao == 2) {
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				
				printf("OPERACAO - CADASTRAR CATEGORIA\n\n");
				getchar();
				
				printf("Digite o nome da nova categoria: ");
				scanf("%[^\n]s", regCategoria.nomeCategoria);
				
				printf("Digite o id da nova categoria: ");
				regCategoria.chaveCategoria = confereIdCategoria(&l);
						
				cadastrarCategoria(&l, regCategoria, tamanho(&l));	
				regCategoria.nomeCategoria[0] = '\0';
				
				if(!(voltarRepetir())) break;
				
			}
			LIMPA_TERMINAL;
		}

		if(confereOpcao == 3) deletarProduto();	
				
		if(confereOpcao == 4) deletarCategoria();

		if(confereOpcao == 5) listarTodosOsProdutos(&l);
	
		if(confereOpcao == 6) listarProdutoEspecifico();
		
		if(confereOpcao == 7) listarCategorias(&l);

		if(confereOpcao == 8) atualizarProduto();
				
		if(confereOpcao == 9) operacoesDeUsuario();
				
		if(confereOpcao == 10) sair();	
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
	printf(" 1 - Cadastrar um produto\n");
	printf(" 2 - Cadastrar categoria\n");
	printf(" 3 - Deletar produto\n");
	printf(" 4 - Deletar categoria\n");
	printf(" 5 - Listar produtos (todos)\n");
	printf(" 6 - Listar produto (especifico)\n");
	printf(" 7 - Listar categoria\n");
	printf(" 8 - Atualizar produto\n");
	printf(" 9 - Operacoes de usuario\n");
	printf("10 - Sair\n");
}


// --- Funções de leitura de dados ---
int leMenuPrincipal() {
	int a = 0;
	bool confere = true;
	
	printaMenuPrincipal();
	
	while(confere) {
		printf("\nDigite um valor: ");
		scanf("%d", &a);
		
		if(a < 1 || a > 10) {
			printf("Opcao invalida!\n");
		} else confere = false;
	}
	
	return a;
}

bool voltarRepetir() {
	int temp;
	printf("1 - Voltar\n2 - Repetir Operacao\n\nDigite um valor: ");
	
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


// --- Funções de manipulação das Listas ---
int tamanho(LISTA* l) {
	return l->tamanhoListaCategoria;
}

void inicializarLista(LISTA* l) {
	l->tamanhoListaCategoria = 0;
}

bool cadastrarProduto(LISTA* l, int idCategoria, REGISTRO_PRODUTO reg) {
	bool temp = false, temp2 = true;
	int j, position;
	int tam;
	
	for(j = 0; j < l->tamanhoListaCategoria; j++) {
		if(l->registroCategoria[j].chaveCategoria == idCategoria) {
			position = j;
			temp = true;
			break;
		}
	}
	
	if(temp == false) {
		printf("O id da categoria nao existe. Tente novamente.\n\n");
		return false;	
	}		

	tam = l->registroCategoria[position].tamanhoListaProduto;
	if (tam == MAX_PRODUTO) {
		printf("Tamanho excedido. Apague alguns produtos.\n\n");
		return false;	
	}
	
	while(temp2) {
		if(temp2 == true) temp2 = false;
		printf("Digite o id do novo produto (-1 para cancelar): ");
		scanf("%d", &reg.chaveProduto);
		if(reg.chaveProduto == -1) return false;
		for(j = 0; j < tam; j++) {
			if (l->registroCategoria[position].registroProduto[j].chaveProduto == reg.chaveProduto) {
				printf("Id do produto ja existe. Tente novamente.\n\n");
				temp2 = true;
			}
		}			
	}
	
	l->registroCategoria[position].registroProduto[tam] = reg;
	l->registroCategoria[position].tamanhoListaProduto++;
	
	printf("\nProduto cadastrado com sucesso!\n");
	printf("Nome: %s, id: %d\n", l->registroCategoria[position].registroProduto[tam].nomeProduto, l->registroCategoria[position].registroProduto[tam].chaveProduto);
	printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[position].registroProduto[tam].valor, l->registroCategoria[position].registroProduto[tam].quantidade);					
	
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
	l->registroCategoria[i].tamanhoListaProduto = 0;
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

bool listarTodosOsProdutos(LISTA *l) {
	int i, j;
	int tamCategoria = l->tamanhoListaCategoria;
	int tamProdutos;
	
	printf("PRODUTOS:\n\n");
	
	if(tamCategoria == 0) {
		printf("Nao foram cadastradas categorias.\n\n");
		printf("----------------------------------------\n");
		return false;
	} else {
		for(i = 0; i < tamCategoria; i++) {
			printf("%s - %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
			tamProdutos = l->registroCategoria[i].tamanhoListaProduto;
			if(tamProdutos == 0) {
				printf("Nao foram cadastrados produtos nessa categoria.\n");	
			} else {
				for(j = 0; j < tamProdutos; j++) {
					printf("Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
					printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);					
				}
			}
			printf("----------------------------------------\n");
		}		
	}
	
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

void listarCategorias(LISTA *l) {
	int i;
	LIMPA_TERMINAL;
	printaTitulo();
	printf("\nCATEGORIAS DISPONIVEIS:\n\n");
	if (tamanho(l) > 0) {
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			printf("Nome: %s, Id: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
		}		
	} else {
		printf("Nao foram cadastradas categorias!\n");
	}
}

// --- Sair ---
void sair() {
	LIMPA_TERMINAL;
	printaTitulo();
	printf("Obrigado por usar nossos servicos!\n\n");
	exit(0);
}
