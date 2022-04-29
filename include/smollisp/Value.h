#ifndef SMOLLISP_H__VALUE
#define SMOLLISP_H__VALUE

#include <stdint.h>

typedef enum smollisp_ValueKind {
  SMOLLISP_VALUE_KIND_NONE,
  SMOLLISP_VALUE_KIND_INT32,
} smollisp_ValueKind;

typedef struct smollisp_Value {
  smollisp_ValueKind kind;
  union {
    int32_t int32;
  };
} smollisp_Value;

void smollisp_Value_new_none(smollisp_Value *value) {
  value->kind = SMOLLISP_VALUE_KIND_NONE;
}

void smollisp_Value_new_int32(smollisp_Value *value, int32_t int32) {
  value->kind = SMOLLISP_VALUE_KIND_INT32;
  value->int32 = int32;
}

#endif
