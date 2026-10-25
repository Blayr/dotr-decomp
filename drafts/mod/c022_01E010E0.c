#include "common.h"

/* shape c022:01E010E0, 292 insns, 1 copy (C022PAINT_RAIN): draws a ribbon segment (c022:01E00750's) as a quad from
   the scene's sine table (ctx+0x3A50): mode 0 sets up the packet (two colours, alpha blend, texture ctx+0xCC); else
   1 or 2 layers (2 apart) from its top ring to its bottom ring, or, linked, from the link's ring to its own */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c022_01E010E0;

typedef struct {
    Rgbaq_c022_01E010E0 c;
    u64 st;
    u64 xyz;
} Vtx_c022_01E010E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c022_01E010E0 v[4];
} Pkt_c022_01E010E0;

typedef struct Seg_c022_01E010E0 {
    u8 pad0[0x10];
    struct Seg_c022_01E010E0 *link;
    u8 pad14[8];
    f32 top;
    f32 bottom;
    f32 bob;
    u8 col[4];
    u8 col2[4];
    s16 two;
    u8 pad32[2];
    s16 ang0;
    s16 ang1;
} Seg_c022_01E010E0;

typedef struct {
    u8 pad0[0xCC];
    s32 tex;
    u8 padD0[0x392C];
    s32 ot;
    u8 pad3A00[0x28];
    f32 depth;
    u8 pad3A2C[0x24];
    u8 sin[4];
} Scene_c022_01E010E0;

static void func_01E010E0_c022(Scene_c022_01E010E0 *g, Seg_c022_01E010E0 *o, Pkt_c022_01E010E0 *p, s32 mode) {
    extern void func_00105D00(void *, s32, s32);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c022_01E010E0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    u8 rm[0x10];
    Vec4f q[4];
    s32 i;
    Seg_c022_01E010E0 *l;
    s16 a;
    s32 n;
    f32 d;
    f32 off;

    l = o->link;
    off = 0.0f;
    if (mode == 0) {
        func_00105D00(rm, 2, 0);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    n = (o->two == 0) ? 1 : 2;
    *(f32 *)(u32)&q[1].y = *(f32 *)(u32)&q[0].y = o->bob;
    *(f32 *)(u32)&q[3].y = 0.0f;
    *(f32 *)(u32)&q[2].y = 0.0f;
    for (i = 0; i < n; i++) {
        if (l == NULL) {
            a = o->ang0 - 8;
            q[0].x = o->top * func_00108030(g->sin, a, 1);
            q[0].z = o->top * func_00108030(g->sin, a, 0);
            q[2].x = (o->bottom - off) * func_00108030(g->sin, o->ang1, 1);
            q[2].z = (o->bottom - off) * func_00108030(g->sin, o->ang1, 0);
            a = o->ang0 - 23;
            q[1].x = o->top * func_00108030(g->sin, a, 1);
            q[1].z = o->top * func_00108030(g->sin, a, 0);
            a = o->ang1 - 15;
            q[3].x = (o->bottom - off) * func_00108030(g->sin, a, 1);
            q[3].z = (o->bottom - off) * func_00108030(g->sin, a, 0);
        } else {
            d = l->top - l->bottom;
            q[0].x = (l->top + d) * func_00108030(g->sin, o->ang0 - 16, 1);
            q[0].z = (l->top + d) * func_00108030(g->sin, o->ang0 - 16, 0);
            q[2].x = l->top * func_00108030(g->sin, l->ang0 - 8, 1);
            q[2].z = l->top * func_00108030(g->sin, l->ang0 - 8, 0);
            q[0].x = (l->top + d) * func_00108030(g->sin, o->ang0 - 31, 1);
            q[1].z = (l->top + d) * func_00108030(g->sin, o->ang0 - 31, 0);
            q[3].x = l->top * func_00108030(g->sin, l->ang0 - 23, 1);
            q[3].z = l->top * func_00108030(g->sin, l->ang0 - 23, 0);
            *(f32 *)(u32)&q[1].y = *(f32 *)(u32)&q[0].y = l->bob;
            *(f32 *)(u32)&q[3].y = *(f32 *)(u32)&q[2].y = l->bob / 2.0f;
        }
        if (func_00205630(q, 0x70000000, NULL, p, &g->depth) != 0) {
            func_002075F0(p, g->ot, func_001A23B0(g->depth));
        }
        off += 2.0f;
    }
}
