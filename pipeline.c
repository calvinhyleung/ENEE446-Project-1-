
/*
 * 
 * pipeline.c
 * 
 */


#include <stdlib.h>
#include "fu.h"
#include "pipeline.h"

void
perform_write(state_t * state, int instr, unsigned long pc) {
  int use_imm;
  const op_info_t *op_info = decode_instr(instr, &use_imm);;
  operand_t result;

  int opcode = FIELD_OPCODE(instr);
  int func = FIELD_FUNC(instr);
  int r1 = FIELD_R1(instr);
  int r2 = FIELD_R2(instr);
  int r3 = FIELD_R3(instr);
  int imm = FIELD_IMM(instr);
  int immu = FIELD_IMMU(instr); 
  int offset = FIELD_OFFSET(instr);
  int hex;
    float f;

  switch(op_info->fu_group_num) {
    /******************************** INT */ 
    case FU_GROUP_INT:
      switch(op_info->operation) {
        case OPERATION_ADD:
          //result.integer.w = operand1.integer.w + operand2.integer.w;
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w + state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w + imm;}
          break;
        case OPERATION_ADDU:
          if (use_imm == 0) {state->rf_int.reg_int[r3].wu = state->rf_int.reg_int[r1].wu + state->rf_int.reg_int[r2].wu;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].wu = state->rf_int.reg_int[r1].wu + immu;}
          break;
        case OPERATION_SUB:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w - state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w - imm;}
          break;
        case OPERATION_SUBU:
          if (use_imm == 0) {state->rf_int.reg_int[r3].wu = state->rf_int.reg_int[r1].wu - state->rf_int.reg_int[r2].wu;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].wu = state->rf_int.reg_int[r1].wu - immu;}
          break;
        case OPERATION_SLL:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w << state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w << imm;}
          break;
        case OPERATION_SRL:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w >> state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w >> imm;}
          break;
        case OPERATION_AND:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w & state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w & imm;}
          break;
        case OPERATION_OR:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w | state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w | imm;}
          break;
        case OPERATION_XOR:
          if (use_imm == 0) {state->rf_int.reg_int[r3].w = state->rf_int.reg_int[r1].w ^ state->rf_int.reg_int[r2].w;}
          if (use_imm == 1) {state->rf_int.reg_int[r2].w = state->rf_int.reg_int[r1].w ^ imm;}
          break;
        case OPERATION_SLT:
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].w < state->rf_int.reg_int[r2].w) {state->rf_int.reg_int[r3].w = 1;} else {state->rf_int.reg_int[r3].w = 0;} }
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].w < imm) {state->rf_int.reg_int[r3].w = 1;} else {state->rf_int.reg_int[r3].w = 0;} }
          break;
        case OPERATION_SGT:
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].w > state->rf_int.reg_int[r2].w) {state->rf_int.reg_int[r3].w = 1;} else {state->rf_int.reg_int[r3].w = 0;} }
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].w > imm) {state->rf_int.reg_int[r3].w = 1;} else {state->rf_int.reg_int[r3].w = 0;} }
          break;
        case OPERATION_SLTU:
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].wu < state->rf_int.reg_int[r2].wu) {state->rf_int.reg_int[r3].wu = 1;} else {state->rf_int.reg_int[r3].wu = 0;} }
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].wu < immu) {state->rf_int.reg_int[r3].wu = 1;} else {state->rf_int.reg_int[r3].wu = 0;} }
          break;
        case OPERATION_SGTU:
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].wu > state->rf_int.reg_int[r2].wu) {state->rf_int.reg_int[r3].wu = 1;} else {state->rf_int.reg_int[r3].wu = 0;} }
          if (use_imm == 0) {if (state->rf_int.reg_int[r1].wu > immu) {state->rf_int.reg_int[r3].wu = 1;} else {state->rf_int.reg_int[r3].wu = 0;} }
          break;
        
      }
      break;

    /******************************** ADD */
    case FU_GROUP_ADD:
      switch (op_info->operation){
          case OPERATION_ADD:
            state->rf_fp.reg_fp[r3] = state->rf_fp.reg_fp[r1] + state->rf_fp.reg_fp[r2];
            printf("r1: %.6f\n", state->rf_fp.reg_fp[r1]);
            printf("r2: %.6f\n", state->rf_fp.reg_fp[r2]);
            printf("r3: %.6f\n", state->rf_fp.reg_fp[r3]);
            break;
          case OPERATION_SUB:
            state->rf_fp.reg_fp[r3] = state->rf_fp.reg_fp[r1] - state->rf_fp.reg_fp[r2];
            break;
      }
      break;

    /******************************** MULT */
    case FU_GROUP_MULT:
        state->rf_fp.reg_fp[r3] = state->rf_fp.reg_fp[r1] * state->rf_fp.reg_fp[r2];
        printf("r1: %.6f\n", state->rf_fp.reg_fp[r1]);
        printf("r2: %.6f\n", state->rf_fp.reg_fp[r2]);
        printf("r3: %.6f\n", state->rf_fp.reg_fp[r3]);
      break;
    /******************************** DIV */
    case FU_GROUP_DIV:
        state->rf_fp.reg_fp[r3] = state->rf_fp.reg_fp[r1] / state->rf_fp.reg_fp[r2];
        printf("r1: %.6f\n", state->rf_fp.reg_fp[r1]);
        printf("r2: %.6f\n", state->rf_fp.reg_fp[r2]);
        printf("r3: %.6f\n", state->rf_fp.reg_fp[r3]);
      break;

    /******************************** MEM */
    case FU_GROUP_MEM:
      switch(op_info->operation){
        case OPERATION_LOAD:
          switch (op_info->data_type){
            case DATA_TYPE_W:
              state->rf_int.reg_int[r2].w = state->mem[state->rf_int.reg_int[r1].w + imm];
              break;
            case DATA_TYPE_F:
                            
                hex = (state->mem[state->rf_int.reg_int[r1].wu + imm + 3] << 24) 
                    + (state->mem[state->rf_int.reg_int[r1].wu + imm + 2] << 16) 
                    + (state->mem[state->rf_int.reg_int[r1].wu + imm + 1] << 8) 
                    + (state->mem[state->rf_int.reg_int[r1].wu + imm + 0]);
              //state->rf_fp.reg_fp[r2] = (float) state->mem[state->rf_int.reg_int[r1].w + imm + 3];
              
              f = *((float*)&hex);
              state->rf_fp.reg_fp[r2] = f; 
            //   printf("hex: %d\n", hex);
            //   printf("float: %.6f\n", f);
              break;
            }
          break; 
        case OPERATION_STORE:
          switch (op_info->data_type){
            case DATA_TYPE_W:
              state->mem[state->rf_int.reg_int[r1].w + imm] = state->rf_int.reg_int[r2].w;
              break;
            case DATA_TYPE_F:
              state->mem[state->rf_int.reg_int[r1].w + imm] = (int)state->rf_fp.reg_fp[r2];
              break;
          }
          break;
      }
      break;

    /******************************** CONTROL */
    case FU_GROUP_BRANCH:
        switch (op_info->operation) {
            case OPERATION_J:
                state->if_id.instr = 0;
                printf("pc: %2x, offset: %d\n", state->pc, FIELD_OFFSET(instr));
                state->pc = state->pc + FIELD_OFFSET(instr) - 4 ;
                printf("new pc: %2x\n", state->pc);
                break;
            case OPERATION_JR:
                state->pc = state->rf_int.reg_int[FIELD_R1(instr)].wu;
                break;
            case OPERATION_JAL:
                state->rf_int.reg_int[31].wu = state->pc; 
                state->pc = state->pc + FIELD_OFFSET(instr) + 4;
                break;
            case OPERATION_JALR:
                state->rf_int.reg_int[31].wu = state->pc; 
                state->pc = state->rf_int.reg_int[FIELD_R1(instr)].wu;
                break;
            case OPERATION_BEQZ:
                state->pc = (state->rf_int.reg_int[FIELD_R1(instr)].wu == 0) ? (state->pc + FIELD_IMM(instr) - 4) : (state->pc);
                break;
            case OPERATION_BNEZ:
                state->pc = (state->rf_int.reg_int[FIELD_R1(instr)].wu != 0) ? (state->pc + FIELD_IMM(instr) - 4) : (state->pc);
                break;
        }
        printf("disabling control stall\n");
        state->control_stall = FALSE; 
        break;

    /******************************** HALT */
    case FU_GROUP_HALT:
  
      break;

    /******************************** NOP */
    case FU_GROUP_NONE:
  
      break;

    case FU_GROUP_INVALID:
      fprintf(stderr, "error: invalid opcode (instr = %.8X)\n", instr);
  }

}

