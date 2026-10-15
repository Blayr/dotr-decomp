#include "common.h"

/* shape c020:01E00080, 79 insns: spawn this tick's rain drops: 10/15/20/25 by the weather level (0 otherwise), each at a random x/z in -150..189 and height 170, through shape c020:01E006F0 with handler c020:01E001C0 once the scene state reaches 19 */

typedef struct {
    u8 pad0[0x80];
    f32 x, y, z;
    u8 pad8C[0x3190 - 0x8C];
    s32 state;
    u8 pad3194[0x320E - 0x3194];
    s16 level;
    u8 pad3210[2];
    s16 tick;
    u8 pad3214[6];
    s16 n;
} Ctx_c020_01E00080;

static void func_01E00080_c020(Ctx_c020_01E00080 *ctx) {
    extern void c020_01E001C0();
    extern void c020_01E006F0(Ctx_c020_01E00080 *, void *);
    s32 i;

    ctx->tick++;
    if (ctx->level == 0) {
        ctx->n = 10;
    } else if (ctx->level == 1) {
        ctx->n = 15;
    } else if (ctx->level == 2) {
        ctx->n = 20;
    } else if (ctx->level == 3) {
        ctx->n = 25;
    } else {
        ctx->n = 0;
    }
    for (i = 0; i < ctx->n; i++) {
        ctx->x = func_0019A5C8() % 340 - 150;
        ctx->z = func_0019A5C8() % 340 - 150;
        ctx->y = 170.0f;
        if (ctx->state > 18) {
            c020_01E006F0(ctx, c020_01E001C0);
        }
    }
}

/* shape c020:01E001C0, 80 insns: a falling piece: 0x26 grows by its speed (0x22) below 0x3C; the position moves by
   (-0x20, -0x22, -0x24); once below -30 it hands its position to the scene (0x80) once and, unless the scene flag
   0x320E is set, spawns a c020:01E00300 effect through c020:01E00990; then it ends (also below scene counter 2) */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E001C0;

typedef struct {
    V4_c020_01E001C0 pos;
    u8 pad10[0x10];
    s16 vx;
    s16 vy;
    s16 vz;
    s16 f26;
    u8 pad28[4];
    s16 mode;
    s16 done;
} Fx_c020_01E001C0;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E001C0 pos;
    u8 pad90[0x3190 - 0x90];
    s32 count;
    u8 pad3194[0x7A];
    s16 flag;
} Scene_c020_01E001C0;

