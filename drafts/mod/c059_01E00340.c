#include "common.h"

/* shape c059:01E00340, 157 insns: the scene's sound setup: lists the voices whose bit (21 - k) is set in 0x2CC0 (k + 0xF5
   above 10), switches all 22 voices on, then for each of three sparks picks a size 9..34 / 6, a step 5..12 (signed
   %8), a speed 0x100..0x18FF and a turn -0x400..0x3FF, places it 35 out along its path, aims the listed voice at it
   and sets that voice's volume byte to 0x80 */

typedef struct {
    f32 x, y, z, w;
} V4_c059_01E00340;

typedef struct {
    u8 pad0[0x28];
    s32 step;
    u8 pad2C[8];
    s32 speed;
    s32 turn;
    u8 pad3C[0x14];
    V4_c059_01E00340 pos;
    u8 col[4];
    s32 h64;
    u8 pad68[8];
} Spark_c059_01E00340;

typedef struct {
    u8 pad0[0x2650];
    Spark_c059_01E00340 sp[3];
    u8 pad27A0[0x1C0];
    u8 at[3][16];
    u8 pad2990[0x20];
    u8 path[3][16];
    u8 pad29E0[0x2CC];
    s32 ch[5];
    u32 mask;
} Scene_c059_01E00340;

static void func_01E00340_c059(Scene_c059_01E00340 *g) {
    extern void func_001F5970(s32, s32);
    extern void func_001099E0(void *, void *, void *, f32);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    V4_c059_01E00340 v;
    Spark_c059_01E00340 *o;
    s16 i;
    s32 n;
    s32 c;

    n = 0;
    for (i = 0; i < 22; i++) {
        if ((g->mask >> (21 - i)) & 1) {
            c = i;
            if (c > 10) {
                c += 0xF5;
            }
            g->ch[n++] = c;
        }
    }
    for (i = 0; i < 22; i++) {
        c = i;
        if (c > 10) {
            c += 0xF5;
        }
        func_001F5970(c, 1);
    }
    for (i = 0; i < 3; i++) {
        c = g->ch[i];
        o = &g->sp[i];
        o->h64 = 0;
        o->pos.y = (func_0019A5C8() % 26 + 9) / 6;
        o->step = func_0019A5C8() % 8 + 5;
        o->speed = func_0019A5C8() % 0x1800 + 0x100;
        o->turn = func_0019A5C8() % 0x800 - 0x400;
        if (i < 3) {
            func_001099E0(&v, g->path[i], o, 35.0f);
            o->pos = v;
        }
        func_001F5CA0(g->ch[i], g->at[i]);
        func_001F6490(c, o->col);
        o->col[3] = 0x80;
        func_001F63E0(c, o->col);
    }
}
