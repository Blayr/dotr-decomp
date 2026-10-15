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

static void func_01E00080_b538(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E004D0_b538(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
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
        func_01E00080_b538((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
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

/* shape b538:01E00A50, 65 insns: scene colour (0x80, 0, 0, 0); count 0x35E8 up; between 0x58 and 0x12D place the
   scene at the model point 0x35C8 (y - 1, z +/- 3.5 by the side flag 0x35E4) and run the module's b538:01E00B60
   through b538:01E01220 once */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x3584 - 0x25C];
    u8 col[4];
    u8 pad3588[0x40];
    s16 point;
    u8 pad35CA[0x1A];
    s16 side;
    u8 pad35E6[2];
    s16 count;
} Scene_b538_01E00A50;

static void func_01E00A50_b538(Scene_b538_01E00A50 *g) {
    extern void b538_01E00B60(void);
    extern void b538_01E01220(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 pt[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count > 0x57 && g->count < 0x12E) {
        func_001F5620(func_001F53A0(), g->point, pt);
        g->pos[0] = pt[0];
        g->pos[1] = pt[1] - 1.0f;
        g->pos[2] = pt[2];
        if (g->side != 0) {
            g->pos[2] += 3.5f;
        } else {
            g->pos[2] -= 3.5f;
        }
        for (i = 0; i < 1; i++) {
            b538_01E01220(g, b538_01E00B60, 0);
        }
    }
}

/* shape b538:01E00B60, 207 insns: b566:01E018E0's glow in violet (0xC0, 0x10, 0xFF) on joints g+0x35C8/0x35CA, rise
   5..9, h8 0..24, held 45..54 ticks fading in by 0x30 to 97 then down by 9; depth drift /40 for 40 ticks then /60;
   frame steps to 5, f38 grows by 1 */

typedef struct {
    u8 pad0[0x35C8];
    s16 ja;
    s16 jb;
} Game_b538_01E00B60;

typedef struct {
    s16 h0;
    u8 pad2[2];
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
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
} Glow_b538_01E00B60;

static s32 func_01E00B60_b538(Game_b538_01E00B60 *g, Glow_b538_01E00B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v[3];

    if (o->mode == 1) {
        o->f38 = 70;
        o->kind = 0;
        func_001076F0(o->col, 0xC0, 0x10, 0xFF);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 25;
        o->h6 = func_0019A5C8() % 10 + 45;
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->hC = func_001A22C0(v[1].x - v[0].x);
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] < 97) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5F90(func_001F53A0(), &v[1]);
    *(f32 *)(u32)&v[0].z -= v[1].z;
    if (o->tick < 40) {
        *(f32 *)(u32)&v[0].z /= 40.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    } else {
        *(f32 *)(u32)&v[0].z /= 60.0f;
        o->h4 = func_001A22C0(o->h4 + v[0].z);
    }
    if (o->tick % 2 == 1) {
        o->h0 += o->hC;
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
        o->f38 += 1;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* OVL_WARM */

/* shape b538:01E00EA0, 222 insns: the b538 module's main step: keeps two order tables; with a code it clears the scene,
   sets up its two coordinates, keeps the code and a 372-tick timer, the model's joints 0x22/0x3A/0x40/0x47/0x4E, the
   camera's turned-back flag (turn / 180), textures (5,0) and (5,1), 256 random offsets -15..14 and eight random
   0..3 words; otherwise it runs the scene step (b538:01E00A50), every live glow slot (200 of 0x40 bytes,
   b538:01E00B60), then draws each glow as gas (b538:01E004D0) with texture 0, its frame through func_00106080 and a
   random 0..3 variant; counts the timer down and returns 1 / 4 / 2 at steps 90 / 370 / 355, 6 between 101 and 349,
   8 when the timer ends */

typedef struct {
    u8 pad0[0x24];
    s32 (*fn)(void *, void *);
    u8 pad28[0xC];
    s16 frame;
    s16 used;
    u8 pad38[8];
} Slot_b538_01E00EA0;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0[8];
    u8 padD0[8];
    u8 crdD8[0x290 - 0xD8];
    s32 w290;
    s32 w294;
    s32 w298;
    u8 pad29C[0x300 - 0x29C];
    Slot_b538_01E00EA0 slot[200];
    s32 tex[2];
    u8 pad3508[0x3580 - 0x3508];
    s32 timer;
    u8 pad3584[8];
    s32 ot2;
    u8 pad3590[0x35C8 - 0x3590];
    s16 joint[5];
    u8 pad35D2[0x35E4 - 0x35D2];
    s16 turn;
    s16 code;
    s16 step;
    u8 pad35EA[2];
    s8 noise[0x100];
    u8 crd36EC[1];
} Scene_b538_01E00EA0;

static s32 func_01E00EA0_b538(s32 arg0, s32 code) {
    extern void b538_01E004D0(Scene_b538_01E00EA0 *, Slot_b538_01E00EA0 *, s32, void *);
    extern void b538_01E00A50(Scene_b538_01E00EA0 *, s32);
    extern s32 b538_01E00B60(void *, void *);
    Scene_b538_01E00EA0 *g = (Scene_b538_01E00EA0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    f32 pos[4];
    f32 rm[4];
    s32 ang[4];
    s32 n;
    s32 i;

    n = 0;
    g->ot = func_00207500();
    g->ot2 = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3860);
        func_00107C10(g->crd36EC);
        func_00107C10(g->crdD8);
        g->code = code;
        g->timer = 372;
        g->w290 = 0;
        g->w294 = 0;
        g->w298 = 0;
        g->joint[0] = func_001F5560(func_001F53A0(), 0x22, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x3A, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x40, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x47, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x4E, 0);
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s16)(ang[1] / 180.0f);
        for (; n < 2; n++) {
            g->tex[n] = func_00202BF0(5, n);
        }
        for (i = 0; i < 0x100; i++) {
            g->noise[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    b538_01E00A50(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == b538_01E00B60) {
                b538_01E00B60(g, &g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), pos);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == b538_01E00B60) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->slot[i].frame, 0);
                g->rect = *(Vec4f *)rm;
                g->hB8 = 7;
                g->hBE = func_0019A5C8() % 4;
                b538_01E004D0(g, &g->slot[i], 0, g->noise);
                g->hB8 = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 90) {
        return 1;
    }
    if (g->step == 370) {
        return 4;
    }
    if (g->step == 355) {
        return 2;
    }
    if (g->step > 100 && g->step < 350) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b538:01E01220, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x35E2 and the two arguments; returns 1 if a
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
} Slot_b538_01E01220;

typedef struct {
    u8 pad[0x250];
    u8 m[0xB0];
    Slot_b538_01E01220 s[200];
    u8 pad3500[0x84];
    u8 r, g, b, a;
    u8 pad3588[0x5A];
    s16 v;
} Pool_b538_01E01220;

static s32 func_01E01220_b538(Pool_b538_01E01220 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b538_01E01220 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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

INCLUDE_ASM("asm/nonmatchings/mod/b538", func_01E01380_b538);