int max(int x, int y){ if (x >= y){ return x; } else { return y; } }
int min(int x, int y){ if (x <= y){ return x; } else { return y; } }

void
writeback(state_t *state, int *num_insn) {
    printf("\n\nRUNNING WRITEBACK\n");
    printf("int_wb: %08x\n", state->int_wb.instr);
    perform_write(state, state->int_wb.instr, state->pc);
    perform_write(state, state->fp_wb.instr, state->pc);
    if (state->int_wb.instr != 0){
        printf("INCREMENTING\n");
        (*num_insn)++;
    }
    if (state->fp_wb.instr != 0){
        printf("INCREMENTING\n");
        (*num_insn)++;
    }
    state->int_wb.instr = 0;
    state->fp_wb.instr = 0;
     
    
}

void
execute(state_t *state) {
    printf("\n\nRUNNING EXECUTE\n");
    printf("fetch_lock: %d\n", state->fetch_lock);
    advance_fu_int(state->fu_int_list, &state->int_wb);
    advance_fu_fp(state->fu_add_list, &state->fp_wb);
    advance_fu_fp(state->fu_mult_list, &state->fp_wb);
    advance_fu_fp(state->fu_div_list, &state->fp_wb);
    if((state->fetch_lock) && !(state->control_stall) && !(state->halt_activated) && !(state->structral_lock)) {
        printf("case: fetch lock, no control stall, no halt activated\n");
        printf("stall counter: %d\n", state->stall_counter);
        if ((state->stall_counter - 1) > 0 ) {
            state->stall_counter = state->stall_counter - 1;
            printf("decremented counter: %d\n", state->stall_counter);
        } else {
            if (state->halt_activated == FALSE) {
                state->stall_counter = 0;
                printf("decremented counter: %d\n", state->stall_counter);
                state->fetch_lock = FALSE;
                printf("fetch lock diabled\n");
            }
        }
    }
    if ((state->fetch_lock) && (state->halt_activated)) {
        printf("case: fetch lock, halt activated\n");
        if (fu_int_done(state->fu_int_list) && fu_fp_done(state->fu_add_list)
            && fu_fp_done(state->fu_mult_list) && fu_fp_done(state->fu_div_list)
            && (state->int_wb.instr == 0) && (state->fp_wb.instr == 0)){
            state->end_simulation = TRUE;
        }
    }
    if (state->fetch_lock && state->structral_lock){ 
        state->fetch_lock = FALSE;
        state->structral_lock = FALSE;
    }
}

