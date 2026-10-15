#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b294(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b294(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E005A0_b294(Obj_b008_01E004D0 *o, Spr_b008_01E004D0 *s, s32 mode, s8 *tbl) {
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
        func_01E00150_b294((Pk_b008_01E00080 *)p, &o->rect, o->ids[i]);
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

/* shape b294:01E00B20, 163 insns: the effect scene's step: clears the tint to 0x80/0/0/0 and counts the frame (0x37C6);
   from frame 113 to 264 it spawns a 0x1E00DB0 two above joint 0x37A8 each frame; on frames 65 and 95 it bursts twenty
   0x1E017C0 one below each of the four joints 0x37AA..0x37B0 */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x3508];
    u8 col[4];
    u8 pad3768[0x40];
    s16 joint;
    s16 j2[4];
    u8 pad37B2[0x14];
    s16 t;
} Scene_b294_01E00B20;

static void func_01E00B20_b294(Scene_b294_01E00B20 *g) {
    extern void b294_01E00DB0(void);
    extern void b294_01E017C0(void);
    extern s32 b294_01E02410(Scene_b294_01E00B20 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t > 112 && g->t < 265) {
        func_001F5620(func_001F53A0(), g->joint, &v);
        g->px = v.x;
        g->py = 2.0f + v.y;
        g->pz = v.z;
        for (i = 0; i < 1; i++) {
            b294_01E02410(g, (s32)b294_01E00DB0, 0);
        }
    }
    if (g->t == 65 || g->t == 95) {
        func_001F5620(func_001F53A0(), g->j2[0], &v);
        g->px = v.x;
        g->py = v.y - 1.0f;
        g->pz = v.z;
        for (i = 0; i < 20; i++) {
            b294_01E02410(g, (s32)b294_01E017C0, 0);
        }
        func_001F5620(func_001F53A0(), g->j2[1], &v);
        g->px = v.x;
        g->py = v.y - 1.0f;
        g->pz = v.z;
        for (i = 0; i < 20; i++) {
            b294_01E02410(g, (s32)b294_01E017C0, 0);
        }
        func_001F5620(func_001F53A0(), g->j2[2], &v);
        g->px = v.x;
        g->py = v.y - 1.0f;
        g->pz = v.z;
        for (i = 0; i < 20; i++) {
            b294_01E02410(g, (s32)b294_01E017C0, 0);
        }
        func_001F5620(func_001F53A0(), g->j2[3], &v);
        g->px = v.x;
        g->py = v.y - 1.0f;
        g->pz = v.z;
        for (i = 0; i < 20; i++) {
            b294_01E02410(g, (s32)b294_01E017C0, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b294", func_01E00DB0_b294);

INCLUDE_ASM("asm/nonmatchings/mod/b294", func_01E01110_b294);

INCLUDE_ASM("asm/nonmatchings/mod/b294", func_01E01400_b294);

/* shape b294:01E017C0, 90 insns: b115:01E01980 family: a grey/white spark (size 60, random frame 0..6) at two random angles drifting 11 a tick along its angle (sine table ctx+0x38CC): alpha 0x80 for 7 ticks, then out by 13 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b294_01E017C0;

typedef struct {
    u8 pad[0x38cc];
    u8 sin[1];
} Game_b294_01E017C0;

static s32 func_01E017C0_b294(Game_b294_01E017C0 *g, Glow_b294_01E017C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 11.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 11.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b257:01E031C0, 55 insns: a flash: on start f38 0x12C, colours (0xF0,0xF0,0xF0) and (0xF0,0xF0,0x10) with
   alpha 0x10, a random direction; alpha grows by 0x60 for the first 2 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b257_01E031C0;

static s32 func_01E01930_b294(s32 arg0, Flash_b257_01E031C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b294:01E01A10, 173 insns: b482:01E02E40 family scene flash light (ctx+0x3520, 0xC4 70) at the effect's point: warms by 42/21/10 toward orange while the level rises 0.2 to 1, then cools by 16/16/8 and dims 0.1 to 0.1; ends when ctx+0x3760 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b294_01E01A10;

typedef struct {
    u8 pad0[0x3520];
    Light_b294_01E01A10 light;
    u8 padL[0x3760 - 0x3520 - 0x2C];
    s32 flag;
} Scene_b294_01E01A10;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b294_01E01A10;

static s32 func_01E01A10_b294(Scene_b294_01E01A10 *g, Fx_b294_01E01A10 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.c[0] = 0.0f;
        g->light.c[1] = 0.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 70.0f;
        g->light.level = 0.0f;
        g->light.pos.x = o->x;
        g->light.pos.y = o->y;
        g->light.pos.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.2f;
        } else {
            o->phase = 1;
        }
        if (g->light.c[0] < 128.0f) {
            g->light.c[0] += 42.0f;
        } else {
            g->light.c[0] = 128.0f;
        }
        if (g->light.c[1] < 64.0f) {
            g->light.c[1] += 21.0f;
        } else {
            g->light.c[1] = 128.0f;
        }
        if (g->light.c[2] < 32.0f) {
            g->light.c[2] += 10.0f;
        } else {
            g->light.c[2] = 64.0f;
        }
    } else {
        if (g->light.level > 0.1f) {
            g->light.level -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (g->light.c[0] > 16.0f) {
            g->light.c[0] -= 16.0f;
        } else {
            g->light.c[0] = 0.0f;
        }
        if (g->light.c[1] > 16.0f) {
            g->light.c[1] -= 16.0f;
        } else {
            g->light.c[1] = 0.0f;
        }
        if (g->light.c[2] > 8.0f) {
            g->light.c[2] -= 8.0f;
        } else {
            g->light.c[2] = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b294:01E01CD0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3760 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3760];
    s32 state;
} Game_b294_01E01CD0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b294_01E01CD0;

static s32 func_01E01CD0_b294(Game_b294_01E01CD0 *g, Fade_b294_01E01CD0 *o) {
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

static s32 func_01E01D90_b294(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02780_b294;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02788_b294;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b294", func_01E01DE0_b294);

/* shape b294:01E02410, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x37C2 and the two arguments; returns 1 if a
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
} Slot_b294_01E02410;

typedef struct {
    u8 pad[0x250];
    u8 m[0xB0];
    Slot_b294_01E02410 s[200];
    u8 pad3500[0x264];
    u8 r, g, b, a;
    u8 pad3768[0x5A];
    s16 v;
} Pool_b294_01E02410;

static s32 func_01E02410_b294(Pool_b294_01E02410 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b294_01E02410 *s = NULL;
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

/* shape b294:01E02530, 124 insns: one camera-facing sprite into a 9-reg packet: texture frame 0x14 at obj+0x34 through
   the module's sprite-UV helper (shape b008:01E00080, static), object colour, scene texture; a tenth-scale matrix from
   its turn at its position plus drift / 10, sent at size x size with the depth kept in the scene (0x3794) */

typedef struct {
    f32 s;
    f32 t;
} St_b294_01E02530;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b294_01E02530 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b294_01E02530;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x1A];
    u8 tex[8];
    u8 pad30[4];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Obj_b294_01E02530;

typedef struct {
    u8 pad0[0x3500];
    void *tex;
    u8 pad3504[0x268];
    s32 ctx;
    u8 pad3770[0x24];
    f32 depth[1];
} Scene_b294_01E02530;

static void func_01E02530_b294(Scene_b294_01E02530 *g, Obj_b294_01E02530 *obj, Pk_b294_01E02530 *pk) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    Rect_b008_01E00080 rect[2];
    Vec4f world[4];
    s32 rot[4];
    St_b294_01E02530 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    func_00106080(rect, 0x14, obj->h34, rect);
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
    func_01E00150_b294((Pk_b008_01E00080 *)pk, rect, 0);
    func_00208700(pk, g->tex, 1);
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
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, g->depth) != 0) {
        func_002075F0((s32)pk, g->ctx, func_001A23B0(g->depth[0]));
    }
}
