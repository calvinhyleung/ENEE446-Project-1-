
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
    printf("\n\nRUNNING WRITEBACK\n");
}


void
execute(state_t *state) {
    printf("\n\nRUNNING EXECUTE\n");
    advance_fu_int(state->fu_int_list, &state->int_wb);
    printf("int_wb: %08x\n", (&state->int_wb)->instr);
    if((state->fetch_lock) && !(state->control_stall)) {
        printf("stall counter: %d\n", state->stall_counter);
        if (state->stall_counter != 0 ) {
            state->stall_counter = state->stall_counter - 1;
            printf("decremented counter: %d\n", state->stall_counter);
        } else {
            if (state->halt_activated == FALSE) {
                state->fetch_lock = FALSE;
                printf("fetch lock diabled\n");
            }
        }
    }

}

int destination_extract(int inst){
    int use_imm;
    const op_info_t *op_info = decode_instr(inst, &use_imm); 
    switch(op_info->fu_group_num) {
        case FU_GROUP_INT:
            if (use_imm == 0) { return FIELD_R3(inst); } 
            if (use_imm == 1) { return FIELD_R2(inst); } 
        break; 
        case FU_GROUP_ADD:
        case FU_GROUP_MULT:
        case FU_GROUP_DIV:
            return FIELD_R3(inst);
        break;
        case FU_GROUP_MEM:
            if (op_info->operation == OPERATION_LOAD) { return FIELD_R2(inst); }
            if (op_info->operation == OPERATION_STORE) { return -1; }
        break;
    } 

} 

int RAW_finder (state_t* state, int inst) {
    int R1 = FIELD_R1(inst);
    int R2 = FIELD_R2(inst);
    int R3 = FIELD_R3(inst);
    int stall_for_RAW_count = 0; 
    printf("FINDING RAW\n");

    // if (destination_extract(state->int_wb.instr) == R1 
    //     || destination_extract(state->int_wb.instr) == R2) {
    //     stall_for_RAW_count ++; 
    //     printf("RAW DETECTED AT WB, stall count: %d\n", stall_for_RAW_count);
    // }

    // fu_int_t *fu_int_list = state->fu_int_list; 
    // fu_int_stage_t *stage_int = fu_int_list->stage_list;
    // while (stage_int != NULL){
    //     printf("prev inst: %08x\n", stage_int->instr);
    //     if (stage_int->current_cycle != -1){
    //         if (destination_extract(stage_int->instr) == R1 
    //             || destination_extract(stage_int->instr) == R2) {
    //             stall_for_RAW_count += stage_int->num_cycles - stage_int->current_cycle;
    //             printf("RAW DETECTED AT EX, stall count: %d\n", stall_for_RAW_count);
    //         }
    //     }
    //     stage_int = stage_int->prev;
    // }
    // return stall_for_RAW_count;

    fu_int_t *fu_int;
    fu_int_stage_t *stage;
    int j;
    fu_int = state->fu_int_list;
    while (fu_int != NULL) {
        printf("flag 1\n");
        j = 0;
        stage = fu_int->stage_list;
        while (stage != NULL) {
            printf("flag 2, j = %d\n", j);
            printf("prev inst: %08x\n", stage->instr);
            if (stage->current_cycle != -1) {
	            if (destination_extract(stage->instr) == R1 
                    || destination_extract(stage->instr) == R2) {
                    stall_for_RAW_count += stage->num_cycles - stage->current_cycle;
                    printf("RAW DETECTED AT EX, stall count: %d\n", stall_for_RAW_count);
                }
            }
            j++;
            stage = stage->prev;
        }
        fu_int = fu_int->next;
    }
    return stall_for_RAW_count;
}

