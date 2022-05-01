#ifndef SMOLLISP_H__CONTEXT
#define SMOLLISP_H__CONTEXT

#include "Result.h"
#include "Value.h"
#include <stdlib.h>

typedef struct smollisp_ContextVariable {
  const char *name;
  smollisp_Value value;
} smollisp_ContextVariable;

typedef struct smollisp_Context {
  smollisp_Context *parent;
  smollisp_ContextVariable *variables;
  size_t variable_count;
} smollisp_Context;

void smollisp_Context_new(smollisp_Context *ctx) {
  ctx->parent = NULL;
  ctx->variables = NULL;
  ctx->variable_count = 0;
}

void smollisp_Context_define_var(smollisp_Context *ctx, const char *name,
                                 smollisp_Value mov_value) {
  ctx->variable_count++;
  ctx->variables = (smollisp_ContextVariable *)realloc(
      (void *)ctx->variables,
      sizeof(smollisp_ContextVariable) * ctx->variable_count);

  char *varname = (char *)malloc(sizeof(char) * strlen(name));
  strcpy(varname, name);
  ctx->variables[ctx->variable_count - 1].name = varname;
  ctx->variables[ctx->variable_count - 1].value = mov_value;
}

smollisp_Result smollisp_Context_lookup(smollisp_Context *ctx, const char *name,
                                        smollisp_Value *out) {
  for (int j = 0; j < ctx->variable_count; j++) {
    if (strcmp(ctx->variables[j].name, name) == 0) {
      smollisp_Value_copy(&ctx->variables[j].value, out);
      return SMOLLISP_RESULT_OK;
    }
  }

  if (ctx->parent)
    return smollisp_Context_lookup(ctx->parent, name, out);
  else
    return SMOLLISP_RESULT_VAR_NOT_FOUND;
}

#endif
