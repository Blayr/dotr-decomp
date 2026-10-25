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

static void func_01E00080_b069(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b068:01E00920, 355 insns (b008:01E004D0 with func_00205C40 called twice and separate x/y sizes): draws a row of small camera-facing sprites (one per entry, texture corner
   mode per entry via b008:01E00080), each shaken by a per-entry table offset that grows along the row;
   depth mode 0 (projected), 1 (far) or 2 (front). Calls the module's UV helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b068_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b068_01E00920 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b068_01E00920;

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
} Obj_b068_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    s16 sy;
    s16 sx;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b068_01E00920;

static void func_01E004D0_b069(Obj_b068_01E00920 *o, Spr_b068_01E00920 *s, s32 mode, s8 *tbl) {
    extern Rgbaq_b068_01E00920 func_00107740(void *);
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
    Pkt_b068_01E00920 pkt __attribute__((aligned(8)));
    s16 i;
    f32 size;
    Pkt_b068_01E00920 *p;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p = (Pkt_b068_01E00920 *)(s32)&pkt;
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
        func_01E00080_b069((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
        func_00108CE0(quad, s->sx, s->sy);
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

/* shape b069:01E00A60, 88 insns: scene colour (0x80, 0, 0, 0); count 0x39B6 up; at 0x2D run b069:01E00EF0 and
   b069:01E010B0 (0x39AA 0 then 0x5A) for both sides (0x39B0 0/1); from 0x5A, once the counter 0x3950 passes 0x43, place
   the scene at model point 0x399C and run b069:01E00BC0 twice; all through b069:01E01700 */

typedef struct {
    u8 pad0[0x2D0];
    f32 pos[3];
    u8 pad2DC[0x3950 - 0x2DC];
    s32 count2;
    u8 col[4];
    u8 pad3958[0x44];
    s16 point;
    u8 pad399E[0xC];
    s16 f39AA;
    u8 pad39AC[4];
    s16 side;
    u8 pad39B2[4];
    s16 count;
} Scene_b069_01E00A60;

static void func_01E00A60_b069(Scene_b069_01E00A60 *g) {
    extern void b069_01E00BC0(void);
    extern void b069_01E00EF0(void);
    extern void b069_01E010B0(void);
    extern void b069_01E01700(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 pt[4];

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count == 0x2D) {
        g->side = 0;
        b069_01E01700(g, b069_01E00EF0, 0);
        g->f39AA = 0;
        b069_01E01700(g, b069_01E010B0, 0);
        g->f39AA = 0x5A;
        b069_01E01700(g, b069_01E010B0, 0);
        g->side = 1;
        b069_01E01700(g, b069_01E00EF0, 0);
        g->f39AA = 0;
        b069_01E01700(g, b069_01E010B0, 0);
        g->f39AA = 0x5A;
        b069_01E01700(g, b069_01E010B0, 0);
    }
    if (g->count >= 0x5A) {
        if (g->count2 > 0x43) {
            func_001F5620(func_001F53A0(), g->point, pt);
            g->pos[0] = pt[0];
            g->pos[1] = pt[1];
            g->pos[2] = pt[2];
            g->side = 0;
            b069_01E01700(g, b069_01E00BC0, 0);
            b069_01E01700(g, b069_01E00BC0, 0);
        }
    }
}

/* shape b069:01E00BC0, 204 insns: b068:01E021B0 twin: grey 0x80 glow (kind 0, f38 70), size 10 x 50 growing by 4
   (hA by 4 more after tick 10 while under h8), fading in by 48 to 97 for 45..54 ticks, rising 1 every fifth tick; it
   drifts with the camera depth by 1/50 of the gap (1/40 after tick 10) */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
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
} Glow_b069_01E00BC0;

static s32 func_01E00BC0_b069(s32 arg0, Glow_b069_01E00BC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 70;
        o->kind = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 7;
        o->hC = 50;
        o->hA = 10;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 45;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 97) {
            o->col[3] += 48;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 10) {
        *(f32 *)(u32)&v[0].z /= 50.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 40.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 5 == 1) {
        o->h2--;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->hC += 4;
        o->hA += 4;
        if (o->tick > 10) {
            if (o->h8 > o->hA) {
                o->hA += 4;
            }
        }
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape b069:01E00EF0, 110 insns: flash that follows one of two scene objects, fading in and out on the scene timer */

typedef struct Fl_b069_01E00EF0 {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[0x18];
    u8 c28[4];
    u8 c2C[4];
    s16 which;
    s16 h32;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 h3A;
} Fl_b069_01E00EF0;

typedef struct Scn_b069_01E00EF0 {
    u8 pad0[0x20];
    Vec4f pts[0x397];
    u8 pad3990[8];
    s16 id0;
    s16 id1;
    u8 pad399C[0x1A];
    s16 timer;
} Scn_b069_01E00EF0;

static s32 func_01E00EF0_b069(Scn_b069_01E00EF0 *w, Fl_b069_01E00EF0 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    s16 t;
    Vec4f v[2];

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->c28, 0x80, 0x80, 0x80);
        func_001076F0(o->c2C, 0x60, 0x10, 0x10);
        o->hE = 0;
        o->h3A = func_0019A5C8() % 360;
        o->state = 2;
        o->c2C[3] = 0;
    }
    t = w->timer;
    if (t < 0x14A) {
        if (t < 0x11A || t > 0x134) {
            if (o->c28[3] < 0x80) {
                o->c28[3] += 0x40;
            }
        } else if (o->c28[3] > 0x30) {
            o->c28[3] -= 0x30;
        } else {
            o->c28[3] = 0;
        }
    } else if (o->c28[3] > 0x20) {
        o->c28[3] -= 0x14;
    } else {
        o->state = 0;
    }
    if (o->which == 0) {
        func_001F5620(func_001F53A0(), w->id0, &v[0]);
    } else {
        func_001F5620(func_001F53A0(), w->id1, &v[0]);
    }
    w->pts[o->which].x = v[0].x;
    w->pts[o->which].y = v[0].y;
    w->pts[o->which].z = v[0].z;
    o->hE++;
    o->h32++;
    return 0;
}

/* shape b069:01E010B0, 87 insns: a red column (b073:01E02BD0 shape): size 13 by 30 growing by 7, turning 10 */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b069_01E010B0;

static s32 func_01E010B0_b069(void *arg0, Obj_b069_01E010B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x80, 0x30, 0x30);
        func_001076F0(o->c1, 0x80, 0x30, 0x30);
        o->w = 0xD;
        o->h = 0x1E;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xE) {
            o->c1[3] -= 0xD;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->dir == 0) {
        o->h += 7;
    } else {
        o->h += 7;
    }
    o->t++;
    o->ang += 0xA;
    return 0;
}

