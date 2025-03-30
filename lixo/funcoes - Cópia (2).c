/*****************************************************************
 * \file   funcoes.c
 * \brief  Ficheiro de fun��es do programa antenas
 *
 * \author $NSMC1975
 * \date   March 2025
 ****************************************************************/

#include "funcoes.h"
#include <stdio.h>	
//#include <stdlib.h>
#include <malloc.h> 

int maxX = 0, maxY = 0; // Vari�veis globais para limites da matriz


#define dist =2;

 //      Fun��o Criar Antena
Antena* criarAntena(char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) return NULL;
    nova->frequencia = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

//      Fun��o Inserir Antena
Antena* inserirAntena(Antena* inicio, Antena* a) {
    if (a == NULL) return inicio; // Se a antena for inv�lida, retorna a lista inalterada

    // Inserir no in�cio se a lista estiver vazia ou se a antena deve ser a primeira
    if (inicio == NULL || a->x < inicio->x || (a->x == inicio->x && a->y < inicio->y)) {
        a->prox = inicio;
        return a; // Novo in�cio da lista
    }

    Antena* aux = inicio;
    Antena* aux2 = NULL;

    // Percorrer a lista para encontrar o ponto de inser��o correto
    while (aux != NULL && (a->x > aux->x || (a->x == aux->x && a->y > aux->y))) {
        aux2 = aux;
        aux = aux->prox;
    }

    // Garantir que aux2 n�o � NULL antes de alterar os apontadores, segmentation fault
    if (aux2 != NULL) {
        aux2->prox = a;
        a->prox = aux;
    }

    return inicio; // Retorna a cabe�a da lista
}


//      Fun��o Carregar Ficheiro
Antena* carregarFicheiro(const char* nomeFicheiro) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    Antena* inicio = NULL;
    char linha[100]; // M�ximo de caracteres por linha
    int nrLinha = 0; // Contador de numero linhas da matriz

    while (fgets(linha, sizeof(linha), ficheiro)) {  
        for (int x = 0; linha[x] != '\0'; x++) {
            if (linha[x] != '.' && linha[x] != '\n') { // Ignora '.' e quebras de linha
                Antena* nova = criarAntena(linha[x], x, nrLinha);
                if (nova) { // Garante que a antena foi criada com sucesso
                    inicio = inserirAntena(inicio, nova);
                }
            }
        }
        nrLinha++; // Pr�xima linha da matriz
    }

    fclose(ficheiro);
    return inicio; // Retorna a nova cabe�a da lista
}


// fun��o listar antenas
void listarAntenas(Antena* inicio) {
/*	Antena* aux = inicio;
	while (aux) {
		printf("Antena: %c (%d, %d)\n", aux->frequencia, aux->x, aux->y);
		aux = aux->prox;
	}
}*/
    if (!inicio) {
        printf("Nao ha antenas na lista.\n");
        return;
    }

    // Determinar os limites m�ximos da matriz
    //int maxX = 0, maxY = 0;
    Antena* aux = inicio;
    while (aux) {
        if (aux->x > maxX) maxX = aux->x;
        if (aux->y > maxY) maxY = aux->y;
        aux = aux->prox;
    }
	maxX++; maxY++; // Ajustar tamanho para aparecer os nefastos

    // Percorrer a matriz e imprimir diretamente
    for (int y = 0; y <= maxY; y++) {
        for (int x = 0; x <= maxX; x++) {
            aux = inicio;
            char simbolo = '.'; // Por padr�o, imprimimos '.'

            // Verificar se existe uma antena nesta posi��o
            while (aux) {
                if (aux->x == x && aux->y == y) {
                    simbolo = aux->frequencia;
                    break; // Encontramos a antena, podemos parar
                }
                aux = aux->prox;
            }

            printf("%c", simbolo);
        }
        printf("\n"); // Nova linha ap�s cada linha da matriz
    }
}



