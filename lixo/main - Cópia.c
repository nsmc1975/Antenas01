/** ***************************************************************
 * @file   main.c
 * @brief  Ficheiro principal do programa antenas
 * @details Pretende-se considerar uma cidade com v�rias antenas. 
 * Cada antena � sintonizada numa frequ�ncia espec�fica indicada por um caracter.
 *
 * @author $NSMC1975
 * @date   March 2025
 *************************************************************** */

#include "funcoes.h"
#include <stdio.h>
#pragma once

int main() {
    Antena* inicio = NULL;  

	// Inserir Antenas do ficheiro
    carregarFicheiro(&inicio, "antenas.txt");

    

    printf("Lista de Antenas Ordenada:\n");
    Antena* aux = inicio;
	while (aux) { //enquanto aux nao for nulo
        printf("Antena: %c (%d, %d)\n", aux->frequencia, aux->x, aux->y);
        aux = aux->prox;
    }

    return 0;
}

