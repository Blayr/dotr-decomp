#include "common.h"

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00080_c062(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E004D0_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E00730_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E00E30_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E01050_c062);

typedef struct {
    f32 x, y, z, w;
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E01870_c062(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
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
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
    }
}

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;
typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;
typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;

/* shape b707:01E00C70, 362 insns, 2 copies (b445:01E00D10 twin, kind 0 also turned): draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b707_01E00C70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b707_01E00C70 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b707_01E00C70;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b707_01E00C70;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f pos;
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 w50;
    u8 pad52[8];
    s16 axis;
    u8 pad5C[4];
    u8 col[4];
} Spr_b707_01E00C70;

static void func_01E01BD0_c062(Obj_b707_01E00C70 *o, Spr_b707_01E00C70 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b707_01E00C70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f e;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b707_01E00C70 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b707_01E00C70 *p;
    u8 mode;

    p = (Pkt_b707_01E00C70 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00080_c062((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    p2.x = s->pos.x;
    p2.y = s->pos.y;
    p2.z = s->pos.z;
    if (o->kind == 0) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00080_c062((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
            func_00108CE0(quad, s->size, s->size);
            func_00109100(quad, rot, 1, o->xD8);
            func_00109100(quad, rot, 0, o->xD8);
        } else if (o->kind == 1) {
            func_00108CE0(quad, s->size, s->size);
        }
        for (c = 0; c < 3; c++) {
            if (c == 0) {
                off = 0;
            }
            if (c == 1) {
                off = 100;
            }
            if (c == 2) {
                off = 180;
            }
            f = (tbl + i)[s->off + off];
            f /= 20.0f;
            u = f * (f32)(s->w50 + (i >> 1));
            if (c == 0) {
                e.x = u;
            }
            if (c == 1) {
                e.y = u;
            }
            if (c == 2) {
                e.z = u;
            }
        }
        if (o->kind == 0) {
            func_00108950(&e, ax, 0, o->xD8);
        }
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (o->kind == 1) {
            quad[0].y = 0.0f;
            quad[1].y = 0.0f;
            quad[0].x = s->size;
            quad[1].x = -s->size;
            quad[0].z = 0.0f;
            quad[1].z = 0.0f;
        }
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E02180_c062(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
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
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
        }
    }
}

/* shape c062:01E024F0, 88 insns: a fading tinted glow: alpha up by 8 to 0x80 for 15 frames (orange on the first), then down by
   5 from frame 50 until it ends; its colour steps through phases (green down to 2, then red down to 2 with blue set to 0xFF,
   then blue down by 2 to 3); ends when the scene timer reaches 270 */

typedef struct {
    u8 pad0[0x693C];
    s16 timer;
} Scene_c062_01E024F0;

typedef struct {
    u8 pad0[0x50];
    s16 phase;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_c062_01E024F0;

static s32 func_01E024F0_c062(Scene_c062_01E024F0 *g, Obj_c062_01E024F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->t < 0xF) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 8;
        }
        if (o->t == 0) {
            func_001076F0(o->c0, 0x80, 0x60, 0);
        }
    } else if (o->t >= 0x32) {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 5;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (o->phase == 0) {
        if (o->c0[1] > 2) {
            o->c0[1]--;
        } else {
            o->phase = 1;
        }
    } else if (o->phase == 1) {
        o->c0[2] = 0;
        if (o->c0[0] > 2) {
            o->c0[0]--;
        } else {
            o->phase = 2;
            o->c0[2] = 0xFF;
        }
    } else if (o->phase == 2) {
        if (o->c0[2] > 3) {
            o->c0[2] -= 2;
        }
    }
    if (g->timer >= 0x10E) {
        o->state = 0;
    }
    return 0;
}

/* shape c062:01E02650, 73 insns: a grey smoke ring growing 1 a tick up to 7 that flickers (alpha 0xAF / 0x8F) while the scene value is under 270, then out by 9 (second colour by 2) and ends; bumps the scene counter up to 5 */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_c062_01E02650;

