#ifndef SMOLLISP_H__RESULT
#define SMOLLISP_H__RESULT

#include <stdint.h>

typedef enum smollisp_Result {
  SMOLLISP_RESULT_OK,

  /* VM errors, occur when an OP is misused */
  // Operands on the VM stack do not support this OP
  SMOLLISP_RESULT_TYPE_MISMATCH,
  // Not enough operands on the stack to perform the OP
  SMOLLISP_RESULT_STACK_UNDERFLOW,
  // Whatever the frame it's waaay too nested, exists to avoid infinite loops
  SMOLLISP_RESULT_VAR_NOT_FOUND,
} smollisp_Result;

#endif
