#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00080_c026);

/* shape c026:01E00B10, 54 insns: fades two alphas by the game timer: up 8 to 0x80 for 13 frames, then down 16 to 0x10
   while the phase is below 6, then up 8 to 0xB0; clears the flag below phase 2 */

typedef struct {
    u8 pad0[0x1A40];
    s32 phase;
    u8 pad1A44[0x80];
    s16 timer;
} Game_c026_01E00B10;

typedef struct {
    u8 pad0[0x64];
    u8 c0[4];
    u8 c1[4];
    s16 flag;
} Obj_c026_01E00B10;

static s32 func_01E00B10_c026(Game_c026_01E00B10 *g, Obj_c026_01E00B10 *o) {
    if (g->timer < 0xD) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 8;
        }
    } else if (g->phase < 6) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        }
        if (o->c1[3] > 0x10) {
            o->c1[3] -= 0x10;
        }
    } else {
        if (o->c0[3] < 0xB0) {
            o->c0[3] += 8;
        }
        if (o->c1[3] < 0xB0) {
            o->c1[3] += 8;
        }
    }
    if (g->phase < 2) {
        o->flag = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00BF0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E00F20_c026);

/* shape c026:01E01170, 64 insns: takes the first free of 50 effect slots (0x80 bytes, b108:01E02FF0 family), marks it with
   its index + 1, colours both from the context, hooks c026:01E014F0 with the given argument and remembers it */

typedef struct {
    u8 pad0[0x58];
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    u8 c64[4];
    u8 c68[4];
    s16 used;
    u8 pad6E[0x12];
} Slot_c026_01E01170;

typedef struct {
    u8 pad0[0x140];
    Slot_c026_01E01170 slots[0x32];
    u8 pad[0x1A44 - 0x140 - 0x32 * 0x80];
    u8 rgba[4];
    u8 pad1A48[8];
    Slot_c026_01E01170 *last;
} Ctx_c026_01E01170;

static void func_01E01170_c026(Ctx_c026_01E01170 *ctx, s32 arg) {
    extern void c026_01E014F0(void);
    extern void func_001076F0();
    extern void func_00195108();
    Slot_c026_01E01170 *s = NULL;
    s16 i;

    for (i = 0; i < 0x32; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00195108(s, 0x80);
            ctx->slots[i].used = i + 1;
            i = 0x32;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_001076F0(s->c68, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c68[3] = ctx->rgba[3];
        s->cb = c026_01E014F0;
        s->arg = arg;
        ctx->last = s;
    }
}

/* shape c026:01E01270, 158 insns: c026 trail link spawner (c017:01E01400 family, 50 slots of 0x80 at ctx+0x140): both colours from the context with alpha 0, its vector, sizes as shorts, four heights (two at the context's height, two 18 above) capped by the context's ceiling, chained after the context's last piece and becomes it; draws with c026:01E01860 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
} Col_c026_01E01270;

typedef struct Ent_c026_01E01270 {
    Vec4f v;
    u8 pad10[4];
    f32 f14;
    u8 pad18[0xC];
    f32 f24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0xC];
    f32 f44;
    u8 pad48[8];
    struct Ent_c026_01E01270 *prev;
    struct Ent_c026_01E01270 *next;
    void (*cb)(void);
    s32 arg;
    u8 pad60[4];
    Col_c026_01E01270 col0;
    Col_c026_01E01270 col1;
    s16 used;
    s16 h6E;
    u8 pad70[2];
    s16 h72;
    s16 h74;
    s16 h76;
    s16 h78;
    s16 h7A;
    s16 h7C;
    u8 pad7E[2];
} Ent_c026_01E01270;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0x140 - 0x90];
    Ent_c026_01E01270 ent[50];
    u8 padEnd[0x1A44 - 0x140 - 50 * 0x80];
    u8 rgb[4];
    u8 pad1A48[8];
    Ent_c026_01E01270 *last;
    u8 pad1A54[4];
    f32 f1A58;
    f32 f1A5C;
    f32 f1A60;
    u8 pad1A64[0x1AB0 - 0x1A64];
    f32 f1AB0;
    u8 pad1AB4[2];
    s16 h1AB6;
    u8 pad1AB8[2];
    s16 h1ABA;
    u8 pad1ABC[2];
    s16 h1ABE;
    u8 pad1AC0[0x1B4E - 0x1AC0];
    s16 top;
} Ctx_c026_01E01270;

static void func_01E01270_c026(Ctx_c026_01E01270 *g, s32 arg) {
    extern void c026_01E01860(void);
    extern void func_00195108(void *, s32);
    extern void func_001076F0();
    s16 i;
    Ent_c026_01E01270 *e = NULL;
    Ent_c026_01E01270 *p;
    f32 h;
    f32 d;

    for (i = 0; i < 50; i++) {
        if (g->ent[i].used == 0) {
            e = &g->ent[i];
            func_00195108(e, 0x80);
            g->ent[i].used = i + 1;
            i = 50;
        }
    }
    if (e != NULL) {
        d = 18.0f;
        func_001076F0(&e->col0, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, g->rgb[0], g->rgb[1], g->rgb[2]);
        e->col1.a = 0;
        e->v = g->v;
        e->h74 = (s16)g->f1A58;
        e->h76 = (s16)g->f1A5C;
        e->h72 = (s16)g->f1A60;
        e->h6E = g->h1AB6;
        e->prev = g->last;
        e->h7A = g->h1ABE;
        if (e->prev == NULL) {
            h = g->f1A60;
            e->f14 = e->f24 = h;
            e->f44 = e->f34 = h + d;
        } else {
            h = g->f1A60;
            e->f14 = e->f24 = h;
            e->f44 = e->f34 = h + d;
        }
        if ((f32)g->top < e->f14) {
            e->f14 = g->top;
        }
        if ((f32)g->top < e->f24) {
            e->f24 = g->top;
        }
        if ((f32)g->top < e->f34) {
            e->f34 = g->top;
        }
        if ((f32)g->top < e->f44) {
            e->f44 = g->top;
        }
        e->h7C = (s16)g->f1AB0;
        e->prev = g->last;
        p = e->prev;
        if (p != NULL) {
            p->next = e;
        }
        e->h78 = g->h1ABA;
        e->cb = c026_01E01860;
        e->arg = arg;
        g->last = e;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E014F0_c026);

INCLUDE_ASM("asm/nonmatchings/mod/c026", func_01E01860_c026);