/* shape b069:01E01210, 315 insns: b069's scene manager (b060:01E013C0 family): with a scene id (>= 0) it clears the
   scene, resets both camera blocks, keeps the id, sets the 381-frame countdown, zeroes three fades, takes seven model
   handles, loads textures 11..15, 2 and page-5 textures 0..1, and fills the 256-entry jitter table (0..99: -10..9,
   100..179: -4..7, 180..255: -3..2); otherwise it runs the module's step and every live node's update, then draws
   every live node by its callback with the matching texture and rect, counts down and returns 1 / 3 / 6 at frames
   170 / 355 / 181..344, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Node_b069_01E01210;

typedef struct {
    u8 pad0[0x80];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 camD8[0x238];
    f32 f310;
    f32 f314;
    f32 f318;
    u8 pad31C[4];
    s32 tex[16];
    u8 pad360[0x65C - 0x360];
    Node_b069_01E01210 node[150];
    u8 pad2BDC[0x3930 - 0x2BDC];
    s32 tex5[2];
    u8 pad3938[0x18];
    s32 count;
    u8 pad3954[8];
    s32 ot;
    u8 pad3960[0x38];
    s16 model[7];
    u8 pad39A6[0xE];
    s16 id;
    s16 timer;
    u8 pad39B8[2];
    s8 rnd[256];
    u8 pad3ABA[2];
    u8 cam[0x170];
} Scene_b069_01E01210;

static s32 func_01E01210_b069(s32 arg0, s32 id) {
    Scene_b069_01E01210 *g = (Scene_b069_01E01210 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00A60_b069();
    extern void func_01E004D0_b069();
    extern s32 func_01E00BC0_b069();
    extern s32 func_01E00EF0_b069();
    extern s32 func_01E010B0_b069();
    extern void b069_01E01830();
    extern void b069_01E01A70();
    s32 n;
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    u8 buf[0x90];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3C30);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 381;
        g->f310 = 0.0f;
        g->f314 = 0.0f;
        g->f318 = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x67, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x68, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x6A, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x26, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0xA, 0);
        g->model[6] = func_001F5560(func_001F53A0(), 0x3D, 0);
        for (i = 11; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 100; i < 180; i++) {
            g->rnd[i] = func_0019A5C8() % 12 - 4;
        }
        for (i = 0; i < 100; i++) {
            g->rnd[i] = func_0019A5C8() % 20 - 10;
        }
        for (i = 180; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 6 - 3;
        }
        return 0;
    }
    func_01E00A60_b069(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E00BC0_b069) {
                func_01E00BC0_b069(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00EF0_b069) {
                func_01E00EF0_b069(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E010B0_b069) {
                func_01E010B0_b069(g, &g->node[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E00BC0_b069) {
                g->tex88 = g->tex5[1];
                func_00106080(&r1, 0x14, g->node[i].h34, 0);
                g->rect = r1;
                g->hB8 = 2;
                g->hBE = func_0019A5C8() % 4;
                func_01E004D0_b069(g, &g->node[i], 0, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E00EF0_b069) {
                g->tex88 = g->tex5[0];
                func_00106080(&r2, 0x14, g->node[i].h34, 0);
                g->rect = r2;
                b069_01E01830(g, &g->node[i], buf, 0);
            }
            if (g->node[i].fn == func_01E010B0_b069) {
                g->tex88 = g->tex[15];
                func_00106080(&r3, 0x9A, 1, 0);
                g->rect = r3;
                b069_01E01A70(g, &g->node[i], buf, 0);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 170) {
        return 1;
    }
    if (g->timer == 355) {
        return 3;
    }
    if (g->timer > 180 && g->timer < 345) {
        return 6;
    }
    if (g->count <= 0) {
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

static s32 func_01E01700_b069(Pool_b008_01E01EB0 *o, s32 a, s32 b) {
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

/* shape b069:01E01830, 142 insns: b056:01E04980 family sprite quad into the given packet (rect at ctx+0x94, texture ctx+0x88, needs func_01E00080_b069 static in the file) at the module's point o->h30, scaled 0.1, size o->h38, far z */

