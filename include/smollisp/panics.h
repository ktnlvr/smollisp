#ifndef SMOLLISP_H__PANICS
#define SMOLLISP_H__PANICS

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define SMOLLISP_PANIC_CODE_UNREACHABLE 0xDEAD
#define SMOLLISP_PANIC_CODE_ASSERT_FAIL 0xA55

#define SMOLLISP_UNREACHABLE                                                   \
  {                                                                            \
    printf("Hit unreachable at " __FILE__ ":%d\n", __LINE__);                  \
    exit(SMOLLISP_PANIC_CODE_UNREACHABLE); /* call panic handler maybe? */     \
  }

#define SMOLLISP_ASSERT(cond)                                                  \
  {                                                                            \
    if (!(cond)) {                                                             \
      printf("Failed assertion (" #cond ") in " __FILE__ ":%d\n", __LINE__);   \
      raise(SIGTRAP);                                                          \
      exit(SMOLLISP_PANIC_CODE_ASSERT_FAIL);                                   \
    }                                                                          \
  }

#endif
