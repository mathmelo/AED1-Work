/* 
*	Algoritmos e Estruturas de Dados 1
*	Ciencia da Computacao
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

// --- Definicao das Listas ---

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


// --- Funcoes de manipulacao das Listas ---
void inicializarLista(LISTA* l); // COMPLETO
int tamanho(LISTA* l); // COMPLETO
bool cadastrarProduto(LISTA *l, int idCategoria, REGISTRO_PRODUTO reg); // COMPLETO
bool cadastrarCategoria(LISTA *l, REGISTRO_CATEGORIA reg, int i); // COMPLETO
bool deletarProduto(LISTA *l, int i); //COMPLETO
bool deletarCategoria(LISTA *l, int i); //COMPLETO
bool listarTodosOsProdutos(); // COMPLETO
bool listarProdutoEspecifico(LISTA *l, TIPOCHAVE idProduto); // COMPLETO
void listarCategorias(LISTA *l); // COMPLETO
bool atualizarProduto(LISTA *l, int op, int idProduto); // COMPLETO
int confereIdProduto(LISTA *l);

// --- Funcoes de projecoes na tela ---
void printaTitulo(); // COMPLETO
void printaMenuPrincipal(); // COMPLETO

// --- Funcoes de leitura de dados ---
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
	
	// Variaveis e Arquivo
	bool a = true;
	int confereOpcao = 0;
	int idTemporarioCategoria, idTemporarioProduto;
	int cat, op;
	
	inicializarLista(&l);
	LIMPA_TERMINAL;
	
	// Loop do Menu principal
	while(a) {
		printaTitulo();
		
		// Le o menu e retorna o valor para confereOpcao
		confereOpcao = leMenuPrincipal(); 
		
		// CADASTRAR UM PRODUTO
		if(confereOpcao == 1) {
			
			// Loop que permite cadastrar varios produtos.
			while(true) {
				
				// Confere se existem categorias para cadastrar produtos
				if(tamanho(&l) == 0) {
					printf("\nNao foram cadastradas categorias, crie uma antes.\n\n");
					
					// Funcao de quebra de loop
					if(!(voltarRepetir())) {
						LIMPA_TERMINAL;
						break;
					}
				} else {
					
					// Bloco que le dados e aloca na struct "regProduto"
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
					
					// Confere se o usuario cancelou a operacao
					if(idTemporarioCategoria == -1) {
						regProduto.nomeProduto[0] = '\0';
						
						// Funcao de quebra de loop
						if(!(voltarRepetir())) {
							LIMPA_TERMINAL;
							break;
						}
					} else {
						// Chamada da funcao de cadastro
						cadastrarProduto(&l, idTemporarioCategoria, regProduto);
						
						// Funcao de quebra de loop
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

		if(confereOpcao == 3) {
			
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				
				printf("Digite o id do produto a ser apagado: ");
				scanf("%d", &cat);
				deletarProduto(&l,cat);
				
				if(!(voltarRepetir())) break;	
			}
			LIMPA_TERMINAL;


		} 	
				
		// DELETAR UMA CATEGORIA
		if(confereOpcao == 4) { 
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				
				printf("Digite o id da categoria a ser apagada: ");
				scanf("%d", &cat);
				deletarCategoria(&l , cat);
				
				if(!(voltarRepetir())) break;	
			}
			LIMPA_TERMINAL;
		}

		// LISTAR TODOS OS PRODUTOS
		if(confereOpcao == 5) {
			while(true) {
				listarTodosOsProdutos(&l);
				if(!(voltarRepetir())) {
					LIMPA_TERMINAL;
					break;
				}				
			}
		}
	
		if(confereOpcao == 6) {				
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				printf("LISTAGEM DE PRODUTO\n\n");
				printf("Digite o id do produto: ");
				
				scanf("%d", &idTemporarioProduto);
				listarProdutoEspecifico(&l, idTemporarioProduto);
				
				if(!(voltarRepetir())) {
					LIMPA_TERMINAL;
					break;
				}
			}
		}
	
		// LISTAR TODAS AS CATEGORIAS	
		if(confereOpcao == 7) listarCategorias(&l);

		if(confereOpcao == 8) {
			
			while(true) {
				LIMPA_TERMINAL;
				printaTitulo();
				printf("ATUALIZACAO DE PRODUTOS\n\n");
				printf("Informe o id do produto a ser atualizado: ");
				scanf("%d",&idTemporarioProduto);
				LIMPA_TERMINAL;
				printf("OPERACOES:\n");
				printf("\n1 - Atualizar nome do produto\n2 - Atualizar valor do produto\n3 - Atualizar quantidade do produto");
				printf("\n\nDigite uma opcao: ");
				scanf("%d", &op);
				LIMPA_TERMINAL;
				atualizarProduto(&l, op, idTemporarioProduto);
				if(!(voltarRepetir())) {
					LIMPA_TERMINAL;
					break;
				}
			}
		} 
				
		if(confereOpcao == 9) operacoesDeUsuario();
			
		// SAIR E ENCERRAR O PROGRAMA	
		if(confereOpcao == 10) sair();	
	}
	
    return 0;
}


// --- Funcoes de projecao de menus na tela ---
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


// --- Funcoes de leitura de dados ---
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
	
	
	while(true) {
		printf("\n1 - Voltar\n2 - Repetir Operacao\n\nDigite um valor: ");
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


// --- Funcoes de manipulacao das Listas ---
int tamanho(LISTA* l) {
	return l->tamanhoListaCategoria;
}

void inicializarLista(LISTA* l) {
	l->tamanhoListaCategoria = 0;
}

bool cadastrarProduto(LISTA* l, int idCategoria, REGISTRO_PRODUTO reg) {
	bool temp = false, temp2 = true;
	int j, position, i;
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
		
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			for(j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++) {
				if (l->registroCategoria[i].registroProduto[j].chaveProduto == reg.chaveProduto) {
					printf("Id do produto ja existe. Tente novamente.\n\n");
					temp2 = true;
					break;
				}
			}
			
			if(temp2 == true) break;			
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

bool deletarProduto(LISTA *l, int i) {

	int count, countAux, j;
	bool temp;

	temp=false;

	for(count = 0; count < l->tamanhoListaCategoria; count++) {

		for(countAux=0; countAux<l->registroCategoria[count].tamanhoListaProduto; countAux++) {

			if(l->registroCategoria[count].registroProduto[countAux].chaveProduto == i) {
				temp = true;
				break;
			}
		}
		if(temp==true) break;
    }
	if(temp==true) {


		for(j = countAux; j < l->registroCategoria[count].tamanhoListaProduto-1; j++) {

			l->registroCategoria[count].registroProduto[j] = l->registroCategoria[count].registroProduto[j+1];
		}
		l->registroCategoria[count].tamanhoListaProduto--;
		printf("Produto excluido com sucesso!\n");
		return true;
    }
	printf("Produto inexistente\n");
	return false;
}

bool deletarCategoria(LISTA *l, int i) {
	int j, count;
	bool aux = false;

	if(i<=0 || l->tamanhoListaCategoria == 0) return false;

	for(j=0; j<l->tamanhoListaCategoria; j++) {
		if(l->registroCategoria[j].chaveCategoria == i)
		{
			aux = true;
			break;
		}
	}

	if(aux==true) {
		
		for(count = 0; count < l->registroCategoria[j].tamanhoListaProduto; count++) {

            l->registroCategoria[j].registroProduto[i].nomeProduto[0] = '\0';
        }

		l->registroCategoria[j].tamanhoListaProduto = 0;
		l->registroCategoria[j].nomeCategoria[0] = '\0';

		for (count = j; count < l->tamanhoListaCategoria-1; count++) {
		
			l->registroCategoria[count] = l->registroCategoria[count+1];
		}

		l->tamanhoListaCategoria--;
		printf("\nCategoria excluida com sucesso!\n");
		return true;
	}
	else {
		printf("Id nao encontrado!\n");
		return false;
	}
	
}

bool listarTodosOsProdutos(LISTA *l) {
	int i, j;
	int tamCategoria = l->tamanhoListaCategoria;
	int tamProdutos;

	LIMPA_TERMINAL;
	printaTitulo();
	printf("\nPRODUTOS:\n\n");

	if(tamCategoria == 0) {
		printf("Nao foram cadastradas categorias e nem produtos.\n\n");
		printf("----------------------------------------\n\n");
		return false;
	} else {
		for(i = 0; i < tamCategoria; i++) {
			tamProdutos = l->registroCategoria[i].tamanhoListaProduto;
			if(tamProdutos == 0) {
				printf("%s - ID: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
				printf("   Nao foram cadastrados produtos nessa categoria.\n\n");
			} else {
				printf("%s - ID: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
				for(j = 0; j < tamProdutos; j++) {
					printf("   Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
					printf("   Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);					
				}
			}
			printf("----------------------------------------\n");
		}		
	}
	
	return true;
}

bool listarProdutoEspecifico(LISTA *l, TIPOCHAVE idProduto) {
	int i, j, tam = l->tamanhoListaCategoria;
	int count1, count2;
	bool aux = false;
	
	for(i = 0; i < tam; i++) {
		for(j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++) {
			if (l->registroCategoria[i].registroProduto[j].chaveProduto == idProduto) {
				aux = true;
				break;
			}
		}
		if (aux == true) break;
	}
	
	if(aux == false) {
		printf("Produto nao encontrado!\n\n");	
		return false;
	} else {
		printf("Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
		printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);	
		printf("------------------------------\n");
	}
	
	return true;
}

void listarCategorias(LISTA *l) {
	int i;
	LIMPA_TERMINAL;
	printaTitulo();
	printf("CATEGORIAS DISPONIVEIS:\n\n");
	if (tamanho(l) > 0) {
		for(i = 0; i < l->tamanhoListaCategoria; i++) {
			printf("Nome: %s, Id: %d\n", l->registroCategoria[i].nomeCategoria, l->registroCategoria[i].chaveCategoria);
		}		
	} else {
		printf("Nao foram cadastradas categorias!\n");
	}
}

bool atualizarProduto(LISTA *l, int op, int idProduto) {

	int i, j, auxTemp;
	float valorTemp;
	char novoNomeProduto[MAX_NOME];
	bool aux;

	if (l->tamanhoListaCategoria == 0) {

		printf("\nNao existem categorias e nem produtos cadastrados!\n");
		printf("--------------------------------\n");
		return false;
	}

	for (aux = false, i = 0; i < l->tamanhoListaCategoria; i++) {
			for (j = 0; j < l->registroCategoria[i].tamanhoListaProduto; j++) {
				if (l->registroCategoria[i].registroProduto[j].chaveProduto == idProduto) {
					aux = true;
					break;
				}
			}
			if (aux == true) break;
		}

	if (op == 1) { //ALTERAR NOME DO PRODUTO

		if (aux == false) {
			printf("Produto nao encontrado!\n\n");	
			return false;
		}
		else {
			l->registroCategoria[i].registroProduto[j].nomeProduto[0] = '\0';
			printf("Digite o novo nome do produto: ");
			getchar();

			scanf("%[^\n]s", novoNomeProduto);
			strcpy(l->registroCategoria[i].registroProduto[j].nomeProduto, novoNomeProduto);

			printf("\nNome alterado com sucesso!\n");
			printf("Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
			printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);	
			printf("------------------------------\n");
			return true;
		}
	}

	if (op == 2) { //ALTERAR VALOR DO PRODUTO

		printf("Digite um novo valor para o produto: ");
		scanf("%f", &valorTemp);

		l->registroCategoria[i].registroProduto[j].valor = valorTemp;

		printf("\nValor alterado com sucesso!\n");
		printf("Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
		printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);	
		printf("------------------------------\n");

		return true;
	}

	if (op == 3) { //ALTERAR QUANTIDADE DO PRODUTO

		printf("Digite uma nova quantidade para esse produto: ");
		scanf("%d",&auxTemp);

		l->registroCategoria[i].registroProduto[j].quantidade = auxTemp;

		printf("\nValor alterado com sucesso!\n");
		printf("Nome: %s, id: %d\n", l->registroCategoria[i].registroProduto[j].nomeProduto, l->registroCategoria[i].registroProduto[j].chaveProduto);
		printf("Valor: %.2f, Quantidade: %d\n\n", l->registroCategoria[i].registroProduto[j].valor, l->registroCategoria[i].registroProduto[j].quantidade);	
		printf("------------------------------\n");
	 	return true;
	}
	else {
		printf("\nOperacao invalida! Informe uma opcao existente.\n");
		return false;
	}
	 
	return true;
}

// --- Sair ---
void sair() {
	LIMPA_TERMINAL;
	printaTitulo();
	printf("Obrigado por usar nossos servicos!\n\n");
	exit(0);
}
