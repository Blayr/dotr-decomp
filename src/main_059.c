#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020F780);

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FA10);

typedef struct {
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 bit6 : 1;
    u8 bit7 : 1;
} Flags_0020FAF0;

typedef struct {
    u8 *data;
    Flags_0020FAF0 flags4;
    Flags_0020FAF0 flags5;
    u8 pad6[2];
    u8 *src8;
    f32 valueC;
    u8 *src10;
    f32 value14;
    f32 value18;
    f32 value1C;
    s32 value20;
    s32 value24;
    s32 value28;
} Args_0020FAF0;

typedef struct {
    u8 pad0[8];
    s32 offset8;
    s32 sizeC;
    u8 pad10[8];
    s32 offset18;
    s32 size1C;
    u8 pad20[0x34];
    f32 value54;
    s32 value58;
} Data_0020FAF0;

void func_0020FF80(void *);
void func_00210260(void *, void *, void *, f32, f32, f32, f32);
void func_002108C0(void *, void *, f32);
void func_002114B0(void *, void *, f32);
void func_00211F70(void *, void *, void *, s32);
void func_00212170(void *, void *, void *, s32, s32);
void func_00212250(void *, void *, void *, void *, void *);

void func_0020FAF0(void *arg0) {
    Args_0020FAF0 *arg = arg0;
    s32 value24;

    if ((*(s32 *)0x700000D8 + ((*(Data_0020FAF0 **)0x700000DC)->value58 << 8)) > 0x3F10) {
        *(u8 **)0x700000B4 = *(u8 **)0x700000C4;
    } else {
        *(u8 **)0x700000B4 = (u8 *)0x700000F0;
    }

    **(__int128 **)0x700000C4 = *(__int128 *)(arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset8);
    func_0020B380(*(u8 **)0x700000C4 + *(s32 *)0x700000D8,
                 arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset8 + *(s32 *)0x700000D8,
                 ((*(Data_0020FAF0 **)0x700000DC)->sizeC - *(s32 *)0x700000D8) >> 4);
    func_0020FED0(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000C4, 0);
    *(u8 **)0x700000C8 = *(u8 **)0x700000C4 + (*(Data_0020FAF0 **)0x700000DC)->sizeC;

    if ((*(Data_0020FAF0 **)0x700000DC)->size1C > 0) {
        if (arg->flags5.bit3) {
            *(u8 **)0x700000CC = (u8 *)func_0020A0B0((s32)*(u8 **)0x700000C8, 0);
        } else {
            **(s32 **)0x700000C8 = 0x20000000;
            (*(s32 **)0x700000C8)[1] = (s32)(*(u8 **)0x700000C8 + (*(Data_0020FAF0 **)0x700000DC)->size1C + 0x10);
            (*(s32 **)0x700000C8)[2] = 0;
            (*(s32 **)0x700000C8)[3] = 0;
            *(u8 **)0x700000CC = *(u8 **)0x700000C8 + 0x10;
        }
        func_0020B380(*(u8 **)0x700000CC,
                     arg->data + (*(Data_0020FAF0 **)0x700000DC)->offset18,
                     (*(Data_0020FAF0 **)0x700000DC)->size1C >> 4);
        func_0020FED0(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, 1);
        *(u8 **)0x700000D0 = *(u8 **)0x700000CC + (*(Data_0020FAF0 **)0x700000DC)->size1C;
        if (arg->flags5.bit3) {
            *(u8 **)0x700000D0 = (u8 *)func_0020A0B0((s32)*(u8 **)0x700000D0, 1);
        }
    } else {
        *(u8 **)0x700000CC = NULL;
        *(u8 **)0x700000D0 = NULL;
    }

    if (arg->flags4.bit6) {
        value24 = arg->value24;
    } else {
        value24 = -1;
    }
    func_00211F70(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, value24);
    func_00212170(arg->data, *(u8 **)0x700000C4, *(u8 **)0x700000CC, !arg->flags4.bit5, arg->value20);
    if (arg->flags4.bit7 || arg->flags5.bit0 || arg->flags5.bit1) {
        func_00212250(*(u8 **)0x700000C4,
                     *(u8 **)0x700000C4 + (*(Data_0020FAF0 **)0x700000DC)->sizeC,
                     *(u8 **)0x700000CC,
                     *(u8 **)0x700000CC + (*(Data_0020FAF0 **)0x700000DC)->size1C,
                     arg);
    }
    *(s32 *)0x700000B8 = arg->value28;
    if (!arg->flags4.bit2) {
        func_0020FF80(arg->data);
    } else {
        *(s32 *)0x700000B0 = 0;
        *(f32 *)0x700000BC = (*(Data_0020FAF0 **)0x700000DC)->value54;
        if (arg->flags4.bit3) {
            func_00210260(arg->data, arg->src8 + 0xC, arg->src10 + 0xC,
                         arg->valueC, arg->value14, arg->value18, arg->value1C);
        } else if (arg->flags4.bit4) {
            func_002108C0(arg->data, arg->src8 + 0xC, arg->valueC);
        } else {
            func_002114B0(arg->data, arg->src8 + 0xC, arg->valueC);
        }
    }
}

