#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00080_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00220_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00620_b053);

/* shape b053:01E00870, 32 insns: b120:01E01EA0 family: fades in by 0x40 to 0x80, then out by 9 and ends; colour (0xF0, 0x80, 0x40) */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Glow_b053_01E00870;

static s32 func_01E00870_b053(s32 arg0, Glow_b053_01E00870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->f30 == 0) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        } else {
            o->f30 = 1;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001076F0(o->col, 0xF0, 0x80, 0x40);
    return 0;
}

/* shape b053:01E008F0, 63 insns: a red sparkle: first tick picks three random turns, then grows by 3 a tick at size 10 and ends past 70 */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 state;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b053_01E008F0;

static s32 func_01E008F0_b053(s32 arg0, Glow_b053_01E008F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 0) {
        o->h2 = 0;
        o->col[3] = 0x30;
        o->col2[3] = 0xFF;
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->state = 1;
    } else if (o->state == 1) {
        o->h6 = 10;
        o->h2 += 3;
        if (o->h2 > 70) {
            o->mode = 0;
        }
    }
    func_001076F0(o->col, 0xFF, 0x3F, 0x3F);
    func_001076F0(o->col2, 0xFF, 0x3F, 0x3F);
    return 0;
}

typedef struct {
    u8 pad0000[0x3B64];
    u8 tab[1];
} Mgr_b053_01E009F0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 x, y, z;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b053_01E009F0;

static s32 func_01E009F0_b053(Mgr_b053_01E009F0 *m, Obj_b053_01E009F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        func_0019A5C8();
        func_001076F0(o->col, 0xFF, 0, 0xFF);
        o->h3A = func_0019A5C8() % 360;
        o->h30 = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 10 + 10;
        o->h6 = func_0019A5C8() % 15 + 1;
        o->h38 = 6;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    o->x = o->x + o->hE * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + o->hE * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + o->hE * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b053:01E00BD0, 76 insns: a dark ring (b130:01E012D0 shape): set up once at alpha 0x60 with a random turn on all three
   axes and a random growth step 2..6; grows by that step up to 50, fades by 9 after 10, turns 12 a frame */

typedef struct {
    u8 pad0[0xE];
    s16 step;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[8];
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b053_01E00BD0;

static s32 func_01E00BD0_b053(void *arg0, Obj_b053_01E00BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x10, 0x10, 8);
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->step = func_0019A5C8() % 5 + 2;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x60;
    }
    if (o->size > 0xA) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    if (o->size < 0x32) {
        o->size += o->step;
    }
    o->ang += 0xC;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00D00_b053);

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b053:01E00F20, 113 insns: glow pinned to a scene object, rising slowly; its size follows a sine ramp */

typedef struct Fl_b053_01E00F20 {
    s16 x, y, z;
    u8 pad6[4];
    s16 ang;
    u8 padC[0x1C];
    u8 c28[4];
    u8 c2C[4];
    s16 rise;
    s16 age;
    s16 h34;
    s16 state;
    s16 size;
    s16 h3A;
} Fl_b053_01E00F20;

typedef struct Scn_b053_01E00F20 {
    u8 pad0[0x3B48];
    s16 id;
    u8 pad3B4A[0x1A];
    u8 table[0x10];
} Scn_b053_01E00F20;

static s32 func_01E00F20_b053(Scn_b053_01E00F20 *w, Fl_b053_01E00F20 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Vec4f v;

    func_001076F0(o->c28, 0x28, 0x10, 0x28);
    if (o->state == 1) {
        o->size = 10;
        o->h3A = func_0019A5C8() % 360;
        o->h34 = 0;
        o->rise = 0;
        o->ang = 20;
        o->state = 2;
    }
    func_001F5620(func_001F53A0(), w->id, &v);
    o->x = (s32)v.x;
    o->y = (s32)(v.y - 8.0f + (f32)o->rise);
    o->z = (s32)v.z;
    if (o->age % 2 == 1) {
        o->rise++;
    }
    o->size = (s32)(100.0f * func_00108030((s32)w->table, o->ang, 0));
    if (o->ang < 0x5A) {
        o->ang += 5;
    }
    if (o->age < 8) {
        if (o->c28[3] < 0x30) {
            o->c28[3] += 6;
        }
    } else if (o->ang >= 0x46) {
        if (o->c28[3] > 5) {
            o->c28[3] -= 4;
        } else {
            o->state = 0;
        }
    }
    o->age++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E010F0_b053);