int destination_extract(int inst){
    int use_imm;
    const op_info_t *op_info = decode_instr(inst, &use_imm); 
    switch(op_info->fu_group_num) {
        case FU_GROUP_INT:
            if (use_imm == 0) { return INT_DEST_AT_3; } 
            if (use_imm == 1) { return INT_DEST_AT_2; } 
        break; 
        case FU_GROUP_ADD:
        case FU_GROUP_MULT:
        case FU_GROUP_DIV:
            return FP_DEST_AT_3;
        break;
        case FU_GROUP_MEM:
            if (op_info->operation == OPERATION_LOAD) { 
                if (op_info->data_type == DATA_TYPE_W){ return INT_DEST_AT_2; }
                if (op_info->data_type == DATA_TYPE_F){ return FP_DEST_AT_2; } 
            }
            if (op_info->operation == OPERATION_STORE) { return -1; }
        break;
    } 

} 

// return how many sources it reads from (return 1 for only r1, reutrn 2 for r1 and r2) 
int source_extract(int inst){
    int use_imm;
    const op_info_t *op_info = decode_instr(inst, &use_imm); 
    switch(op_info->fu_group_num) {
        case FU_GROUP_INT:
            if (use_imm == 0) { return INT_SOURCE_TWO; } 
            if (use_imm == 1) { return INT_SOURCE_ONE; } 
            break; 
        case FU_GROUP_ADD:
        case FU_GROUP_MULT:
        case FU_GROUP_DIV:
            return FP_SOURCE_TWO;
            break;
        case FU_GROUP_MEM:
            if (op_info->operation == OPERATION_LOAD) { 
                return INT_SOURCE_ONE;
            }
            if (op_info->operation == OPERATION_STORE) { 
                if (op_info->data_type == DATA_TYPE_W){
                    return INT_SOURCE_TWO;
                }
                if (op_info->data_type == DATA_TYPE_F){
                    return BOTH_SOURCE;
                }  
            }
            break;
    } 

} 

