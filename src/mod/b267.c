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

static void func_01E00080_b267(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E00260_b267);

/* shape b194:01E00C60, 134 insns, 2 copies: a violet wisp (b018:01E01F60 twin): set up once (random heading, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18, its frame every third up to 7; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x3E34];
    u8 trig[1];
} World_b194_01E00C60;

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
} Wisp_b194_01E00C60;

static s32 func_01E00860_b267(World_b194_01E00C60 *w, Wisp_b194_01E00C60 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E00A80_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E00BF0_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E00E50_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E00F90_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01260_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01500_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01610_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01740_b267);

/* shape b194:01E01A20, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3DD0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3DD0];
    s32 state;
} Game_b194_01E01A20;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b194_01E01A20;

static s32 func_01E01820_b267(Game_b194_01E01A20 *g, Fade_b194_01E01A20 *o) {
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

static s32 func_01E018E0_b267(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03D00_b267;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03D08_b267;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01930_b267);

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E01B20_b267(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b267:01E01DC0, 41 insns: look up the textures: group 4 cells 0-4, group 4 cells 14-15, group 5
   cells 0-1 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x320];
    s32 tex[16];
    u8 pad360[0x3A40];
    s32 tex5[2];
} Scene_b267_01E01DC0;

static void func_01E01DC0_b267(s32 arg0, Scene_b267_01E01DC0 *o) {
    s32 i;

    for (i = 0; i < 5; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 2; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E01E70_b267);

/* shape b267:01E02530, 74 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3E2A and 0x3E22 and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b267_01E02530;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x204];
    Slot_b267_01E02530 s[220];
    u8 pad3BD4[0x200];
    u8 r, g, b, a;
    u8 pad3DD8[0x4A];
    s16 w;
    u8 pad3E24[0x6];
    s16 v;
} Pool_b267_01E02530;

static s32 func_01E02530_b267(Pool_b267_01E02530 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b267_01E02530 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E02660_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E028D0_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E02C70_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E02F20_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E033C0_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E03830_b267);

INCLUDE_ASM("asm/nonmatchings/mod/b267", func_01E03A80_b267);
