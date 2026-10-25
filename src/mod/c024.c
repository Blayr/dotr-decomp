#include "common.h"

/* shape c024:01E00080, 223 insns: the c024 module's scene step: full alpha, 0x3B78 = 20, counts ticks (0x3B6E); at 1
   white and the grid built (c024:01E01CD0); for the first 32 ticks, while the rise 0x3B7A is under 230, four grey
   c024:01E00400 sparks a tick at height 0x3B62 + 4 (size 10..18, random angle, scale 1.5); 0x3B62 climbs 4 a tick;
   the rise climbs 8 to 230 (copied to 0x3B7C once past it), then 0x3B7C drops 3 every other tick; a 180-step delay
   loop; at 34 and 37 bursts of 30 c024:01E004F0 at the origin in the saved colour (0x3B58) when 0x3B20 is over 17 */

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x124 - 0xCC];
    f32 scale;
    u8 pad128[0x3B20 - 0x128];
    s32 level;
    u8 col[4];
    u8 pad3B28[8];
    s32 w3B30;
    u8 pad3B34[4];
    f32 size;
    u8 pad3B3C[0x3B58 - 0x3B3C];
    u8 save[3];
    u8 pad3B5B[3];
    s16 ang;
    u8 pad3B60[2];
    s16 height;
    u8 pad3B64[0x3B6E - 0x3B64];
    s16 count;
    u8 pad3B70[8];
    s16 h3B78;
    s16 rise;
    s16 top;
    s16 wait;
} Ctx_c024_01E00080;

