#include <stdio.h>
#include <stdlib.h>
#ifndef MEM_H_INCLUDED
#define MEM_H_INCLUDED
#ifdef HUGE
/*Tamanho maximo da memoria.Espaco de enderecamento de  16 bits*/
#define MAX_MEM_SIZE 65536
#else
#define MAX_MEM_SIZE 256
#endif
typedef int word_t;
typedef word_t memory_t[MAX_MEM_SIZE];
/* Limpa tod
o o conteudo da memoria usada pela CPU */
void clearMem(memory_t mem);
/* Imprime no console todos os enderecos de memoria e seus conteudos */
void dumpMem(const memory_t mem);
/* Retorna uma palavra da memoria no endereco especificado*/
word_t getWord(const memory_t mem, int address);
/* Armazena uma palavra na memoria*/
void setWord(memory_t mem,int address, word_t word);
#endif // MEM_H_INCLUDED
