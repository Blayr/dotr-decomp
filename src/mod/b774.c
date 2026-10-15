#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00080_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E009D0_b774);

/* shape b774:01E00E50, 78 insns: on start 0x38 = 30, one random roll thrown away, colour blue, random rotation; alpha
   grows by 12 for 10 ticks, then fades by 9 and stops; 0x38 counts up; the position follows the game's float point
   at 0x610 */

typedef struct {
    u8 pad0[0x610];
    f32 pos[3];
} Game_b774_01E00E50;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b774_01E00E50;

static s32 func_01E00E50_b774(Game_b774_01E00E50 *g, Fx_b774_01E00E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 30;
        func_0019A5C8();
        func_001076F0(o->col, 0, 0, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] += 12;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f38++;
    o->tick++;
    o->x = g->pos[0];
    o->y = g->pos[1];
    o->z = g->pos[2];
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00F90_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E011C0_b774);

/* shape b774:01E014A0, 75 insns: an orange tumbling glow at three random turns, growing 5 a tick up to 100 and turning 12: in by 24 for 4 ticks; past size 30 out by 9, and ends */

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
} Glow_b774_01E014A0;

static s32 func_01E014A0_b774(s32 arg0, Glow_b774_01E014A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x80, 0x40, 0x20);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->kind = 0;
        o->f38 = 0;
        o->mode = 2;
    }
    if (o->tick < 4) {
        o->col[3] += 0x18;
    }
    if (o->f38 > 30) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->f38 < 100) {
        o->f38 += 5;
    }
    o->tick++;
    o->ang += 12;
    return 0;
}

/* shape b774:01E015D0, 97 insns: on start random rotation, variant 0, alpha 0; alpha grows by 6 (below 0x40) for 10
   ticks; the colour flickers red; 0x38 from the game float 0x36F8 and the position from the game point 0x610; fades by
   9 and stops while the game counter 0x36D0 is below 0x1E */

typedef struct {
    u8 pad0[0x610];
    f32 pos[3];
    u8 pad61C[0x36D0 - 0x61C];
    s32 count;
    u8 pad36D4[0x24];
    f32 f36F8;
} Game_b774_01E015D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b774_01E015D0;

static s32 func_01E015D0_b774(Game_b774_01E015D0 *g, Fx_b774_01E015D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f34 = 0;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x40) {
            o->col[3] += 6;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0x10, 0x20);
    } else {
        func_001076F0(o->col, 0x5F, 0x10, 0x20);
    }
    o->f38 = g->f36F8;
    o->x = g->pos[0];
    o->y = g->pos[1];
    o->z = g->pos[2];
    if (g->count < 0x1E) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* OVL_WARM */

/* shape b774:01E01760, 85 insns: a purple glow at three random turns sitting on the scene point (ctx+0x610) for its first 4 ticks, sized by the scene value (ctx+0x36F8): in by 80 up to 0x50 on its first tick; its angle sweeps 8 a tick from 90 and it ends at 270 */

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
} Glow_b774_01E01760;

typedef struct {
    u8 pad[0x610];
    f32 x, y, z;
    u8 pad61C[0x36F8 - 0x61C];
    f32 size;
} Game_b774_01E01760;

static s32 func_01E01760_b774(Game_b774_01E01760 *g, Glow_b774_01E01760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x3F, 0x10, 0x30);
    if (o->mode == 1) {
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->kind = 0;
        o->h30 = 90;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 1) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x50;
        }
    }
    o->f38 = g->size;
    if (o->tick < 4) {
        o->h0 = g->x;
        o->h2 = g->y;
        o->h4 = g->z;
    }
    o->tick++;
    if (o->h30 < 270) {
        o->h30 += 8;
    } else {
        o->mode = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E018C0_b774);

/* shape b774:01E01B70, 87 insns: a green spark (size 1, random frame 0..3) at two random angles and three random turns: alpha 0x18 for 10 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[2];
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
} Glow_b774_01E01B70;

static s32 func_01E01B70_b774(s32 arg0, Glow_b774_01E01B70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->kind = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0, 0xFF, 0);
        func_001076F0(o->col2, 0, 0xFF, 0);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x18;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b774:01E01CD0, 87 insns: second colour (0x20, 0x10, 0x10); on start the rotation faces the model angle side
   (-0x4000 or -0xC000, 0, 0x3800), 0x24 = 0, size 0x5A, second alpha 0; it grows by 0x40 (below 0x80) for 2 ticks,
   then fades by 5 and stops; 0x28 = 10 + the game float 0x36F4; the size grows by 8 up to 0xA0 */

