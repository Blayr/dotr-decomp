#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020F780);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FA10);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FAF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FED0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FF80);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210010);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210260);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210310);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002106E0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002108C0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210940);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210CF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002114B0);

typedef f32 Vec4_00211530[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00211530 v;
} Quad_00211530;

typedef struct {
    f32 v[4];
} Plain4_00211530;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00211530 pos;
} Node_00211530;

typedef struct {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x60];
    u8 *base90;
    u8 *tbl94;
    f32 f98;
    s32 cnt9C;
    u8 padA0[0x10];
    u32 flagsB0;
    u8 *ptrB4;
    Plain4_00211530 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00211530;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00211530;

#define PARENT ((f32 *)arg2)

extern u32 D_0032A728;
extern s32 D_0032A770;
extern Slot_00211530 D_0032A780[];

void func_0020B340(void *, void *, s32);
void func_0020B380(void *, void *, s32);
void func_0020BAD0(void *);
void func_0020CB20(void *, void *);
void func_0020DB00(void *);
void func_0020DB20(void);
void func_0020DB80(void);
void func_0020DBE0(void *, void *, void *);
s32 func_0020EDE0(void *, f32);
s32 func_002118F0(void *, s64, u16, void *, void *, void *, f32);

s32 func_00211530(void *arg0, s32 depth, void *arg2) {
    Spr_00211530 *spr = (Spr_00211530 *)0x70000000;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00211530 *node = arg0;

        func_0020B380(vec, arg2, 1);
        flags = node->flags;
        func_0020B380(spr, node, 3);
        if (depth < spr->cnt9C) {
            p = spr->tbl94;
            if (spr->flagsE0 & 4) {
                p += depth * 0x18;
            } else {
                p += depth * 0x10;
            }
            flags = func_002118F0(p, func_001A22C0(spr->f98), node->flags, spr->v20, spr->v10, spr,
                                  depth == 0 ? 1.0f : spr->fBC);
            if (depth == 0 && (spr->flagsE0 & 4)) {
                func_0020B340(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00211530 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= PARENT[0];
            spr->v20[1] *= PARENT[1];
            spr->v20[2] *= PARENT[2];
            func_0020DB20();
            func_0020DBE0(NULL, (flags & 2) ? NULL : spr->v10, (flags & 1) ? NULL : spr->v20);
        }
        if (!(flags & 4)) {
            vec[0] *= spr->v00[0];
            vec[1] *= spr->v00[1];
            vec[2] *= spr->v00[2];
        }
        if (node->idx != 0) {
            p = spr->ptrB4 + node->idx * 0x10;
            func_0020DB00(p);
            func_0020CB20(p, vec);
        }
        if (!(node->flags & 0x8000)) {
            f = node->pos.v[3];
            max = vec[0];
            if (max < vec[1]) {
                max = vec[1];
            }
            if (max < vec[2]) {
                max = vec[2];
            }
            f = f * (spr->fBC * max);
            *(Quad_00211530 *)spr->v20 = node->pos;
            spr->v20[3] = 1.0f;
            func_0020DB20();
            func_0020CB20(NULL, vec);
            spr->flagsB0 |= func_0020EDE0(spr->v20, f);
            func_0020DB80();
        }
        for (i = 0; i < D_0032A728; i++) {
            if (D_0032A770 == D_0032A780[i].id) {
                D_0032A780[i].used = 1;
                func_0020BAD0(D_0032A780[i].data);
                break;
            }
        }
        D_0032A770++;
        if (node->child != 0) {
            depth = func_00211530(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
        }
        if (mode != 3) {
            func_0020DB80();
        }
        if (node->sibling == 0) {
            return depth;
        }
        arg0 = spr->base90 + (node->sibling & 0x0FFFFFFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_002118F0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00211F70);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212170);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212250);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212D70);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DE0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DF0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212E60);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212FD0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002130A0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002131D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213410);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002134D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213680);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002138D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213A40);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213D00);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213F10);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213F60);

void func_00213F90(void) {
    func_00209D30(func_00213FC0(func_00209D20()));
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213FC0);

s32 func_00214080(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214090);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214100);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214190);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214210);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214290);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145E0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214620);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214910);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214990);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214BB0);

typedef struct {
    u8 pad[0xFF9C];
    u8 lo : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 hi : 3;
    u8 pad2[3];
} Side_00214D00;

extern Side_00214D00 D_0032F790[];
extern u8 D_0034F6D0;

s32 func_00214D00(s32 arg0, s32 arg1) {
    Side_00214D00 *side;
    s32 idx;

    if (D_0034F6D0 == arg0) {
        idx = 0;
    } else {
        idx = 1;
    }
    side = &D_0032F790[idx];
    switch (arg1) {
    case 0:
        return side->flag2 ? 1 : 0;
    case 1:
        return side->flag3 ? 1 : 0;
    case 2:
        return side->flag4 ? 1 : 0;
    default:
        return -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214DD0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214F00);
