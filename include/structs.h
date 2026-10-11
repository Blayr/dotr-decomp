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

typedef struct {
    f32 x, y, z, w;
} Vec4f;

typedef struct {
    u8 pad00[4];
    s32 f4;
} ObjSlotInner_0031ABB0;

typedef struct {
    u8 pad00[0x14];
    ObjSlotInner_0031ABB0 *f14;
} ObjSlot_0031ABB0;

/* D_0031ABB0 holds 0x54 pointers to these (func_001F25D0, func_001F0830, func_001F1400). */
typedef struct {
    u8 pad000[0x30];
    Vec4f v;                     /* 0x030 */
    u8 pad040[0x138];
    ObjSlot_0031ABB0 *slots[18]; /* 0x178 */
    s32 vals[8];                 /* 0x1C0 */
    s8 lv[4];                    /* 0x1E0 */
} Obj_0031ABB0;

extern Obj_0031ABB0 *D_0031ABB0[];

#endif
