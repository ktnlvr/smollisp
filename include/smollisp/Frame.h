#ifndef SMOLLISP_H__FRAME
#define SMOLLISP_H__FRAME

#include <stdlib.h>

#include "Op.h"
#include "Result.h"
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

void smollisp_Frame_destroy(smollisp_Frame *frame) { /* TODO */ }

void smollisp_Frame_push(smollisp_Frame *frame, smollisp_Value mov_value) {
  SMOLLISP_ASSERT(frame->stack_length < frame->stack_capacity);

  frame->stack[frame->stack_length++] = mov_value;
}

smollisp_Result smollisp_Frame_return(smollisp_Frame *return_from,
                                      uint16_t return_num,
                                      smollisp_Frame *return_into) {
  SMOLLISP_ASSERT(return_from->stack_length >= return_num);

  for (int i = 0; i < return_num; i++)
    smollisp_Frame_push(return_into,
                        return_from->stack[return_from->stack_length-- - 1]);

  return SMOLLISP_RESULT_OK;
}

smollisp_Value smollisp_Frame_pop(smollisp_Frame *frame) {
  SMOLLISP_ASSERT(frame->stack_length > 0);

  return frame->stack[frame->stack_length-- - 1];
}

smollisp_Result smollisp_Frame__do_add(smollisp_Frame *frame) {
  /* TODO: handle stack overflow and underflow */
  if (frame->stack_length < 2)
    return SMOLLISP_RESULT_STACK_UNDERFLOW;

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
    default:
      return SMOLLISP_RESULT_TYPE_MISMATCH;
    }
  } break;

  case SMOLLISP_VALUE_KIND_NONE:
    return SMOLLISP_RESULT_TYPE_MISMATCH;

  default:
    SMOLLISP_UNREACHABLE;
  }

  return SMOLLISP_RESULT_OK;
}

smollisp_Result smollisp_Frame_do_op(smollisp_Frame *frame, smollisp_Op op) {
  smollisp_Result ret;

  switch (op) {
  case SMOLLISP_OP_ADD: {
    ret = smollisp_Frame__do_add(frame);
  } break;

  default:
    SMOLLISP_UNREACHABLE;
  }

  return ret;
}

#endif
