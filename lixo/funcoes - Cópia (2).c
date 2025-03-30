/*****************************************************************
 * \file   funcoes.c
 * \brief  Ficheiro de funções do programa antenas
 *
 * \author $NSMC1975
 * \date   March 2025
 ****************************************************************/

#include "funcoes.h"
#include <stdio.h>	
//#include <stdlib.h>
#include <malloc.h> 

int maxX = 0, maxY = 0; // Variáveis globais para limites da matriz


#define dist =2;

 //      Função Criar Antena
Antena* criarAntena(char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) return NULL;
    nova->frequencia = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

//      Função Inserir Antena
Antena* inserirAntena(Antena* inicio, Antena* a) {
    if (a == NULL) return inicio; // Se a antena for inválida, retorna a lista inalterada

    // Inserir no início se a lista estiver vazia ou se a antena deve ser a primeira
    if (inicio == NULL || a->x < inicio->x || (a->x == inicio->x && a->y < inicio->y)) {
        a->prox = inicio;
        return a; // Novo início da lista
    }

    Antena* aux = inicio;
    Antena* aux2 = NULL;

    // Percorrer a lista para encontrar o ponto de inserção correto
    while (aux != NULL && (a->x > aux->x || (a->x == aux->x && a->y > aux->y))) {
        aux2 = aux;
        aux = aux->prox;
    }

    // Garantir que aux2 não é NULL antes de alterar os apontadores, segmentation fault
    if (aux2 != NULL) {
        aux2->prox = a;
        a->prox = aux;
    }

    return inicio; // Retorna a cabeça da lista
}


//      Função Carregar Ficheiro
Antena* carregarFicheiro(const char* nomeFicheiro) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    Antena* inicio = NULL;
    char linha[100]; // Máximo de caracteres por linha
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
        nrLinha++; // Próxima linha da matriz
    }

    fclose(ficheiro);
    return inicio; // Retorna a nova cabeça da lista
}


// função listar antenas
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

    // Determinar os limites máximos da matriz
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
            char simbolo = '.'; // Por padrão, imprimimos '.'

            // Verificar se existe uma antena nesta posição
            while (aux) {
                if (aux->x == x && aux->y == y) {
                    simbolo = aux->frequencia;
                    break; // Encontramos a antena, podemos parar
                }
                aux = aux->prox;
            }

            printf("%c", simbolo);
        }
        printf("\n"); // Nova linha após cada linha da matriz
    }
}



//  função remover antenas
Antena* removerAntena(Antena* inicio, int x, int y) {
    if (inicio == NULL) {
        printf("Erro: Lista vazia, não há antenas para remover.\n");
        return NULL;
    }

    Antena* atual = inicio;
    Antena* anterior = NULL;

    // Percorrer a lista para encontrar a antena a remover
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            // Encontrou a antena a remover
            if (anterior == NULL) {
                // Caso especial: a antena está no início da lista
                inicio = atual->prox;
            }
            else {
                // Caso geral: ligar o anterior ao próximo nó
                anterior->prox = atual->prox;
            }
            free(atual); // Libertar a memória da antena removida
            printf("Antena em (%d, %d) removida com sucesso.\n", x, y);
            return inicio;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se chegou aqui, significa que não encontrou a antena
    printf("Erro: Nenhuma antena encontrada em (%d, %d).\n", x, y);
    return inicio;
}

//função adicionar Nefasto
Nefasto* adicionarNefasto(Nefasto* lista, int x, int y) {
    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto));
    if (!novo) return lista; // Falha ao alocar memória

    novo->x = x;
    novo->y = y;
    novo->prox = lista; // Adiciona no início da lista

    return novo;
}

// função efeitos nefastos
Nefasto* efeitosNefastos(Antena* inicio) {
    Nefasto* listaNefastos = NULL;  // Lista de efeitos nefastos
    Antena* atual = inicio;

    // Percorrer todas as antenas
    while (atual != NULL) {
        // Verificar as posições ao redor da antena dentro dos limites definidos por maxX e maxY
        // Aqui estamos a verificar à direita da antena (atual->x + 1, atual->y)
        if (atual->x + 1 < maxX && atual->y >= 0 && atual->y < maxY) { // Verificação para a posição à direita
            listaNefastos = adicionarNefasto(listaNefastos, atual->x + 1, atual->y);
        }

        // Avançar para a próxima antena
        atual = atual->prox;
    }

    return listaNefastos;
}

// Função para listar os efeitos nefastos
void listarNefastos(Nefasto* lista) {
    Nefasto* atual = lista;
    while (atual != NULL) {
        printf("Efeito nefasto em (%d, %d)\n", atual->x, atual->y);
        atual = atual->prox;
    }
}
// EFEITOS NEFASTOS QUE ESTOU A USAR AGORA, nao devia mas usa uma matriz fixa.
void efeitosNefastosEImprimir(Antena* inicio) {
    char matriz[10][20]; // Declaração da matriz de 10x20

    // Inicializar a matriz com '.'
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            matriz[i][j] = '.';  // Inicializa todas as células com '.'
        }
    }

    // Colocar as antenas na matriz
    Antena* atual = inicio;
    while (atual != NULL) {
        // Verifica se as coordenadas da antena são válidas para a matriz (10x20)
        if (atual->y >= 0 && atual->y < 10 && atual->x >= 0 && atual->x < 20) {
            matriz[atual->y][atual->x] = atual->frequencia;  // Coloca a antena na posição correta
        }
        atual = atual->prox;
    }

    // Adicionar os efeitos nefastos nas posições adjacentes às antenas
    atual = inicio;
    while (atual != NULL) {
        // Verificar as posições adjacentes (esquerda, direita, cima, baixo)
        // Esquerda
        if (atual->x > 0 && matriz[atual->y][atual->x - 1] == '.') {
            matriz[atual->y][atual->x - 1] = '#';  // Coloca efeito nefasto à esquerda
        }
        // Direita
        if (atual->x < 19 && matriz[atual->y][atual->x + 1] == '.') {
            matriz[atual->y][atual->x + 1] = '#';  // Coloca efeito nefasto à direita
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
        printf("\n");  // Nova linha após cada linha da matriz
    }
}

// falta funcao para libertar Lista de Antenas free
// gravar struct para ficheiro binario