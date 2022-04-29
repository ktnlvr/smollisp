#ifndef SMOLLISP_H__FRAME
#define SMOLLISP_H__FRAME

#include <stdlib.h>

#include "Op.h"
#include "Value.h"

typedef struct smollisp_Frame {
  size_t stack_length;
  size_t stack_capacity;
  smollisp_Value *stack;
} smollisp_Frame;

void smollisp_Frame_new(smollisp_Frame *frame) {
  frame->stack_length = 0;
  frame->stack_capacity = 16;
  frame->stack = (smollisp_Value *)malloc(sizeof(smollisp_Value) * 16);
}

void smollisp_Frame_push(smollisp_Frame *frame, smollisp_Value mov_value) {
  if (frame->stack_length >= frame->stack_capacity)
    abort();

  frame->stack[frame->stack_length++] = mov_value;
}

smollisp_Value smollisp_Frame_pop(smollisp_Frame *frame) {
  if (frame->stack_length <= 0)
    abort();

  return frame->stack[frame->stack_length-- - 1];
}

void smollisp_Frame_do_op(smollisp_Frame *frame, smollisp_Op op) {
  switch (op) {
  case SMOLLISP_OP_ADD_UNCHECKED: {
    smollisp_Value a = smollisp_Frame_pop(frame);
    smollisp_Value b = smollisp_Frame_pop(frame);
    smollisp_Value out;

    smollisp_Value_new_int32(&out, a.int32 + b.int32);
    smollisp_Frame_push(frame, out);
  } break;

  default:
    // Unreachable
    abort();
  }
}

#endif
