#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00080_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E009D0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00E50_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E00F90_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E011C0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E014A0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E015D0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E01760_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E018C0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E01B70_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E01CD0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E01E30_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02080_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02160_b774);

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

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02E70_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E02F60_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03370_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E036C0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03860_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03BB0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E03E90_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E041D0_b774);

INCLUDE_ASM("asm/nonmatchings/mod/b774", func_01E04530_b774);
