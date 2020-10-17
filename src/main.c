/* 
*	Algoritmos e Estrutura de Dados 1
*	Ci�ncia da Computa��o
*
*	Desenvolvido por:
*			Matheus Melo da Costa
*   		Daniel Lopes Silva 
*/

// -------------------------------------
// 	    -- GERENCIADOR DE ESTOQUE --
// -------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#define LIMPA_TERMINAL system("cls")
#else
#define LIMPA_TERMINAL system("clear")
#endif

// --- Defini��o das Listas ---

// Registro dos produtos
typedef struct {
} REGISTRO_PRODUTO;

// Registro das Categorias
typedef struct {
} REGISTRO_CATEGORIA;

// Registro da lista
typedef struct {
	int tamanho;
} LISTA;

// --- Fun��es de manipula��o das Listas ---
// --- Fun��es de proje��o de menus na tela ---
void printaTitulo();
// --- Fun��es de leitura de dados ---


int main() {
	int a;
	printaTitulo();
	
    return 0;
}

// --- Fun��es de proje��o de menus na tela ---
void printaTitulo() {
	printf("\n-------------------------------------");
	printf("\n    -- GERENCIADOR DE ESTOQUE --\n");
 	printf("-------------------------------------\n\n");
 
}
