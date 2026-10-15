#include "common.h"

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b490(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E00920_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E00BF0_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E00D90_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E00E90_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E01080_b490);

typedef struct {
    u8 r, g, b, a;
} Col_b361_01E01040;

typedef struct {
    u8 pad00[0x50];
    s16 h50;
    u8 pad52[6];
    s16 h58;
    u8 pad5A[9];
    u8 b63;
} Obj_b361_01E01040;

extern Col_b361_01E01040 D_01E02E00_b490;
extern Col_b361_01E01040 D_01E02E08_b490;

static s32 func_01E01160_b490(s32 unused, Obj_b361_01E01040 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    Col_b361_01E01040 c0;
    Col_b361_01E01040 c1;

    *(f32 *)(u32)&c0 = *(f32 *)(u32)&D_01E02E00_b490;
    *(f32 *)(u32)&c1 = *(f32 *)(u32)&D_01E02E08_b490;
    if (o->h58 == 1) {
        o->h50 = 0;
        o->b63 = 0;
    }
    if (o->h50 == 0) {
        if (o->b63 < 0xC0) {
            o->b63 += 0x1E;
        } else {
            o->h50 = 1;
        }
    } else {
        if (o->b63 > 0x40) {
            o->b63 -= 0x1E;
        } else {
            o->h50 = 0;
        }
    }
    c0.b = o->b63;
    c1.b = o->b63;
    c0.g = o->b63;
    c1.g = o->b63;
    c0.r = o->b63;
    c1.r = o->b63;
    func_001F7170(3, 1, &c0, &c1, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E01260_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E01D50_b490);

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E020F0_b490);

/* shape b490:01E02670, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x136 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b490_01E02670 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b490_01E02670;

typedef struct Obj_b490_01E02670 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2e0 - 0x250 - 12];
    Slot_b490_01E02670 slots[0x136];
    u8 padB[0x8b04 - 0x2e0 - 0x136 * 0x70];
    u8 rgba[4];
    u8 padC[0x8b50 - 0x8b04 - 4];
    s16 fB2B0;
} Obj_b490_01E02670;

static s32 func_01E02670_b490(Obj_b490_01E02670 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b490_01E02670 *s = NULL;
    s16 i;

    for (i = 0; i < 0x136; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x136;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b490 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b361_01E022E0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b361_01E022E0_unused;

typedef struct Obj_b361_01E022E0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b361_01E022E0;

typedef struct Xyz_b361_01E022E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b361_01E022E0;

typedef struct Uv_b361_01E022E0 {
    f32 u, v;
} Uv_b361_01E022E0;

typedef struct Pk_b361_01E022E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b361_01E022E0 uv;
    u64 pad18;
    Xyz_b361_01E022E0 v[4];
    u64 pad60[6];
} Pk_b361_01E022E0;

typedef struct Buf_b361_01E022E0 {
    u64 tag;
    Pk_b361_01E022E0 pk;
} Buf_b361_01E022E0;


typedef struct Data_b361_01E022E0 {
    u8 pad0[0x20];
    s32 wh[2];
    u8 padB[0x38];
    Vec4f uv;
} Data_b361_01E022E0;

static void func_01E02800_b490(Obj_b361_01E022E0 *obj, Data_b361_01E022E0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b361_01E022E0 buf;
    Uv_b361_01E022E0 uv;
    Pk_b361_01E022E0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (mode == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (mode == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->uv);
    p->uv = uv;
    func_01E00080_b490((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] = 0x4000;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->wh[0], data->wh[1]);
    func_00109100(view, data->wh, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b361:01E024D0, 126 insns: b018:01E00C50 family: an 18-sector disc of float radius at the object's position */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 radius;
    u8 pad4C[0xE];
    s16 angle;
    u8 pad5C[4];
    s32 tex0;
    s32 tex1;
} Obj_b361_01E024D0;

static void func_01E029F0_b490(u8 *self, Obj_b361_01E024D0 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b490", func_01E02BF0_b490);
