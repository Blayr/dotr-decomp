#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E00080_c031);

/* shape c031:01E00360, 81 insns: turns an effect by its three spin speeds (each angle pinned at 360 once it leaves -360..360);
   fades both alphas by 48 while the scene state is below 6, else holds them at 0xFF; clears its flag below state 2. The conversion is the runtime fptosi (func_001A22C0) declared as returning s16:
   a plain (s32) cast adds a sign-extension the original does not have. */

typedef struct {
    u8 pad0[0x36C];
    s32 state;
} Scene_c031_01E00360;

typedef struct {
    u8 pad0[0x20];
    f32 vx, vy, vz;
    u8 pad2C[0xC];
    u8 c38[4];
    u8 c3C[4];
    s16 flag;
    s16 ax, ay, az;
} Fx_c031_01E00360;

static s32 func_01E00360_c031(Scene_c031_01E00360 *s, Fx_c031_01E00360 *o) {
    extern s16 func_001A22C0(f32);
    if (o->ax < 0x168 && o->ax > -0x168) {
        o->ax += func_001A22C0(o->vx);
    } else {
        o->ax = 0x168;
    }
    if (o->ay < 0x168 && o->ay > -0x168) {
        o->ay += func_001A22C0(o->vy);
    } else {
        o->ay = 0x168;
    }
    if (o->az < 0x168 && o->az > -0x168) {
        o->az += func_001A22C0(o->vz);
    } else {
        o->az = 0x168;
    }
    if (s->state < 6) {
        if (o->c38[3] > 0x30) {
            o->c38[3] -= 0x30;
        }
        if (o->c3C[3] > 0x30) {
            o->c3C[3] -= 0x30;
        }
    } else {
        o->c38[3] = 0xFF;
        o->c3C[3] = 0xFF;
    }
    if (s->state < 2) {
        o->flag = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E004B0_c031);

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E006E0_c031);

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E00960_c031);

/* shape c031:01E00B90, 91 insns: take a free row (7 of 0x54 bytes at 0x120, mark = index + 1), clear it, two colours
   from the scene colour 0x370, copy the scene vector 0x80 and a velocity of -1/10 of it, 0x52 from 0x3EA, callback
   c031:01E01950 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c031_01E00B90;

typedef struct {
    V4_c031_01E00B90 pos;
    u8 pad10[0x10];
    f32 vx, vy, vz;
    u8 pad2C[4];
    void (*cb)(void);
    s32 arg;
    u8 c38[4];
    u8 c3C[4];
    s16 used;
    u8 pad42[0x10];
    s16 f52;
} Row_c031_01E00B90;

typedef struct {
    u8 pad0[0x80];
    V4_c031_01E00B90 pos;
    u8 pad90[0x90];
    Row_c031_01E00B90 rows[7];
    u8 pad36C[4];
    u8 rgba[4];
    u8 pad374[0x76];
    s16 f3EA;
} Scene_c031_01E00B90;

static void func_01E00B90_c031(Scene_c031_01E00B90 *g, s32 arg) {
    extern void c031_01E01950(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c031_01E00B90 *s = NULL;
    s16 i;

    for (i = 0; i < 7; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x54);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 7;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c38, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c38[3] = g->rgba[3];
        func_001076F0(s->c3C, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c3C[3] = g->rgba[3];
        s->pos = g->pos;
        s->vx = -(g->pos.x / 10.0f);
        s->vy = -(g->pos.y / 10.0f);
        s->vz = -(g->pos.z / 10.0f);
        s->f52 = g->f3EA;
        s->cb = c031_01E01950;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E00D00_c031);

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E01950_c031);
