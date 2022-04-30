#ifndef SMOLLISP_H__FRAME
#define SMOLLISP_H__FRAME

#include <stdlib.h>

#include "Op.h"
#include "Value.h"
#include "panics.h"

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
  SMOLLISP_ASSERT(frame->stack_length < frame->stack_capacity);

  frame->stack[frame->stack_length++] = mov_value;
}

smollisp_Value smollisp_Frame_pop(smollisp_Frame *frame) {
  SMOLLISP_ASSERT(frame->stack_length > 0);

  return frame->stack[frame->stack_length-- - 1];
}

void smollisp_Frame__do_add(smollisp_Frame *frame) {
  /* TODO: handle stack overflow and underflow */
  SMOLLISP_ASSERT(frame->stack_length >= 2);

  /* x1 x2 -- x3 */
  smollisp_Value x1 = smollisp_Frame_pop(frame);
  smollisp_Value x2 = smollisp_Frame_pop(frame);
  smollisp_Value x3;

  switch (x1.kind) {
  case SMOLLISP_VALUE_KIND_INT32: {
    switch (x2.kind) {
    case SMOLLISP_VALUE_KIND_INT32:
      smollisp_Value_new_int32(&x3, x1.int32 + x2.int32);
      smollisp_Frame_push(frame, x3);
      break;

    case SMOLLISP_VALUE_KIND_NONE:
    /* TODO: raise type error for types which cannot be added */
    default:
      SMOLLISP_UNREACHABLE;
    }
  } break;

  case SMOLLISP_VALUE_KIND_NONE:
    /* TODO: raise type error for types which cannot be added */
  default:
    SMOLLISP_UNREACHABLE;
  }
}

void smollisp_Frame_do_op(smollisp_Frame *frame, smollisp_Op op) {
  switch (op) {
  case SMOLLISP_OP_ADD: {
    smollisp_Frame__do_add(frame);
  } break;

  default:
    SMOLLISP_UNREACHABLE;
  }
}

#endif
