#include "common.h"

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

static void func_01E00080_b260(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
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

/* shape b260:01E004E0, 242 insns: a beam trail of 69 points at w+0x18B0: set up once from the source point (0x74A0),
   size 20, colour (0x80, 0x10, 0x10); alpha held at 0xC0 until the world clock (0x768A) reaches 215, then fades by 7
   and the size shrinks by 0.5; blinks red/dark red by tick parity; ticks 16..79 grow the size by 7 (13 from clock 135);
   the head point (0x74B0) sits on joint 0x7654 and the first o->frame points run toward joint 0x7664 in 30ths, the
   reach growing for 50 ticks; the source point follows the first trail point */

typedef struct {
    u8 pad0[0x18B0];
    Vec4f trail[69];
    u8 pad1D00[0x74A0 - 0x1D00];
    Vec4f src;
    Vec4f head;
    u8 pad74C0[0x7654 - 0x74C0];
    s16 ja;
    u8 pad7656[0xE];
    s16 jb;
    u8 pad7666[0x24];
    s16 clock;
} World_b260_01E004E0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    u8 pad8[0x40];
    f32 size;
    u8 pad4C[4];
    s16 reach;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Beam_b260_01E004E0;

static s32 func_01E004E0_b260(World_b260_01E004E0 *w, Beam_b260_01E004E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[12];
    f32 *q;
    Vec4f *p;
    f32 k;
    f32 t;
    s16 i;
    s16 j;

    if (o->state == 1) {
        o->frame = 8;
        o->c0[3] = 0;
        p = w->trail;
        for (i = 0; i < 69; i++) {
            p[i].x = w->src.x;
            p[i].y = w->src.y;
            p[i].z = w->src.z;
        }
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
        o->reach = 0;
        o->size = 20.0f;
        o->state = 2;
    }
    if (o->frame < 68) {
        o->frame++;
    }
    if (w->clock < 215) {
        o->c0[3] = 0xC0;
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->size > 0.0f) {
            o->size -= 0.5f;
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0x10, 0x10);
    } else {
        func_001076F0(o->c0, 0xE0, 0x10, 0x10);
    }
    if (o->t > 15 && o->t < 80) {
        if (w->clock < 135) {
            o->size += 7.0f;
        } else {
            o->size += 13.0f;
        }
    }
    if (o->t < 50) {
        o->reach++;
    }
    k = o->reach;
    func_001F5620(func_001F53A0(), w->ja, v);
    func_001F5620(func_001F5380(), w->jb, q = (f32 *)(u32)&v[4]);
    w->head = *(Vec4f *)v;
    q[0] = (q[0] - v[0]) / 30.0f;
    v[6] = (v[6] - v[2]) / 30.0f;
    v[5] = (v[5] - v[1]) / 30.0f;
    for (j = 0; j < 69; j++) {
        w->trail[j].x = 0.0f;
        if (j < o->frame) {
            t = k - j;
            if (t < 0.0f) {
                t = 0.0f;
            }
            w->trail[j].z = v[2] + v[6] * t;
            w->trail[j].x = v[0] + q[0] * t;
            w->trail[j].y = v[1] + v[5] * t;
        } else {
            w->trail[j].x = v[0];
            w->trail[j].z = v[2];
            w->trail[j].y = v[1];
        }
    }
    w->src = w->trail[0];
    o->t++;
    return 0;
}

/* shape b260:01E008B0, 96 insns: a red flicker flash: size 110 growing by 3 until frame 180, random angle; colour flickers red
   by frame parity; alpha up by 16 while the scene timer is under 240, then down by 12 until it ends; spins a quarter turn */

typedef struct {
    u8 pad0[0x768A];
    s16 timer;
} Game_b260_01E008B0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b260_01E008B0;

static s32 func_01E008B0_b260(Game_b260_01E008B0 *g, Obj_b260_01E008B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 110.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0x10, 0x10);
    } else {
        func_001076F0(o->c0, 0xD0, 0x10, 0x10);
    }
    if (g->timer < 0xF0) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x10;
        }
    } else if (o->c0[3] > 0xD) {
        o->c0[3] -= 0xC;
    } else {
        o->state = 0;
    }
    if (o->t < 0xB4) {
        o->size += 3.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b260:01E00A30, 99 insns: on start f48 5 then 90, colour white, second colour (0x40, 0x10, 0x80) with alpha 0,
   random 0x5A; alpha grows by 0x2A (below 0x80) for 0x78 ticks, then fades by 8 and stops; f48 grows by 3 up to 300;
   the second colour flickers red; the rotation at 0x20 advances 0x4000 */

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
} Fx_b260_01E00A30;