typedef struct {
    f32 u, v;
} Uv_b069_01E01830;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b069_01E01830;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b069_01E01830 uv;
    u64 pad18;
    Xyz_b069_01E01830 v[4];
} Pk_b069_01E01830;

typedef struct {
    u8 pad0[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
} Ctx_b069_01E01830;

typedef struct {
    u8 pad0[0x28];
    u8 col[8];
    s16 point;
    u8 pad32[6];
    s16 size;
} Fx_b069_01E01830;

static void func_01E01830_b069(Ctx_b069_01E01830 *g, Fx_b069_01E01830 *o, Pk_b069_01E01830 *p) {
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Uv_b069_01E01830 uv __attribute__((aligned(8)));

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    *(s32 *)&p->uv.v = 0;
    p->v[0].fog = 0;
    p->v[1].fog = 0;
    p->v[2].fog = 0;
    p->v[3].fog = 0;
    func_00107740(&uv, o->col);
    p->uv = uv;
    func_01E00080_b069((Pk_b008_01E00080 *)p, &g->rect, 0);
    func_00208700(p, g->tex, 1);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = g->pts[o->point].x;
    pos.y = g->pts[o->point].y;
    pos.z = g->pts[o->point].z;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0(p, g->ot, 0);
    }
}

/* shape b069:01E01A70, 166 insns: draws 4 copies of a gradient quad (colour A on three corners, B on the last)
   at one of the object's points (fx->point), each turned by the effect's rotation; far z. The packet is passed
   in. Same family as b020:01E00E70. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b069_01E01A70;

typedef struct {
    Rgbaq_b069_01E01A70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b069_01E01A70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b069_01E01A70 v[4];
    u8 tail[0x20];
} Pkt_b069_01E01A70;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b069_01E01A70;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b069_01E01A70;

static void func_01E01A70_b069(Obj_b069_01E01A70 *o, Fx_b069_01E01A70 *fx, Pkt_b069_01E01A70 *p) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b069_01E01A70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = o->pts[fx->point].x;
    t.y = o->pts[fx->point].y;
    t.z = o->pts[fx->point].z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b069", func_01E01D80_b069);