/* shape b053:01E01730, 87 insns: takes the first free of 15 trail segments (0x7C bytes), copies the context's point and two frames,
   chains it after the context's last segment (height from the context, its lower edge 18 below), and makes it the new last */

typedef struct Seg_b053_01E01730 {
    u8 pad0[4];
    f32 top;
    u8 pad8[0xC];
    f32 bottom;
    u8 pad18[0x18];
    Vec4f pos;
    u8 pad40[0x10];
    struct Seg_b053_01E01730 *prev;
    struct Seg_b053_01E01730 *next;
    u8 pad58[0x10];
    s16 used;
    u8 pad6A[4];
    s16 f6E;
    u8 pad70[2];
    s16 f72;
    s16 f74;
    s16 f76;
    u8 pad78[4];
} Seg_b053_01E01730;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x80];
    Seg_b053_01E01730 segs[0xF];
    u8 pad[0x3B10 - 0x110 - 0xF * 0x7C];
    Seg_b053_01E01730 *last;
    u8 pad3B14[8];
    f32 height;
    u8 pad3B20[0x34];
    s16 f3B54;
    u8 pad3B56[4];
    s16 f3B5A;
} Ctx_b053_01E01730;

static s32 func_01E01730_b053(Ctx_b053_01E01730 *ctx) {
    extern void func_00195108();
    Seg_b053_01E01730 *s = NULL;
    Seg_b053_01E01730 *p;
    s16 i;
    f32 h;

    for (i = 0; i < 0xF; i++) {
        if (ctx->segs[i].used == 0) {
            func_00195108(&ctx->segs[i], 0x7C);
            ctx->segs[i].used = 1;
            s = &ctx->segs[i];
            i = 0xF;
        }
    }
    if (s != NULL) {
        s->pos = ctx->pos;
        s->f72 = ctx->f3B54;
        s->prev = ctx->last;
        s->f6E = ctx->f3B5A;
        if (s->prev == NULL) {
            h = ctx->height;
            s->top = h;
            s->bottom = h - 18.0f;
        } else {
            h = ctx->height;
            s->top = h;
            s->bottom = h - 18.0f;
        }
        s->prev = ctx->last;
        p = s->prev;
        if (p != NULL) {
            p->next = s;
        }
        s->f74 = 1;
        s->f76 = 1;
        ctx->last = s;
        return 1;
    }
    return 0;
}

/* shape b053:01E01890, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3B5A and 0x3B54 and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b053_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x7D4];
    Slot_b053_01E01890 s[200];
    u8 pad3A54[0xB0];
    u8 r, g, b, a;
    u8 pad3B08[0x4C];
    s16 w;
    u8 pad3B56[0x4];
    s16 v;
} Pool_b053_01E01890;

static s32 func_01E01890_b053(Pool_b053_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b053_01E01890 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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
        s->w = o->w;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E019C0_b053);

/* shape b053:01E01E30, 107 insns: b053:01E022F0 with a 0.1 scale vector (texture 0x9B, page at ctx+0x10C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b053_01E01E30;

static void func_01E01E30_b053(u8 *ctx, Obj_b053_01E01E30 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    sc.z = sc.y = sc.x = 0.1f;
    func_00108EF0(m, &sc, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E01FE0_b053);

/* shape b053:01E022F0, 103 insns: one textured square of an object (like b058:01E00080); mode 0 only sets up the
   packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn via
   func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b053_01E022F0;

static void func_01E022F0_b053(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E02490_b053);
