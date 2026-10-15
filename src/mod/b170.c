#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b170(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
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

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b082_01E00920;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0x0E];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b082_01E00920;

static void func_01E00110_b170(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    i = 0;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
}

/* shape b170:01E00570, 123 insns: the module's script step: ticks the timer, follows two joints with the effect point (x from the
   first, z from it until frame 74, then sliding 6.5 one way or the other until 118, y 1.3 above the second until 220), keeps a
   copy until 170, and at frames 73/74 spawns the b170:01E00980 pair, the b170:01E00760 effect and the b170:01E00B00 effect */

typedef struct {
    f32 x, y, z, w;
} V4_b170_01E00570;

typedef struct {
    u8 pad0[0x250];
    V4_b170_01E00570 spawn;
    u8 pad260[0x74A0 - 0x260];
    V4_b170_01E00570 pt;
    V4_b170_01E00570 copy;
    u8 pad74C0[0x7654 - 0x74C0];
    s16 joint1;
    u8 pad7656[2];
    s16 joint0;
    u8 pad765A[0x28];
    s16 idx;
    u8 pad7684[2];
    s16 side;
    u8 pad7688[2];
    s16 t;
} Scene_b170_01E00570;

static void func_01E00570_b170(Scene_b170_01E00570 *s) {
    extern void b170_01E00760(void);
    extern void b170_01E00980(void);
    extern void b170_01E00B00(void);
    extern s32 b170_01E01090(Scene_b170_01E00570 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    V4_b170_01E00570 a;
    V4_b170_01E00570 b[2];

    s->t++;
    func_001F5620(func_001F53A0(), s->joint0, &a);
    func_001F5620(func_001F53A0(), s->joint1, b);
    s->pt.x = a.x;
    if (s->t < 0x4A) {
        s->pt.z = a.z;
    } else if (s->t < 0x76) {
        if (s->side != 0) {
            s->pt.z -= 6.5f;
        } else {
            s->pt.z += 6.5f;
        }
    }
    if (s->t < 0xAA) {
        s->copy = s->pt;
    }
    if (s->t < 0xDC) {
        s->pt.y = 1.3f + b[0].y;
    }
    if (s->t == 0x4A) {
        s->spawn = s->pt;
        b170_01E01090(s, b170_01E00B00, 0);
    }
    if (s->t == 0x49) {
        s->idx = 0;
        b170_01E01090(s, b170_01E00980, 0);
        s->idx = 1;
        b170_01E01090(s, b170_01E00980, 0);
    }
    if (s->t == 0x49) {
        s->idx = 0;
        s->idx = 1;
    }
    if (s->t == 0x49) {
        b170_01E01090(s, b170_01E00760, 0);
    }
}

/* shape b170:01E00760, 135 insns: purple trail (70 points at ctx+0x18B0) from the scene's point (ctx+0x74A0): on start fills it, length grows to 68; alpha 0xC0 until scene count 215, then down by 7 while the width shrinks 0.5; colour flips every tick; between ticks 16 and 79 the width grows 7 (13 after count 135); pushes the point for 50 ticks (b170:01E00080) */

typedef struct {
    u8 pad0[0x18B0];
    Vec4f tr[70];
    u8 pad1D10[0x74A0 - 0x1D10];
    Vec4f at;
    u8 pad74B0[0x768A - 0x74B0];
    s16 count;
} Ctx_b170_01E00760;

typedef struct {
    u8 pad0[6];
    s16 len;
    u8 pad8[0x40];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b170_01E00760;

static s32 func_01E00760_b170(Ctx_b170_01E00760 *g, Fx_b170_01E00760 *o) {
    extern void b170_01E00080(Vec4f *, s32, s32, Vec4f *);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Vec4f *p;

    if (o->mode == 1) {
        o->len = 8;
        o->col[3] = 0;
        p = g->tr;
        for (i = 0; i < 69; i++) {
            p[i].x = g->at.x;
            p[i].y = g->at.y;
            p[i].z = g->at.z;
        }
        func_001076F0(o->col2, 0x40, 0x10, 0x80);
        o->f48 = 20.0f;
        o->mode = 2;
    }
    if (o->len < 68) {
        o->len++;
    }
    if (g->count < 215) {
        o->col[3] = 0xC0;
    } else {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
        if (o->f48 > 0.0f) {
            o->f48 -= 0.5f;
        }
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0x80, 0x10, 0xFF);
    } else {
        func_001076F0(o->col, 0x40, 0x10, 0x80);
    }
    if (o->tick > 15 && o->tick < 80) {
        if (g->count < 135) {
            o->f48 += 7.0f;
        } else {
            o->f48 += 13.0f;
        }
    }
    if (o->tick < 50) {
        b170_01E00080(&g->tr[69], 70, 0, &g->at);
    }
    o->tick++;
    return 0;
}

/* shape b170:01E00980, 96 insns: on start f48 30, colour white, second colour (0x40, 0x10, 0x80) with alpha 0, random
   0x5A; the colour flickers purple; alpha grows by 0x10 (below 0xC0) while the game step 0x768A is below 0x6F, then
   fades by 12 and stops; f48 grows by 3 for 0x50 ticks; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x768A];
    s16 step;
} Game_b170_01E00980;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b170_01E00980;

static s32 func_01E00980_b170(Game_b170_01E00980 *g, Fx_b170_01E00980 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 30.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x10, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick % 2 == 0) {
        func_001076F0(o->col, 0x80, 0x10, 0xFF);
    } else {
        func_001076F0(o->col, 0x40, 0x10, 0x80);
    }
    if (g->step < 0x6F) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 0xD) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->tick < 0x50) {
        o->f48 += 3.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b170:01E00B00, 86 insns: on start f48 5, colour white, second colour (0x40, 0x10, 0x80) with alpha 0, random
   0x5A; alpha grows by 0x2A (below 0x80) for 0x50 ticks, then fades by 8 and stops; f48 then 90; the second colour
   flickers purple; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b170_01E00B00;

static s32 func_01E00B00_b170(s32 arg0, Fx_b170_01E00B00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x10, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x50) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f48 = 90.0f;
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0x40, 0x10, 0x80);
    } else {
        func_001076F0(o->col2, 0x60, 0x10, 0xA0);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b170", func_01E00C60_b170);

typedef struct {
    f32 x, y, z, w;
} Vec_b084_01E03610;

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    u8 pad52[6];
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Ent_b084_01E03610;

typedef struct {
    u8 pad0000[0x250];
    Vec_b084_01E03610 v250;
    u8 pad0260[0x40];
    Ent_b084_01E03610 ent[50];
    u8 pad1CC0[0x7624 - 0x2A0 - 50 * 0x70];
    u8 r, g, b, a;
    u8 pad7628[0x5A];
    s16 h7682;
} Obj_b084_01E03610;

static s32 func_01E01090_b170(Obj_b084_01E03610 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Ent_b084_01E03610 *e;
    s16 i;

    e = 0;
    for (i = 0; i < 50; i++) {
        if (o->ent[i].active == 0) {
            func_00195108(&o->ent[i], 0x70);
            o->ent[i].active = 1;
            e = &o->ent[i];
            i = 50;
        }
    }
    if (e != 0) {
    func_001076F0(e->c0, o->r, o->g, o->b);
    e->c0[3] = o->a;
    func_001076F0(e->c1, o->r, o->g, o->b);
    e->c1[3] = o->a;
    func_00106AB0(e, &o->v250, 0);
    e->x = o->v250.x;
    e->y = o->v250.y;
    e->z = o->v250.z;
    e->h50 = o->h7682;
    e->w40 = b;
    e->w44 = a;
    return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b170", func_01E011D0_b170);
