#include "common.h"

/* shape b555:01E00EA0, 180 insns: b046:01E00DD0 family sprite quad with the b016:01E00ED0 depth modes: blend by the mode's high nibble (0x48 / 0x44 / 0x42), size 0x38 square turned by 0x10 through the object table, low nibble 0 = depth, 1 = far z */

typedef struct Cam_b555_01E00EA0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b555_01E00EA0_unused;

typedef struct Obj_b555_01E00EA0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b555_01E00EA0;

typedef struct Xyz_b555_01E00EA0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b555_01E00EA0;

typedef struct Uv_b555_01E00EA0 {
    f32 u, v;
} Uv_b555_01E00EA0;

typedef struct Pk_b555_01E00EA0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b555_01E00EA0 uv;
    u64 pad18;
    Xyz_b555_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b555_01E00EA0;

typedef struct Buf_b555_01E00EA0 {
    u64 tag;
    Pk_b555_01E00EA0 pk;
} Buf_b555_01E00EA0;


typedef struct Data_b555_01E00EA0 {
    u8 pad0[0x10];
    s32 ang[4];
    u8 pad20[8];
    Vec4f f28;
    s16 f38;
} Data_b555_01E00EA0;

static void func_01E00EA0_b555(Obj_b555_01E00EA0 *obj, Data_b555_01E00EA0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b555_01E00EA0 buf;
    Uv_b555_01E00EA0 uv;
    s32 sel;
    s32 md;
    Pk_b555_01E00EA0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = mode >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->f28);
    p->uv = uv;
    func_01E00080_b555((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->f38, data->f38);
    func_00109100(view, data->ang, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        md = mode & 0xF;
        if (md == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (md == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        }
    }
}
