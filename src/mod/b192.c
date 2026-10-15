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

static void func_01E00080_b192(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00260_b192(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

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

static void func_01E00330_b192(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b045:01E005A0, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E005A0;

static void func_01E00780_b192(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E005A0 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

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
    func_01E00330_b192((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E00960_b192(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

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
    func_01E00330_b192((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
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
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E00CE0_b192);

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E00FB0_b192);

/* shape b192:01E013B0, 134 insns: b019:01E01F60 with its sine table at ctx+0x375C */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x375C];
    u8 tab[1];
} Mgr_b192_01E013B0;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b192_01E013B0;

static s32 func_01E013B0_b192(Mgr_b192_01E013B0 *m, Fx_b192_01E013B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b192:01E015D0, 79 insns: a green-purple rising glow: frame 650 rising by 4, random sub-frame 0..6; alpha up by 0x50 to
   0xA0 for 2 frames, then down by 13 past frame 20, and also by 15 while the game state is below 10 */

typedef struct {
    u8 pad0[0x3610];
    s32 state;
} Game_b192_01E015D0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b192_01E015D0;

static s32 func_01E015D0_b192(Game_b192_01E015D0 *g, Obj_b192_01E015D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x28A;
        o->sub = func_0019A5C8() % 7;
        o->c1[3] = 0x10;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 0x14) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->state < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    func_001076F0(o->c0, 0x40, 0xF0, 0x40);
    func_001076F0(o->c1, 0x10, 0x80, 0x10);
    o->t++;
    o->h38 += 4;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E01710_b192);

/* shape b192:01E019C0, 40 insns: b120:01E01890 family: a yellow glow held at the model point, alpha 0x50 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b192_01E019C0;

typedef struct {
    u8 pad[0x3610];
    s32 state;
    u8 padS[0x34];
    s16 val;
} Game_b192_01E019C0;

static s32 func_01E019C0_b192(Game_b192_01E019C0 *g, Glow_b192_01E019C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 buf[4];

    func_001076F0(o->col, 0x50, 0x50, 0);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->val, buf);
    o->col[3] = 0x50;
    o->tick = 10;
    if (g->state == 0x32) {
        o->mode = 0;
    }
    return 0;
}

/* shape b192:01E01A60, 90 insns: a green drifting spark: frame 4 growing by 10..24, random turns, drift 15 by its side; alpha
   up by 42 to 0x80 for 3 frames, then down by 10 until it ends */

typedef struct {
    u8 pad0[6];
    s16 x;
    s16 dx;
    s16 grow;
    u8 padC[8];
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 side;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b192_01E01A60;

static s32 func_01E01A60_b192(void *arg0, Obj_b192_01E01A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x10, 0x40, 0x10);
    if (o->state == 1) {
        o->h38 = 4;
        o->rot2 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
        if (o->side == 0) {
            o->dx = 0xF;
        } else {
            o->dx = -0xF;
        }
        o->grow = func_0019A5C8() % 15 + 0xA;
        o->state = 2;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->x += o->dx;
    o->h38 += o->grow;
    o->t++;
    return 0;
}

/* shape b192:01E01BD0, 116 insns: a green drifting mote (b080:01E023D0 shape): frame 123, random turn and angle; alpha up by 32
   for 6 frames, then down by 10; sub-frame steps up to 7 every third frame; drifts 14 along its angle and bobs 4 by its turn */

typedef struct {
    u8 pad0[0x375C];
    u8 sin[1];
} Game_b192_01E01BD0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b192_01E01BD0;

static s32 func_01E01BD0_b192(Game_b192_01E01BD0 *g, Obj_b192_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0x7B;
        o->sub = 0;
        func_001076F0(o->c0, 0x20, 0x40, 0x20);
        o->turn = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 6) {
        o->c0[3] += 0x20;
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 14.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 14.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b192:01E01DA0, 85 insns: a green rising spark: frame 35, random sub-frame 0..3, angle, rise step 3..18, start height
   0..9 and full-alpha time 5..11; then fades by 10 until it ends; rises by its step each frame */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b192_01E01DA0;

static s32 func_01E01DA0_b192(void *arg0, Obj_b192_01E01DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x23;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x20, 0x80, 0x20);
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x375C];
    u8 tab[1];
} Mgr_b192_01E01F00;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b192_01E01F00;

static s32 func_01E01F00_b192(Mgr_b192_01E01F00 *m, Obj_b192_01E01F00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 130;
        o->h34 = 0;
        func_001076F0(o->col, 0x20, 0x40, 0x20);
        o->h30 = func_0019A5C8() % 360;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    if (o->h32 % 3 == 1) {
        if (o->h34 < 7) {
            o->h34++;
        }
    }
    o->h32++;
    o->x = o->x + 14.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 6.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 14.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b192:01E020D0, 95 insns: on start 0x38 = 260, variant 0..6, second alpha 8, green colours (darker before game
   step 0x365A reaches 0x4A); alpha grows by 0x10 (below 0x20) for 2 ticks, then fades by 12 once 0x38 passes 0x14 and
   by 15 while the game counter 0x3610 is below 10; 0x38 grows by 4 */

typedef struct {
    u8 pad0[0x3610];
    s32 count;
    u8 pad3614[0x46];
    s16 step;
} Game_b192_01E020D0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b192_01E020D0;

static s32 func_01E020D0_b192(Game_b192_01E020D0 *g, Fx_b192_01E020D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 260;
        o->f34 = func_0019A5C8() % 7;
        o->col2[3] = 8;
        if (g->step < 0x4A) {
            func_001076F0(o->col, 0x10, 0x60, 0x10);
            func_001076F0(o->col2, 8, 0x20, 8);
        } else {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 8, 0x40, 8);
        }
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x20) {
            o->col[3] += 0x10;
        }
    } else {
        if (o->f38 > 0x14) {
            if (o->col[3] > 0xD) {
                o->col[3] -= 12;
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
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* shape b192:01E02250, 74 insns: a dark spark (size 60, or 110 once the scene value reaches 74) at the scene angle and a random frame, growing 2 and turning 15 a tick: in by 64 up to 0x80 for 2 ticks, then out by 12 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[8];
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b192_01E02250;

typedef struct {
    u8 pad[0x3650];
    s16 ang;
    u8 pad3652[8];
    s16 val;
} Game_b192_01E02250;

static s32 func_01E02250_b192(Game_b192_01E02250 *g, Glow_b192_01E02250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->used == 1) {
        o->f38 = 60;
        if (g->val > 73) {
            o->f38 = 110;
        }
        o->ang = g->ang;
        o->kind = func_0019A5C8() % 7;
        o->col2[3] = 8;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->used = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->used = 0;
    }
    o->tick++;
    o->f38 += 2;
    o->ang += 15;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b270:01E04340, 47 insns, 1 copy: fade a level toward 0x40 or 0x80 by the scene timer */

typedef struct Ctx_b046_01E030F0 {
    u8 pad[0x3610];
    s32 timer;
} Ctx_b046_01E030F0;

typedef struct Obj_b046_01E030F0 {
    u8 pad0[0x30];
    s16 level;
    u8 pad32[4];
    s16 state;
} Obj_b046_01E030F0;

static s32 func_01E02380_b192(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (ctx->timer > 0x1E) {
        if (o->level > 0x30) {
            o->level -= 10;
        } else {
            o->level = 0x30;
        }
    } else {
        if (o->level < 0x80) {
            o->level += 10;
        } else {
            o->level = 0x80;
        }
    }
    if (ctx->timer == 1) {
        func_001F6D00((u8)o->level);
    } else {
        func_001F6D00((u8)o->level);
    }
    return 0;
}

static s32 func_01E02440_b192(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03C00_b192;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03C08_b192;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E02490_b192);

/* shape b192:01E02F00, 75 insns: take a free slot from the given pool (g->0xB8 slots of 0x40 bytes), clear it, colour
   both colours from the object colour 0x8C, attach it to the object, 0x30 from 0xB2, store the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 col[4];
    u8 col2[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b192_01E02F00;

typedef struct {
    u8 pad0[0x8C];
    u8 rgba[4];
    u8 pad90[0x22];
    s16 fB2;
    u8 padB4[4];
    s16 count;
} Obj_b192_01E02F00;

static s32 func_01E02F00_b192(Obj_b192_01E02F00 *g, s32 a1, s32 a2, Slot_b192_01E02F00 *pool) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b192_01E02F00 *s = NULL;
    s16 i;

    for (i = 0; i < g->count; i++) {
        if (pool[i].used == 0) {
            func_00195108(&pool[i], 0x40);
            pool[i].used = 1;
            s = &pool[i];
            i = g->count;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g, 0);
        s->f30 = g->fB2;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E03030_b192);

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E03310_b192);

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E03600_b192);

INCLUDE_ASM("asm/nonmatchings/mod/b192", func_01E03920_b192);