static void func_01E00080_c024(Ctx_c024_01E00080 *g) {
    extern s32 c024_01E00400(void);
    extern s32 c024_01E004F0(void);
    extern void c024_01E009B0(Ctx_c024_01E00080 *, s32 (*)(void));
    extern void c024_01E00AE0(Ctx_c024_01E00080 *, s32 (*)(void));
    extern void c024_01E01CD0(Ctx_c024_01E00080 *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;
    s32 k;

    g->col[3] = 0x80;
    g->h3B78 = 20;
    g->count++;
    if (g->count == 1) {
        g->col[0] = 0xFF;
        g->col[1] = 0xFF;
        g->col[2] = 0xFF;
    }
    if (g->count == 1) {
        c024_01E01CD0(g, 0);
    }
    if (g->count < 33 && g->rise < 230) {
        for (i = 0; i < 4; i++) {
            g->pos[0] = 0.0f;
            g->pos[1] = g->height + 4;
            g->pos[2] = 0.0f;
            g->col[0] = 0x80;
            g->col[1] = 0x80;
            g->col[2] = 0x80;
            g->size = func_0019A5C8() % 9 + 10;
            g->col[3] = 10;
            g->ang = func_0019A5C8() % 360;
            g->scale = 1.5f;
            c024_01E009B0(g, c024_01E00400);
        }
    }
    g->height += 4;
    if (g->rise < 230) {
        g->rise += 8;
        if (g->rise > 230) {
            g->top = g->rise;
        }
    } else if (g->wait == 0) {
        g->top -= 3;
        g->wait = 1;
    } else {
        g->wait--;
    }
    for (k = 0; k < 180; k++) {
    }
    if (g->count == 34) {
        g->col[3] = 0;
        g->col[0] = g->save[0];
        g->col[1] = g->save[1];
        g->col[2] = g->save[2];
        func_00106DD0(g->pos, 0.0f, 0.0f, 0.0f);
        for (i = 0; i < 30; i++) {
            g->scale = func_0019A5C8() % 10 + 8;
            g->size = func_0019A5C8() % 140 + 5;
            g->w3B30 = 0;
            if (g->level > 17) {
                c024_01E00AE0(g, c024_01E004F0);
            }
        }
    }
    if (g->count == 37) {
        g->col[3] = 0;
        g->col[0] = g->save[0];
        g->col[1] = g->save[1];
        g->col[2] = g->save[2];
        for (i = 0; i < 30; i++) {
            func_00106DD0(g->pos, 0.0f, 0.0f, 0.0f);
            g->size = func_0019A5C8() % 140 + 5;
            g->scale = func_0019A5C8() % 10 + 8;
            g->w3B30 = 0;
            if (g->level > 17) {
                c024_01E00AE0(g, c024_01E004F0);
            }
        }
    }
}

/* shape c024:01E00400, 59 insns: an animated sprite: frame steps every 3 ticks up to 7 (then dies), slides by its speed; in by 15 for frames 0-2, then out by 12 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E00400;

static s32 func_01E00400_c024(s32 arg0, Spr_c024_01E00400 *o) {
    if (o->h22 == 0) {
        if (o->frame < 7) {
            o->frame++;
        } else {
            o->alive = 0;
        }
        o->h22 = 2;
    } else {
        o->h22--;
    }
    o->h16 -= o->h1C;
    o->h26++;
    if (o->frame < 3) {
        if (o->alpha < 0x80) {
            o->alpha += 15;
        }
        if (o->alpha < 0x80) {
            o->alpha2 += 15;
        }
    } else {
        if (o->alpha > 0x10) {
            o->alpha -= 12;
        }
        if (o->alpha > 0x10) {
            o->alpha2 -= 12;
        } else {
            o->alive = 0;
        }
    }
    return 0;
}

/* shape c024:01E004F0, 59 insns: a rising sprite: frame 0 climbs by its speed (dies past 260), others by 8 (die past 180); in by 27 up to 0xC0, past 130 out by 32 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E004F0;

static s32 func_01E004F0_c024(s32 arg0, Spr_c024_01E004F0 *o) {
    if (o->frame == 0) {
        o->h16 += o->h1C;
        if (o->h16 > 0x104) {
            o->alive = 0;
        }
    } else {
        o->h16 += 8;
        if (o->h16 > 180) {
            o->alive = 0;
        }
    }
    if (o->frame == 0) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else if (o->h16 < 0x82) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else {
        if (o->alpha > 0x20) {
            o->alpha -= 0x20;
        } else {
            o->alive = 0;
        }
        if (o->alpha2 > 0x20) {
            o->alpha2 -= 0x20;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E005E0_c024);

/* shape c024:01E009B0, 74 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), 0x26/0x1C from the scene floats
   0x3B38/0x124, 0x28 from 0x3B5E, store arg */

typedef struct {
    u8 pad0[0x10];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[7];
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E009B0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E009B0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E009B0;

static void func_01E009B0_c024(Scene_c024_01E009B0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Slot_c024_01E009B0 *s = NULL;
    s32 i;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x34);
            g->slots[i].used = i + 1;
            s = &g->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->f1C = g->f124;
        s->arg = arg;
    }
}

/* shape c024:01E00AE0, 123 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), two random words 0x0/0x8
   (-0x4000..0x3FF0), 0x26/0x28 from the scene 0x3B38/0x3B5E, a random half-size flag 0x24 (0x1C = scene 0x124,
   halved when set), 0x20 random 0..19, store arg */