int get_latency(int inst){
    int use_imm;
    const op_info_t *op_info = decode_instr(inst, &use_imm);
    switch(op_info->fu_group_num) {
        case FU_GROUP_INT:
            return 2;
            break; 
        case FU_GROUP_ADD:
            return 3;
            break;
        case FU_GROUP_MULT:
            return 4;
            break;
        case FU_GROUP_DIV:
            return 8;
            break;
        case FU_GROUP_MEM:
            return 2;
            break;
        case FU_GROUP_BRANCH:
            break;
    } 

}

int WAW_dependancy(int curr_inst, int prev_inst) {
    int dest_prev = destination_extract(prev_inst);
    int dest_curr = destination_extract(curr_inst);
    switch (dest_curr)
    {
    case INT_DEST_AT_2:
        switch (dest_prev)
        {
        case INT_DEST_AT_2:
            if (FIELD_R2(curr_inst) == FIELD_R2(prev_inst)) { return TRUE; }
            break;
        case INT_DEST_AT_3:
            if (FIELD_R2(curr_inst) == FIELD_R3(prev_inst)) { return TRUE; }
            break;
        case FP_DEST_AT_2:
        case FP_DEST_AT_3:
            return FALSE;
            break;
        }
        break;
    case INT_DEST_AT_3:
        switch (dest_prev)
        {
        case INT_DEST_AT_2:
            if (FIELD_R3(curr_inst) == FIELD_R2(prev_inst)) { return TRUE; }
            break;
        case INT_DEST_AT_3:
            if (FIELD_R3(curr_inst) == FIELD_R3(prev_inst)) { return TRUE; }
            break;
        case FP_DEST_AT_2:
        case FP_DEST_AT_3:
            return FALSE;
            break;
        }
        break;
    case FP_DEST_AT_2:
        switch (dest_prev)
        {
        case INT_DEST_AT_2:
        case INT_DEST_AT_3:
            return FALSE;
            break;
        case FP_DEST_AT_2:
            if (FIELD_R2(curr_inst) == FIELD_R2(prev_inst)) { return TRUE; }
            break;
        case FP_DEST_AT_3:
            if (FIELD_R2(curr_inst) == FIELD_R3(prev_inst)) { return TRUE; }
            break;
        }
        break;
    case FP_DEST_AT_3:
        switch (dest_prev)
        {
        case INT_DEST_AT_2:
        case INT_DEST_AT_3:
            return FALSE;
            break;
        case FP_DEST_AT_2:
            if (FIELD_R3(curr_inst) == FIELD_R2(prev_inst)) { return TRUE; }
            break;
        case FP_DEST_AT_3:
            if (FIELD_R3(curr_inst) == FIELD_R3(prev_inst)) { return TRUE; }
            break;
        }
        break;
    }
    return FALSE;
}

