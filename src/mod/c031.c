#include "common.h"

/* shape c031:01E00080, 182 insns: c035:01E00080 family scene start: clears the scene alpha, size 20, counts ticks; on the first tick picks the scene colour by its kind (ctx+0x3EC: red, white, green, blue, yellow, magenta, cyan, pink, violet, orange, else white), sets eight 160 values and spawns c031:01E004B0 at the four corners (+-100, +-100) in slots 0..3 */

typedef struct {
    u8 pad0[0x80];
    f32 v80[4];
    u8 pad90[0x370 - 0x90];
    u8 col[4];
    u8 pad374[0x3A4 - 0x374];
    f32 f3A4[8];
    u8 pad3C4[0x3EA - 0x3C4];
    s16 slot;
    s16 kind;
    u8 pad3EE[2];
    s16 timer;
    u8 pad3F2[8];
    s16 h3FA;
    s16 h3FC;
} Ctx_c031_01E00080;

static void func_01E00080_c031(Ctx_c031_01E00080 *g) {
    extern void c031_01E004B0(void);
    extern void c031_01E00B90(Ctx_c031_01E00080 *, void (*)(void));
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;
    s16 k;

    g->col[3] = 0;
    g->h3FA = 20;
    g->timer++;
    if (g->timer == 1) {
        g->h3FC = 0;
        k = g->kind;
        if (k == 0) {
            func_001076F0(g->col, 0xFF, 0, 0);
        } else if (k == 1) {
            func_001076F0(g->col, 0xFF, 0xFF, 0xFF);
        } else if (k == 2) {
            func_001076F0(g->col, 0, 0xFF, 0);
        } else if (k == 3) {
            func_001076F0(g->col, 0, 0, 0xFF);
        } else if (k == 4) {
            func_001076F0(g->col, 0xFF, 0xFF, 0);
        } else if (k == 5) {
            func_001076F0(g->col, 0xFF, 0, 0xFF);
        } else if (k == 6) {
            func_001076F0(g->col, 0, 0xFF, 0xFF);
        } else if (k == 7) {
            func_001076F0(g->col, 0xFF, 0x80, 0xFF);
        } else if (k == 8) {
            func_001076F0(g->col, 0x80, 0, 0xFF);
        } else if (k == 9) {
            func_001076F0(g->col, 0xFF, 0x80, 0);
        } else {
            func_001076F0(g->col, 0xFF, 0xFF, 0xFF);
        }
        g->col[3] = 0;
        for (i = 0; i < 8; i++) {
            g->f3A4[i] = 160.0f;
        }
        g->slot = 0;
        func_00106DD0(g->v80, -100.0f, 100.0f, 0.0f);
        c031_01E00B90(g, c031_01E004B0);
        g->slot = 1;
        func_00106DD0(g->v80, 100.0f, 100.0f, 0.0f);
        c031_01E00B90(g, c031_01E004B0);
        g->slot = 2;
        func_00106DD0(g->v80, -100.0f, -100.0f, 0.0f);
        c031_01E00B90(g, c031_01E004B0);
        g->slot = 3;
        func_00106DD0(g->v80, 100.0f, -100.0f, 0.0f);
        c031_01E00B90(g, c031_01E004B0);
    }
}

/* shape c031:01E00360, 81 insns: turns an effect by its three spin speeds (each angle pinned at 360 once it leaves -360..360);
   fades both alphas by 48 while the scene state is below 6, else holds them at 0xFF; clears its flag below state 2. The conversion is the runtime fptosi (func_001A22C0) declared as returning s16:
   a plain (s32) cast adds a sign-extension the original does not have. */

typedef struct {
    u8 pad0[0x36C];
    s32 state;
} Scene_c031_01E00360;

typedef struct {
    u8 pad0[0x20];
    f32 vx, vy, vz;
    u8 pad2C[0xC];
    u8 c38[4];
    u8 c3C[4];
    s16 flag;
    s16 ax, ay, az;
} Fx_c031_01E00360;

static s32 func_01E00360_c031(Scene_c031_01E00360 *s, Fx_c031_01E00360 *o) {
    extern s16 func_001A22C0(f32);
    if (o->ax < 0x168 && o->ax > -0x168) {
        o->ax += func_001A22C0(o->vx);
    } else {
        o->ax = 0x168;
    }
    if (o->ay < 0x168 && o->ay > -0x168) {
        o->ay += func_001A22C0(o->vy);
    } else {
        o->ay = 0x168;
    }
    if (o->az < 0x168 && o->az > -0x168) {
        o->az += func_001A22C0(o->vz);
    } else {
        o->az = 0x168;
    }
    if (s->state < 6) {
        if (o->c38[3] > 0x30) {
            o->c38[3] -= 0x30;
        }
        if (o->c3C[3] > 0x30) {
            o->c3C[3] -= 0x30;
        }
    } else {
        o->c38[3] = 0xFF;
        o->c3C[3] = 0xFF;
    }
    if (s->state < 2) {
        o->flag = 0;
    }
    return 0;
}

