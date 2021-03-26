
/*
 * 
 * pipeline.c
 * 
 */


#include <stdlib.h>
#include "fu.h"
#include "pipeline.h"


void
writeback(state_t *state, int *num_insn) {
}


void
execute(state_t *state) {
}


int
decode(state_t *state) {
    printf("\n\nRUNNING DECODE\n");
    int inst, pc;
    int flag; 
    const op_info_t *wtv;

    pc = state->if_id.pc;
    inst = state->if_id.instr;
    printf("%08x\n", pc);
    printf("%08x\n", inst);
    wtv = decode_instr(inst, &flag); 
    
    const int type = wtv->data_type;
    const int num = wtv->fu_group_num;
    const char *name = wtv->name;
    const int op = wtv->operation;
    printf("%d\n", flag);
    printf("type: %d num: %d op: %d name: %s\n", type , num, op, name);
}


void
fetch(state_t *state) { 
    printf("\n\nRUNNING FETCH\n");
    int pc, inst;  
    pc = state->pc; 
    inst = (state->mem[pc + 3] << 24) + (state->mem[pc + 2] << 16) 
        + (state->mem[pc + 1] << 8) + (state->mem[pc + 0]);
    state->if_id.instr = inst;
    state->if_id.pc = pc;;
    state->pc = pc + 4;
}
