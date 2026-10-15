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

static void func_01E00080_b041(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

/* OVL_WARM */

/* shape b041:01E004D0, 156 insns, 2 copies: draws one full-screen textured quad in the sprite's colour (all four corners),
   blend from flags >> 4, texture window from the object, depth from the caller */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b041_01E004D0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b041_01E004D0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b041_01E004D0 c;
        u64 st;
        Xyz_b041_01E004D0 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b041_01E004D0;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b041_01E004D0;

typedef struct {
    u8 pad00[0x60];
    u8 col[4];
} Spr_b041_01E004D0;

static void func_01E004D0_b041(Obj_b041_01E004D0 *o, Spr_b041_01E004D0 *s, s32 flags, f32 depth) {
    extern Rgbaq_b041_01E004D0 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Pkt_b041_01E004D0 pkt;
    Pkt_b041_01E004D0 *p;
    u8 *ot;
    s16 b;
    s16 hw;
    s16 hh;

    ot = func_00207500();
    p = &pkt;
    func_00109270(p, 0, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->v[0].c = func_00107740(s->col);
    p->v[1].c = func_00107740(s->col);
    p->v[2].c = func_00107740(s->col);
    p->v[3].c = func_00107740(s->col);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    func_00108CE0(quad, 100.0f, 100.0f);
    hw = 320;
    hh = 240;
    p->v[0].p.x = (0x800 - hw) * 16;
    p->v[0].p.y = (0x800 - hh) * 16;
    p->v[0].p.z = 0xFFFFFF;
    p->v[0].p.f = 0;
    p->v[1].p.x = (0x800 + hw) * 16;
    p->v[1].p.y = (0x800 - hh) * 16;
    p->v[1].p.z = 0xFFFFFF;
    p->v[1].p.f = 0;
    p->v[2].p.x = (0x800 - hw) * 16;
    p->v[2].p.y = (0x800 + hh) * 16;
    p->v[2].p.z = 0xFFFFFF;
    p->v[2].p.f = 0;
    p->v[3].p.x = (0x800 + hw) * 16;
    p->v[3].p.y = (0x800 + hh) * 16;
    p->v[3].p.z = 0xFFFFFF;
    p->v[3].p.f = 0;
    func_002075F0(p, (s32)ot, (u32)depth);
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
/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00740_b041(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b041((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b041((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E00CF0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E00FD0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E012A0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01660_b041);

/* shape b041:01E01820, 70 insns: a white pulse (60 x 120): in by 16 up to 0xC0 for 15 ticks; its phase turns 25 degrees a tick and the size is 60 + 3 * sine (table at ctx+0x8978), height twice that */

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
} Obj_v1;

typedef struct {
    u8 pad[0x8978];
    u8 sin[1];
} Game_v1;

static s32 func_01E01820_b041(Game_v1 *g, Obj_v1 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->h8 = 60;
        o->hA = o->h8 * 2;
        o->h56 = 0;
        o->f48 = 3.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    if (o->t < 15) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x10;
        }
    }
    o->h5C += 25;
    if (o->h5C >= 360) {
        o->h5C %= 360;
    }
    o->f30 = 60.0f + o->f48 * func_00108030(g->sin, o->h5C, 0);
    o->f34 = 2.0f * o->f30;
    return 0;
}

/* shape b041:01E01940, 75 insns: on start 0x8 = 30, 0xA = 60, colour 0x30 grey, random tilt -30..29 (0x5A); alpha
   grows by 0x40 (below 0x80) for 15 ticks, then fades by 9 and stops; after the first tick 0x8 grows by 15 and
   0xA = 1.2 x 0x8 (double maths through the runtime helpers, called by address) */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b041_01E01940;

static s32 func_01E01940_b041(s32 arg0, Fx_b041_01E01940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern double func_001A2EB0(s32);
    extern double func_001A2918(double, double);
    extern s32 func_001A2F68(double);

    if (o->mode == 1) {
        o->f8 = 30;
        o->fA = o->f8 * 2;
        o->f56 = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x30);
        o->f5A = func_0019A5C8() % 60 - 30;
        o->mode = 2;
    }
    if (o->tick < 15) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f8 += 15;
        o->fA = func_001A2F68(func_001A2918(1.2, func_001A2EB0(o->f8)));
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01A70_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E01C40_b041);

/* shape b041:01E01DF0, 113 insns: a dim two-colour glow: fades both colours in by 4 up to 0x60 for 22 frames, then out by 7 while the scene's counter is under 30; its frame counter runs 0..127 up or down by o->h50 */


typedef struct {
    u8 pad0[0x8700];
    s32 count;
} Ctx_b041_01E01DF0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[0x46];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b041_01E01DF0;

static s32 func_01E01DF0_b041(Ctx_b041_01E01DF0 *ctx, Obj_b041_01E01DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        func_001076F0(o->col2, 0x20, 0x20, 0x20);
        o->h6 = 22;
        o->h8 = func_0019A5C8() % 128;
        o->state = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x60) {
            o->col[3] += 4;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 4;
        }
    } else if (ctx->count < 30) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->col2[3] = 0;
        }
    }
    if (o->h50 == 0) {
        o->h8++;
        if (o->h8 >= 128) {
            o->h8 %= 128;
        }
    }
    if (o->h50 == 1) {
        o->h8--;
        if (o->h8 <= 0) {
            o->h8 = 128 - o->h8 % 128;
        }
    }
    o->t++;
    return 0;
}

/* shape b041:01E01FC0, 57 insns: volume fade (func_001F6D00 family): starts at 0x80; while the game counter at 0x8700
   is over 0x1E it drops by 10 while above 0x50, else snaps to 0x30; otherwise rises by 10 to 0x80 (clamped);
   func_001F6D00 gets 0x80 when the counter is 2, else the volume */

typedef struct {
    u8 pad0[0x8700];
    s32 count;
} Game_b041_01E01FC0;

typedef struct {
    u8 pad0[0x50];
    s16 v;
    u8 pad52[6];
    s16 mode;
} Fx_b041_01E01FC0;

static s32 func_01E01FC0_b041(Game_b041_01E01FC0 *g, Fx_b041_01E01FC0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x1E) {
        if (o->v > 0x50) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E020B0_b041);

INCLUDE_ASM("asm/nonmatchings/mod/b041", func_01E022D0_b041);

/* shape b041:01E02C00, 102 insns, 2 copies: spawns an effect into the first free slot (170 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

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
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b041_01E02C00;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b041_01E02C00 slot[170];
    u8 pad4500[0x8704 - 0x2A0 - 170 * 0x70];
    u8 col[4];
    u8 pad8708[0x66];
    s16 h876E;
} Scene_b041_01E02C00;

static s32 func_01E02C00_b041(Scene_b041_01E02C00 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b041_01E02C00 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 170; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 170;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->h876E;
        sl->h52 = s->h876E;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}
