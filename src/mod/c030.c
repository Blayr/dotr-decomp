#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E00080_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E00B60_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E00E30_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E01110_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E012A0_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E01510_c030);

/* shape c030:01E018C0, 133 insns: c030 trail link spawner (c560:01E01C50 family, 65 slots of 0x7C at ctx+0x334): first free slot (marked slot+1), both colours and alpha from the context, its vector, sizes as shorts, height 18 above, both capped at 50, chained after the context's last piece and becomes it; draws with c030:01E02170 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E018C0;

typedef struct Ent_c030_01E018C0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E018C0 *prev;
    struct Ent_c030_01E018C0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E018C0 col0;
    Col_c030_01E018C0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E018C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E018C0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E018C0 ent[65];
} Ctx_c030_01E018C0;

static void func_01E018C0_c030(Ctx_c030_01E018C0 *g, s32 arg) {
    extern void c030_01E02170(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E018C0 *e = NULL;
    Ent_c030_01E018C0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        e->f70 = g->f2D4;
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E02170;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

/* shape c030:01E01AE0, 134 insns: c030:01E018C0 with f70 copied after the caps and the c030:01E01D00 draw callback */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c030_01E01AE0;

typedef struct Ent_c030_01E01AE0 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    Vec4f v;
    u8 pad40[0x10];
    struct Ent_c030_01E01AE0 *prev;
    struct Ent_c030_01E01AE0 *next;
    void (*cb)(void);
    s32 arg;
    Col_c030_01E01AE0 col0;
    Col_c030_01E01AE0 col1;
    s16 used;
    s16 f6A;
    s16 f6C;
    s16 f6E;
    s16 f70;
    s16 f72;
    s16 f74;
    u8 pad76[2];
    s16 f78;
    u8 pad7A[2];
} Ent_c030_01E01AE0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xF4 - 0x90];
    u8 rgba[4];
    u8 padF8[8];
    Ent_c030_01E01AE0 *last;
    u8 pad104[4];
    f32 f108;
    f32 f10C;
    f32 f110;
    u8 pad114[0x2D4 - 0x114];
    s16 f2D4;
    s16 f2D6;
    u8 pad2D8[2];
    s16 f2DA;
    u8 pad2DC[2];
    s16 f2DE;
    u8 pad2E0[0x2F0 - 0x2E0];
    s16 f2F0;
    u8 pad2F2[0x334 - 0x2F2];
    Ent_c030_01E01AE0 ent[65];
} Ctx_c030_01E01AE0;

static void func_01E01AE0_c030(Ctx_c030_01E01AE0 *g, s32 arg) {
    extern void c030_01E01D00(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c030_01E01AE0 *e = NULL;
    Ent_c030_01E01AE0 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 65; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x7C);
            g->ent[i].used = i + 1;
            i = 65;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col0.a = g->rgba[3];
        func_001076F0(&e->col1, g->rgba[0], g->rgba[1], g->rgba[2]);
        e->col1.a = g->rgba[3];
        e->v = g->v;
        e->f6A = (s16)g->f108;
        e->f6C = (s16)g->f10C;
        e->f72 = g->f2D6;
        e->prev = g->last;
        e->f6E = g->f2DE;
        if (e->prev == NULL) {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        } else {
            h = g->f110;
            e->f4 = h;
            e->f14 = h + d;
        }
        if (50.0f < e->f4) {
            e->f4 = 50.0f;
        }
        if (50.0f < e->f14) {
            e->f14 = 50.0f;
        }
        e->f78 = g->f2F0;
        e->f70 = g->f2D4;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->cb = c030_01E01D00;
        e->arg = arg;
        e->f74 = g->f2DA;
        g->last = e;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E01D00_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E02170_c030);

INCLUDE_ASM("asm/nonmatchings/mod/c030", func_01E02600_c030);