int WAW_finder_loop(state_t* state, int inst, fu_fp_t *fu_fp_list) {
    int stall_for_WAW_count = 0; 
    fu_fp_t *fu_fp = fu_fp_list;
    fu_fp_stage_t *stage_fp = fu_fp->stage_list;
    int j;
    while (fu_fp != NULL) {
        //printf("flag 1\n");
        j = 0;
        stage_fp = fu_fp->stage_list;
        while (stage_fp != NULL) {
            if (stage_fp->current_cycle != -1) {
                printf("flag 2, j = %d\t", j);
                printf("prev inst: %08x\n", stage_fp->instr);
                if (WAW_dependancy(inst, stage_fp->instr) == TRUE){
                    stall_for_WAW_count = get_latency(inst) - (stage_fp->num_cycles - stage_fp->current_cycle);
                    printf("WAW DETECTED AT EX, stall count: %d\n", stall_for_WAW_count);
                }
            }
            j++;
            stage_fp = stage_fp->prev;
        }
        fu_fp = fu_fp->next;
    }
    return stall_for_WAW_count;
}

int WAW_finder (state_t* state, int inst, fu_int_t *fu_int_list, fu_fp_t *fu_add_list,
    fu_fp_t *fu_mult_list, fu_fp_t *fu_div_list) {
    printf("FINDING WAW\n");
    int stall_for_WAW_count = 0;
    int latency = get_latency(inst); 
    fu_int_t *fu_int = fu_int_list;
    fu_int_stage_t *stage_int = fu_int->stage_list;
    int j;
    while (fu_int != NULL) {
        //printf("flag 1\n");
        j = 0;
        stage_int = fu_int->stage_list;
        while (stage_int != NULL) {
            if (stage_int->current_cycle != -1) {
                printf("flag 2, j = %d\t", j);
                printf("prev inst: %08x\n", stage_int->instr);
                if (WAW_dependancy(inst, stage_int->instr) == TRUE){
                    stall_for_WAW_count = min(stage_int->num_cycles, (stage_int->num_cycles - stage_int->current_cycle));
                    printf("WAW DETECTED AT EX, stall count: %d\n", stall_for_WAW_count);
                }
            }
            j++;
            stage_int = stage_int->prev;
        }
        fu_int = fu_int->next;
    }
    if (WAW_dependancy(inst, state->int_wb.instr) == TRUE){
        stall_for_WAW_count = max(1, stall_for_WAW_count);
        printf("WAW DETECTED AT WB, stall count: %d\n", stall_for_WAW_count);
    }
    // Doing the same for fp
    stall_for_WAW_count = max(stall_for_WAW_count, WAW_finder_loop(state, inst, fu_add_list)); 
    stall_for_WAW_count = max(stall_for_WAW_count, WAW_finder_loop(state, inst, fu_mult_list)); 
    stall_for_WAW_count = max(stall_for_WAW_count, WAW_finder_loop(state, inst, fu_div_list));
    // same while loop stuff 
    // replace the insides of "if (stage->current_cycle != -1)" with the following: 
    // if (destination_extract(stage->instr) == destination_extract(inst)){
    //     if (((stage->num_cycles - stage->current_cycle) - latency) > 0){
    //         stall_for_WAW_count += ((stage->num_cycles - stage->current_cycle) - latency);
    //         printf("WAW DETECTED AT EX, stall count: %d\n", stall_for_WAW_count);
    //     }        
    // }
    printf("Return value of WAW finder: %d\n", stall_for_WAW_count);
    return stall_for_WAW_count;
}

