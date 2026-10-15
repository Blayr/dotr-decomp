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

static void func_01E00080_b195(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

static s32 func_01E00260_b195(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00330_b195(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E00780_b195);

/* shape b195:01E00A00, 134 insns: b194:01E00C60 with the sine table at g+0x4084 */

typedef struct {
    u8 pad0[0x4084];
    u8 trig[1];
} World_b195_01E00A00;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b195_01E00A00;

static s32 func_01E00A00_b195(World_b195_01E00A00 *w, Wisp_b195_01E00A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b195:01E00C20, 89 insns: on start 0x38 = 8, random rotation (0x18 0x2000..0x5FFF, 0x10 -0x2000..0x1FFF,
   0x14 0), variant 0..6; alpha grows by 0x40 (below 0x80) for 2 ticks, then fades by 13 once 0x38 passes 0x19 and by
   15 while the game counter at 0x4020 is below 10; colour (0x40, 0x20, 0); 0x38 grows by 2 */

typedef struct {
    u8 pad0[0x4020];
    s32 count;
} Game_b195_01E00C20;

typedef struct {
    u8 pad0[0x10];
    s32 rot10;
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b195_01E00C20;

static s32 func_01E00C20_b195(Game_b195_01E00C20 *g, Fx_b195_01E00C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->rot18 = func_0019A5C8() % 0x4000 + 0x2000;
        o->rot10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = 0;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->f38 > 0x19) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
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
    func_001076F0(o->col, 0x40, 0x20, 0);
    o->tick++;
    o->f38 += 2;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E00D90_b195);

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E01060_b195);

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E01390_b195(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E014A0_b195);

/* shape b195:01E01730, 67 insns: a brown ember of random size 10..39 (frame 6, angle -45) tipped by random turns of +-0x2000: alpha 0x40 for 5 ticks, then out by 7 and ends */

typedef struct {
    u8 pad0[0x10];
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
} Glow_b195_01E01730;

static s32 func_01E01730_b195(s32 arg0, Glow_b195_01E01730 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 30 + 10;
        o->kind = 6;
        o->ang = -45;
        func_001076F0(o->col, 0x30, 0x18, 8);
        o->w18 = func_0019A5C8() % 0x4000 + 0x2000;
        o->w10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = 0;
        o->mode = 2;
    }
    if (o->tick < 5) {
        o->col[3] = 0x40;
        o->col2[3] = 0;
    } else if (o->col[3] > 10) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b018:01E02480, 54 insns, 11 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
   state 2; full alpha for the first 5 ticks, then fades by 10 until state 0 */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b018_01E02480;

static s32 func_01E01840_b195(void *arg0, Obj_b018_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x14A;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b195:01E01920, 97 insns: b112:01E02420 with the light at game 0x3E80 (end flag 0x4020); a point light for the scene: on start sets the light (colour 128/4/2, range
   63) at the effect's position; its strength rises by 0.2 up to 1, then falls by 0.08 and the effect ends; the
   light is switched off (func_001F6C10(0)) once ended, and the effect ends when the game value 0x4020 is 1 */

typedef struct {
    f32 a, b, c, d;
    f32 x, y, z;
    u8 pad1C[4];
    f32 e, f, g;
} Light_b195_01E01920;

typedef struct {
    u8 pad[0x3E80];
    Light_b195_01E01920 light;
    u8 pad302C[0x174];
    s32 v;
} Game_b195_01E01920;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b195_01E01920;

static s32 func_01E01920_b195(Game_b195_01E01920 *g, Fx_b195_01E01920 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a = 128.0f;
        g->light.b = 4.0f;
        g->light.c = 2.0f;
        g->light.d = 0.0f;
        g->light.e = 0.0f;
        g->light.f = 63.0f;
        g->light.g = 0.0f;
        g->light.x = o->x;
        g->light.y = o->y;
        g->light.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.g < 1.0f) {
            g->light.g += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->light.g > 0.1f) {
        g->light.g -= 0.08f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->v == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b195:01E01AB0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x4020 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x4020];
    s32 state;
} Game_b195_01E01AB0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b195_01E01AB0;

static s32 func_01E01AB0_b195(Game_b195_01E01AB0 *g, Fade_b195_01E01AB0 *o) {
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

static s32 func_01E01B70_b195(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03780_b195;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03788_b195;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E01BC0_b195(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E01E50_b195);

/* shape b195:01E02650, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x407A and the two arguments; returns 1 if a
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
} Slot_b195_01E02650;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x4A4];
    Slot_b195_01E02650 s[220];
    u8 pad3E74[0x1B0];
    u8 r, g, b, a;
    u8 pad4028[0x52];
    s16 v;
} Pool_b195_01E02650;

static s32 func_01E02650_b195(Pool_b195_01E02650 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b195_01E02650 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 220; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 220;
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

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E02770_b195);

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E02A40_b195);

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E02D00_b195);

/* shape b195:01E02FE0, 133 insns: b120:01E03DF0's two-pass quad with 9 quads: mode 0 sets the material (frame 0x97, two
   colours, scene texture 0x37C); other modes place it at the object with a 0.4 x-scale and a -0x4000 turn, then draw each of
   the 9 quads at scene 0x380 against the matrix at 0x290 (depth 0x4054, packet list 0x402C) */

typedef struct {
    f32 x, y, z, w;
} Vec_b195_01E02FE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E02FE0;

typedef struct {
    Rgbaq_b195_01E02FE0 c;
    u64 st;
    u64 xyz;
} Vtx_b195_01E02FE0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b195_01E02FE0 v[4];
} Pkt_b195_01E02FE0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    s32 r0;
    s32 r1;
    s32 r2;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
} Anim_b195_01E02FE0;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0xAC];
    s32 texture;
    Vec_b195_01E02FE0 quad[9][4];
    u8 pad5C0[0x3A6C];
    s32 target;
    u8 pad4030[0x24];
    f32 depth;
} Game_b195_01E02FE0;

