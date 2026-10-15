#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

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
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b136(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00260_b136(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E002E0_b136);

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E008C0_b136);

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E00AE0_b136);

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E00CA0_b136);

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E014B0_b136);

/* shape b136:01E01670, 67 insns: a tumbling spark at three random turns, growing 1 and turning 0x400 a tick: in by 64 for 2 ticks, then orange, out by 10 and ends */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b136_01E01670;

static s32 func_01E01670_b136(s32 arg0, Glow_b136_01E01670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x8F, 0x1F, 0x10);
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->w14 += 0x400;
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01780, 48 insns: an orange flash placed at (0x4000, 0x400, 0): fades in by 0x26 for 5 ticks, out by 10 and ends; grows 1 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b136_01E01780;

static s32 func_01E01780_b136(s32 arg0, Glow_b136_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 5;
        func_001076F0(o->col, 0x8F, 0x1F, 0xF0);
        o->w10 = 0x4000;
        o->w14 = 0x400;
        o->w18 = 0;
        o->mode = 2;
    }
    if (o->tick < 5) {
        o->col[3] += 0x26;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01840, 67 insns: a tumbling spark at three random turns, growing 1 and turning 0x400 a tick: in by 64 for 2 ticks, then dark, out by 14 and ends */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b136_01E01840;

static s32 func_01E01840_b136(s32 arg0, Glow_b136_01E01840 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x2F, 0x1F, 0x20);
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->w14 += 0x400;
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01950, 31 insns: func_001F7170(6, 2, &a, &b, 0) with copies of the module's floats at 0x01E02600 and
   0x01E02608; when the game value at 0x365C is 94 the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b136_01E01950;

typedef struct {
    u8 pad0[0x365C];
    s16 v;
} Game_b136_01E01950;

typedef struct {
    u8 pad0[0x36];
    s16 f36;
} Fx_b136_01E01950;

extern F_b136_01E01950 D_01E02600_b136;
extern F_b136_01E01950 D_01E02608_b136;

static s32 func_01E01950_b136(Game_b136_01E01950 *g, Fx_b136_01E01950 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b136_01E01950 a;
    F_b136_01E01950 b;

    a = D_01E02600_b136;
    b = D_01E02608_b136;
    func_001F7170(6, 2, &a, &b, 0);
    if (g->v == 94) {
        o->f36 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E019D0_b136);

/* shape b136:01E01F00, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3658 and the two arguments; returns 1 if a
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
} Slot_b136_01E01F00;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b136_01E01F00 s[180];
    u8 pad2F84[0x680];
    u8 r, g, b, a;
    u8 pad3608[0x50];
    s16 v;
} Pool_b136_01E01F00;

static s32 func_01E01F00_b136(Pool_b136_01E01F00 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b136_01E01F00 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

/* shape b136:01E02020, 41 insns: mode 0 sets up the drawing state: a 0x96 matrix from the anim's angle at 0x34,
   colour, texture group 4 cell 15 */

typedef struct {
    u8 pad0[0x28];
    u8 col[0xC];
    s16 h34;
} Anim_b136_01E02020;

static void func_01E02020_b136(s32 arg0, Anim_b136_01E02020 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    f32 rm[4];

    func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x96, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 1);
        func_00208700(p, func_00202BF0(4, 15), 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E020D0_b136);

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E02400_b136);