int
decode(state_t *state) {
    printf("\n\nRUNNING DECODE\n");
    int inst = state->if_id.instr;
    int pc = state->if_id.pc;
    int use_imm; 
    //printf("%08x\n", pc);
    printf("Decoding: %08x\n", inst);

    const op_info_t *op_info = decode_instr(inst, &use_imm);  
    const int group_num = op_info->fu_group_num;
    const int op = op_info->operation;
    const int data_type = op_info->data_type;
    const char *name = op_info->name;
    printf("group: %d, op: %d, type: %d, name: %s, use_imm: %d\n", group_num, op, data_type , name, use_imm);
    
    int opcode = FIELD_OPCODE(inst);
    int func = FIELD_FUNC(inst);
    int r1 = FIELD_R1(inst);
    int r2 = FIELD_R2(inst);
    int r3 = FIELD_R3(inst);
    int imm = FIELD_IMM(inst);
    int immu = FIELD_IMMU(inst); 
    int offset = FIELD_OFFSET(inst);
    printf("opcode: %d, func: %d, r1: %d, r2: %d, r3: %d, imm: %d, immu: %d, offset: %d\n", opcode, func, r1, r2, r3, imm, immu, offset);
    // int isconflict;
    // printf("checking previous inst\n");
    // fu_int_t *head = state->fu_int_list; 
    // //fu_int_stage_t *head = state->fu_int_list->stage_list;
    // while (head != NULL){
    //     printf("prev inst: %08x\n", head->stage_list->instr);
    //     isconflict = conflict(head->stage_list->instr, inst);
    //     if (isconflict){
    //         printf("There is a conflict\n");
    //     } else {
    //         printf("There is a NO conflict\n");
    //     }
        
    //     head = head->next; 
    // }
    // printf("writing back: %08x\n", (&state->int_wb)->instr);
    // isconflict = conflict((&state->int_wb)->instr, inst);
    // if (isconflict){
    //     printf("There is a conflict\n");
    // } else {
    //     printf("There is a NO conflict\n");
    // }
    
    
    
    // int flag2; 
    // const op_info_t *decode2;
    // decode2 = decode_instr(testinst, &flag2); 
    // const int group_num2 = decode2->fu_group_num;
    // const int op2 = decode2->operation;
    // const int data_type2 = decode2->data_type;
    // const char *name2 = decode2->name;
    // printf("group2: %d op2: %d type2: %d name2: %s\n", group_num2, op2, data_type2, name2);

    int stall_for_RAW = RAW_finder(state, inst); 
    int stall = FALSE; 
    //const op_info_t *op_info = decode_instr(inst, &use_imm); 
    switch(op_info->fu_group_num) {
        case FU_GROUP_INT:
            if (use_imm == 0) {
                // check for RAW when not using immediate
                if (stall_for_RAW > 0){
                    stall = TRUE;
                }
            } else {
                // check for RAW when using immediate 
                if (stall_for_RAW > 0){
                    stall = TRUE;
                }
            }
        break; 
    }

    if(stall) { 
        state->stalled_inst = state->if_id.instr;
        state->stall_counter = stall_for_RAW; 
        state->fetch_lock = TRUE;
    } else { 
        switch (group_num) {
            case FU_GROUP_INT:
                issue_fu_int(state->fu_int_list, inst);
            break;
            case FU_GROUP_ADD:
            case FU_GROUP_MULT:
            case FU_GROUP_DIV:
            break;
            case FU_GROUP_MEM:
                issue_fu_int(state->fu_int_list, inst);
            break;
            case FU_GROUP_BRANCH:
            break;
            case FU_GROUP_NONE:
            break;
            case FU_GROUP_INVALID:
            break;
            case FU_GROUP_HALT:
            break;
        }
    }
    

    
    
}


void
fetch(state_t *state) { 

    if (state->fetch_lock != TRUE){
        printf("\n\nRUNNING FETCH\n");
        int pc, inst;  
        pc = state->pc; 
        inst = (state->mem[pc + 3] << 24) + (state->mem[pc + 2] << 16) 
            + (state->mem[pc + 1] << 8) + (state->mem[pc + 0]);
        state->if_id.instr = inst;
        state->if_id.pc = pc;;
        state->pc = pc + 4;
        printf("fetching: %08x\n", inst);
    }
}
