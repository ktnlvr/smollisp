#ifndef SMOLLISP_H__VALUE
#define SMOLLISP_H__VALUE

#include <stdint.h>
#include <string.h>

#define SMOLLISP_SMALL_STRING_LENGTH (15)

typedef enum smollisp_ValueKind {
  SMOLLISP_VALUE_KIND_NONE,
  SMOLLISP_VALUE_KIND_INT32,
  SMOLLISP_VALUE_KIND_STRING,
} smollisp_ValueKind;

typedef struct smollisp_Value {
  smollisp_ValueKind kind;
  union {
    int32_t int32;
    struct {
      char *buf;
      size_t length;
    } string;
  };
} smollisp_Value;

void smollisp_Value_new_none(smollisp_Value *value) {
  value->kind = SMOLLISP_VALUE_KIND_NONE;
}

void smollisp_Value_new_int32(smollisp_Value *value, int32_t int32) {
  value->kind = SMOLLISP_VALUE_KIND_INT32;
  value->int32 = int32;
}

void smollisp_Value_new_string(smollisp_Value *value, const char *cstr) {
  value->kind = SMOLLISP_VALUE_KIND_STRING;
  size_t len = strlen(cstr);
  value->string.buf = (char *)malloc(sizeof(char) * len);
  memcpy(value->string.buf, cstr, sizeof(char) * len);
  value->string.length = len;
}

void smollisp_Value_new_string_mov(smollisp_Value* value, char* mov_cstr) {
  value->kind = SMOLLISP_VALUE_KIND_STRING;
  value->string.buf = mov_cstr;
  value->string.length = strlen(value->string.buf);
}

void smollisp_Value_destroy(smollisp_Value *value) {
  switch (value->kind) {
  case SMOLLISP_VALUE_KIND_STRING:
    free(value->string.buf);
    break;

  default:
    break;
  }
}

#endif
