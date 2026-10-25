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

static void func_01E00080_b086(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b008:01E004D0, 351 insns, 12 copies: draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b008_01E004D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b008_01E004D0 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b008_01E004D0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b008_01E004D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b008_01E004D0;

static void func_01E004D0_b086(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b008_01E004D0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b008_01E004D0 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b008_01E004D0 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b008_01E004D0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    pkt.c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_01E00080_b086((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        size = s->size;
        func_00108CE0(quad, size, size);
        func_00109100(quad, rot, 1, o->xD8);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180] / 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b086:01E00A50, 81 insns: sets the scene colour to red 0x80 and counts its timer; from frame 45 while the game state is
   past 70, puts the effect point at the model joint and spawns two b086:01E00BA0 then two b086:01E00F70 effects (sides 0, 1) */

typedef struct {
    u8 pad0[0x2D0];
    f32 x, y, z;
    u8 pad2DC[0x3950 - 0x2DC];
    s32 state;
    u8 r, g, b, a;
    u8 pad3958[0x40];
    s16 joint;
    u8 pad399A[0x16];
    s16 side;
    u8 pad39B2[4];
    s16 t;
} Scene_b086_01E00A50;

static void func_01E00A50_b086(Scene_b086_01E00A50 *s) {
    extern void b086_01E00BA0(void);
    extern void b086_01E00F70(void);
    extern s32 b086_01E01730(Scene_b086_01E00A50 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;

    s->r = 0x80;
    s->g = 0;
    s->b = 0;
    s->a = 0;
    s->t++;
    if (s->t >= 0x2D && s->state > 0x46) {
        func_001F5620(func_001F53A0(), s->joint, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        s->side = 0;
        b086_01E01730(s, b086_01E00BA0, 0);
        s->side = 1;
        b086_01E01730(s, b086_01E00BA0, 0);
    }
    if (s->t >= 0x2D && s->state > 0x46) {
        func_001F5620(func_001F53A0(), s->joint, &a);
        s->x = a.x;
        s->y = a.y;
        s->z = a.z;
        s->side = 0;
        b086_01E01730(s, b086_01E00F70, 0);
        s->side = 1;
        b086_01E01730(s, b086_01E00F70, 0);
    }
}

/* shape b086:01E00BA0, 242 insns: b008:01E00C30's puff (speed 5..9) that starts on joint 0x3998 of the scene, 3 above
   it */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b086_01E00BA0;

typedef struct {
    u8 pad0[0x3998];
    s16 joint;
} Scene_b086_01E00BA0;

static s32 func_01E00BA0_b086(Scene_b086_01E00BA0 *g, Fx_b086_01E00BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    extern void func_001F5620(s32, s32, void *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 30;
        o->f34 = 0;
        if (o->f30 == 0) {
            func_001076F0(o->col, 0x40, 0x40, 0x40);
        } else {
            func_001076F0(o->col, 0x50, 0x10, 0x10);
        }
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 45;
        func_001F5620(func_001F53A0(), g->joint, v);
        o->x = v[0];
        o->y = v[1] + 3.0f;
        o->z = v[2];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x7F) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    if (o->tick <= 39) {
        v[2] /= 40.0f;
        o->z = o->z + v[2];
        if (o->y > v[5] - 15.0f) {
            o->y--;
        }
    } else {
        v[2] /= 50.0f;
        o->z = o->z + v[2];
        o->f30 += o->speed * 5;
        o->y += 2;
    }
    if (o->tick % 2 == 1) {
        o->x += o->hC;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38 += 3;
    }
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b086:01E00F70, 197 insns: b008:01E00FB0's puff that starts on the joint g+0x3998 (3 higher) and sinks 1 a
   tick while above the camera height less 15 */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b086_01E00F70;

typedef struct {
    u8 pad0[0x3998];
    s16 j;
} Game_b086_01E00F70;

static s32 func_01E00F70_b086(Game_b086_01E00F70 *g, Fx_b086_01E00F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f38 = 40;
        o->f34 = 0;
        if (o->f30 == 0) {
            func_001076F0(o->col, 0x30, 0x30, 0x30);
        } else {
            func_001076F0(o->col, 0x40, 0x10, 0x10);
        }
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 4 + 2;
        func_001F5620(func_001F53A0(), g->j, v);
        o->x = v[0];
        o->y = 3.0f + v[1];
        o->z = v[2];
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x40) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    v[2] = v[2] - v[6];
    v[2] /= 63.0f;
    o->z = o->z + v[2];
    if (o->y > v[5] - 15.0f) {
        o->y--;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->f38++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b086:01E01290, 295 insns: the module's main: on start clears the 0x3D30 context, two cameras, 300 ticks, seven
   model joints, textures 11..15, 2 and 5:0, then two 256-byte jitter tables (the fourth pass rewrites the first, the
   second table at +0x100 stays as cleared); each tick runs the 150 slots' two movers, then draws each with its own
   rotation (mode 3 or 2, a random 0..3 frame, table 1 or 2); ends 1 at step 90, 3 at 275, 6 in 101..269, 8 when the
   timer runs out */

typedef struct {
    u8 pad00[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 rot;
    s16 used;
    u8 pad38[8];
} Slot_b086_01E01290;

typedef struct {
    u8 pad0000[0x80];
    s32 ot2;
    u8 pad0084[4];
    s32 tex88;
    u8 pad008C[8];
    Vec4f m94;
    u8 pad00A4[0x14];
    s16 mode;
    u8 pad00BA[4];
    s16 frame;
    u8 pad00C0[0x18];
    u8 camD8[0x238];
    s32 w310;
    s32 w314;
    s32 w318;
    u8 pad031C[4];
    s32 tex[16];
    u8 pad0360[0x2FC];
    Slot_b086_01E01290 slot[150];
} Ctx_b086_01E01290;

typedef struct {
    u8 pad0000[0x3930];
    s32 tex5[8];
    s32 timer;
    u8 pad3954[8];
    s32 ot;
    u8 pad3960[0x38];
    s16 joint[7];
    u8 pad39A6[0xE];
    s16 code;
    s16 step;
    u8 pad39B8[2];
    s8 jit[256];
    s8 jit2[256];
    u8 pad3BBA[2];
    u8 cam3BBC[1];
} Hi_b086_01E01290;

static s32 func_01E01290_b086(s32 arg0, s32 code) {
    Ctx_b086_01E01290 *g = (Ctx_b086_01E01290 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, s32);
    extern void b086_01E00A50();
    extern s32 b086_01E00BA0();
    extern s32 b086_01E00F70();
    extern void b086_01E004D0();
    Hi_b086_01E01290 *h = (Hi_b086_01E01290 *)g;
    Vec4f m1;
    Vec4f m2;
    s32 n;
    s32 i;

    n = 0;
    h->ot = func_00207500();
    g->ot2 = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3D30);
        func_00107C10(h->cam3BBC);
        func_00107C10(g->camD8);
        h->code = code;
        h->timer = 300;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        h->joint[0] = func_001F5560(func_001F53A0(), 0x41, 1);
        h->joint[1] = func_001F5560(func_001F53A0(), 0x69, 0);
        h->joint[2] = func_001F5560(func_001F53A0(), 0x1B, 0);
        h->joint[3] = func_001F5560(func_001F53A0(), 0x26, 0);
        h->joint[4] = func_001F5560(func_001F53A0(), 0xF, 0);
        h->joint[5] = func_001F5560(func_001F53A0(), 0xA, 0);
        h->joint[6] = func_001F5560(func_001F53A0(), 0x3D, 0);
        for (i = 11; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 1; i++) {
            h->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 100; i < 180; i++) {
            h->jit[i] = func_0019A5C8() % 20 - 10;
        }
        for (i = 0; i < 100; i++) {
            h->jit[i] = func_0019A5C8() % 80 - 40;
        }
        for (i = 180; i < 256; i++) {
            h->jit[i] = func_0019A5C8() % 2 + 1;
        }
        for (i = 0; i < 256; i++) {
            h->jit[i] = func_0019A5C8() % 20 - 10;
        }
        return 0;
    }
    b086_01E00A50(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == b086_01E00BA0) {
                b086_01E00BA0(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b086_01E00F70) {
                b086_01E00F70(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == b086_01E00BA0) {
                g->tex88 = h->tex5[0];
                func_00106080(&m1, 0x14, g->slot[i].rot, 0);
                g->m94 = m1;
                g->mode = 3;
                g->frame = func_0019A5C8() % 4;
                b086_01E004D0(g, &g->slot[i], 0, h->jit);
                g->mode = 0;
            }
            if (g->slot[i].fn == b086_01E00F70) {
                g->tex88 = h->tex5[0];
                func_00106080(&m2, 0x14, g->slot[i].rot, 0);
                g->m94 = m2;
                g->mode = 2;
                g->frame = func_0019A5C8() % 4;
                b086_01E004D0(g, &g->slot[i], 1, h->jit2);
                g->mode = 0;
            }
        }
    }
    if (h->timer != 0) {
        h->timer--;
    }
    if (h->step == 90) {
        return 1;
    }
    if (h->step == 275) {
        return 3;
    }
    if (h->step > 100 && h->step < 270) {
        return 6;
    }
    if (h->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b008:01E01EB0, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x39B0 and 0x39AA and the two arguments; returns 1 if a
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
} Slot_b008_01E01EB0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x38C];
    Slot_b008_01E01EB0 s[150];
    u8 pad2BDC[0xD78];
    u8 r, g, b, a;
    u8 pad3958[0x52];
    s16 w;
    u8 pad39AC[0x4];
    s16 v;
} Pool_b008_01E01EB0;

static s32 func_01E01730_b086(Pool_b008_01E01EB0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b008_01E01EB0 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
