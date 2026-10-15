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

static void func_01E00080_b266(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E004D0_b266(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b266((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E00800_b266);

/* shape b266:01E01060, 87 insns: on start 0x38 = 8, random rotation (0x18 -0x2000..0x1FFF, 0x14), variant 0..6; alpha grows
   by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0x14 and by 15 while the game counter at
   0x2EA0 is below 10; colour (0x80, 0x40, 0); 0x38 grows by 4 */

typedef struct {
    u8 pad0[0x2EA0];
    s32 count;
} Game_b266_01E01060;

typedef struct {
    u8 pad0[0x14];
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b266_01E01060;

static s32 func_01E01060_b266(Game_b266_01E01060 *g, Fx_b266_01E01060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->rot18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x14) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b266:01E011C0, 113 insns: swipe that turns to face the camera side, fades in, widens and fades out */

typedef struct Sw_b266_01E011C0 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[0xC];
    u8 c28[4];
    u8 c2C[4];
    s16 w;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
} Sw_b266_01E011C0;

typedef struct Scn_b266_01E011C0 {
    u8 pad0[0x2EA0];
    s32 count;
} Scn_b266_01E011C0;

static s32 func_01E011C0_b266(Scn_b266_01E011C0 *sc, Sw_b266_01E011C0 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F6160();
    s32 v[4];
    s16 side;

    func_001076F0(o->c28, 0x18, 0x18, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), v);
        side = (s32)((f32)v[1] / 180.0f);
        if (side != 0) {
            o->f10 = -0x4000;
        } else {
            o->f10 = -0xC000;
        }
        o->f14 = 0;
        if (side != 0) {
            if (o->w == 0) {
                o->f18 = 0x1800;
            } else {
                o->f18 = -0x1800;
            }
        } else if (o->w == 0) {
            o->f18 = -0x1800;
        } else {
            o->f18 = 0x1800;
        }
        o->h34 = 0;
        o->w = 0x5A;
        o->state = 2;
        o->c28[3] = 0;
    }
    if (o->age < 2) {
        if (o->c28[3] < 0x80) {
            o->c28[3] += 0x40;
        }
    } else if (o->c28[3] > 10) {
        o->c28[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 50;
    o->age++;
    if (o->w < 0xA0) {
        o->w += 8;
    }
    if (sc->count < 15) {
        if (o->c28[3] > 14) {
            o->c28[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b266:01E01390, 59 insns: an orange glow that drops toward the scene joint's height (step = func_001A22C0 of the gap): in by 25 up to 0x80 for 5 ticks */

typedef struct {
    s16 h0;
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b266_01E01390;

typedef struct {
    u8 pad[0x2EEA];
    s16 joint;
} Game_b266_01E01390;

static s32 func_01E01390_b266(Game_b266_01E01390 *g, Glow_b266_01E01390 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f pos;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x50, 0x20, 0);
        func_001F5620(func_001F53A0(), g->joint, &pos);
        o->hE = func_001A22C0(pos.y - o->h2);
        o->f38 = 50;
        o->ang = 0;
        o->kind = 2;
        o->h30 = 1;
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x19;
        }
    }
    o->tick++;
    o->hA -= o->hE;
    return 0;
}

/* shape b266:01E01480, 100 insns: a grey camera-facing slash: frame 3..10, turned by the camera side and by its side flag
   (+-0x2800 tilt), random sub-frame 0..6; alpha up by 20 to 0x50 for 4 frames, then down by 13 until it ends */

typedef struct {
    u8 pad0[6];
    s16 side0;
    u8 pad8[8];
    s32 rot0;
    u8 pad14[4];
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 side;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b266_01E01480;

static s32 func_01E01480_b266(void *arg0, Obj_b266_01E01480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s16 func_001A22C0(f32);
    s32 ang[4];
    s32 flip;

    func_001F6160(func_001F53A0(), ang);
    flip = func_001A22C0(ang[1] / 180.0f);
    func_001076F0(o->c0, 0xA0, 0xA0, 0xA0);
    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (flip != 0) {
            o->rot0 = 0;
        } else {
            o->rot0 = 0x8000;
        }
        if (flip != 0) {
            if (o->side == 0) {
                o->rot2 = -0x2800;
            } else {
                o->rot2 = 0x2800;
            }
        } else if (o->side == 0) {
            o->rot2 = 0x2800;
        } else {
            o->rot2 = -0x2800;
        }
        o->side0 = o->side;
        o->sub = func_0019A5C8() % 7;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x14;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 0xD;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b266:01E01610, 101 insns: an orange ember (size 13, frame 2) at two random angles drifting 9 a tick on all three axes (sine table ctx+0x3004): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[2];
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
} Glow_b266_01E01610;

typedef struct {
    u8 pad[0x3004];
    u8 sin[1];
} Game_b266_01E01610;

static s32 func_01E01610_b266(Game_b266_01E01610 *g, Glow_b266_01E01610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 13;
        o->kind = 2;
        func_001076F0(o->col, 0x60, 0x40, 8);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 9.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 9.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 9.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b207:01E030D0, 79 insns, 2 copies: a streak flash: size and turn by kind (0..3) once, two colours; full alpha for 5
   frames, then fades out (b003:01E01780 family) */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b207_01E030D0;

static s32 func_01E017B0_b266(void *arg0, Obj_b207_01E030D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->state == 1) {
        if ((k = o->kind) == 0) {
            o->h38 = 0x19;
            o->h34 = 6;
        } else if (k == 1) {
            o->h38 = 6;
            o->h34 = 0x19;
        } else if (k == 2) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = 0x2D;
        } else if (k == 3) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = -0x2D;
        }
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x80, 0x40, 0);
        o->state = 2;
    }
    if (o->t < 5) {
        o->c0[3] = 0x40;
        o->c1[3] = 0;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 col[3];
    u8 alpha;
    u8 pad2C[4];
    s16 pos;
    s16 age;
    s16 kind;
    s16 state;
    s16 mode;
    s16 angle;
} Spark_b018_01E02950;

static s32 func_01E018F0_b266(s32 unused, Spark_b018_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 16) {
        o->alpha -= 10;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b266:01E01A60, 119 insns: b582:01E03470 family scene light at ctx+0x2D00 (orange 4/2/0, height 70) whose range swells by 42 to 128 while it rises and shrinks by 16 to 0 while it falls; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b266_01E01A60;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x174];
    s32 state;
} Light_b266_01E01A60;

typedef struct {
    u8 pad[0x2D00];
    Light_b266_01E01A60 l;
} Game_b266_01E01A60;

static s32 func_01E01A60_b266(Game_b266_01E01A60 *g, Obj_b266_01E01A60 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 0.0f;
        g->l.r = 4.0f;
        g->l.g = 2.0f;
        g->l.b = 0.0f;
        g->l.w20 = 0;
        g->l.h = 70.0f;
        g->l.level = 0.0f;
        g->l.x = o->x;
        g->l.y = o->y;
        g->l.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        } else {
            o->phase = 1;
        }
        if (g->l.w0 < 128.0f) {
            g->l.w0 += 42.0f;
        } else {
            g->l.w0 = 128.0f;
        }
    } else {
        if (g->l.level > 0.1f) {
            g->l.level -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (g->l.w0 > 16.0f) {
            g->l.w0 -= 16.0f;
        } else {
            g->l.w0 = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b266:01E01C40, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2EA0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2EA0];
    s32 state;
} Game_b266_01E01C40;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b266_01E01C40;

static s32 func_01E01C40_b266(Game_b266_01E01C40 *g, Fade_b266_01E01C40 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

static s32 func_01E01D00_b266(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03580_b266;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03588_b266;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E01D50_b266);

/* shape b266:01E02520, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2EFA and the two arguments; returns 1 if a
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
} Slot_b266_01E02520;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x4A4];
    Slot_b266_01E02520 s[150];
    u8 pad2CF4[0x1B0];
    u8 r, g, b, a;
    u8 pad2EA8[0x52];
    s16 v;
} Pool_b266_01E02520;

static s32 func_01E02520_b266(Pool_b266_01E02520 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b266_01E02520 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E02640_b266);

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E029F0_b266);

/* shape b266:01E02D50, 111 insns: draws a small sprite (b089:01E03780 shape): unlit, it sets up the colour and texture page; lit,
   it builds a matrix at a tenth scale from its turn, at its position plus a tenth of its drift, and draws a square of its size
   with the lower texture corners at u 0.5 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b266_01E02D50;

typedef struct {
    u8 pad0[0x37C];
    s32 tex;
} Scene_b266_01E02D50;

static void func_01E02D50_b266(Scene_b266_01E02D50 *g, Fx_b266_01E02D50 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;
    f32 f;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9b, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    scale.z = 0.1f;
    scale.y = 0.1f;
    scale.x = 0.1f;
    func_00205C40((s32)rot);
    f = o->dx;
    f /= 10.0f;
    pos.x = o->x;
    pos.x += f;
    f = o->dy;
    f /= 10.0f;
    pos.y = o->y;
    pos.y += f;
    f = o->dz;
    f /= 10.0f;
    pos.z = o->z;
    pos.z += f;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[2].x = 0.5f;
    quad[3].x = 0.5f;
    func_00108F90(quad, p, m, v);
}

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E02F10_b266);

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E03130_b266);

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E03340_b266);
