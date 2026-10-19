/* Memory copy and fill (RhMem_*). */

#include "common.h"

/* Copies `size` bytes; returns the end of the copy. */
u8 *RhMem_CopyMemory(u8 *dst, u8 *src, s32 size) {
    if (size > 0) {
        do {
            size -= 1;
            *dst = *src;
            src += 1;
            dst += 1;
        } while (size > 0);
    }
    return dst;
}

/* Copies `count` words; returns the end of the copy. */
void *RhMem_CopyMemory4(void *dest, void *source, s32 count) {
    s32 *dst = dest;
    s32 *src = source;

    if (count > 0) {
        do {
            count--;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
    }
    return dst;
}

/* Copies `count` quadwords; returns the end of the copy. */
void *RhMem_CopyMemory16(void *dest, void *source, s32 count) {
    __int128 *dst = dest;
    __int128 *src = source;

    if (count > 0) {
        do {
            count -= 1;
            *dst = *src;
            src++;
            dst++;
        } while (count > 0);
    }
    return dst;
}

/* Fills `size` bytes with `value`. */
s8 *RhMem_FillMemory(s8 *dst, s8 value, s32 size) {
    if (size > 0) {
        do {
            *dst = value;
            size -= 1;
            dst += 1;
        } while (size > 0);
    }
    return dst;
}

/* Fills `count` words with `val`. */
void *RhMem_FillMemory4(void *dst, s32 val, s32 count) {
    s32 *p = dst;

    while (count > 0) {
        *p++ = val;
        count--;
    }
    return p;
}

/* Fills `count` doublewords with `value`. */
s64 *RhMem_FillMemory8(s64 *dst, s64 value, s32 count) {
    while (count > 0) {
        *dst = value;
        count -= 1;
        dst++;
    }
    return dst;
}