typedef struct {
    s32 w0;
    u8 pad4[4];
    s32 w8;
    u8 padC[4];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[2];
    s16 f20;
    u8 pad22[2];
    s8 half;
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E00AE0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E00AE0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E00AE0;

static void func_01E00AE0_c024(Scene_c024_01E00AE0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    Slot_c024_01E00AE0 *s = NULL;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            s = &g->slots[i];
            func_00195108(s, 0x34);
            g->slots[i].used = i + 1;
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        func_0019A5C8();
        s->w8 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->w0 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->half = func_0019A5C8() % 2;
        if (s->half == 0) {
            s->f1C = g->f124;
        } else {
            s->f1C = g->f124 / 2.0f;
        }
        s->f20 = func_0019A5C8() % 20;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E00CD0_c024);

/* shape c024:01E01220, 233 insns: b004:01E01A00's hanging quad in two passes: with lit 0 it sets up the packet (rect
   0x8C,0,4,0x7F, colours 0x2A top and 0x2E bottom, scene texture 0x10C) and returns; otherwise it builds the scene
   matrix (0x40) from the point func_001F53B0 gives and the anim's rotation, and draws one quad 3 wide at the anim's
   s16 point hanging 60 down, heights kept within 12..200, depth in 0x3B48, into 0x3B2C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c024_01E01220;

typedef struct {
    Rgbaq_c024_01E01220 c;
    u64 st;
    u64 xyz;
} Vtx_c024_01E01220;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c024_01E01220 v[4];
} Pkt_c024_01E01220;

typedef struct {
    s16 x, y, w, h;
} Rect_c024_01E01220;

typedef struct {
    s32 rot[4];
    u8 pad10[4];
    s16 x, y, z;
    u8 pad1A[0x10];
    u8 col[4];
    u8 col2[4];
} Anim_c024_01E01220;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0x8C];
    s32 tex;
    u8 pad110[0x3B2C - 0x110];
    s32 ot;
    u8 pad3B30[0x18];
    f32 depth;
} Scene_c024_01E01220;

static void func_01E01220_c024(Scene_c024_01E01220 *g, Anim_c024_01E01220 *an, Pkt_c024_01E01220 *p, s32 lit) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c024_01E01220 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    Rect_c024_01E01220 r __attribute__((aligned(16)));

    if (lit == 0) {
        r.x = 0x8C;
        r.y = 0;
        r.w = 4;
        r.h = 0x7F;
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, &r, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_001F53B0(0, v);
    func_0020EB40(g->m);
    func_0020C940(m, 0, an->rot, v);
    func_0020BC00(g->m, m);
    q[0].x = an->x;
    q[0].y = an->y;
    q[0].z = an->z;
    q[1] = q[0];
    q[1].x += 3.0f;
    q[2].x = an->x;
    q[2].y = an->y;
    q[2].z = an->z;
    q[2].y -= 60.0f;
    q[3] = q[2];
    q[3].x += 3.0f;
    if (q[0].y > 200.0f) {
        q[0].y = 200.0f;
    }
    if (q[1].y > 200.0f) {
        q[1].y = 200.0f;
    }
    if (q[2].y > 200.0f) {
        q[2].y = 200.0f;
    }
    if (q[3].y > 200.0f) {
        q[3].y = 200.0f;
    }
    if (q[0].y < 12.0f) {
        q[0].y = 12.0f;
    }
    if (q[1].y < 12.0f) {
        q[1].y = 12.0f;
    }
    if (q[2].y < 12.0f) {
        q[2].y = 12.0f;
    }
    if (q[3].y < 12.0f) {
        q[3].y = 12.0f;
    }
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c024", func_01E015D0_c024);

/* shape c024:01E01CD0, 210 insns (C024_MAP_ATTACK_1): builds a 10x24 point bowl at ctx+0x150: rings of radius 100
   shrinking by 10 (at least 1), 15 degrees between points; each ring is shifted by a random walk (-5..4 a ring on x and
   z) and each point jittered by up to the ring's spread (70, -7 a ring, 1 from the ninth ring), centred; heights rise
   by 20 a ring for the first eight rings, then by 3 */

typedef struct {
    f32 x, y, z, w;
} V_c024_01E01CD0;

typedef struct {
    u8 pad0[0x150];
    V_c024_01E01CD0 p[10][24];
} Ctx_c024_01E01CD0;

static void func_01E01CD0_c024(Ctx_c024_01E01CD0 *g) {
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    s32 i;
    s32 j;
    s16 a;
    s16 z;
    s16 r;
    s16 x;
    s16 w;
    s16 dx;
    s16 dz;
    s16 y;
    f32 t;

    a = 0;
    z = 0;
    r = 100;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 24; j++) {
            t = 3.1415927f * a / 180.0f;
            g->p[i][j].x = r * func_001A6898(t);
            g->p[i][j].z = r * func_001A6A88(t);
            a += 15;
        }
        r -= 10;
        a = 0;
        if (r <= 0) {
            r = 1;
        }
    }
    w = 70;
    x = 0;
    for (i = 0; i < 10; i++) {
        x += (s16)(func_0019A5C8() % 10 - 5);
        z += (s16)(func_0019A5C8() % 10 - 5);
        for (j = 0; j < 24; j++) {
            dx = func_0019A5C8() % w;
            dz = func_0019A5C8() % w;
            g->p[i][j].x += x + (dx - (w >> 1));
            g->p[i][j].z += z + (dz - (w >> 1));
        }
        if (i < 8) {
            w -= 7;
        }
        if (i == 8) {
            w = 1;
        }
        if (w <= 0) {
            w = 1;
        }
    }
    y = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 24; j++) {
            g->p[i][j].y = y;
        }
        if (i < 8) {
            y += 20;
        } else {
            y += 3;
        }
    }
}