typedef struct {
    u8 pad[0x6900];
    s32 count;
    u8 pad6904[0x38];
    s16 val;
} Game_c062_01E02650;

static s32 func_01E02650_c062(Game_c062_01E02650 *g, Obj_c062_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->f48 < 7.0f) {
        o->f48 += 1.0f;
    }
    func_001076F0(o->col, 0x4F, 0x4F, 0x4F);
    func_001076F0(o->col2, 0x30, 0x30, 0x30);
    if (g->val < 270) {
        if (o->h50 == 0) {
            o->col[3] = 0xAF;
            o->col2[3] = 0x10;
            o->h50 = 1;
        } else {
            o->col[3] = 0x8F;
            o->col2[3] = 0x10;
            o->h50 = 0;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 3) {
            o->col2[3] -= 2;
        }
    }
    if (g->count < 5) {
        g->count++;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E02780_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E02B20_c062);

/* shape c062:01E02E40, 137 insns: three-kind ring glow: kind 0 white over grey, held 12, size 600; kind 1 blue under grey,
   held 5, growing from 600 by 10; kind 2 grey under white, held 10, growing from 1800 by 10; the second alpha grows by
   0x50 (below 0xA0) while held, then fades by 12 (kind 1: by 7); turns 0x20 by 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    s32 w48;
    f32 size;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_c062_01E02E40;

static s32 func_01E02E40_c062(s32 arg0, Fx_c062_01E02E40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w48 = 0;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
            o->hold = 12;
        }
        if (o->kind == 1) {
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
            func_001076F0(o->col, 0x40, 0x40, 0x80);
            o->hold = 5;
            o->size = 600.0f;
        }
        if (o->kind == 2) {
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0x40, 0x40, 0x40);
            o->hold = 10;
            o->size = 1800.0f;
        }
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->col2[3] < 0xA0) {
            o->col2[3] += 0x50;
        }
    } else if (o->kind != 1) {
        if (o->col2[3] > 0xD) {
            o->col2[3] -= 12;
        } else {
            o->mode = 0;
        }
    } else if (o->col2[3] > 8) {
        o->col2[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->size = 600.0f;
    }
    if (o->kind == 1) {
        o->size += 10.0f;
    }
    if (o->kind == 2) {
        o->size += 10.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape c062:01E03070, 103 insns: a red falling spark (b434:01E02210 shape): size 35, random sub-frame 0..3, height 3000..4999
   falling by 200..399 once started until under 31, angle, width 0..34, hold 3..5; alpha up by 0x40 to 0xC0 until the hold, then down by 14 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_c062_01E03070;

static s32 func_01E03070_c062(void *arg0, Obj_c062_01E03070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 35.0f;
        o->sub = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->y = func_0019A5C8() % 2000 + 0xBB8;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 200 + 0xC8;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->y > 0x1E) {
            o->y -= o->step;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* shape c062:01E03210, 115 insns: far spark (depth 800, growing) with random radius, spin and life */