typedef struct Header_0020FED0 {
    u8 pad[0x30];
    s32 offset0;
    s32 pad34;
    s32 offset1;
} Header_0020FED0;

void func_0020FED0(void *arg0, void *arg1, void *arg2, s32 arg3) {
    Header_0020FED0 *header;
    s32 i;
    s32 value;
    s32 *table;
    s32 *entry;
    s32 tagged;

    header = (Header_0020FED0 *)((u8 *)arg0 + 0x10);
    if (arg3 != 0) {
        table = (s32 *)((u8 *)arg0 + header->offset1);
    } else {
        table = (s32 *)((u8 *)arg0 + header->offset0);
    }
    for (i = 0; (value = *table) != -1; i++) {
        switch (value & ~0x0FFFFFFF) {
        case 0x20000000:
        case 0x40000000:
            entry = (s32 *)((u32)arg2 + (value & 0x0FFFFFFF));
            tagged = *entry;
            switch (tagged & ~0x0FFFFFFF) {
            case 0x20000000:
            case 0x40000000:
                *entry = (u32)arg1 + (tagged & 0x0FFFFFFF);
                break;
            }
            break;
        }
        table++;
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_0020FF80);

typedef struct Vec3_00210010 {
    f32 x, y, z;
} Vec3_00210010;

typedef struct Node_00210010 {
    Vec3_00210010 scale;
    u16 flags;
    u16 matrix;
    Vec3_00210010 rotation;
    u32 child;
    Vec3_00210010 translation;
    u32 next;
} Node_00210010;

typedef struct Model_00210010 {
    u8 pad0[0x90];
    u8 *nodes;
    u8 pad94[0x20];
    f32 (*matrices)[4];
} Model_00210010;

typedef struct Entry_00210010 {
    s32 id;
    s32 active;
    u8 pad8[8];
    f32 matrix[16];
} Entry_00210010;

extern Vec3_00210010 D_00295080;
extern u32 D_0032A728;
extern s32 D_0032A770;

void func_0020DB20(void);
void func_0020DBE0(void *, void *, void *);
void func_0020DB00(void *);
void func_0020CB20(void *, void *);
void func_0020BAD0(void *);
void func_0020DB80(void);

void func_00210010(void *arg0, void *arg1, void *arg2) {
    extern Entry_00210010 D_0032A780[];
    u8 buffer[0x20];
    Vec3_00210010 translation;
    Vec3_00210010 *scale;
    s32 flags;
    s32 mode;
    f32 *matrix;
    s32 matrixIndex;
    Entry_00210010 *entry;
    u32 i;
    u32 offset;
    Model_00210010 *model = arg0;
    Vec3_00210010 *parentScale = arg2;

    scale = (Vec3_00210010 *)(((u32)buffer + 15) & ~15);
    for (;;) {
        func_0020B380(scale, parentScale, 1);
        flags = ((Node_00210010 *)arg1)->flags;
        mode = flags & 3;
        if (mode != 3) {
            translation = D_00295080;
            translation.x = ((Node_00210010 *)arg1)->translation.x * parentScale->x;
            translation.y = ((Node_00210010 *)arg1)->translation.y * parentScale->y;
            translation.z = ((Node_00210010 *)arg1)->translation.z * parentScale->z;
            func_0020DB20();
            func_0020DBE0(NULL, (flags & 2) ? NULL : &((Node_00210010 *)arg1)->rotation,
                         (flags & 1) ? NULL : &translation);
        }
        if (!(flags & 4)) {
            scale->x *= ((Node_00210010 *)arg1)->scale.x;
            scale->y *= ((Node_00210010 *)arg1)->scale.y;
            scale->z *= ((Node_00210010 *)arg1)->scale.z;
        }
        matrixIndex = ((Node_00210010 *)arg1)->matrix;
        if (matrixIndex != 0) {
            matrix = model->matrices[matrixIndex];
            func_0020DB00(matrix);
            func_0020CB20(matrix, scale);
        }
        entry = D_0032A780;
        for (i = 0; i < D_0032A728; entry++, i++) {
            if (D_0032A770 == entry->id) {
                D_0032A780[i].active = 1;
                func_0020BAD0(D_0032A780[i].matrix);
                break;
            }
        }
        D_0032A770++;
        offset = ((Node_00210010 *)arg1)->child;
        if (offset != 0) {
            func_00210010(model, model->nodes + (offset & 0x0FFFFFFF), scale);
        }
        if (mode != 3) {
            func_0020DB80();
        }
        offset = ((Node_00210010 *)arg1)->next;
        if (offset == 0) {
            break;
        }
        arg1 = model->nodes + (offset & 0x0FFFFFFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00210260);

typedef f32 Vec4_00210310[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00210310 v;
} Quad_00210310;

typedef struct {
    f32 v[4];
} Plain4_00210310;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00210310 pos;
} Node_00210310;

typedef struct {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    u8 pad30[0x60];
    u8 *base90;
    u8 *tbl94;
    f32 f98;
    s32 cnt9C;
    u8 *tblA0;
    f32 fA4;
    f32 fA8;
    f32 fAC;
    u32 flagsB0;
    u8 *ptrB4;
    Plain4_00210310 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00210310;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00210310;

extern u32 D_0032A728;
extern s32 D_0032A770;

void func_0020B340(void *, void *, s32);
void func_0020BAD0(void *);
void func_0020CB20(void *, void *);
void func_0020DB00(void *);
void func_0020DB20(void);
void func_0020DB80(void);
void func_0020DBE0(void *, void *, void *);
s32 func_0020EDE0(void *, f32);
s32 func_002106E0(void *, void *, u16, void *, void *, void *, f32, f32, f32, f32, f32);

s32 func_00210310(void *arg0, s32 depth, void *arg2) {
    extern Slot_00210310 D_0032A780[];
    Spr_00210310 *spr = (Spr_00210310 *)0x70000000;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    u8 *q;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00210310 *node = arg0;

        func_0020B380(vec, arg2, 1);
        flags = node->flags;
        func_0020B380(spr, node, 3);
        if (depth < spr->cnt9C) {
            p = spr->tbl94;
            q = spr->tblA0;
            if (spr->flagsE0 & 4) {
                p += depth * 0x18;
                q += depth * 0x18;
            } else {
                p += depth * 0x10;
                q += depth * 0x10;
            }
            {
                u16 nflags = node->flags;
                f32 *pos = spr->v20;
                f32 *rot = spr->v10;
                f32 scale = depth == 0 ? 1.0f : spr->fBC;

                flags = func_002106E0(p, q, nflags, pos, rot, spr, spr->f98, spr->fA8, spr->fA4, spr->fAC, scale);
            }
            if (depth == 0 && (spr->flagsE0 & 4)) {
                func_0020B340(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00210310 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= ((f32 *)arg2)[0];
            spr->v20[1] *= ((f32 *)arg2)[1];
            spr->v20[2] *= ((f32 *)arg2)[2];
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
            *(Quad_00210310 *)spr->v20 = node->pos;
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
            depth = func_00210310(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
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

INCLUDE_ASM("asm/nonmatchings/main_059", func_002106E0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002108C0);

typedef f32 Vec4_00210940[4] __attribute__((aligned(16)));

typedef struct {
    Vec4_00210940 v;
} Quad_00210940;

typedef struct {
    f32 v[4];
} Plain4_00210940;

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u16 idx;
    u8 pad10[0xC];
    u32 child;
    u8 pad20[0xC];
    u32 sibling;
    Quad_00210940 pos;
} Node_00210940;

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
    Plain4_00210940 *outB8;
    f32 fBC;
    u8 padC0[0x20];
    u16 flagsE0;
} Spr_00210940;

typedef struct {
    s32 id;
    s32 used;
    u8 pad8[8];
    u8 data[0x40];
} Slot_00210940;

extern u32 D_0032A728;
extern s32 D_0032A770;

void func_0020B340(void *, void *, s32);
void func_0020BAD0(void *);
void func_0020CB20(void *, void *);
void func_0020DB00(void *);
void func_0020DB20(void);
void func_0020DB80(void);
void func_0020DBE0(void *, void *, void *);
s32 func_0020EDE0(void *, f32);
s32 func_00210CF0(void *, u16, f32, void *, void *, void *, f32);

s32 func_00210940(void *arg0, s32 depth, void *arg2) {
    extern Slot_00210940 D_0032A780[];
    Spr_00210940 *spr = (Spr_00210940 *)0x70000000;
    u8 buf[32];
    f32 *vec = (f32 *)(((s32)buf + 0xF) & ~0xF);
    u32 flags;
    s32 mode;
    u8 *p;
    f32 f;
    f32 max;
    u32 i;

    for (;;) {
        Node_00210940 *node = arg0;

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
            flags = func_00210CF0(p, node->flags, spr->f98, spr->v20, spr->v10, spr,
                                  depth == 0 ? 1.0f : spr->fBC);
            if (depth == 0 && (spr->flagsE0 & 4)) {
                func_0020B340(spr, node, 3);
            }
        }
        if (depth == 0) {
            if (spr->outB8 != NULL) {
                *spr->outB8 = *(Plain4_00210940 *)spr->v20;
            }
        }
        mode = flags & 3;
        depth++;
        if (mode != 3) {
            spr->v20[0] *= ((f32 *)arg2)[0];
            spr->v20[1] *= ((f32 *)arg2)[1];
            spr->v20[2] *= ((f32 *)arg2)[2];
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
            *(Quad_00210940 *)spr->v20 = node->pos;
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
            depth = func_00210940(spr->base90 + (node->child & 0x0FFFFFFF), depth, vec);
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

void func_00212D70(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    if (var_s0 < arg2) {
        var_s1 = arg0;
        do {
            func_0020BCF0(var_s1, arg1);
            var_s0 += 1;
            var_s1 += 0x70;
        } while (var_s0 < arg2);
    }
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DE0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00212DF0);

s32 func_00212E60(s32 arg0, void *arg1) {
    u32 i;
    s32 *state;
    s32 offset;
    void *payload;
    Slot_00211530 *record;
    u8 temporary[0x40];

    if ((D_0032A728 == 0) || (arg0 <= 0) || (arg1 == NULL)) {
        return 0;
    }
    record = D_0032A780;
    for (i = 0; i < D_0032A728; record++, i++) {
        if (arg0 == record->id) {
            offset = i * 0x50;
            state = (s32 *)(D_0032A784 + offset);
            if (*state == -1) {
                return 0;
            }
            if (*state == 1) {
                *state = 0;
                func_00198790(temporary, D_0032A730, 0x40);
                payload = (u8 *)D_0032A780 + offset + 0x10;
                func_0020BC00((s32)temporary, payload);
                func_00198790(payload, temporary, 0x40);
            }
            if (*state == 0) {
                func_00198790(arg1, (u8 *)D_0032A780 + offset + 0x10, 0x40);
            }
            break;
        }
    }
    if (i == D_0032A728) {
        return 0;
    }
    return 1;
}

u8 *func_00212FD0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *temp_s1;
    u8 *temp_v0;

    func_002130A0(arg3);
    *(s32 *)(arg0 + 0) = 0x10000002;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 8) = 0x11000000;
    *(s32 *)(arg0 + 0xC) = 0x51000002;
    *(s64 *)(arg0 + 0x10) = 0x1000000000008001LL;
    *(s64 *)(arg0 + 0x18) = 0xE;
    *(s64 *)(arg0 + 0x20) = 0x73;
    temp_s1 = arg0 + 0x30;
    *(s64 *)(arg0 + 0x28) = 0;
    temp_v0 = func_002131D0(temp_s1, arg1, arg2);
    if (temp_v0 == NULL) {
        return arg0;
    }
    func_00213D00(temp_s1, temp_v0);
    func_00213F10(temp_s1, temp_v0);
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_002130A0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002131D0);

s32 func_00213410(s32 arg0, u32 cursor, s32 size) {
    u32 end = cursor + size;
    u32 *scratchpad = (u32 *)0x70000000;
    u32 packet;

    if (cursor < end) {
        do {
        packet = cursor;
        if (!(*(u32 *)(cursor + 0xC) & 0x8000)) {
            arg0 = func_002134D0(arg0, (s32 *)cursor);
        } else {
            arg0 = func_002138D0(arg0, (s32 *)cursor);
        }
        cursor = scratchpad[0x3F];
        if (*(u32 *)(packet + 4) & 0x8000) {
            cursor += 4;
        }
        while (*(s32 *)cursor == 0) {
            cursor += 4;
        }
        } while (cursor < end);
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_002134D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213680);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002138D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213A40);

INCLUDE_ASM("asm/nonmatchings/main_059", func_00213D00);

void func_00213F10(u8 *start, u8 *end) {
    s32 *field;
    s32 previous;
    s32 value;
    u8 *cursor;

    cursor = start;
    previous = 0;
    if (cursor < end) {
        do {
            field = (s32 *)(cursor + 4);
            value = *field;
            if (value == previous) {
                *(s32 *)(cursor + 0) = 0x10000000;
                *field = 0;
                *(s32 *)(cursor + 8) = 0;
                *(s32 *)(cursor + 0xC) = 0;
            } else {
                previous = value;
            }
            cursor += 0x80;
        } while (cursor < end);
    }
}

void func_00213F60(s32 arg0, s32 arg1) {
    D_0032F780 = arg0;
    D_0032F784 = arg1;
    D_0032F78C = arg1;
    D_0032F788 = 1;
}

void func_00213F90(void) {
    func_00209D30(func_00213FC0(func_00209D20()));
}

typedef struct {
    s32 key;
    s32 value;
} Record_00213FC0;

typedef struct {
    s32 *output;
    Record_00213FC0 *end;
    s32 ready;
    Record_00213FC0 *begin;
} State_00213FC0;

void func_0020B840(void *, s32, s32, s32 (*)(s32 *, s32 *));

s32 func_00213FC0(s32 arg0) {
    State_00213FC0 *state = (State_00213FC0 *)&D_0032F780;
    s32 *output = (s32 *)arg0;
    Record_00213FC0 *record;

    if (D_0032F78C == D_0032F784) {
        return arg0;
    }

    func_0020B840(state->begin, state->end - state->begin, 8, func_00214080);
    for (record = state->begin; record < state->end; record++) {
        output[0] = 0x50000000;
        output[1] = record->value;
        output[2] = 0;
        output[3] = 0;
        output += 4;
    }

    state->output = output;
    state->begin = state->end;
    state->ready = 1;
    return (s32)output;
}

s32 func_00214080(s32 *arg0, s32 *arg1) {
    return *arg0 - *arg1;
}

typedef struct Flags_00214090 {
    u8 unused : 7;
    u8 enabled : 1;
} Flags_00214090;

typedef struct Header_00214090 {
    s32 magic;
    u8 padding[0xC];
    u16 count;
    u8 unknown;
    Flags_00214090 flags;
    u32 data;
    u32 extra;
} Header_00214090;

s32 func_00214090(void *arg0) {
    Header_00214090 *header = arg0;

    if (header->magic != 0x1A544F4D) {
        return 0;
    }
    header->data = (u32)header + header->data;
    header->extra = (u32)header + header->extra;
    func_00214100((void *)header->data, (s32)header, header->count, header->flags.enabled);
    return 1;
}

s32 func_00214100(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_v0_2;

    if (arg3 != 0) {
        *(s32 *)((u8 *)arg0 - 4) = arg1 + *(s32 *)((u8 *)arg0 - 4);
    }
    temp_v1 = *(u16 *)((u8 *)arg0 + 8) & 0x3F;
    if (temp_v1 == 3) {
        temp_v0 = *(s32 *)arg0;
        if (temp_v0 != 0) {
            *(s32 *)arg0 = arg1 + temp_v0;
            func_00214190((u8 *)*(s32 *)arg0, arg1, arg2, arg3);
        }
    } else if (temp_v1 == 7) {
        temp_v0_2 = *(s32 *)arg0;
        if (temp_v0_2 != 0) {
            *(s32 *)arg0 = arg1 + temp_v0_2;
            func_00214210((u8 *)*(s32 *)arg0, arg1, arg2, arg3);
        }
    }
    return 1;
}

s32 func_00214190(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 j;
    s32 *p;

    if (arg3 != 0) {
        *(s32 *)(arg0 - 4) = arg1 + *(s32 *)(arg0 - 4);
    }
    for (i = 0; i < arg2; i++) {
        j = 0;
        p = (s32 *)arg0;
        do {
            if (*p != 0) {
                *p = arg1 + *p;
                if (arg3 != 0) {
                    *(s32 *)(*p - 4) = arg1 + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 2);
        arg0 += 0x10;
    }
    return 1;
}

s32 func_00214210(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 j;
    s32 *p;

    if (arg3 != 0) {
        *(s32 *)(arg0 - 4) = arg1 + *(s32 *)(arg0 - 4);
    }
    for (i = 0; i < arg2; i++, arg0 += 0x18) {
        j = 0;
        p = (s32 *)arg0;
        do {
            if (*p != 0) {
                *p = arg1 + *p;
                if (arg3 != 0) {
                    *(s32 *)(*p - 4) = arg1 + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 3);
    }
    return 1;
}

typedef struct Slot_00214290 {
    u32 value : 31;
    u32 flag : 1;
    u32 other : 30;
    u32 type : 2;
} Slot_00214290;

typedef struct Card_00214290 {
    Slot_00214290 slots[9];
    u16 value : 14;
    u16 flag : 1;
    u16 otherFlag : 1;
    s16 count;
} Card_00214290;

typedef struct Deck_00214290 {
    s16 cards[40];
    s16 card;
    s16 count;
} Deck_00214290;

typedef struct Flags_00214290 {
    u8 mode : 2;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 bit4 : 1;
    u8 bit5 : 1;
    u8 unused : 2;
} Flags_00214290;

typedef struct Save_00214290 {
    Card_00214290 cards[0x356];
    s16 values[5];
    u8 padding[2];
    Deck_00214290 decks[3];
    u8 bytes[16];
    union {
        u8 bytes[22];
        struct {
            u8 header[3];
            u8 grid[5][7][7];
        } board;
    } data;
    u8 padding2[4];
    Flags_00214290 flags;
    u8 padding3[3];
} Save_00214290;

void func_00214290(void) {
    extern Save_00214290 D_0032F790[2];
    s32 card;
    s32 slot;
    s32 profile;
    Slot_00214290 *slotPtr;
    Card_00214290 *cardPtr;
    Save_00214290 *save;
    s16 *valuePtr;
    s32 value;
    Deck_00214290 *currentDeck;
    s16 *deckCardPtr;
    u8 *deckBase;
    s32 deck;
    s32 deckCard;
    s32 byte;
    s32 dataByte;
    s32 grid;
    u8 *columnPtr;
    u8 *rowBase;
    u8 *gridBase;
    s32 row;
    s32 column;

    func_0020B3C0((s8 *)D_0032F790, 0, 0x1FF40);
    save = D_0032F790;
    profile = 0;
    do {
        card = 0;
        cardPtr = save->cards;
        do {
            slot = 0;
            slotPtr = cardPtr->slots;
            do {
                slotPtr->value = 0;
                slotPtr->other = 0;
                slotPtr->type = 3;
                slotPtr->flag = 0;
                slot++;
                slotPtr++;
            } while (slot < 9);
            cardPtr->value = 0;
            cardPtr->count = 0;
            cardPtr->flag = 0;
            cardPtr->otherFlag = 0;
            card++;
            cardPtr++;
        } while (card < 0x356);
        value = 0;
        valuePtr = (s16 *)save;
        do {
            valuePtr[0x7EC4] = 999;
            value++;
            valuePtr++;
        } while (value < 5);
        deck = 0;
        deckBase = (u8 *)save;
        do {
            currentDeck = (Deck_00214290 *)(deckBase + 0xFD94);
            deckCard = 0;
            deckCardPtr = currentDeck->cards;
            do {
                *deckCardPtr = 999;
                deckCard++;
                deckCardPtr++;
            } while (deckCard < 40);
            currentDeck->card = 999;
            currentDeck->count = 0;
            deck++;
            deckBase += 0x54;
        } while (deck < 3);
        byte = 0;
        do {
            save->bytes[byte] = 0;
            byte++;
        } while (byte < 16);
        dataByte = 0;
        do {
            save->data.bytes[dataByte] = 0;
            dataByte++;
        } while (dataByte < 22);
        grid = 0;
        gridBase = (u8 *)save;
        do {
            row = 0;
            rowBase = gridBase;
            do {
                column = 0;
                columnPtr = rowBase;
                do {
                    columnPtr[0xFEA3] = 7;
                    column++;
                    columnPtr++;
                } while (column < 7);
                row++;
                rowBase += 7;
            } while (row < 7);
            grid++;
            gridBase += 0x31;
        } while (grid < 5);
        save->flags.mode = 0;
        save->flags.bit2 = 1;
        save->flags.bit3 = 1;
        save->flags.bit4 = 1;
        save->flags.bit5 = 1;
        save++;
        profile++;
    } while (profile < 2);
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145D0);

INCLUDE_ASM("asm/nonmatchings/main_059", func_002145E0);

typedef struct {
    u8 values[9][8];
    u16 id : 14;
    u16 flag1 : 1;
    u16 flag2 : 1;
    s16 count;
} Entry_00214620;

typedef struct {
    s16 values[40];
    s16 active;
    s16 count;
} Deck_00214620;

typedef struct {
    u8 mode : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 unused : 2;
} Flags_00214620;

typedef union {
    u8 zeroes[22];
    struct {
        u8 prefix[3];
        u8 values[5][7][7];
    } map;
} Region_00214620;

typedef struct {
    Entry_00214620 entries[854];
    s16 values[5];
    s16 padding_fd92;
    Deck_00214620 decks[3];
    u8 bytes_fe90[16];
    Region_00214620 region;
    s32 count;
    Flags_00214620 flags;
    u8 padding_ff9d[3];
} State_00214620;

extern u8 D_0034F6D0;

void func_00214620(s32 arg0) {
    extern State_00214620 D_0032F790[2];
    s32 i;
    State_00214620 *state;
    Entry_00214620 *entry;
    s32 j;
    u8 *value;
    s16 *value_base;
    s32 n_values;
    Deck_00214620 *deck;
    s16 *card;
    u8 *deck_base;
    s32 n_decks;
    s32 n_cards;
    s32 n_bytes1;
    s32 n_bytes2;
    s32 n_layers;
    u8 *cell;
    u8 *row;
    u8 *layer;
    s32 n_rows;
    s32 n_cells;

    state = &D_0032F790[D_0034F6D0 == arg0 ? 0 : 1];
    i = 0;
    entry = state->entries;
    do {
        j = 0;
        value = entry->values[0];
        do {
            func_00214FD0(value);
            j++;
            value += 8;
        } while (j < 9);
        entry->id = 0;
        entry->count = 0;
        entry->flag1 = 0;
        entry->flag2 = 0;
        i++;
        entry++;
    } while (i < 854);

    n_values = 0;
    value_base = (s16 *)state;
    do {
        value_base[0x7EC4] = 999;
        n_values++;
        value_base++;
    } while (n_values < 5);

    n_decks = 0;
    deck_base = (u8 *)state;
    do {
        deck = (Deck_00214620 *)(deck_base + 0xFD94);
        n_cards = 0;
        card = deck->values;
        do {
            *card = 999;
            n_cards++;
            card++;
        } while (n_cards < 40);
        deck->active = 999;
        deck->count = 0;
        n_decks++;
        deck_base += 0x54;
    } while (n_decks < 3);

    n_bytes1 = 0;
    do {
        state->bytes_fe90[n_bytes1] = 0;
        n_bytes1++;
    } while (n_bytes1 < 16);

    n_bytes2 = 0;
    do {
        state->region.zeroes[n_bytes2] = 0;
        n_bytes2++;
    } while (n_bytes2 < 22);

    n_layers = 0;
    layer = (u8 *)state;
    do {
        n_rows = 0;
        row = layer;
        do {
            n_cells = 0;
            cell = row;
            do {
                cell[0xFEA3] = 7;
                n_cells++;
                cell++;
            } while (n_cells < 7);
            n_rows++;
            row += 7;
        } while (n_rows < 7);
        n_layers++;
        layer += 49;
    } while (n_layers < 5);
    state->count = 0;
    state->flags.mode = 0;
    state->flags.flag2 = 1;
    state->flags.flag3 = 1;
    state->flags.flag4 = 1;
    state->flags.flag5 = 0;
}

s32 func_00214910(s32 arg0, s32 arg1) {
    if (arg0 < 0 || arg0 >= 51) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= 41) {
        return -1;
    }
    return D_002D0970[arg0][arg1] & 0xFFF;
}

typedef struct {
    u8 entries[0xFD88];
    s16 values[5];
    u8 pad_fd92[0x206];
    s32 count;
    u8 flags;
    u8 pad_ff9d[3];
} State_00214990;

extern s32 D_002D19D8;
extern u16 D_002D49D4[];
extern u8 D_0034F6D0;
void func_002029B0(s32, s32);
s32 func_00215280(s32, s32, s32);

void func_00214990(s32 arg0, s32 arg1) {
    extern State_00214990 D_0032F790[2];
    u16 *deck;
    s32 sum;
    s32 i;
    u16 *src;
    u16 *card;
    u16 value;
    State_00214990 *state;

    state = &D_0032F790[D_0034F6D0 == arg0 ? 0 : 1];
    deck = D_002D0970[arg1];
    if (!(arg1 >= 0 && arg1 < 51)) {
        return;
    }
    func_00214620(arg0);
    if (arg1 < 17) {
        sum = 0;
        src = &D_002D49D4[D_002D19D8] + 2;
        while (1) {
            value = *src;
            sum += value & 0x1FFF;
            if (value & 0x8000) {
                break;
            }
            src++;
        }
        do {
            state->count = (sum + func_0019A5C8()) & 0x7FFFFFFF;
        } while (state->count == 0);
    } else {
        state->count = arg1 + 0x40000000;
    }
    i = 0;
    card = deck;
    do {
        func_00216040(arg0, 0, *card & 0xFFF);
        i++;
        card++;
    } while (i < 41);
    for (i = 0; i < 5; i++) {
        state->values[i] = 999;
    }
    func_002172D0(arg0, *deck & 0xFFF, *deck >> 12);
    func_00215280(arg0, 0, *deck & 0xFFF);
    deck++;
    i = 1;
    do {
        func_002154E0(arg0, 0, *deck & 0xFFF);
        i++;
        deck++;
    } while (i < 41);
    func_002029B0(0, 1);
    func_002029B0(0, 0);
    func_002029B0(1, -1);
}

typedef struct State_00214BB0 {
    u8 pad[0xFF9C];
    u8 unused0 : 2;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 unused5 : 3;
    u8 tail[3];
} State_00214BB0;

void func_00217A70(u64);
extern u8 D_0034F6D0;

s32 func_00214BB0(s32 arg0, s32 arg1, s32 arg2) {
    extern State_00214BB0 D_0032F790[];
    s32 index;
    State_00214BB0 *state;

    if (D_0034F6D0 == arg0) {
        index = 0;
    } else {
        index = 1;
    }
    state = &D_0032F790[index];
    switch (arg1) {
    case 0:
        state->flag2 = arg2 ? 1 : 0;
        break;
    case 1:
        state->flag3 = arg2 ? 1 : 0;
        break;
    case 2:
        state->flag4 = arg2 ? 1 : 0;
        func_00217A70(state->flag4);
        break;
    default:
        return 0;
    }
    return 1;
}

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

void *func_00214DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    typedef struct {
        u32 id : 31;
        u32 active : 1;
        u32 value : 30;
        u32 type : 2;
    } Entry_00214DD0;
    s32 side;
    Entry_00214DD0 *entry;
    s32 count;

    if (arg0 < 0 || arg0 >= 2) {
        return NULL;
    }
    if (arg1 == 0x29F) {
        arg1 = 0x3E7;
    }
    if (arg1 < 0 || arg1 >= 0x356) {
        return NULL;
    }
    if (D_0034F6D0 == arg0) {
        side = 0;
    } else {
        side = 1;
    }
    entry = (Entry_00214DD0 *)((u8 *)D_0032F790 + side * 0xFFA0 + arg1 * 0x4C);
    count = 9;
    while (count--) {
        if (entry->id != 0 && entry->type == arg2 &&
            (entry->active != 0) == (arg3 == 1)) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/main_059", func_00214F00);
