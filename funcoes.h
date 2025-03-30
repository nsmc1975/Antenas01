
/** 
 * @file   funcoes.h
 * @brief  cabeçalho de funções e estruturas do programa antenas
 * @author  $NSMC1975
 * @date March 2025
 * 
 */

#pragma once

#include "dados.h"
#include <malloc.h>
#include <stdbool.h>

// FUNÇÕES
//      Criar Antena
Antena* criarAntena(char freq, int x, int y);

//      Inserir Antena 
Antena* inserirAntena(Antena* inicio, Antena* a);

//    funcao Eliminar Antena
Antena* removerAntena(Antena* inicio, int x, int y);

// função carregar ficheiro
Antena* carregarFicheiro(const char* nomeFicheiro);

// função Listar Antenas
void listarAntenas(Antena* inicio);

//função  Nefasto
Nefasto* criarInserirNefasto(Nefasto* lista, int x, int y);
void listarNefastos(Nefasto* lista);



//funções com FICHEIROS
bool GravarBinario(char* nomeFicheiro, Antena* h);
Antena* LerBinario(char* nomeFicheiro);




// funcao para libertar Lista de Antenas free




