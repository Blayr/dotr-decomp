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

static void func_01E00080_b058(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E00260_b058);

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E00B40_b058);

/* shape b058:01E00D60, 117 insns: a dark smoke puff (size 2 growing to 25, random frame 0..6, random heading, tilt -30..29) swept 50 a tick along its heading and 4 up/down by the tilt (sine table ctx+0x3560): in by 5 up to 0x60 for 20 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b058_01E00D60;

typedef struct {
    u8 pad[0x3560];
    u8 sin[1];
} Game_b058_01E00D60;

static s32 func_01E00D60_b058(Game_b058_01E00D60 *g, Glow_b058_01E00D60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->col, 0x28, 0x28, 0x28);
    if (o->mode == 1) {
        o->f38 = 2;
        o->ang = func_0019A5C8() % 360;
        o->kind = func_0019A5C8() % 7;
        o->h30 = func_0019A5C8() % 60 - 30;
        o->mode = 2;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x60) {
            o->col[3] += 5;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 25) {
        o->f38++;
    }
    o->h8 = func_001A22C0(o->h8 + 50.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 50.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

typedef struct {
    u8 pad0000[0x3560];
    u8 tab[1];
} Mgr_b058_01E00F40;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b058_01E00F40;

static s32 func_01E00F40_b058(Mgr_b058_01E00F40 *m, Obj_b058_01E00F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x60, 0x30, 0);
    if (o->h36 == 1) {
        o->h38 = 2;
        o->h3A = func_0019A5C8() % 360;
        o->h34 = 0;
        o->h30 = func_0019A5C8() % 30 - 15;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    if (o->h32 % 3 == 1) {
        if (o->h34 < 7) {
            o->h34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y - 10.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b058:01E01120, 97 insns: an orange spark (size 1, random frame 0..3) at a random angle drifting 16 a tick along it and bobbing 20 x sine of a phase that turns 6 a tick (sine table ctx+0x3560): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[8];
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
} Glow_b058_01E01120;

typedef struct {
    u8 pad[0x3560];
    u8 sin[1];
} Game_b058_01E01120;

static s32 func_01E01120_b058(Game_b058_01E01120 *g, Glow_b058_01E01120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->kind = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h30 += 6;
    o->h8 = func_001A22C0(o->h8 + 16.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(20.0f * func_00108030(g->sin, o->h30, 0));
    o->hC = func_001A22C0(o->hC + 16.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E012B0_b058);

/* shape b058:01E01600, 103 insns: b027:01E00F90 family: an olive flame (size 15 shrinking to 0) at a random angle, or (scene value 130 on) within 60 degrees of 0 or of 180 depending on the scene handle being under 10: in by 15 up to 0x60 for 8 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b058_01E01600;

typedef struct {
    u8 pad[0x355C];
    s16 val;
} Game_b058_01E01600;

static s32 func_01E01600_b058(Game_b058_01E01600 *g, Glow_b058_01E01600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x40, 0x40, 0x1F);
    if (o->mode == 1) {
        o->f38 = 15;
        if (func_001F53A0() < 10) {
            if (g->val < 130) {
                o->ang = func_0019A5C8() % 360;
            } else {
                o->ang = func_0019A5C8() % 120 - 60;
            }
        } else if (g->val < 130) {
            o->ang = func_0019A5C8() % 360;
        } else {
            o->ang = func_0019A5C8() % 120 + 120;
        }
        o->kind = 0;
        o->col[3] = 0;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 15;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 != 0) {
        o->f38--;
    }
    return 0;
}

/* shape b058:01E017A0, 53 insns: volume fade by game state (b003:01E02330 family): state at 0x3500 limit 0x19,
   down 10 to 0x30, up 7 capped at 0x80 */

typedef struct {
    u8 pad[0x3500];
    s32 state;
} Game_b058_01E017A0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b058_01E017A0;

static s32 func_01E017A0_b058(Game_b058_01E017A0 *g, Fade_b058_01E017A0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x19) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 7;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E01880_b058);

/* shape b058:01E01DE0, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3558 and the two arguments; returns 1 if a
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
} Slot_b058_01E01DE0;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b058_01E01DE0 s[180];
    u8 pad2F84[0x580];
    u8 r, g, b, a;
    u8 pad3508[0x50];
    s16 v;
} Pool_b058_01E01DE0;

static s32 func_01E01DE0_b058(Pool_b058_01E01DE0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b058_01E01DE0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

typedef struct {
    f32 x, y, z, w;
} Vec_b058_01E01F00;

typedef struct {
    u8 pad000[0x10C];
    s32 texture;
} Mgr_b058_01E01F00;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[8];
    s16 h34;
    u8 pad36[2];
    s16 scale;
} Obj_b058_01E01F00;

static void func_01E01F00_b058(Mgr_b058_01E01F00 *m, Obj_b058_01E01F00 *o, void *p, s32 flag) {
    extern s32 func_00207500(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    f32 m3[16];
    Vec_b058_01E01F00 pos;
    Vec_b058_01E01F00 buf;
    f32 m2[16];
    Vec_b058_01E01F00 v;
    s32 t;
    f32 s;

    t = func_00207500();
    if (flag == 0) {
        func_00106080(&buf, 0x99, o->h34, &buf);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, &buf, 0);
        func_00208700(p, m->texture, 1);
        return;
    }
    func_00205C40(&v);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m2, 0, &v, &pos);
    s = o->scale;
    func_00108CE0(m3, s, s);
    func_00108F90(m3, p, m2, t);
}

/* shape b053:01E022F0, 103 insns: one textured square of an object (like b058:01E00080); mode 0 only sets up the
   packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn via
   func_00108F90. */

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
} Obj_b053_01E022F0;

static void func_01E020A0_b058(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b058:01E02240, 107 insns, 2 copies: one textured square of an object (b053:01E022F0 with a 0.1 scale); mode 0 only
   sets up the packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn
   via func_00108F90. */

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
} Obj_b058_01E02240;

static void func_01E02240_b058(u8 *ctx, Obj_b058_01E02240 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E023F0_b058);
