#include <stdio.h>

#include "smollisp/VM.h"

int main(void) {
  smollisp_VM vm;
  smollisp_VM_new(&vm);
  smollisp_VM_begin_frame(&vm);

  smollisp_Value i_16;
  smollisp_Value i_32;

  smollisp_Value_new_int32(&i_16, 16);
  smollisp_Value_new_int32(&i_32, 32);

  smollisp_Frame *frame = smollisp_VM_get_top_frame(&vm);
  smollisp_Frame_push(frame, i_16); // i_16 moved
  smollisp_Frame_push(frame, i_32); // i_32 moved
  smollisp_Result result = smollisp_Frame_do_op(frame, SMOLLISP_OP_ADD);

  SMOLLISP_ASSERT(result == SMOLLISP_RESULT_OK);

  printf("%d\n", frame->stack[0].int32);
  return 0;
}
