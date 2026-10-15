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

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E00800_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E00970_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01230_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E013B0_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01530_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01690_b378);

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01910_b378);

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

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E01B80_b378);

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
