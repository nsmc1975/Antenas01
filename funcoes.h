
/** 
 * @file   funcoes.h
 * @brief  cabe�alho de fun��es e estruturas do programa antenas
 * @author  $NSMC1975
 * @date March 2025
 * 
 */

#pragma once

#include "dados.h"
#include <malloc.h>
#include <stdbool.h>

// FUN��ES
//      Criar Antena
Antena* criarAntena(char freq, int x, int y);

//      Inserir Antena 
Antena* inserirAntena(Antena* inicio, Antena* a);

//    funcao Eliminar Antena
Antena* removerAntena(Antena* inicio, int x, int y);

// fun��o carregar ficheiro
Antena* carregarFicheiro(const char* nomeFicheiro);

// fun��o Listar Antenas
void listarAntenas(Antena* inicio);

//fun��o  Nefasto
Nefasto* criarInserirNefasto(Nefasto* lista, int x, int y);
void listarNefastos(Nefasto* lista);



//fun��es com FICHEIROS
bool GravarBinario(char* nomeFicheiro, Antena* h);
Antena* LerBinario(char* nomeFicheiro);




// funcao para libertar Lista de Antenas free




