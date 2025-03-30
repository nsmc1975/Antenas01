/*****************************************************************
 * \file   funcoes.c
 * \brief  ficheiro de funções do programa antenas
 * 
 * \author $NSMC1975
 * \date   March 2025
 ****************************************************************/

#include "funcoes.h"
#include <stdio.h>	
#include <malloc.h>

 //      Função Criar Antena
Antena* criarAntena(char freq, int x, int y) {
	Antena* novaAntena = (Antena*)malloc(sizeof(Antena));
	if (novaAntena == NULL) return NULL;
	novaAntena->frequencia = freq;
	novaAntena->x = x;
	novaAntena->y = y;
	novaAntena->prox = NULL;
	return novaAntena;
}



//      Função Inserir Antena
void inserirAntena(Antena** inicio, char freq, int x, int y) {
    Antena* nova = criarAntena(freq, x, y);
    if (!nova) {
        printf("Erro ao criar antena!\n");
        return;
    }

    // Se a lista estiver vazia ou se a nova antena deve ser a primeira
    if (*inicio == NULL || (*inicio)->x > x || ((*inicio)->x == x && (*inicio)->y > y)) {
        nova->prox = *inicio;
        *inicio = nova;
        return;
    }

    // Percorrer a lista para encontrar a posição correta
    Antena* atual = *inicio; //atual aponta para inicio
    while (atual->prox != NULL && //enquanto o apontado do prox nao for nulo e (x do prox < x atual ou (x prox = x atual
        (atual->prox->x < x || (atual->prox->x == x && atual->prox->y < y))) { // e y prox < y atual
        atual = atual->prox; // passa apontador da antena atual para a seguinte e assim sucessivamente ate se falso e
    } //nesse caso está na posicao a escrever no local correto

    // Inserir no local correto
    nova->prox = atual->prox;
    atual->prox = nova;
}


// função ler ficheiros
void carregarFicheiro(Antena** inicio, const char* nomeFicheiro) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    char linha[256]; // maximo de caracteres de cada linha
    int nrLinha = 0; // Linha da matriz

    while (fgets(linha, sizeof(linha), ficheiro)) {
        for (int x = 0; linha[x] != '\0'; x++) {
            if (linha[x] != '.' && linha[x] != '\n') { // Ignora '.' e quebras de linha
                inserirAntena(inicio, linha[x], x, nrLinha);
            }
        }
        nrLinha++; // Próxima linha da matriz
    }

    fclose(ficheiro);
}

// funcao para libertar Lista de Antenas free