typedef struct {
    u8 pad0[0x36F4];
    f32 v;
} Game_b774_01E01CD0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[4];
    s16 size;
    s16 tick;
    s16 f24;
    s16 mode;
    s16 f28;
    u8 pad2A[2];
    u8 col2[4];
} Fx_b774_01E01CD0;

static s32 func_01E01CD0_b774(Game_b774_01E01CD0 *g, Fx_b774_01E01CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 ang[4];

    func_001076F0(o->col2, 0x20, 0x10, 0x10);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), ang);
        if ((s32)(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->f24 = 0;
        o->size = 0x5A;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->f28 = 10.0f + g->v;
    o->tick++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E01E30_b774);

/* shape b774:01E02080, 55 insns: volume fade by game state (b058:01E017A0 shape): state at 0x36D0 limit 0x1E, down 10
   to 0x30, up 10 capped at 0x80; state 2 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0x36D0];
    s32 state;
} Game_b774_01E02080;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b774_01E02080;

static s32 func_01E02080_b774(Game_b774_01E02080 *g, Fade_b774_01E02080 *o) {
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
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    if (g->state == 2) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b774:01E02160, 31 insns: func_001F7170(3, 0, &a, &b, 0) with copies of the module's floats at 0x01E04880 and
   0x01E04888; when the game value at 0x371E is 0x3A the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b774_01E02160;

typedef struct {
    u8 pad0[0x371E];
    s16 v;
} Game_b774_01E02160;

typedef struct {
    u8 pad0[0x36];
    s16 f;
} Fx_b774_01E02160;

extern F_b774_01E02160 D_01E04880_b774;
extern F_b774_01E02160 D_01E04888_b774;

static s32 func_01E02160_b774(Game_b774_01E02160 *g, Fx_b774_01E02160 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b774_01E02160 a;
    F_b774_01E02160 b;

    a = D_01E04880_b774;
    b = D_01E04888_b774;
    func_001F7170(3, 0, &a, &b, 0);
    if (g->v == 0x3A) {
        o->f = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E021E0_b774);

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

static void func_01E02430_b774(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02610_b774);

/* shape b774:01E02D50, 72 insns: twin of b046:01E03E20: take the first free slot of the 170-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3716 and the two arguments; returns 1 if a
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
} Slot_b774_01E02D50;

typedef struct {
    u8 pad[0x40];
    u8 m[0x620];
    Slot_b774_01E02D50 s[170];
    u8 pad30E0[0x5F4];
    u8 r, g, b, a;
    u8 pad36D8[0x3E];
    s16 v;
} Pool_b774_01E02D50;

static s32 func_01E02D50_b774(Pool_b774_01E02D50 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b774_01E02D50 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 170; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 170;
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

/* shape b774:01E02E70, 59 insns: takes the first free of 30 effect slots (0x30 bytes, b108:01E02FF0 family), colours it
   from the context, places it at the context's position and copies the context's frame */

typedef struct {
    u8 pad0[0x20];
    s16 f20;
    u8 pad22[4];
    s16 used;
    u8 pad28[4];
    u8 c2C[4];
} Slot_b774_01E02E70;

typedef struct {
    u8 pad0[0x40];
    f32 pos[3];
    u8 pad4C[0x30E0 - 0x4C];
    Slot_b774_01E02E70 slots[0x1E];
    u8 pad[0x36D4 - 0x30E0 - 0x1E * 0x30];
    u8 rgba[4];
    u8 pad36D8[0x3E];
    s16 f3716;
} Ctx_b774_01E02E70;

static s32 func_01E02E70_b774(Ctx_b774_01E02E70 *ctx) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b774_01E02E70 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1E; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x30);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x1E;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2C, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c2C[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->f20 = ctx->f3716;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02F60_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03370_b774);

/* shape b774:01E036C0, 103 insns: mode 0 sets the drawing state (a 0x9C matrix from its angle 0x34, colour, the scene
   texture 0x10C); otherwise draws the effect as a camera-facing square of its size 0x38: camera rotation, world matrix at its position offset by
   a tenth of 0x8..0xC, then func_00108F90 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b774_01E036C0;

typedef struct {
    u8 pad0[0x10C];
    s32 tex;
} Scene_b774_01E036C0;

static void func_01E036C0_b774(Scene_b774_01E036C0 *g, Fx_b774_01E036C0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x9C, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x + o->dx / 10;
        pos.y = o->y + o->dy / 10;
        pos.z = o->z + o->dz / 10;
        func_00108EF0(m, 0, rot, &pos);
        func_00108CE0(quad, o->size, o->size);
        func_00108F90(quad, p, m, v);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03860_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03BB0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03E90_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E041D0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E04530_b774);