int RAW_dependancy(int curr_inst, int prev_inst){
    int source_type = source_extract(curr_inst);
    int dest_type = destination_extract(prev_inst);
    printf("dest type: %d, source type: %d\n", dest_type, source_type);
    switch (source_type)
    {
    case INT_SOURCE_ONE:
        switch (dest_type){
            case INT_DEST_AT_2:
                printf("INT_SOURCE_ONE and INT_DEST_AT_2\n");
                printf("fields: %d, %d\n", FIELD_R2(prev_inst), FIELD_R1(curr_inst));
                if (FIELD_R2(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
            case INT_DEST_AT_3:
                printf("INT_SOURCE_ONE and INT_DEST_AT_3\n");
                printf("fields: %d, %d\n", FIELD_R3(prev_inst), FIELD_R1(curr_inst));
                if (FIELD_R3(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_2:
            case FP_DEST_AT_3:
                return FALSE;
                break;
        }
        break;
    case INT_SOURCE_TWO:
        switch (dest_type){
            case INT_DEST_AT_2:
                printf("INT_SOURCE_TWO and INT_DEST_AT_2\n");
                if (FIELD_R2(prev_inst) == FIELD_R1(curr_inst) || FIELD_R2(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
            case INT_DEST_AT_3:
                printf("INT_SOURCE_TWO and INT_DEST_AT_3\n");
                if (FIELD_R3(prev_inst) == FIELD_R1(curr_inst) || FIELD_R3(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_2:
            case FP_DEST_AT_3:
                return FALSE;
                break;
        }
        break;
    case FP_SOURCE_ONE:
        switch (dest_type){
            case INT_DEST_AT_2:
            case INT_DEST_AT_3:
                return FALSE;
                break;
            case FP_DEST_AT_2:
                if (FIELD_R2(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_3:
                if (FIELD_R3(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
        }
        break;
    case FP_SOURCE_TWO:
        switch (dest_type){
            case INT_DEST_AT_2:
            case INT_DEST_AT_3:
                return FALSE;
                break;
            case FP_DEST_AT_2:
                if (FIELD_R2(prev_inst) == FIELD_R1(curr_inst) || FIELD_R2(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_3:
                if (FIELD_R3(prev_inst) == FIELD_R1(curr_inst) || FIELD_R3(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
        }
        break;
    case BOTH_SOURCE: // both source meaning r2 is FP and r1 is INT
        switch (dest_type){
            case INT_DEST_AT_2:
                if (FIELD_R2(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
            case INT_DEST_AT_3:
                if (FIELD_R3(prev_inst) == FIELD_R1(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_2:
                if (FIELD_R2(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
            case FP_DEST_AT_3:
                if (FIELD_R3(prev_inst) == FIELD_R2(curr_inst)){ return TRUE; }
                break;
        }
        break;
    }
    return FALSE;
    
}

int RAW_finder_loop (state_t* state, int inst, fu_fp_t *fu_fp_list){
    int stall_for_RAW_count = 0; 
    fu_fp_t *fu_fp = fu_fp_list;
    fu_fp_stage_t *stage_fp = fu_fp->stage_list;
    int j;
    while (fu_fp != NULL) {
        //printf("flag 1\n");
        j = 0;
        stage_fp = fu_fp->stage_list;
        while (stage_fp != NULL) {
            if (stage_fp->current_cycle != -1) {
                printf("flag 2, j = %d\t", j);
                printf("prev inst: %08x\n", stage_fp->instr);
                if (RAW_dependancy(inst, stage_fp->instr) == TRUE){
                    stall_for_RAW_count = stage_fp->num_cycles - stage_fp->current_cycle;
                    printf("RAW DETECTED AT EX, stall count: %d\n", stall_for_RAW_count);
                }
            }
            j++;
            stage_fp = stage_fp->prev;
        }
        fu_fp = fu_fp->next;
    }
    return stall_for_RAW_count;
    
}

int RAW_finder (state_t* state, int inst, fu_int_t *fu_int_list, fu_fp_t *fu_add_list,
    fu_fp_t *fu_mult_list, fu_fp_t *fu_div_list) {
    printf("FINDING RAW\n");
    int stall_for_RAW_count = 0; 

    fu_int_t *fu_int = fu_int_list;
    fu_int_stage_t *stage_int = fu_int->stage_list;
    int j;
    //fu_int = state->fu_int_list;
    while (fu_int != NULL) {
        //printf("flag 1\n");
        j = 0;
        stage_int = fu_int->stage_list;
        while (stage_int != NULL) {
            if (stage_int->current_cycle != -1) {
                printf("flag 2, j = %d\t", j);
                printf("prev inst: %08x\n", stage_int->instr);
                if (RAW_dependancy(inst, stage_int->instr) == TRUE){
                    stall_for_RAW_count = stage_int->num_cycles - stage_int->current_cycle;
                    printf("RAW DETECTED AT EX, stall count: %d\n", stall_for_RAW_count);
                }
            }
            j++;
            stage_int = stage_int->prev;
        }
        fu_int = fu_int->next;
    }
    // stall for the insturction that just got adavnced to write back
    if (RAW_dependancy(inst, state->int_wb.instr) == TRUE){
        stall_for_RAW_count = max(1, stall_for_RAW_count);
        printf("RAW DETECTED AT WB, stall count: %d\n", stall_for_RAW_count);
    }

    // Doing the same for fp
    stall_for_RAW_count = max(stall_for_RAW_count, RAW_finder_loop(state, inst, fu_add_list)); 
    stall_for_RAW_count = max(stall_for_RAW_count, RAW_finder_loop(state, inst, fu_mult_list)); 
    stall_for_RAW_count = max(stall_for_RAW_count, RAW_finder_loop(state, inst, fu_div_list)); 
    if (RAW_dependancy(inst, state->fp_wb.instr) == TRUE){
        stall_for_RAW_count = max(1, stall_for_RAW_count);
        printf("RAW DETECTED AT WB, stall count: %d\n", stall_for_RAW_count);
    }
    printf("Return value of RAW finder: %d\n", stall_for_RAW_count);
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

    int stall_for_RAW = RAW_finder(state, inst, state->fu_int_list, state->fu_add_list, state->fu_mult_list, state->fu_div_list); 
    int stall = FALSE; 
    if (stall_for_RAW > 0) {
        stall = TRUE;
    }
    if(stall) { 
        state->stalled_inst = state->if_id.instr;
        // add max (WAW, RAW)
        state->stall_counter = stall_for_RAW; 
        state->fetch_lock = TRUE;
    } else { 
        switch (group_num) {
            case FU_GROUP_INT:
                if (issue_fu_int(state->fu_int_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                    state->structral_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_ADD:
                if (issue_fu_fp(state->fu_add_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                    state->structral_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_MULT:
                if (issue_fu_fp(state->fu_mult_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                    state->structral_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_DIV:
                if (issue_fu_fp(state->fu_div_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                    state->structral_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_MEM:
                if (issue_fu_int(state->fu_int_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                    state->structral_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_BRANCH:
                state->control_stall = TRUE;
                //state->fetch_lock = TRUE;
                if (issue_fu_int(state->fu_int_list, inst) == -1) {
                    printf("Structral Hazard Detected\n");
                    state->fetch_lock = TRUE;
                } else {
                    state->structral_lock = FALSE;
                }
                break;
            case FU_GROUP_NONE:
                break;
            case FU_GROUP_INVALID:
                break;
            case FU_GROUP_HALT:
                // halt_activated 
                state->halt_activated = TRUE;
                // state->if_id.pc = 0;
                // fetch lock 
                state->fetch_lock = TRUE;
                break;
        }
    }
}

void
fetch(state_t *state) { 
    if (state->fetch_lock == FALSE){
        printf("\n\nRUNNING FETCH\n");
        int pc, inst;  
        pc = state->pc; 
        inst = (state->mem[pc + 3] << 24) + (state->mem[pc + 2] << 16) 
            + (state->mem[pc + 1] << 8) + (state->mem[pc + 0]);
        state->if_id.instr = inst;
        state->if_id.pc = pc;
        state->pc = pc + 4;
        printf("incrementing PC, PC at %8x\n",state->pc);
        printf("fetching: %08x\n", inst);
    }
    if (state->control_stall == TRUE){
        printf("control stalling\n");
        state->fetch_lock = TRUE; 
        printf("fetch_lock: %d\n", state->fetch_lock);
    }
    // control stall 
}
