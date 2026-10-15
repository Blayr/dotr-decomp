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

static void func_01E00080_b378(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E00260_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E005E0_b378);

/* shape b378:01E00800, 92 insns: a dark swirl: frame 90, random angle, sinking to -30 by 4; alpha up by 8 to 0xA0 for 20 frames,
   then while the game state is below 20 down by 13 until it ends; past game frame 0x118 it spins up by 0x30 a frame (to 0x600)
   and regrows its frame to 90 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 state;
    u8 pad3BA4[0x5A];
    s16 frame;
} Game_b378_01E00800;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b378_01E00800;

static s32 func_01E00800_b378(Game_b378_01E00800 *g, Obj_b378_01E00800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x1F, 0x1F, 0x1F);
    if (o->state == 1) {
        o->h38 = 0x5A;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 0;
        o->y = 0;
        o->state = 2;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 8;
        }
    } else if (g->state < 0x14) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    if (g->frame > 0x118) {
        if (o->ang < 0x600) {
            o->ang += 0x30;
        }
    }
    if (g->frame > 0x118) {
        if (o->h38 < 0x5A) {
            o->h38 += 4;
        } else {
            o->h38 = 0x5A;
        }
    }
    if (o->y > -0x1E) {
        o->y -= 4;
    }
    o->t++;
    o->ang++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E00970_b378);

/* shape b378:01E01230, 95 insns: a yellow camera-facing glow: turned by the camera's side, size 90 growing by 8 up to 160;
   alpha up by 0x40 for 2 frames, then down by 5 until it ends; fades faster (by 13) once the scene timer drops under 15 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 timer;
} Scene_b378_01E01230;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 size;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E01230;

static s32 func_01E01230_b378(Scene_b378_01E01230 *g, Obj_b378_01E01230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 ang[4];

    func_001076F0(o->c0, 0x20, 0x20, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (func_001A22C0(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->sub = 0;
        o->size = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    if (g->timer < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b378:01E013B0, 95 insns: a red camera-facing glow (b378:01E01230 shape): turned by the camera's side, size 90 growing by 8 up to 160;
   alpha up by 0x40 for 2 frames, then down by 5 until it ends; fades faster (by 13) once the scene timer drops under 15 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 timer;
} Scene_b378_01E013B0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 size;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E013B0;

static s32 func_01E013B0_b378(Scene_b378_01E013B0 *g, Obj_b378_01E013B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 ang[4];

    func_001076F0(o->c0, 0x40, 0, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (func_001A22C0(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->sub = 0;
        o->size = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    if (g->timer < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b378:01E01530, 87 insns: an orange rising spark (b192:01E015D0 family): frame 4 rising by 2, random tilt -0x7000..-0x1001,
   y turn and sub-frame 0..6; alpha up by 0x50 to 0xA0 for 2 frames, then down by 13 past frame 8, and also by 15 while the
   game state is below 10 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 state;
} Game_b378_01E01530;

typedef struct {
    u8 pad0[0x14];
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E01530;

static s32 func_01E01530_b378(Game_b378_01E01530 *g, Obj_b378_01E01530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 4;
        o->rot2 = func_0019A5C8() % 24576 - 0x7000;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 8) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->state < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    func_001076F0(o->c0, 0xFF, 0x80, 0);
    o->t++;
    o->h38 += 2;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01690_b378);

/* shape b378:01E01910, 87 insns: on start 0x38 = 4, random rotation (0x18 -0x2000..0x1FFF, 0x14), variant 0..6; alpha grows
   by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0x14 and by 15 while the game counter at
   0x3BA0 is below 10; colour (0x80, 0x40, 0); 0x38 grows by 2 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 count;
} Game_b378_01E01910;

typedef struct {
    u8 pad0[0x14];
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b378_01E01910;

static s32 func_01E01910_b378(Game_b378_01E01910 *g, Fx_b378_01E01910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 4;
        o->rot18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x14) {
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
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    o->f38 += 2;
    return 0;
}

/* shape b378:01E01A70, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3BA0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3BA0];
    s32 state;
} Game_b378_01E01A70;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b378_01E01A70;

static s32 func_01E01A70_b378(Game_b378_01E01A70 *g, Fade_b378_01E01A70 *o) {
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

static s32 func_01E01B30_b378(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03C00_b378;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03C08_b378;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b378:01E01B80, 98 insns: b001:01E00900 family: draws the grey bar sprite at its own alpha, which fades in by 12 up to 0x60 for 90 ticks, then out by 12 and ends */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b378_01E01B80;

typedef struct {
    Hdr_b378_01E01B80 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b378_01E01B80;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b378_01E01B80;

static s32 func_01E01B80_b378(s32 arg0, Obj_b378_01E01B80 *o) {
    Pkt_b378_01E01B80 p __attribute__((aligned(8)));

    ((Hdr_b378_01E01B80 *)(s32)&p)->count = 0x26;
    ((Hdr_b378_01E01B80 *)(s32)&p)->tag = 5;
    ((Hdr_b378_01E01B80 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b378_01E01B80 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = o->col[3];
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    if (o->tick < 90) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01D10_b378);

/* shape b378:01E02320, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3BFA and the two arguments; returns 1 if a
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
} Slot_b378_01E02320;

typedef struct {
    u8 pad[0x80];
    u8 m[0x254];
    Slot_b378_01E02320 s[220];
    u8 pad39D4[0x1D0];
    u8 r, g, b, a;
    u8 pad3BA8[0x52];
    s16 v;
} Pool_b378_01E02320;

static s32 func_01E02320_b378(Pool_b378_01E02320 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b378_01E02320 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E02440_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E02950_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E02D00_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E03080_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E03450_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E03790_b378);
