#ifndef STRUCTS_H
#define STRUCTS_H

/* Types and globals that more than one function uses. Edited by hand; dk never
   rewrites this file. A type used by one function only stays beside it. */

/* Two 12-byte records (func_001FD1B0, func_001FD220). */
typedef struct {
    u8 pad0[5];
    u8 lo;
    u8 hi;
    s8 pad7 : 6;
    s8 flag : 1;
    s8 pad7b : 1;
    u8 pad8[4];
} Entry_0031C050;

extern Entry_0031C050 D_0031C050[];

#endif
