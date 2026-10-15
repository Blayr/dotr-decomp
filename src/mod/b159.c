#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b159(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b159", func_01E00150_b159);

/* shape b159:01E004C0, 134 insns: b019:01E01F60 with its sine table at ctx+0x3B68 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3B68];
    u8 tab[1];
} Mgr_b159_01E004C0;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b159_01E004C0;

static s32 func_01E004C0_b159(Mgr_b159_01E004C0 *m, Fx_b159_01E004C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b159:01E006E0, 124 insns: b064:01E01A00 with a tilt of 0..359 and the sine table at g+0x3B68: a grey puff drifting 13 a
   frame; fades in by 8 to 0xA0 for 8 ticks, out by 5; f38 grows to 13, kind steps every 5 ticks to 7 */

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
} Spark_b159_01E006E0;

static s32 func_01E006E0_b159(u8 * g, Spark_b159_01E006E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 13) {
        o->f38++;
    }
    if (o->tick % 5 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 13.0f * func_00108030(g + 0x3B68, o->dir, 0);
    o->fA = o->fA + 13.0f * func_00108030(g + 0x3B68, o->angle, 1);
    o->fC = o->fC + 13.0f * func_00108030(g + 0x3B68, o->dir, 1);
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E008D0_b159(void) {
    return 0;
}

/* shape b159:01E008E0, 106 insns: on start 0x38 = 1, variant 0..3, colour (0x1F, 0x1F, 0xFF), random headings 0x30 and
   0x3A; alpha 0x80 for 10 ticks, then fades by 10 and stops; it drifts 9 a tick (x by the cosine of 0x3A, y by the
   sine of 0x30, z by the sine of 0x3A, game table 0x3B68) */

typedef struct {
    u8 pad0[0x3B68];
    u8 trig[1];
} Game_b159_01E008E0;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b159_01E008E0;

static s32 func_01E008E0_b159(Game_b159_01E008E0 *g, Fx_b159_01E008E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->f34 = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0x1F, 0x1F, 0xFF);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
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
    o->x = func_001A22C0(o->x + 9.0f * func_00108030(g->trig, o->f3A, 0));
    o->y = func_001A22C0(o->y + 9.0f * func_00108030(g->trig, o->f30, 1));
    o->z = func_001A22C0(o->z + 9.0f * func_00108030(g->trig, o->f3A, 1));
    return 0;
}

/* shape b159:01E00A90, 40 insns: b120:01E01890 family: a purple glow held at the model point, alpha 0x30 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b159_01E00A90;

typedef struct {
    u8 pad[0x3b00];
    s32 state;
    u8 padS[0x4c];
    s16 val;
} Game_b159_01E00A90;

static s32 func_01E00A90_b159(Game_b159_01E00A90 *g, Glow_b159_01E00A90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 buf[4];

    func_001076F0(o->col, 0x1F, 0x10, 0x50);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->val, buf);
    o->col[3] = 0x30;
    o->tick = 10;
    if (g->state == 0x32) {
        o->mode = 0;
    }
    return 0;
}

/* shape b117:01E01820, 108 insns, 2 copies: a blue swell by kind: random turn on all axes once; grows 1/3/2 a frame (kinds
   0/1/2, the last two capped at 50/30) and fades out after 11/26/21 frames of growth; turns 12 a frame */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    u8 pad32[2];
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Swell_b117_01E01820;

static s32 func_01E00B30_b159(void *arg0, Swell_b117_01E01820 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x30, 0x30, 0x60);
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x80;
    }
    if (o->kind == 0) {
        if (o->size > 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        o->size += 1;
    } else if (o->kind == 1) {
        if (o->size > 0x19) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x32) {
            o->size += 3;
        }
    } else {
        if (o->size > 0x14) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x1E) {
            o->size += 2;
        }
    }
    o->ang += 12;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b159", func_01E00CE0_b159);

/* shape b159:01E01260, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B60 and the two arguments; returns 1 if a
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
} Slot_b159_01E01260;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b159_01E01260 s[220];
    u8 pad3984[0x180];
    u8 r, g, b, a;
    u8 pad3B08[0x58];
    s16 v;
} Pool_b159_01E01260;

static s32 func_01E01260_b159(Pool_b159_01E01260 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b159_01E01260 *s = NULL;
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

static void func_01E01380_b159(Mgr_b058_01E01F00 *m, Obj_b058_01E01F00 *o, void *p, s32 flag) {
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

static void func_01E01520_b159(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b159", func_01E016C0_b159);

/* shape b159:01E01B30, 181 insns: b064:01E03F20's ring, 9 sectors of 40 between radius o->size and o->size - 10 at the
   object's position; mode 0 sets up the packet's texture (0x96, page o->page) */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b159_01E01B30;

static void func_01E01B30_b159(u8 *ctx, Obj_b159_01E01B30 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A23B0(f32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x10];
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x96, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 9; i++) {
        k = o->ang + a;
        q[2].x = o->size * func_00108030(ctx + 0x3B68, k, 1);
        q[2].z = o->size * func_00108030(ctx + 0x3B68, k, 0);
        q[0].x = (o->size - 10) * func_00108030(ctx + 0x3B68, k, 1);
        q[0].z = (o->size - 10) * func_00108030(ctx + 0x3B68, k, 0);
        k = o->ang + 40 + a;
        q[3].x = o->size * func_00108030(ctx + 0x3B68, k, 1);
        q[3].z = o->size * func_00108030(ctx + 0x3B68, k, 0);
        q[1].x = (o->size - 10) * func_00108030(ctx + 0x3B68, k, 1);
        q[1].z = (o->size - 10) * func_00108030(ctx + 0x3B68, k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B3C)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), func_001A23B0(*(f32 *)(ctx + 0x3B3C)));
        }
        a += 40;
    }
}
