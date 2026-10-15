#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00080_c056);

/* shape c056:01E00240, 70 insns: sound voice k (k + 0xF5 above 10) while the game counter at 0x4478 is below 10:
   if it plays, set its volume byte to 0x80 and (unless bit k of 0x447C) fade it to 0.15; if it is ready, aim it at
   the game's 16-byte slot 0x40E0[k], clear p->4 and attach p, and (unless bit k) start it (0x18) */

typedef struct {
    u8 pad0[0x40E0];
    u8 slot[0x39][16];
    u8 pad4470[8];
    s32 count;
    u32 mask;
} Game_c056_01E00240;

typedef struct {
    u8 pad0[4];
    s32 f4;
} P_c056_01E00240;

static s32 func_01E00240_c056(Game_c056_01E00240 *g, P_c056_01E00240 *p, s32 k) {
    extern s32 func_001F5EC0(s32);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    extern void func_00107370(s32, s32, f32);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_00107650(s32, s32);
    u8 v[4];
    s32 ch;

    ch = k;
    if (k > 10) {
        ch = k + 0xF5;
    }
    if (g->count < 10) {
        if (func_001F5EC0(ch) != 0) {
            func_001F6490(ch, v);
            v[3] = 0x80;
            func_001F63E0(ch, v);
            if (!((g->mask >> k) & 1)) {
                func_00107370(ch, 0, 0.15f);
            }
        }
        if (func_001F5AF0(ch) != 0) {
            func_001F5C40(ch, g->slot[k]);
            p->f4 = 0;
            func_001F5B70(ch, p);
            if (!((g->mask >> k) & 1)) {
                func_00107650(ch, 0x18);
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00360_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00800_c056);

/* shape c056:01E00C10, 15 insns: spawn an effect entity from the context's pool (kind 0x46) and store arg in it */

typedef struct Ent_c056_01E00C10 {
    u8 pad0[0x9C];
    s32 arg;
} Ent_c056_01E00C10;

typedef struct Ctx_c056_01E00C10 {
    u8 pad0[0xC60];
    u8 pool[1];
} Ctx_c056_01E00C10;

static void func_01E00C10_c056(Ctx_c056_01E00C10 *ctx, s32 arg) {
    Ent_c056_01E00C10 *e = (Ent_c056_01E00C10 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        e->arg = arg;
    }
}

/* shape c056:01E00C50, 54 insns, 1 copy: spawn an effect entity, random angle % 360; its callback is
   c056:01E02560 */

typedef struct Col_c056_01E00C50 {
    u8 r, g, b, a;
} Col_c056_01E00C50;

typedef struct Ent_c056_01E00C50 {
    u8 pad0[0x64];
    f32 f64;
    u8 pad68[0x30];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E00C50 col0;
    Col_c056_01E00C50 col1;
    u8 padB4[4];
    s16 fB8;
    u8 padBA[2];
    s16 fBC;
    s16 fBE;
} Ent_c056_01E00C50;

typedef struct Ctx_c056_01E00C50 {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    u8 pad44BA[2];
    s16 f44BC;
} Ctx_c056_01E00C50;

extern void c056_01E02560(void);

static void func_01E00C50_c056(Ctx_c056_01E00C50 *ctx, s32 arg) {
    extern void func_001076F0();
    Ent_c056_01E00C50 *e = (Ent_c056_01E00C50 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col0.a = 0;
        func_001076F0(&e->col1, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        e->col1.a = 0;
        e->f64 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBC = ctx->f44BC;
        e->fBE = func_0019A5C8() % 360;
        e->cb = c056_01E02560;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00D30_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E00F30_c056);

/* shape c056:01E010E0, 53 insns: spawns a green glow (c056:01E00C50 family): colours 0x20/0x38/0x24 with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02E10 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E010E0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E010E0 col0;
    Col_c056_01E010E0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E010E0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E010E0;

static void func_01E010E0_c056(Ctx_c056_01E010E0 *ctx, s32 arg) {
    extern void c056_01E02E10(void);
    extern void func_001076F0();
    Ent_c056_01E010E0 *e = (Ent_c056_01E010E0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x20, 0x38, 0x24);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x20, 0x38, 0x24);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02E10;
        e->arg = arg;
    }
}

/* shape c056:01E011C0, 53 insns: spawns a dark glow (c056:01E00C50 family): colours 0x18 grey with the context's
   alpha, the context's vector at 0x80 copied in, placed at the context's position; draws with c056:01E02BE0 */

typedef struct {
    u8 r, g, b, a;
} Col_c056_01E011C0;

typedef struct {
    u8 pad0[0x60];
    Vec4f v;
    u8 pad70[0x28];
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    Col_c056_01E011C0 col0;
    Col_c056_01E011C0 col1;
    u8 padB4[6];
    s16 fBA;
} Ent_c056_01E011C0;

typedef struct {
    u8 pad0[0x80];
    Vec4f v;
    u8 pad90[0xC60 - 0x90];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[0x449C - 0x4484];
    f32 pos[3];
    u8 pad44A8[0x12];
    s16 f44BA;
} Ctx_c056_01E011C0;

static void func_01E011C0_c056(Ctx_c056_01E011C0 *ctx, s32 arg) {
    extern void c056_01E02BE0(void);
    extern void func_001076F0();
    Ent_c056_01E011C0 *e = (Ent_c056_01E011C0 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);

    if (e != NULL) {
        func_001076F0(&e->col0, 0x18, 0x18, 0x18);
        e->col0.a = ctx->rgba[3];
        func_001076F0(&e->col1, 0x18, 0x18, 0x18);
        e->col1.a = ctx->rgba[3];
        e->v = ctx->v;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->fBA = ctx->f44BA;
        e->cb = c056_01E02BE0;
        e->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E012A0_c056);

/* shape c056:01E01490, 66 insns: spawns a grey glow (c056:01E00C50 family): colours 0x20 with the context's alpha, height
   from the context, placed at the context's position; links to the context's parent effect (copying its vector and
   pointing it back), draws with c056:01E02790, frame 7 */

typedef struct Ent_c056_01E01490 {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x58];
    Vec4f v;
    u8 pad80[0x10];
    struct Ent_c056_01E01490 *parent;
    struct Ent_c056_01E01490 *child;
    void (*cb)(void);
    s32 arg;
    u8 padA0[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 padB4[4];
    s16 fB8;
    s16 fBA;
    u8 padBC[2];
    s16 fBE;
} Ent_c056_01E01490;

typedef struct {
    u8 pad0[0x84];
    f32 f84;
    u8 pad88[0xC60 - 0x88];
    u8 pool[0x4480 - 0xC60];
    u8 rgba[4];
    u8 pad4484[8];
    Ent_c056_01E01490 *parent;
    u8 pad4490[0xC];
    f32 pos[3];
    u8 pad44A8[0x10];
    s16 f44B8;
    s16 f44BA;
} Ctx_c056_01E01490;

static void func_01E01490_c056(Ctx_c056_01E01490 *ctx, s32 arg) {
    extern void c056_01E02790(void);
    extern void func_001076F0();
    Ent_c056_01E01490 *e = (Ent_c056_01E01490 *)func_00106A00((s32)ctx, (s32)ctx->pool, 0x46, 0);
    Ent_c056_01E01490 *p;

    if (e != NULL) {
        func_001076F0(e->col0, 0x20, 0x20, 0x20);
        e->col0[3] = ctx->rgba[3];
        func_001076F0(e->col1, 0x20, 0x20, 0x20);
        e->col1[3] = ctx->rgba[3];
        e->fBA = ctx->f44BA;
        e->f14 = e->f4 = ctx->f84;
        func_00107E40(ctx->pos[0], ctx->pos[1], ctx->pos[2], e);
        e->parent = ctx->parent;
        p = e->parent;
        if (p != NULL) {
            e->v = p->v;
            p->child = e;
        }
        e->cb = c056_01E02790;
        e->arg = arg;
        e->fB8 = ctx->f44B8;
        e->fBE = 7;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E015A0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02020_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E022F0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02560_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02790_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02BE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E02E10_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03090_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03AE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03DA0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E03FE0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E044B0_c056);

/* shape c056:01E04780, 42 insns: a sprite that fades in by 16 to 0x30 while the scene value is under 16, out by 15 while the counter is under 21, holds size 190 and ends when the counter is under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 pad447C[0x46];
    s16 val;
} Ctx_c056_01E04780;

typedef struct {
    u8 pad0[0xA0];
    f32 size;
    s16 state;
    u8 padA6[0xD];
    u8 alpha;
    u8 padB4[6];
    u8 bA[1];
} Obj_c056_01E04780;

static s32 func_01E04780_c056(Ctx_c056_01E04780 *ctx, Obj_c056_01E04780 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 16) {
        if (o->alpha < 0x21) {
            o->alpha += 0x10;
        }
    }
    if (ctx->count < 21) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
    }
    o->size = 190.0f;
    if (ctx->count < 11) {
        o->state = 0;
    }
    return 0;
}

/* shape c056:01E04830, 52 insns: c056:01E04780 two-alpha twin: in by 32/16 while the scene value is under 16, out by 15 while the counter is under 21, ends under 11 */

typedef struct {
    u8 pad0[0x4478];
    s32 count;
    u8 padC[0x46];
    s16 val;
} Ctx_c056_01E04830;

typedef struct {
    u8 pad0[0xA4];
    s16 state;
    u8 padA6[0x9];
    u8 alpha;
    u8 padB0[0x3];
    u8 alpha2;
    u8 padB4[0x6];
    u8 bA[1];
} Obj_c056_01E04830;

static s32 func_01E04830_c056(Ctx_c056_01E04830 *ctx, Obj_c056_01E04830 *o) {
    extern void func_00106D80(s32, void *);

    func_00106D80(5, o->bA);
    if (ctx->val < 0x10) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x20;
        }
        if (o->alpha2 < 0x21) {
            o->alpha2 += 0x10;
        }
    }
    if (ctx->count < 0x15) {
        if (o->alpha > 0x10) {
            o->alpha -= 15;
        }
        if (o->alpha2 > 0x10) {
            o->alpha2 -= 15;
        }
    }
    if (ctx->count < 0xb) {
        o->state = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04900_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04CF0_c056);

INCLUDE_ASM("asm/nonmatchings/mod/c056", func_01E04FE0_c056);
