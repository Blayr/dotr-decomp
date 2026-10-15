#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E00080_c024);

/* shape c024:01E00400, 59 insns: an animated sprite: frame steps every 3 ticks up to 7 (then dies), slides by its speed; in by 15 for frames 0-2, then out by 12 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E00400;

static s32 func_01E00400_c024(s32 arg0, Spr_c024_01E00400 *o) {
    if (o->h22 == 0) {
        if (o->frame < 7) {
            o->frame++;
        } else {
            o->alive = 0;
        }
        o->h22 = 2;
    } else {
        o->h22--;
    }
    o->h16 -= o->h1C;
    o->h26++;
    if (o->frame < 3) {
        if (o->alpha < 0x80) {
            o->alpha += 15;
        }
        if (o->alpha < 0x80) {
            o->alpha2 += 15;
        }
    } else {
        if (o->alpha > 0x10) {
            o->alpha -= 12;
        }
        if (o->alpha > 0x10) {
            o->alpha2 -= 12;
        } else {
            o->alive = 0;
        }
    }
    return 0;
}

/* shape c024:01E004F0, 59 insns: a rising sprite: frame 0 climbs by its speed (dies past 260), others by 8 (die past 180); in by 27 up to 0xC0, past 130 out by 32 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E004F0;

static s32 func_01E004F0_c024(s32 arg0, Spr_c024_01E004F0 *o) {
    if (o->frame == 0) {
        o->h16 += o->h1C;
        if (o->h16 > 0x104) {
            o->alive = 0;
        }
    } else {
        o->h16 += 8;
        if (o->h16 > 180) {
            o->alive = 0;
        }
    }
    if (o->frame == 0) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else if (o->h16 < 0x82) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else {
        if (o->alpha > 0x20) {
            o->alpha -= 0x20;
        } else {
            o->alive = 0;
        }
        if (o->alpha2 > 0x20) {
            o->alpha2 -= 0x20;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E005E0_c024);

/* shape c024:01E009B0, 74 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), 0x26/0x1C from the scene floats
   0x3B38/0x124, 0x28 from 0x3B5E, store arg */

typedef struct {
    u8 pad0[0x10];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[7];
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E009B0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E009B0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E009B0;

static void func_01E009B0_c024(Scene_c024_01E009B0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Slot_c024_01E009B0 *s = NULL;
    s32 i;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x34);
            g->slots[i].used = i + 1;
            s = &g->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->f1C = g->f124;
        s->arg = arg;
    }
}

/* shape c024:01E00AE0, 123 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), two random words 0x0/0x8
   (-0x4000..0x3FF0), 0x26/0x28 from the scene 0x3B38/0x3B5E, a random half-size flag 0x24 (0x1C = scene 0x124,
   halved when set), 0x20 random 0..19, store arg */

typedef struct {
    s32 w0;
    u8 pad4[4];
    s32 w8;
    u8 padC[4];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[2];
    s16 f20;
    u8 pad22[2];
    s8 half;
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E00AE0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E00AE0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E00AE0;

static void func_01E00AE0_c024(Scene_c024_01E00AE0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    Slot_c024_01E00AE0 *s = NULL;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            s = &g->slots[i];
            func_00195108(s, 0x34);
            g->slots[i].used = i + 1;
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        func_0019A5C8();
        s->w8 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->w0 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->half = func_0019A5C8() % 2;
        if (s->half == 0) {
            s->f1C = g->f124;
        } else {
            s->f1C = g->f124 / 2.0f;
        }
        s->f20 = func_0019A5C8() % 20;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E00CD0_c024);

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E01220_c024);

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E015D0_c024);

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E01CD0_c024);

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E02020_c024);