static void func_01E02FE0_b195(Game_b195_01E02FE0 *g, Anim_b195_01E02FE0 *an, Pkt_b195_01E02FE0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b195_01E02FE0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b195_01E02FE0 pos;
    f32 rm[4];
    s32 rot[4];
    Vec_b195_01E02FE0 sc;
    f32 m[16];
    s16 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020EB40(g->m);
        func_00106DD0(&pos, an->x, an->y, an->z);
        sc.x = 0.4f;
        sc.y = 1.0f;
        sc.z = 1.0f;
        rot[0] = an->r0 - 0x4000;
        rot[1] = 0;
        rot[2] = an->r2;
        func_0020C940(m, &sc, rot, &pos);
        func_0020BC00(g->m, m);
        for (i = 0; i < 9; i++) {
            if (func_00205630(g->quad[i], 0x70000000, g->m, p, &g->depth) != 0) {
                func_00109380(p, 0);
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape b195:01E03200, 131 insns: b294:01E02530's sprite in two passes: mode 0 sets the material (frame 0x9B, colour,
   scene texture 0x37C), other modes draw it (depth kept at scene 0x4054, packet list 0x402C) */

typedef struct {
    f32 s;
    f32 t;
} St_b195_01E03200;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b195_01E03200 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b195_01E03200;

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
} Obj_b195_01E03200;

typedef struct {
    u8 pad0[0x37C];
    void *tex;
    u8 pad380[0x3CAC];
    s32 ctx;
    u8 pad4030[0x24];
    f32 depth[1];
} Scene_b195_01E03200;

static void func_01E03200_b195(Scene_b195_01E03200 *g, Obj_b195_01E03200 *obj, Pk_b195_01E03200 *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    Rect_b008_01E00080 rect[2];
    Vec4f world[4];
    s32 rot[4];
    St_b195_01E03200 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x9B, obj->h34, rect);
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
        func_01E00330_b195((Pk_b008_01E00080 *)pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
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
}

INCLUDE_ASM("asm/nonmatchings/mod/b195", func_01E03410_b195);