static s32 func_01E00A30_b260(s32 arg0, Fx_b260_01E00A30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->f48 = 90.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x10, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x78) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->f48 < 300.0f) {
        o->f48 += 3.0f;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
    } else {
        func_001076F0(o->col2, 0xA0, 0x10, 0x10);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b260:01E00BC0, 325 insns, 1 copy: b260's scene manager: with a scene id (>= 0) it clears the scene, builds both
   sine tables, a 260-tick countdown, three model joints and a camera unit, the side the camera looks from, scale 0.1,
   two random tables and a 250 distance; otherwise steps the clock (spawns b260:01E00A30 at 74, b260:01E004E0 and
   b260:01E008B0 at 73), runs every live effect's step and draws three kinds; returns 1 at tick 85, 4 at 255, 2 at 240,
   6 between 96 and 234, 8 when the countdown runs out */

typedef struct Fx_b260_01E00BC0 {
    u8 pad0[0x44];
    s32 (*fn)();
    u8 pad48[8];
    s16 kind;
    u8 pad52[6];
    s16 active;
    u8 pad5A[0x16];
} Fx_b260_01E00BC0;

typedef struct Game_b260_01E00BC0 {
    u8 pad0[0x10];
    f32 scale[3];
    u8 pad1C[0x64];
    s32 ot;
    u8 pad84[0x32];
    s16 hB6;
    u8 padB8[0x20];
    f32 trig[0x72];
    Fx_b260_01E00BC0 fx[50];
    u8 pad1880[0x30];
    u8 b18B0[0x74A0 - 0x18B0];
    Vec4f pA;
    Vec4f pB;
    u8 pad74C0[0x7620 - 0x74C0];
    s32 count;
    u8 pad7624[8];
    s32 ot2;
    u8 pad7630[0x10];
    f32 dist;
    u8 pad7644[0x10];
    s16 j0;
    s16 j1;
    s16 j2;
    u8 pad765A[0xA];
    s16 cam;
    u8 pad7666[0x1C];
    s16 h7682;
    u8 pad7684[2];
    s16 side;
    s16 id;
    s16 clock;
    s8 tblA[256];
    s8 tblB[256];
    f32 trig2[1];
} Game_b260_01E00BC0;

static s32 func_01E010E0_b260();

static s32 func_01E00BC0_b260(Game_b260_01E00BC0 *g0, s32 id) {
    Game_b260_01E00BC0 *g = (Game_b260_01E00BC0 *)(u32)g0;
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void b260_01E01220();
    Vec4f v;
    s32 r[4];
    s16 i;
    s32 (*fn)();
    s16 n;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108((s32)g, 0x7A00);
        func_00107C10(g->trig2);
        func_00107C10(g->trig);
        g->id = id;
        g->count = 260;
        g->j0 = func_001F5560(func_001F53A0(), 2, 1);
        g->j1 = func_001F5560(func_001F53A0(), 0x1E, 0);
        g->j2 = func_001F5560(func_001F53A0(), 1, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        func_001F6160(func_001F53A0(), r);
        g->side = (s32)(r[1] / 180.0f);
        g->scale[0] = 0.1f;
        g->scale[1] = 0.1f;
        g->scale[2] = 0.1f;
        for (i = 0; i < 256; i++) {
            g->tblA[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 256; i++) {
            g->tblB[i] = func_0019A5C8() % 40 - 20;
        }
        g->dist = 250.0f;
        return 0;
    }
    g->clock++;
    if (g->clock == 74) {
        func_01E010E0_b260(g, func_01E00A30_b260, 0);
    }
    if (g->clock == 73) {
        g->h7682 = 0;
        func_01E010E0_b260(g, func_01E004E0_b260, 0);
    }
    if (g->clock == 73) {
        g->h7682 = 0;
        func_01E010E0_b260(g, func_01E008B0_b260, 0);
        g->h7682 = 1;
    }
    g->hB6 = g->clock;
    for (i = 0; i < 50; i++) {
        if (g->fx[i].active) {
            fn = g->fx[i].fn;
            if (fn) {
                fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 50; i++) {
        if (g->fx[i].active) {
            n++;
            if (g->fx[i].fn == func_01E00A30_b260) {
                v = g->pA;
                func_01E00080_b260((void *)g, (void *)&g->fx[i], 0x11, v);
            }
        }
    }
    for (i = 0; i < 50; i++) {
        if (g->fx[i].active) {
            n++;
            if (g->fx[i].fn == func_01E004E0_b260) {
                b260_01E01220(g, &g->fx[i], g->b18B0, 1);
            }
            if (g->fx[i].fn == func_01E008B0_b260) {
                if (g->fx[i].kind == 0) {
                    v = g->pA;
                } else if (g->fx[i].kind == 1) {
                    v = g->pB;
                }
                v = g->pB;
                if (g->clock < 92) {
                    func_01E00080_b260((void *)g, (void *)&g->fx[i], 0x10, v);
                } else {
                    func_01E00080_b260((void *)g, (void *)&g->fx[i], 0x11, v);
                }
            }
        }
    }
    if (g->count) {
        g->count--;
    }
    if (g->clock == 85) {
        return 1;
    }
    if (g->clock == 255) {
        return 4;
    }
    if (g->clock == 240) {
        return 2;
    }
    if (g->clock > 95 && g->clock < 235) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

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

static s32 func_01E010E0_b260(Obj_b084_01E03610 *o, s32 a, s32 b) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b260", func_01E01220_b260);
