#include "common.h"

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E00080_b232(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E00480_b232);

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E00710_b232);

/* shape b232:01E00970, 81 insns: a white-grey rising flash (b749:01E028A0 shape, starting x turn by the game's side, no y turn): f48 200 with f4C 58 below, rising by
   f34 = 950 / 10 a frame with f4C 400 below; full alpha for 15 frames, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x4554];
    s16 side;
} Game_b232_01E00970;

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b232_01E00970;

static s32 func_01E00970_b232(Game_b232_01E00970 *g, Obj_b232_01E00970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->f34 = 950.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        if (g->side != 0) {
            o->rot0 = -0x1800;
        } else {
            o->rot0 = 0x1800;
        }
    }
    if (o->t < 0xF) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    o->t++;
    return 0;
}

/* shape b232:01E00AC0, 70 insns: a white/grey beam from 200 growing 95 a tick (tail 400 behind): alpha 0x80 for 13 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b232_01E00AC0;

static s32 func_01E00AC0_b232(s32 arg0, Obj_b232_01E00AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->f34 = 950.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 13) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    o->t++;
    return 0;
}

/* shape b232:01E00BE0, 89 insns: a white shard (3 x 13, random 3..4 at +8, angle from the scene, tipped +-0x1000 by the scene side flag): alpha at least 0x80 for 8 ticks, then out by 11 and ends; grows 11..20 a tick */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b232_01E00BE0;

typedef struct {
    u8 pad[0x4544];
    s16 ang;
    u8 pad4546[0xE];
    s16 side;
} Game_b232_01E00BE0;

static s32 func_01E00BE0_b232(Game_b232_01E00BE0 *g, Obj_b232_01E00BE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 3.0f;
        o->f4C = 13.0f;
        o->kind = 0;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 2 + 3;
        o->h5C = g->ang;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        if (g->side != 0) {
            o->w20 = -0x1000;
        } else {
            o->w20 = 0x1000;
        }
    }
    if (o->t < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->f48 += 11.0f + func_0019A5C8() % 10;
    }
    o->t++;
    return 0;
}

/* shape b232:01E00D50, 81 insns: a white streak: f48 3 growing by 11..25 a frame, f4C 26, random width 3 or 4, height from the
   game; full alpha for 25 frames, then down by 14 until it ends */

typedef struct {
    u8 pad0[0x4544];
    s16 h;
} Game_b232_01E00D50;

typedef struct {
    u8 pad0[8];
    s16 w;
    u8 padA[0x3E];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[2];
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b232_01E00D50;

static s32 func_01E00D50_b232(Game_b232_01E00D50 *g, Obj_b232_01E00D50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 3.0f;
        o->f4C = 26.0f;
        o->h56 = 0;
        o->state = 2;
        o->w = func_0019A5C8() % 2 + 3;
        o->h = g->h;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
    }
    if (o->t < 0x19) {
        if (o->c0[3] < 0x80) {
            o->c0[3] = 0x80;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->f48 += 11.0f + func_0019A5C8() % 15;
    }
    o->t++;
    return 0;
}

/* shape b232:01E00EA0, 56 insns: volume fade (layout at 0x50): for 0x97 frames down 10 to 0x30, then while the game
   state at 0x44B0 is below 0x1E up 10 to 0x80; state 3 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0x44B0];
    s32 state;
} Game_b232_01E00EA0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b232_01E00EA0;

static s32 func_01E00EA0_b232(Game_b232_01E00EA0 *g, Fade_b232_01E00EA0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0x97) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E00F80_b232);

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E01130_b232);

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E01370_b232);

/* shape b232:01E01A50, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b232_01E01A50 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b232_01E01A50;

typedef struct Obj_b232_01E01A50 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b232_01E01A50 slots[0x96];
    u8 padB[0x74];
    u8 rgba[4];
    u8 padC[0x98];
    s16 fB2B0;
} Obj_b232_01E01A50;

static s32 func_01E01A50_b232(Obj_b232_01E01A50 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b232_01E01A50 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b232", func_01E01B90_b232);

/* shape b232:01E01EE0, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x44C8, ot at
   0x44C4), texture from func_001F5380, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b232:01E01130 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b232_01E01EE0;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b232_01E01EE0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b232_01E01EE0 slots[0x96];
    u8 pad4440[0x84];
    s32 ot;
    Pkt_b232_01E01EE0 *pk;
} Scene_b232_01E01EE0;

static void func_01E01EE0_b232(Scene_b232_01E01EE0 *g) {
    extern void b232_01E01130(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F5380(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b232_01E01EE0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F5380(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b232_01E01130) {
                b232_01E01130(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
