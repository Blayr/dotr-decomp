#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b620", func_01E00080_b620);

/* shape b620:01E01ED0, 106 insns: record a new step in one of the scene's 4-entry trails (track i): mark the next record, copy the track's point, store the distance to the scene centre (+0x30) and a direction (func_00100E40) with a random twist, then advance the track's count and index (wrapping at 4) */

typedef struct {
    f32 x, y, z, w;
} V4_b620_01E01ED0;

typedef struct {
    s8 on;
    u8 pad1[3];
    s32 w4;
    u8 pad8[4];
    f32 len;
    V4_b620_01E01ED0 pos;
    u8 q[0x40];
} Rec_b620_01E01ED0;

typedef struct {
    u8 pad0[0x30];
    V4_b620_01E01ED0 c;
    u8 pad40[0x20];
    V4_b620_01E01ED0 pt[1];
    u8 pad70[0xB68 - 0x70];
    s32 cnt[6];
    s32 cur[8];
    Rec_b620_01E01ED0 rec[1][4];
} Scene_b620_01E01ED0;

#pragma opt_propagation off

static void func_01E01ED0_b620(Scene_b620_01E01ED0 *g0, s32 i) {
    Scene_b620_01E01ED0 *g = g0;
    extern void func_00101080(void *, f32);
    extern void func_00187B00(void *, void *, void *);
    extern void func_00187B18(void *, void *, void *);
    extern f32 func_001A6C48(f32, f32);
    extern f32 func_001A6C60(f32);
    extern void func_00100E40(void *, void *);
    extern void func_00100E00(void *, s32, s32);
    V4_b620_01E01ED0 v;
    s32 c;

    c = g->cur[i];
    g->rec[i][c].on = 1;
    g->rec[i][c].w4 = 0;
    g->rec[i][c].pos = g->pt[i];
    func_00101080(&v, 2.0f);
    func_00187B00(&v, &v, &g->c);
    func_00187B18(&v, &v, &g->pt[i]);
    g->rec[i][c].len = func_001A6C60(func_001A6C48(v.x, 2.0f) + func_001A6C48(v.y, 2.0f) + func_001A6C48(v.z, 2.0f));
    func_00100E40(g->rec[i][c].q, &v);
    func_00100E00(g->rec[i][c].q, (((func_0019A5C8() >> 23) % 256) << 16) >> 8, 2);
    g->cnt[i]++;
    g->cur[i]++;
    if (g->cur[i] >= 4) {
        g->cur[i] = 0;
    }
}
#pragma opt_propagation reset