static s32 func_01E001C0_c020(Scene_c020_01E001C0 *g, Fx_c020_01E001C0 *o) {
    extern void c020_01E00300(void);
    extern void c020_01E00990(void *, s32);
    if (o->f26 < 0x3C) {
        o->f26 += o->vy;
    }
    o->pos.y -= o->vy;
    o->pos.x -= o->vx;
    o->pos.z -= o->vz;
    if (o->pos.y < -30.0f) {
        if (o->done == 0) {
            g->pos = o->pos;
            if (g->flag == 0) {
                c020_01E00990(g, (s32)c020_01E00300);
            }
            o->done = 1;
        }
    }
    if (o->pos.y < -30.0f) {
        o->mode = 0;
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c020:01E00300, 48 insns: a rising wave: height 4 * sine of its angle (table at ctx+0x3250); the angle steps by 30 up to 180 while it grows; past 90 both levels drop by 28 down to 30, ending it */

typedef struct {
    u8 pad0[0x28];
    s16 h28;
    s16 h2A;
    s16 h2C;
    s16 ang;
    s16 h30;
    s16 h32;
    s16 h34;
} Wave_c020_01E00300;

static s32 func_01E00300_c020(u8 *ctx, Wave_c020_01E00300 *o) {
    extern f32 func_00108030(void *, s16, s32);

    o->h30 = 4.0f * func_00108030(ctx + 0x3250, o->ang, 0);
    if (o->ang < 180) {
        o->ang += 30;
        o->h34++;
        o->h32 += 2;
    }
    if (o->ang > 90) {
        if (o->h28 > 30) {
            o->h28 -= 28;
        }
        if (o->h2A > 30) {
            o->h2A -= 28;
        } else {
            o->h2C = 0;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E003C0_c020);

/* OVL_WARM */

/* shape c020:01E006F0, 168 insns: b582:01E04440's slot grab for 220 slots at +0x170 with no argument or result: the
   slot gets colour 0xFF/0, the scene point (0x80) and three x/z pairs scattered by -75..74, a size 24..33, a step
   2..5 (signed %4) and a speed 1..2 */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E006F0;

typedef struct {
    V4_c020_01E006F0 pos;
    u8 pad10[4];
    s16 x0;
    s16 x1;
    s16 x2;
    s16 z0;
    s16 z1;
    s16 z2;
    s16 step;
    s16 size;
    s16 speed;
    u8 pad26[2];
    s16 c28;
    s16 c2A;
    s16 used;
    u8 pad2E[0xA];
} Slot_c020_01E006F0;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E006F0 pt;
    u8 pad90[0xE0];
    Slot_c020_01E006F0 slot[220];
} Scene_c020_01E006F0;

static void func_01E006F0_c020(Scene_c020_01E006F0 *g) {
    extern void func_00195108(void *, s32);
    s16 i;
    Slot_c020_01E006F0 *s;

    s = NULL;
    for (i = 0; i < 220; i++) {
        if (g->slot[i].used == 0) {
            s = &g->slot[i];
            func_00195108(s, 0x38);
            g->slot[i].used = 1;
            i = 220;
        }
    }
    if (s != NULL) {
        s->c28 = 0xFF;
        s->c2A = 0;
        s->pos = g->pt;
        s->x0 = g->pt.x;
        s->z0 = g->pt.z;
        s->x1 = g->pt.x;
        s->z1 = g->pt.z;
        s->x2 = g->pt.x;
        s->z2 = g->pt.z;
        s->x0 += (s16)(func_0019A5C8() % 150 - 75);
        s->z0 += (s16)(func_0019A5C8() % 150 - 75);
        s->x1 += (s16)(func_0019A5C8() % 150 - 75);
        s->z1 += (s16)(func_0019A5C8() % 150 - 75);
        s->x2 += (s16)(func_0019A5C8() % 150 - 75);
        s->z2 += (s16)(func_0019A5C8() % 150 - 75);
        s->size = func_0019A5C8() % 10 + 24;
        s->step = func_0019A5C8() % 4 + 2;
        s->speed = func_0019A5C8() % 2 + 1;
    }
}

/* shape c020:01E00990, 60 insns: take a free slot (0xDC of 0x38 bytes at 0x170), clear it, set 0x28/0x2A = 0x60,
   copy the object's vector at 0x80, store arg and 0x22 = -10 */

typedef struct {
    f32 x, y, z, w;
} V4_c020_01E00990;

typedef struct {
    V4_c020_01E00990 pos;
    s32 arg;
    u8 pad14[0xE];
    s16 f22;
    u8 pad24[4];
    s16 f28;
    s16 f2A;
    s16 used;
    u8 pad2E[0xA];
} Slot_c020_01E00990;

typedef struct {
    u8 pad0[0x80];
    V4_c020_01E00990 pos;
    u8 pad90[0xE0];
    Slot_c020_01E00990 slots[0xDC];
} Obj_c020_01E00990;

static void func_01E00990_c020(Obj_c020_01E00990 *obj, s32 arg) {
    extern void func_00195108();
    Slot_c020_01E00990 *s = NULL;
    s16 i;

    for (i = 0; i < 0xDC; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x38);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xDC;
        }
    }
    if (s != NULL) {
        s->f28 = 0x60;
        s->f2A = 0x60;
        s->pos = obj->pos;
        s->arg = arg;
        s->f22 = -10;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00A80_c020);

INCLUDE_ASM("asm/nonmatchings/mod/c020", func_01E00E50_c020);
