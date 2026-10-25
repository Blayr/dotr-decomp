#include "common.h"

/* shape c027:01E01930, 314 insns: draw one link of c027's rain curtain: mode 0 builds the 4-vertex packet (frame 0x96,
   near colours from the link, alpha 0 at a free end; far colours from the next link or the link's own at alpha 10);
   otherwise the curtain hangs under the model's joint: a 12-wide quad from the link to the next one (or its own base),
   30 deep, turned by the link's rotation and lifted 30, depth-tested */

typedef struct {
    u8 r, g, b, a;
} Col_c027_01E01930;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c027_01E01930;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_c027_01E01930 c;
        u64 uv;
        u64 xyz;
    } v[4];
} Pkt_c027_01E01930;

typedef struct Link_c027_01E01930 {
    f32 x0;
    f32 y4;
    u8 pad8[4];
    f32 xC;
    f32 x10;
    f32 y14;
    u8 pad18[4];
    f32 x1C;
    u8 pad20[0x20];
    s32 rot[4];
    struct Link_c027_01E01930 *next;
    s32 f54;
    u8 pad58[8];
    Col_c027_01E01930 c60;
    Col_c027_01E01930 c64;
} Link_c027_01E01930;

typedef struct {
    u8 pad0[0xCC];
    s32 tex;
    u8 padD0[0x2214];
    s32 ot;
    u8 pad22E8[0x48];
    f32 dep;
    u8 pad2334[0x70];
    u8 table[1];
} Scene_c027_01E01930;

static void func_01E01930_c027(Scene_c027_01E01930 *g, Link_c027_01E01930 *e, Pkt_c027_01E01930 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c027_01E01930 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern Vec4f *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_00205C40();
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Link_c027_01E01930 *q = e->next;
    Vec4f quad[4];
    f32 rm[4];
    f32 m[16];
    f32 m2[16];
    s32 rot[4];
    Vec4f cp;
    Vec4f t;
    Col_c027_01E01930 c;
    s32 i;
    s32 h;
    f32 w;

    if (mode == 0) {
        func_00106080(rm, 0x96, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad4 = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0xB0 << 32) | 0x48);
        if (e->f54 == 0) {
            c = e->c60;
            c.a = 0;
            p->v[0].c = func_00107740(&c);
            p->v[1].c = func_00107740(&c);
        } else {
            p->v[0].c = func_00107740(&e->c60);
            p->v[1].c = func_00107740(&e->c60);
        }
        if (q != 0) {
            p->v[2].c = func_00107740(&q->c64);
            p->v[3].c = func_00107740(&q->c64);
        } else {
            c = e->c60;
            c.a = 10;
            p->v[2].c = func_00107740(&c);
            p->v[3].c = func_00107740(&c);
        }
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    cp = *func_001F9D30(0);
    func_0020EB40(m);
    func_001F5BD0(func_001F5380(), &t);
    cp.x = t.x;
    cp.y = t.y;
    cp.z = t.z;
    func_00205C40(rot);
    func_0020C940(m2, 0, rot, &cp);
    func_0020BC00(m, m2);
    func_00106DD0(&cp, 0.0f, 30.0f, 0.0f);
    w = 6.0f;
    for (i = 0; i < 1; i++) {
        quad[0].x = e->x1C + (e->x10 - w);
        quad[1].x = e->x1C + (e->x10 + w);
        if (q != 0) {
            quad[2].x = q->x1C + (q->x10 - w);
            quad[3].x = q->x1C + (q->x10 + w);
        } else {
            quad[2].x = e->xC + (e->x0 - w);
            quad[3].x = e->xC + (e->x0 + w);
        }
        quad[0].y = e->y14;
        quad[1].y = e->y14;
        if (q != 0) {
            h = q->y14;
        } else {
            h = e->y4;
        }
        quad[3].y = quad[2].y = (s16)h;
        quad[0].z = 30.0f;
        quad[2].z = 30.0f;
        quad[3].z = 30.0f;
        quad[1].z = 30.0f;
        func_00108950(&quad[0], e->rot, 2, g->table);
        func_00108950(&quad[1], e->rot, 2, g->table);
        func_00108950(&quad[2], e->rot, 2, g->table);
        func_00108950(&quad[3], e->rot, 2, g->table);
        quad[0].y += cp.y;
        quad[1].y += cp.y;
        quad[2].y += cp.y;
        quad[3].y += cp.y;
        if (func_00205630(quad, 0x70000000, m, p, &g->dep) != 0) {
            func_002075F0(p, g->ot, (u32)g->dep);
        }
    }
}