typedef struct Sp_c062_01E03210 {
    u8 pad0[6];
    s16 life;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 spin;
    u8 pad10[0x38];
    f32 depth;
    u8 pad4C[4];
    s16 rad;
    u8 pad52[2];
    s16 age;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Sp_c062_01E03210;

static s32 func_01E03210_c062(s32 arg0, Sp_c062_01E03210 *o) {
    extern s32 func_001076F0();
    if (o->state == 1) {
        o->depth = 800.0f;
        o->h56 = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->hA = o->rad;
        o->rad = func_0019A5C8() % 15 + 1;
        o->ang = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 80 + 80;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 10 + 8;
        o->hC = func_0019A5C8() % 2;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->depth += 1.0f;
    }
    if (o->age != 0) {
        o->rad += o->spin;
    }
    o->age++;
    return 0;
}

/* shape c062:01E033E0, 92 insns: b732:01E03BC0 family shock wave (grey/red, scale 6, 200 wide): kind 0 from 2000 growing 140 a tick, kind 1 from 1200 growing 80; in by 64 up to 0x80 for 12 ticks, then out by 7 and ends; spins 6 a tick */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_c062_01E033E0;

static s32 func_01E033E0_c062(s32 arg0, Obj_c062_01E033E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0x10, 0x10);
        if (o->h50 == 0) {
            o->f30 = 200.0f;
            o->f34 = 2000.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 200.0f;
            o->f34 = 1200.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 140.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 80.0f;
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E03550_c062);

/* shape c062:01E037E0, 127 insns: five star points around a centre: each point is cleared to (0, 0, c.z), then placed at
   angle 90 / 18 / 162 / -54 / 234 (the middle four mirrored by the side flag) on a circle of radius c.x around c.y */

typedef struct {
    u8 pad0[0xD8];
    u8 sin[1];
} Scene_c062_01E037E0;

static s32 func_01E037E0_c062(Scene_c062_01E037E0 *g, Vec4f *out, Vec4f *src, s32 side) {
    extern void func_00106DD0(void *, f32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f c;
    f32 cz;
    f32 cy;
    s16 a;
    s16 i;

    c = *src;
    cz = c.z;
    cy = c.y;
    for (i = 0; i < 5; i++) {
        func_00106DD0(out, 0.0f, 0.0f, cz);
        if (i == 0) {
            a = 90;
        } else if (i == 1) {
            if (side == 0) {
                a = 18;
            } else {
                a = 162;
            }
        } else if (i == 2) {
            if (side == 0) {
                a = 162;
            } else {
                a = 18;
            }
        } else if (i == 3) {
            if (side == 0) {
                a = -54;
            } else {
                a = 234;
            }
        } else if (i == 4) {
            if (side == 0) {
                a = 234;
            } else {
                a = -54;
            }
        }
        out->y = cy + c.x * func_00108030(g->sin, a, 0);
        out->x = c.x * func_00108030(g->sin, a, 1);
        if (i < 5) {
            out++;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E039E0_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E03BE0_c062);

INCLUDE_ASM("asm/nonmatchings/mod/c062", func_01E04470_c062);

/* shape c062:01E05520, 82 insns: c035:01E01150 family: take the first free effect slot of 200 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_c062_01E05520;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_c062_01E05520 slot[200];
    u8 padEnd[0x6844 - 0x2a0 - 200 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad6848[0xE0];
    s16 ang;
    u8 pad692A[0xA];
    s16 h30;
} Ctx_c062_01E05520;

static s32 func_01E05520_c062(Ctx_c062_01E05520 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_c062_01E05520 *s;

    s = NULL;
    for (i = 0; i < 200; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h5A = ctx->ang;
        s->h50 = ctx->h30;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

/* shape c062:01E05670, 138 insns: two-colour sprite quad at an object's position (b016:01E00920 packet): blend from flags >> 4, size o->f48; mode (flags & 0xF) 0 = far z, else the given depth */

/* OVL_WARM */

typedef struct {
    f32 u, v;
} Uv_c062_01E05670;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_c062_01E05670;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_c062_01E05670 uv;
    Xyz_c062_01E05670 v[4];
    u64 pad58[7];
} Pk_c062_01E05670;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 size;
    u8 pad4C[0x14];
    u8 col[4];
    u8 col2[4];
} Obj_c062_01E05670;

static void func_01E05670_c062(s32 arg0, Obj_c062_01E05670 *o, s32 flags, f32 depth) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f v;
    f32 d[4];
    f32 m[16];
    Pk_c062_01E05670 pk;
    s32 ot;
    Pk_c062_01E05670 *p;
    s16 sel;

    ot = (s32)func_00207500();
    p = (Pk_c062_01E05670 *)(u32)&pk;
    func_00107990(p, o->col, 1);
    func_00107990(p, o->col2, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v.x = o->x;
    v.y = o->y;
    v.z = o->z;
    func_00108EF0(m, NULL, NULL, &v);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, d) != 0) {
        if ((flags & 0xF) == 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, ot, 0);
            return;
        }
        func_002075F0(p, ot, (u32)depth);
    }
}
