#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b286(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E004D0_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E009B0_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E00B40_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E00C60_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E00F90_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01130_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E013F0_b286);

/* shape b194:01E01AE0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E02500_b286;
extern f32 D_01E02508_b286;

static s32 func_01E014D0_b286(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02500_b286;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02508_b286;
    func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01520_b286);

/* shape b286:01E01990, 72 insns: twin of b046:01E03E20: take the first free slot of the 420-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x6ADE and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b286_01E01990;

typedef struct {
    u8 pad[0x80];
    u8 m[0xA0];
    Slot_b286_01E01990 s[420];
    u8 pad6A20[0x64];
    u8 r, g, b, a;
    u8 pad6A88[0x56];
    s16 v;
} Pool_b286_01E01990;

static s32 func_01E01990_b286(Pool_b286_01E01990 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b286_01E01990 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 420; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 420;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01AB0_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01D40_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E01FC0_b286);

INCLUDE_ASM("asm/nonmatchings/mod/b286", func_01E022A0_b286);
