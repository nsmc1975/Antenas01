/** ***************************************************************
 * @file   funcoes.c
 * @brief  Ficheiro de fun��es do programa antenas
 *
 * @author $NSMC1975
 * @date   March 2025
 *************************************************************** */

#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>	
//#include <stdlib.h>
#include <malloc.h> 
#include <locale.h>


int maxX = 0, maxY = 0; // Vari�veis globais para limites da matriz


//#define dist =2;

#pragma region OperacoesComAntenas

/**
* @brief cria antena
* @param [in] freq frequencia da antena, x e y coordenadas
* @return apontador para a antena criada
*/
Antena* criarAntena(char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) return NULL;
    nova->frequencia = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

/**
* @brief fun��o inserir antena
* @param [in] inicio apontador para a primeira antena, antena que queremos inserir
* @return apontador para a primeira antena (lista de antenas)
*/
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


/**
* @brief Fun��o Carregar Ficheiro de TEXTO
* @param [in]	nome e localiza��o do ficheiro TXT a carregar
* @return apontador para a antena criada
*/      
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
    return inicio; // Retorna a nova inicio da lista
}


/**
* @brief Listar antenas para o ecran
* @param [in] apontador para a primeira antena
* @return VOID, nao retorna nada
*/
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
	maxX++; maxY++; // Ajustar tamanho para poderem aparecer mais tarde os nefastos

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


/**
* @brief fun��o remover antenas
* @param [n] inicio apontador para a primeira antena, x e y coordenadas da antena a remover
* @return apontador para a primeira antena da lista
*/
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

#pragma endregion

#pragma region EfeitosNefastos
// EFEITOS NEFASTOS
/**
* @brief Criar e adicionar na lista o efeito nefasto
* @param [in] apontador para a primeira antena, x e y coordenadas do efeito nefasto
* @return novamente o apontador para a primeira antena (ou lista de antenas )
*/
Nefasto* criarInserirNefasto(Nefasto* lista, int x, int y) {
    Nefasto* novo = (Nefasto*)malloc(sizeof(Nefasto));
    if (!novo) return lista; // Falha ao alocar mem�ria

    novo->x = x;
    novo->y = y;
	novo->prox = lista; // Adiciona no in�cio da lista, nao precisa de estar ordenado

    return novo;
}
/**
* @brief Listar parao o ecra os efeitos nefastos guardados na sua lista
* @param [in] apontador para a primeira antena
* @return VOID, nao retorna nada
*/
void listarNefastos(Nefasto* lista) {
    Nefasto* atual = lista;
    while (atual != NULL) {
        printf("Efeito nefasto em (%d, %d)\n", atual->x, atual->y);
        atual = atual->prox;
    }
}

// fun��o gerar efeitos nefastos baseado na lista de antenas FALTA FAZER


 
#pragma endregion

#pragma region FICHEIROS BINARIOS

// ============== Ficheiros binarios ==============
/**
* @brief Preservar dados em ficheiro
* Grava localiza��o das antenas em Ficheiro binario
*/
bool gravarBinario(char* nomeFicheiro, Antena* h) {
    FILE* fp;

    if (h == NULL) return false;
    if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;
    //grava todos as antenas para ficheiro
    Antena* aux = h;
    AntenaFicheiro auxAntena = { 0 };	//aqui � variavel auxiliar para gravar em ficheiro!
	while (aux) {			//enquanto houver antenas
        //Colocar no registo de ficheiro a inf que est� no registo de mem�ria
        auxAntena.x = aux->x;
		auxAntena.y = aux->y;
		auxAntena.frequencia = aux->frequencia; 
        
        fwrite(&auxAntena, sizeof(AntenaFicheiro), 1, fp);
        
        aux = aux->prox;
    }
    fclose(fp);
    return true;
}

/**
* @brief L� informa��o de ficheiro
*/
Antena* lerBinario(char* nomeFicheiro) {
    FILE* fp;
    Antena* h = NULL;
    Antena* aux;
	AntenaFicheiro auxAntena;

    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
    //l� n registos no ficheiro
    //AntenaFicheiro auxAntena;
    while (fread(&auxAntena, sizeof(AntenaFicheiro), 1, fp)) {
        printf("Antena=%c %d %d \n", auxAntena.frequencia, auxAntena.x, auxAntena.y); //para debug
        aux = criarAntena(auxAntena.frequencia, auxAntena.x, auxAntena.y);
        h = inserirAntena(h, aux);
    }
    fclose(fp);
    return h;
}
#pragma endregion

// falta funcao para libertar Lista de Antenas free
