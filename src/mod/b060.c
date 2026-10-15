#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b060", func_01E00080_b060);

/* shape b060:01E009B0, 125 insns: b064:01E01A00's drifting spark, grey-purple, tilt -15..14, speeds 6/4/6 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b060_01E009B0;

static s32 func_01E009B0_b060(u8 * g, Spark_b060_01E009B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x2F, 0x20, 0x2F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 0x28) {
        o->f38 += 5;
    }
    if (o->tick % 3 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 6.0f * func_00108030(g + 0x3B60, o->dir, 0);
    o->fA = o->fA + 4.0f * func_00108030(g + 0x3B60, o->angle, 1);
    o->fC = o->fC + 6.0f * func_00108030(g + 0x3B60, o->dir, 1);
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b060:01E00BB0, 116 insns: dim mote drifting 13 units a frame along two random angles, fading in and out */

typedef struct Mo_b060_01E00BB0 {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c28[4];
    u8 c2C[4];
    s16 ang2;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Mo_b060_01E00BB0;

typedef struct Scn_b060_01E00BB0 {
    u8 pad0[0x3B60];
    u8 table[0x10];
} Scn_b060_01E00BB0;

static s32 func_01E00BB0_b060(Scn_b060_01E00BB0 *w, Mo_b060_01E00BB0 *o) {
    extern s32 func_001076F0();
    func_001076F0(o->c28, 0x10, 0x10, 0x10);
    if (o->state == 1) {
        o->h38 = 7;
        o->ang = func_0019A5C8() % 360;
        o->h34 = func_0019A5C8() % 7;
        o->ang2 = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->age < 2) {
        if (o->c28[3] < 0x60) {
            o->c28[3] += 0x30;
        }
    } else if (o->c28[3] > 5) {
        o->c28[3] -= 4;
    } else {
        o->state = 0;
    }
    o->age++;
    if (o->h38 < 10) {
        o->h38++;
    }
    o->x = (s32)(o->x + 13.0f * func_00108030((s32)w->table, o->ang, 0));
    o->y = (s32)(o->y + 13.0f * func_00108030((s32)w->table, o->ang2, 1));
    o->z = (s32)(o->z + 13.0f * func_00108030((s32)w->table, o->ang, 1));
    return 0;
}

/* shape b060:01E00D80, 84 insns: a dark blue tumbling glow at three random turns, growing a random 2..6 a tick up to 50 and turning 2: in by 48 for 2 ticks; past size 10 out by 9, and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[4];
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
} Glow_b060_01E00D80;

static s32 func_01E00D80_b060(s32 arg0, Glow_b060_01E00D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x20, 0x20, 0x40);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->hE = func_0019A5C8() % 5 + 2;
        o->kind = 0;
        o->f38 = 0;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x30;
    }
    o->tick++;
    if (o->f38 > 10) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->f38 < 50) {
        o->f38 += o->hE;
    }
    o->ang += 2;
    return 0;
}

/* shape b060:01E00ED0, 107 insns: a grey drifting puff (b194:01E015C0 shape): frame 5, random sub-frame 0..3 and angles; alpha up by
   42 for 3 frames, then down by 5 until it ends; drifts 15 along its angle and bobs 15 by its second angle */

typedef struct {
    u8 pad0[0x3B60];
    u8 sin[1];
} Game_b060_01E00ED0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 bob;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b060_01E00ED0;

static s32 func_01E00ED0_b060(Game_b060_01E00ED0 *g, Obj_b060_01E00ED0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 5;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->bob = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 3) {
        o->c0[3] += 0x2A;
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 15.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 15.0f * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + 15.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b060:01E01080, 103 insns: colour (0x8F, 0x50, 0x5F); on start 0x38 = 17 and a heading 0x3A: random, or (game step 0x3B5C from
   0x82) -60..59 / 120..239 depending on func_001F53A0 below 10; alpha grows by 0x30 (below 0x60) for 2 ticks, then
   fades by 7 and stops; 0x38 counts up to 0x19 */

typedef struct {
    u8 pad0[0x3B5C];
    s16 step;
} Game_b060_01E01080;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b060_01E01080;

static s32 func_01E01080_b060(Game_b060_01E01080 *g, Fx_b060_01E01080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x8F, 0x50, 0x5F);
    if (o->mode == 1) {
        o->f38 = 17;
        if (func_001F53A0() < 10) {
            if (g->step < 0x82) {
                o->heading = func_0019A5C8() % 360;
            } else {
                o->heading = func_0019A5C8() % 120 - 60;
            }
        } else if (g->step < 0x82) {
            o->heading = func_0019A5C8() % 360;
        } else {
            o->heading = func_0019A5C8() % 120 + 120;
        }
        o->f34 = 0;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0x2A) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 0x19) {
        o->f38++;
    }
    return 0;
}

/* shape b060:01E01220, 103 insns: colour (0x40, 0x40, 0x1F); on start 0x38 = 15 and a heading 0x3A: random, or (game step 0x3B5C from
   0x82) -60..59 / 120..239 depending on func_001F53A0 below 10; alpha grows by 0xF (below 0x60) for 8 ticks, then
   fades by 15 and stops; 0x38 counts down to 0 */

typedef struct {
    u8 pad0[0x3B5C];
    s16 step;
} Game_b060_01E01220;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b060_01E01220;

static s32 func_01E01220_b060(Game_b060_01E01220 *g, Fx_b060_01E01220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x40, 0x40, 0x1F);
    if (o->mode == 1) {
        o->f38 = 15;
        if (func_001F53A0() < 10) {
            if (g->step < 0x82) {
                o->heading = func_0019A5C8() % 360;
            } else {
                o->heading = func_0019A5C8() % 120 - 60;
            }
        } else if (g->step < 0x82) {
            o->heading = func_0019A5C8() % 360;
        } else {
            o->heading = func_0019A5C8() % 120 + 120;
        }
        o->f34 = 0;
        o->col[3] = 0;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0xF;
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

INCLUDE_ASM("asm/nonmatchings/mod/b060", func_01E013C0_b060);

/* shape b060:01E01890, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B58 and the two arguments; returns 1 if a
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
} Slot_b060_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b060_01E01890 s[220];
    u8 pad3984[0x180];
    u8 r, g, b, a;
    u8 pad3B08[0x50];
    s16 v;
} Pool_b060_01E01890;

static s32 func_01E01890_b060(Pool_b060_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b060_01E01890 *s = NULL;
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

static void func_01E019B0_b060(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
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

static void func_01E01B50_b060(u8 *ctx, Obj_b058_01E02240 *o, void *pkt, s32 mode) {
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

/* shape b053:01E01E30, 107 insns: b053:01E022F0 with a 0.1 scale vector (texture 0x9B, page at ctx+0x10C) */

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
} Obj_b053_01E01E30;

static void func_01E01D00_b060(u8 *ctx, Obj_b053_01E01E30 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    sc.z = sc.y = sc.x = 0.1f;
    func_00108EF0(m, &sc, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b060", func_01E01EB0_b060);