/* shape c031:01E004B0, 140 insns: a c031 piece sliding until it crosses x = 0 (direction by kind 0..3, moved by its step at +0x20 via func_00106B50), then marked done; while moving both alphas rise by 13 to 0xF0; a kind-1 piece that finishes spawns c031:01E00360 (c031:01E00960); both alphas drop by 48 once the scene timer is under 6, and h40 clears under 2 */

typedef struct {
    u8 pad0[0x36C];
    s32 timer;
} Ctx_c031_01E004B0;

typedef struct {
    f32 x;
    u8 pad4[0x1C];
    u8 step[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h40;
    u8 pad42[8];
    s16 done;
    u8 pad4C[6];
    s16 kind;
} Obj_c031_01E004B0;

static s32 func_01E004B0_c031(Ctx_c031_01E004B0 *g, Obj_c031_01E004B0 *o) {
    extern s32 c031_01E00360(void);
    extern void c031_01E00960(Ctx_c031_01E004B0 *, s32 (*)(void));
    extern void func_00106B50(void *, void *);

    if (o->kind == 0) {
        if (o->x < 0.0f) {
            func_00106B50(o, o->step);
        } else if (o->done == 0) {
            o->done = 1;
        }
    } else if (o->kind == 1) {
        if (o->x > 0.0f) {
            func_00106B50(o, o->step);
        } else if (o->done == 0) {
            o->done = 1;
        }
    } else if (o->kind == 2) {
        if (o->x < 0.0f) {
            func_00106B50(o, o->step);
        } else if (o->done == 0) {
            o->done = 1;
        }
    } else if (o->kind == 3) {
        if (o->x > 0.0f) {
            func_00106B50(o, o->step);
        } else if (o->done == 0) {
            o->done = 1;
        }
    }
    if (o->done == 0) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 13;
        }
        if (o->col2[3] < 0xF0) {
            o->col2[3] += 13;
        }
    } else if (o->done == 1 && o->kind == 1) {
        c031_01E00960(g, c031_01E00360);
        o->done = 2;
    }
    if (g->timer < 6) {
        if (o->col[3] > 48) {
            o->col[3] -= 48;
        }
        if (o->col2[3] > 48) {
            o->col2[3] -= 48;
        }
    }
    if (g->timer < 2) {
        o->h40 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E006E0_c031);

/* shape c031:01E00960, 139 insns: c027:01E008B0 with 7 nodes of 0x54 at ctx+0x120, random sizes 3..5, and the
   c031:01E00D00 callback */

typedef struct {
    u8 pad0[0x20];
    f32 vx, vy, vz;
    u8 pad2C[4];
    s32 fn;
    s32 arg;
    u8 col[4];
    u8 col2[4];
    s16 used;
    u8 pad42[2];
    s16 h44;
    s16 h46;
    u8 pad48[2];
    s16 h4A;
    s16 h4C;
    u8 pad4E[6];
} Node_c031_01E00960;

typedef struct {
    u8 pad0[0x120];
    Node_c031_01E00960 node[7];
    u8 pad36C[4];
    u8 col[4];
    u8 pad374[8];
    Node_c031_01E00960 *head;
} Ctx_c031_01E00960;

static void func_01E00960_c031(Ctx_c031_01E00960 *g, s32 arg) {
    extern void c031_01E00D00();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Node_c031_01E00960 *s;

    s = NULL;
    for (i = 0; i < 7; i++) {
        if (g->node[i].used == 0) {
            s = &g->node[i];
            func_00195108(s, 0x54);
            g->node[i].used = i + 1;
            i = 7;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->col[0], g->col[1], g->col[2]);
        s->col[3] = g->col[3];
        func_001076F0(s->col2, g->col[0], g->col[1], g->col[2]);
        s->col2[3] = g->col[3];
        s->h4A = func_0019A5C8() % 3 + 3;
        s->h4C = func_0019A5C8() % 3 + 3;
        s->h44 = func_0019A5C8() % 180;
        s->h46 = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 == 0) {
            s->vx = 30.0f;
        } else {
            s->vx = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vy = 30.0f;
        } else {
            s->vy = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vz = 30.0f;
        } else {
            s->vz = -30.0f;
        }
        s->fn = (s32)c031_01E00D00;
        s->arg = arg;
        g->head = s;
    }
}

