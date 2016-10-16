#include <stdio.h>
#include <stdlib.h>

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include"mem.h"
#define NUM_INST 14
enum instruction{INVALID = 0x0,READ = 0x1, WRITE = 0x2,LOAD = 0x3,STORE = 0x4,ADD = 0x5,SUB = 0x6,MUL  =  0x7,DIV  =  0x8,  MOD  =  0x9,  BRANCH  =  0xa,
BRANCHNEG  =  0Xb,  BRANCHZERO  =  0xc,HALT  = 0xd};
typedef enum instruction instruction_t;
struct decode {char * inst_name;
word_t opcode;} decode;
struct _cpu
{
memory_t mem;
word_t acc;
int pc;
};
typedef struct _cpu cpu_t;
/* Array contendo pares <nome_instrucao, codigo_instrucao> */
extern struct decode decode_list[NUM_INST];
/* retorna um opcode
, isto e, uma palavra de memoria com a instrucao e o operando */
word_t getOpcodeCPU(const cpu_t cpu);
/* Inicia o funcionamento da CPU, zera o contador de programa e limpa a memoria */
void init(cpu_t *cpu);
/* Roda um programa previamente carregado na
memoria da CPU*/
void run(cpu_t *cpu);
void exec(cpu_t *cpu);
/* Sai da cpu */
void exitCPU(const cpu_t cpu);
/* Mostra o conteudo da CPU */
void dumpCPU(const cpu_t  cpu);
/* Le um arquivo com um programa em linguagem de montagem e compila gerando um
codigo objeto*/
void assembleProgram(char *src_file_name, char *obj_file_name);
/* Carrega em memoria os bytes de um programa executável*/
void loadProgram(cpu_t *cpu, char *file_name);
#endif // CPU_H_INCLUDED
