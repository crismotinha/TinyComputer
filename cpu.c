#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include"mem.h"
#define NUM_INST 14
enum instruction{INVALID = 0x0,READ = 0x1, WRITE = 0x2,LOAD = 0x3,STORE = 0x4,ADD = 0x5,SUB = 0x6,MUL  =  0x7,DIV  =  0x8,  MOD  =  0x9,  BRANCH  =  0xa,
BRANCHNEG  =  0Xb,  BRANCHZERO  =  0xc,HALT  = 0xd};

typedef enum instruction instruction_t;
struct decode {char * inst_name; word_t opcode;} decode; //em vez de chamar struct decode (novo decode) é só chamar decode agora.
struct _cpu
{
memory_t mem;
word_t acc;
int pc;
};
typedef struct _cpu cpu_t; //agora _cpu se chama cpu_t

/* Array contendo pares <nome_instrucao, codigo_instrucao> */
extern struct decode decode_list[NUM_INST];

void creatingDecodeList(struct decode decode_list[NUM_INST]) {
    decode_list[0].inst_name = "INVALID";
    decode_list[0].opcode = 0x0;

    decode_list[1].inst_name = "READ";
    decode_list[1].opcode = 0x1;

    decode_list[2].inst_name = "WRITE";
    decode_list[2].opcode = 0x2;

    decode_list[3].inst_name = "LOAD";
    decode_list[3].opcode = 0x3;

    decode_list[4].inst_name = "STORE";
    decode_list[4].opcode = 0x4;

    decode_list[5].inst_name = "ADD";
    decode_list[5].opcode = 0x5;

    decode_list[6].inst_name = "SUB";
    decode_list[6].opcode = 0x6;

    decode_list[7].inst_name = "MUL";
    decode_list[7].opcode = 0x7;

    decode_list[8].inst_name = "DIV";
    decode_list[8].opcode = 0x8;

    decode_list[9].inst_name = "MOD";
    decode_list[9].opcode = 0x9;

    decode_list[10].inst_name = "BRANCH";
    decode_list[10].opcode = 0xa;

    decode_list[11].inst_name = "BRANCHNEG";
    decode_list[11].opcode = 0Xb;

    decode_list[12].inst_name = "BRANCHZERO";
    decode_list[12].opcode = 0xc;

    decode_list[13].inst_name = "HALT";
    decode_list[13].opcode = 0xd;
}

/* retorna um opcode, isto e, uma palavra de memoria com a instrucao e o operando */
word_t getOpcodeCPU(const cpu_t cpu){
   return cpu.mem;
};

/* Inicia o funcionamento da CPU, zera o contador de programa e limpa a memoria (e zera o acc tb)*/
void init(cpu_t *cpu) {
    cpu->acc =0;
    cpu->pc = 0; //zera o contador
    clearMem(cpu->mem); //limpa a memória
};

/* Roda um programa previamente carregado na
memoria da CPU*/
void run(cpu_t *cpu);
void exec(cpu_t *cpu);

/* Sai da cpu */
void exitCPU(const cpu_t cpu);

/* Mostra o conteudo da CPU */
void dumpCPU(const cpu_t  cpu) {
    printf("Memoria:\n");
    dumpMem(cpu.mem);
    printf("Acumulador: %d \n", cpu.acc);
    printf("Contador de programa: %d \n", cpu.pc);
};

int creatingOpcode(int instruct, int ender) {
    int primDigt = 0x00;
    unsigned int result = (primDigt<<24) | (instruct<<16)| (ender<<16);
    return result;
}
/* Le um arquivo com um programa em linguagem de montagem e compila gerando um
codigo objeto*/
void assembleProgram(char *src_file_name, char *obj_file_name, struct decode decode_list[NUM_INST]){
    FILE *src;
    src = fopen(src_file_name, "r");
    FILE *obj;
    obj = fopen(obj_file_name, "w");
    int i, j;
    char instruc[200];
    int endereco;
    int instruc_decoded;
    for (i=0; i<256; i++) {
        fscanf(src, "%s %d", instruc, &endereco); //aqui que está estourando
        for (j=0; j<NUM_INST+1; j++) {
            if (strcmp(decode_list[j].inst_name, instruc) == 0) {
                instruc_decoded = decode_list[j].opcode;
            }
        }
        int instruction_ready = creatingOpcode(instruc_decoded, endereco);
        fputs(instruction_ready, obj);
    }
    fclose(src_file_name);
    fclose(obj_file_name);
};

/* Carrega em memoria os bytes de um programa executável*/
void loadProgram(cpu_t *cpu, char *file_name){
    FILE *f_exec = fopen(file_name,"r");
    int opcodeExtracted;
    int i;
    char linha[8];
    for (i=0; i<256; i++) {
        fgets(linha, 8, f_exec);
        fscanf(linha, "%d", opcodeExtracted);
        cpu->mem[i] = opcodeExtracted;
    }
};

#endif // CPU_H_INCLUDED