/* shape c024:01E02020, 319 insns: C024PAINT_RAIN5, a flat diamond on the ground: mode 0 builds the packet (texture
   page 0x99 frame b24, the effect's colour in all four corners); other modes stand on the model's root (y + h16),
   take corners at angles 135/45/225/315 of radius r + 5 and push them all r out along the heading ang + 15, then draw
   at the context depth */

typedef struct {
    u8 c[4];
    f32 q;
    u64 uv;
    u64 xyz;
} Vtx_c024_01E02020;

typedef struct {
    u8 pad0[0x10];
    Vtx_c024_01E02020 v[4];
} Pkt_c024_01E02020;

typedef struct {
    u8 pad0[4];
    s32 ry;
    u8 pad8[0xE];
    s16 dy;
    u8 pad18[0xC];
    s8 frame;
    u8 pad25;
    s16 r;
    s16 ang;
    u8 col[4];
} Fx_c024_01E02020;

typedef struct {
    u8 pad0[0x40];
    f32 m[16];
    u8 pad80[0x10C - 0x80];
    void *tex;
    u8 scale[0x3B2C - 0x110];
    s32 ot;
    u8 pad3B30[0x3B48 - 0x3B30];
    f32 depth;
    u8 pad3B4C[0x3B80 - 0x3B4C];
    u8 sin[4];
} Ctx_c024_01E02020;

static void func_01E02020_c024(Ctx_c024_01E02020 *g, Fx_c024_01E02020 *o, Pkt_c024_01E02020 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107710(void *, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_00205C40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    s16 rect[8];
    f32 m1[16];
    Vec4f pos;
    s32 rot[4];

    if (mode == 0) {
        func_00106080(rect, 0x99, o->frame, 0);
        func_00109270(p, 0, 0);
        func_00107710(p->v[0].c, o->col);
        p->v[0].q = 1.0f;
        func_00107710(p->v[1].c, o->col);
        p->v[1].q = 1.0f;
        func_00107710(p->v[2].c, o->col);
        p->v[2].q = 1.0f;
        func_00107710(p->v[3].c, o->col);
        p->v[3].q = 1.0f;
        func_00108500(p, rect, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_001F53B0(0, &pos);
    func_0020EB40(g->m);
    func_00205C40(rot);
    rot[0] = 0;
    rot[1] = o->ry;
    rot[2] = 0;
    pos.y += o->dy;
    func_0020C940(m1, 0, g->scale, &pos);
    func_0020BC00(g->m, m1);
    q[0].x = (o->r + 5) * func_00108030(g->sin, 0x87, 1);
    q[0].y = (o->r + 5) * func_00108030(g->sin, 0x87, 0);
    q[0].z = 0.0f;
    q[1].x = (o->r + 5) * func_00108030(g->sin, 0x2D, 1);
    q[1].y = (o->r + 5) * func_00108030(g->sin, 0x2D, 0);
    q[1].z = 0.0f;
    q[2].x = (o->r + 5) * func_00108030(g->sin, 0xE1, 1);
    q[2].y = (o->r + 5) * func_00108030(g->sin, 0xE1, 0);
    q[2].z = 0.0f;
    q[3].x = (o->r + 5) * func_00108030(g->sin, 0x13B, 1);
    q[3].y = (o->r + 5) * func_00108030(g->sin, 0x13B, 0);
    q[3].z = 0.0f;
    q[0].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[0].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[1].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[1].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[2].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[2].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[3].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[3].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}
