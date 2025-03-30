/**
 * @file   dados.h
 * @brief  ficheiro cabe�alho estruturas e variaveis do programa antenas
 * @author  $NSMC1975
 * @date March 2025
 *
 */
#pragma once

typedef struct Antena {
    char frequencia; // 1 carater que representa uma frequencia de resonancia da antena
    int x, y;        // Coordenadas x e y na matriz 
	struct Antena* prox; // Apontador para a proxima antena
} Antena;

//struct para gravar em ficheiro
typedef struct AntenaFicheiro {
    char frequencia; // 1 carater que representa uma frequencia de resonancia da antena
    int x, y;        // Coordenadas x e y na matriz 
} AntenaFicheiro;

typedef struct Nefasto {
    int x, y;              // Coordenadas da localiza��o com efeito nefasto
    struct Nefasto* prox;  // Pr�ximo efeito nefasto na lista ligada
} Nefasto;


