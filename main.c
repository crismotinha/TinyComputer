#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <cpu.h>

int main () {
    cpu_t cpu;
    init(&cpu);
    //dumpCPU(cpu);
    FILE *teste;
    teste = fopen("/Others/teste.ty", "r");
    FILE *object;
    object = fopen("/Others/object.ty", "w");

    assembleProgram(teste, object);
    fprintf(object, "%d \n");
    return 0;
}
