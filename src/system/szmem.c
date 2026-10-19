/* Memory helpers (SzMem_*). */

#include "common.h"

/* Starts the memory allocator (nothing to do). */
void SzMem_Init(void) {
    func_00197C18(func_00197BC0(0x01FFEFF0 - (s32)&D_1FE0000));
}

/* Allocates `size` bytes, 16-byte aligned. */
s32 SzMem_Alloc(s32 size) {
    return (s32)func_00197990(0x10, size);
}

/* Frees allocation `block`. */
void SzMem_Free(s32 block) {
    func_00197C18(block);
}

/* A newly allocated copy of `str`, or 0. */
char *SzMem_StrDup(char *str) {
    char *copy;

    if (str == 0) {
        return 0;
    }
    copy = func_00197990(0x10, func_0019BEF0(str) + 1);
    if (copy == 0) {
        return 0;
    }
    func_0019BDD8(copy, str);
    return copy;
}
