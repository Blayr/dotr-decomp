#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00080_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00220_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00620_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00870_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E008F0_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E009F0_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00BD0_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00D00_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E00F20_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E010F0_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E01730_b053);

/* shape b053:01E01890, 74 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3B5A and 0x3B54 and the two arguments; returns 1 if a
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
} Slot_b053_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x7D4];
    Slot_b053_01E01890 s[200];
    u8 pad3A54[0xB0];
    u8 r, g, b, a;
    u8 pad3B08[0x4C];
    s16 w;
    u8 pad3B56[0x4];
    s16 v;
} Pool_b053_01E01890;

static s32 func_01E01890_b053(Pool_b053_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b053_01E01890 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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
        s->w = o->w;
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E019C0_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E01E30_b053);

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E01FE0_b053);

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

static void func_01E022F0_b053(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b053", func_01E02490_b053);
