#ifndef SMOLLISP_H__VM
#define SMOLLISP_H__VM

#include <stdlib.h>

#include "Frame.h"

typedef struct smollisp_VM {
  smollisp_Frame *frames;
  size_t frames_capacity;
  size_t frames_length;
} smollisp_VM;

void smollisp_VM_new(smollisp_VM *vm) {
  vm->frames = (smollisp_Frame *)malloc(sizeof(smollisp_Frame) * 16);
  vm->frames_length = 0;
  vm->frames_capacity = 16;
}

void smollisp_VM_begin_frame(smollisp_VM *vm) {
  smollisp_Frame_new(&vm->frames[vm->frames_length++]);
}

smollisp_Frame *smollisp_VM_get_top_frame(smollisp_VM *vm) {
  if (vm->frames_length <= 0)
    abort();

  return &vm->frames[vm->frames_length - 1];
}

void smollisp_VM_destroy(smollisp_VM *vm) { free(vm->frames); }

#endif