/* shape c031:01E00B90, 91 insns: take a free row (7 of 0x54 bytes at 0x120, mark = index + 1), clear it, two colours
   from the scene colour 0x370, copy the scene vector 0x80 and a velocity of -1/10 of it, 0x52 from 0x3EA, callback
   c031:01E01950 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c031_01E00B90;

typedef struct {
    V4_c031_01E00B90 pos;
    u8 pad10[0x10];
    f32 vx, vy, vz;
    u8 pad2C[4];
    void (*cb)(void);
    s32 arg;
    u8 c38[4];
    u8 c3C[4];
    s16 used;
    u8 pad42[0x10];
    s16 f52;
} Row_c031_01E00B90;

typedef struct {
    u8 pad0[0x80];
    V4_c031_01E00B90 pos;
    u8 pad90[0x90];
    Row_c031_01E00B90 rows[7];
    u8 pad36C[4];
    u8 rgba[4];
    u8 pad374[0x76];
    s16 f3EA;
} Scene_c031_01E00B90;

static void func_01E00B90_c031(Scene_c031_01E00B90 *g, s32 arg) {
    extern void c031_01E01950(void);
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Row_c031_01E00B90 *s = NULL;
    s16 i;

    for (i = 0; i < 7; i++) {
        if (g->rows[i].used == 0) {
            func_00195108(&g->rows[i], 0x54);
            g->rows[i].used = i + 1;
            s = &g->rows[i];
            i = 7;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c38, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c38[3] = g->rgba[3];
        func_001076F0(s->c3C, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c3C[3] = g->rgba[3];
        s->pos = g->pos;
        s->vx = -(g->pos.x / 10.0f);
        s->vy = -(g->pos.y / 10.0f);
        s->vz = -(g->pos.z / 10.0f);
        s->f52 = g->f3EA;
        s->cb = c031_01E01950;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c031", func_01E00D00_c031);

/* shape c031:01E01950, 289 insns: a raindrop quad in two passes (b004:01E01A00 style): with lit 0 it sets up the
   packet (rect 0x5A frame 1, colours 0x38 top and 0x3C bottom, scene texture 0xC4); otherwise it builds the scene
   matrix at the player's point, and draws a 20 x 20 quad 30 deep at the drop's corner picked by 0x52 (0..3), three
   times, depth in 0x3C4 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c031_01E01950;

typedef struct {
    Rgbaq_c031_01E01950 c;
    u64 st;
    u64 xyz;
} Vtx_c031_01E01950;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c031_01E01950 v[4];
} Pkt_c031_01E01950;

typedef struct {
    f32 x, y;
    u8 pad8[0x30];
    u8 col[4];
    u8 col2[4];
    u8 pad40[0x12];
    s16 corner;
} Drop_c031_01E01950;

typedef struct {
    u8 pad0[0xC4];
    s32 tex;
    u8 padC8[0x2B0];
    s32 ot;
    u8 pad37C[0x48];
    f32 depth;
} Scene_c031_01E01950;

static void func_01E01950_c031(Scene_c031_01E01950 *g, Drop_c031_01E01950 *o, Pkt_c031_01E01950 *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c031_01E01950 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern s32 func_001F5380(void);
    extern void func_00106DD0(void *, f32, f32, f32);
    Vec4f q[4];
    f32 rm[4];
    f32 m[16];
    f32 m2[16];
    s32 rot[4];
    Vec4f pos;
    Vec4f pt;
    s32 i;
    s32 j;

    if (lit == 0) {
        func_00106080(rm, 0x5A, 1, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = 0x421421421421ULL;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0xB0 << 32) | 0x48);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        pos = *(Vec4f *)func_001F9D30(0);
        func_0020EB40(m);
        func_00205C40((s32)rot);
        func_001F5BD0(func_001F5380(), &pt);
        pos.x = pt.x;
        pos.y = pt.y;
        pos.z = pt.z;
        func_0020C940(m2, 0, rot, &pos);
        func_0020BC00(m, m2);
        func_00106DD0(&pos, 0.0f, 10.0f, 0.0f);
        for (i = 0; i < 1; i++) {
            if (o->corner == 0) {
                q[0].x = o->x + -20.0f;
                q[0].y = pos.y + (o->y + 20.0f);
                q[1].x = o->x;
                q[1].y = pos.y + (o->y + 20.0f);
                q[2].x = o->x + -20.0f;
                q[2].y = o->y + pos.y;
                q[3].x = o->x;
                q[3].y = o->y + pos.y;
            } else if (o->corner == 1) {
                q[0].x = o->x + 20.0f;
                q[0].y = pos.y + (o->y + 20.0f);
                q[1].x = o->x;
                q[1].y = pos.y + (o->y + 20.0f);
                q[2].x = o->x + 20.0f;
                q[2].y = o->y + pos.y;
                q[3].x = o->x;
                q[3].y = o->y + pos.y;
            } else if (o->corner == 2) {
                q[0].x = o->x + -20.0f;
                q[0].y = pos.y + (o->y + -20.0f);
                q[1].x = o->x;
                q[1].y = pos.y + (o->y + -20.0f);
                q[2].x = o->x + -20.0f;
                q[2].y = o->y + pos.y;
                q[3].x = o->x;
                q[3].y = o->y + pos.y;
            } else if (o->corner == 3) {
                q[0].x = o->x + 20.0f;
                q[0].y = pos.y + (o->y + -20.0f);
                q[1].x = o->x;
                q[1].y = pos.y + (o->y + -20.0f);
                q[2].x = o->x + 20.0f;
                q[2].y = o->y + pos.y;
                q[3].x = o->x;
                q[3].y = o->y + pos.y;
            }
            q[0].z = 30.0f;
            q[2].z = 30.0f;
            q[3].z = 30.0f;
            q[1].z = 30.0f;
            for (j = 0; j < 3; j++) {
                if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
                    func_002075F0(p, g->ot, (u32)g->depth);
                }
            }
        }
    }
}
