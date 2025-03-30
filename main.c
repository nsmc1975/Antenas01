/** ***************************************************************
 * @file   main.c
 * @brief  Ficheiro principal do programa antenas
 * @details Pretende-se considerar uma cidade com várias antenas. 
 * Cada antena é sintonizada numa frequência específica indicada por um caracter.
 *
 * @author $NSMC1975
 * @date   March 2025
 ****************************************************************/

#include "funcoes.h"
#include <stdio.h>
#include <locale.h>

#pragma once

int main() {
    setlocale(LC_ALL, "Portuguese");
    Antena* inicio = NULL; // Lista vazia
	Antena* inicio2 = NULL;// para nao estragar a inicio a ler do binario, por segurança
    Nefasto* inicio4 = NULL; // Lista de efeitos nefastos vazia

    // Carregar as antenas do ficheiro
    inicio = carregarFicheiro("antenas.txt");

    // Teste: listar as antenas carregadas
    printf("Lista de Antenas Ordenada:\n");
    listarAntenas(inicio);

    // tenta remover a antena na posição (4,4) que nao existe
    printf("\nRemover antena na posicao (3,4)...\n");
    inicio = removerAntena(inicio, 3, 4);
    
	// remove antena que existe
    printf("\nRemover antena na posicao (3,0)...\n");
    inicio = removerAntena(inicio, 3, 0);

    // Listar novamente
    printf("\nLista de Antenas:\n");
    listarAntenas(inicio);

    //adicionar de novo antena posicao 3,0
	printf("\nAdicionar antena na posicao (3,0)...\n");
	inicio = inserirAntena(inicio, criarAntena('E', 3, 0));

	printf("\nLista de Antenas antes de imprimir para binario:\n");
    listarAntenas(inicio);

	printf("gravar binario\n");
    GravarBinario("antenas1.bin", inicio);

    //ler bin e imprimir ecran
	printf("lido do binario e escrever na struct inicio2:\n");
	inicio2 = LerBinario("antenas1.bin");
	listarAntenas(inicio2);

    //tratar nefastos
	printf("\nEfeitos nefastos:\n");
    printf("a criar nefastos manualmente para debug...");
	inicio4 = criarInserirNefasto(inicio4, 1, 1);
    inicio4 = criarInserirNefasto(inicio4, 1, 3); 
    inicio4 = criarInserirNefasto(inicio4, 1, 4);

	printf("listar nefastos criados:\n");
	listarNefastos(inicio4);
	
    
	// falta juntar os efeitos nefastos, nao está feito
    
    //libertar memoria
    free(inicio);
    free(inicio2);
    return 0;
}