//  fun��o remover antenas
Antena* removerAntena(Antena* inicio, int x, int y) {
    if (inicio == NULL) {
        printf("Erro: Lista vazia, n�o h� antenas para remover.\n");
        return NULL;
    }

    Antena* atual = inicio;
    Antena* anterior = NULL;

    // Percorrer a lista para encontrar a antena a remover
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            // Encontrou a antena a remover
            if (anterior == NULL) {
                // Caso especial: a antena est� no in�cio da lista
                inicio = atual->prox;
            }
            else {
                // Caso geral: ligar o anterior ao pr�ximo n�
                anterior->prox = atual->prox;
            }
            free(atual); // Libertar a mem�ria da antena removida
            printf("Antena em (%d, %d) removida com sucesso.\n", x, y);
            return inicio;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se chegou aqui, significa que n�o encontrou a antena
    printf("Erro: Nenhuma antena encontrada em (%d, %d).\n", x, y);
    return inicio;
}

//fun��o adicionar Nefasto
Nefasto* adicionarNefasto(Nefasto* lista, int x, int y) {
    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto));
    if (!novo) return lista; // Falha ao alocar mem�ria

    novo->x = x;
    novo->y = y;
    novo->prox = lista; // Adiciona no in�cio da lista

    return novo;
}

// fun��o efeitos nefastos
Nefasto* efeitosNefastos(Antena* inicio) {
    Nefasto* listaNefastos = NULL;  // Lista de efeitos nefastos
    Antena* atual = inicio;

    // Percorrer todas as antenas
    while (atual != NULL) {
        // Verificar as posi��es ao redor da antena dentro dos limites definidos por maxX e maxY
        // Aqui estamos a verificar � direita da antena (atual->x + 1, atual->y)
        if (atual->x + 1 < maxX && atual->y >= 0 && atual->y < maxY) { // Verifica��o para a posi��o � direita
            listaNefastos = adicionarNefasto(listaNefastos, atual->x + 1, atual->y);
        }

        // Avan�ar para a pr�xima antena
        atual = atual->prox;
    }

    return listaNefastos;
}

// Fun��o para listar os efeitos nefastos
void listarNefastos(Nefasto* lista) {
    Nefasto* atual = lista;
    while (atual != NULL) {
        printf("Efeito nefasto em (%d, %d)\n", atual->x, atual->y);
        atual = atual->prox;
    }
}
// EFEITOS NEFASTOS QUE ESTOU A USAR AGORA, nao devia mas usa uma matriz fixa.
void efeitosNefastosEImprimir(Antena* inicio) {
    char matriz[10][20]; // Declara��o da matriz de 10x20

    // Inicializar a matriz com '.'
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            matriz[i][j] = '.';  // Inicializa todas as c�lulas com '.'
        }
    }

    // Colocar as antenas na matriz
    Antena* atual = inicio;
    while (atual != NULL) {
        // Verifica se as coordenadas da antena s�o v�lidas para a matriz (10x20)
        if (atual->y >= 0 && atual->y < 10 && atual->x >= 0 && atual->x < 20) {
            matriz[atual->y][atual->x] = atual->frequencia;  // Coloca a antena na posi��o correta
        }
        atual = atual->prox;
    }

    // Adicionar os efeitos nefastos nas posi��es adjacentes �s antenas
    atual = inicio;
    while (atual != NULL) {
        // Verificar as posi��es adjacentes (esquerda, direita, cima, baixo)
        // Esquerda
        if (atual->x > 0 && matriz[atual->y][atual->x - 1] == '.') {
            matriz[atual->y][atual->x - 1] = '#';  // Coloca efeito nefasto � esquerda
        }
        // Direita
        if (atual->x < 19 && matriz[atual->y][atual->x + 1] == '.') {
            matriz[atual->y][atual->x + 1] = '#';  // Coloca efeito nefasto � direita
        }
        // Cima
        if (atual->y > 0 && matriz[atual->y - 1][atual->x] == '.') {
            matriz[atual->y - 1][atual->x] = '#';  // Coloca efeito nefasto acima
        }
        // Baixo
        if (atual->y < 9 && matriz[atual->y + 1][atual->x] == '.') {
            matriz[atual->y + 1][atual->x] = '#';  // Coloca efeito nefasto abaixo
        }
        atual = atual->prox;
    }

    // Imprimir a matriz resultante
    printf("\nAntenas e Efeitos Nefastos:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%c", matriz[i][j]);  // Imprime cada elemento da matriz
        }
        printf("\n");  // Nova linha ap�s cada linha da matriz
    }
}

// falta funcao para libertar Lista de Antenas free
// gravar struct para ficheiro binario