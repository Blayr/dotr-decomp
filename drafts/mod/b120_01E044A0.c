#include "common.h"
#define OVL_LOCAL static
#include "mod/b120.c"

/* shape b120:01E044A0, 144 insns: b045:01E005A0 family: one camera-facing sprite at the context's point obj->idx, far z; calls the module's sprite-UV helper (shape b008:01E00080) as a static function */

typedef struct {
    f32 s;
    f32 t;
} St_b120_01E044A0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u64 pad;
} Vtx_b120_01E044A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b120_01E044A0 st;
    u64 pad18;
    Vtx_b120_01E044A0 v[4];
} Pk_b120_01E044A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 idx;
    u8 pad32[6];
    s16 size;
} Obj_b120_01E044A0;

typedef struct {
    u8 pad0[0x20];
    Vec4f pts[1];
} Ctx_b120_01E044A0;

static void func_01E044A0_b120(u8 *self, Obj_b120_01E044A0 *obj, Pk_b120_01E044A0 *pk) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b120_01E044A0 uv;
    f32 r;

    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->v[0].f = 0;
    pk->v[1].f = 0;
    pk->v[2].f = 0;
    pk->v[3].f = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E002E0_b120((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = ((Ctx_b120_01E044A0 *)self)->pts[obj->idx].x;
    pos.y = ((Ctx_b120_01E044A0 *)self)->pts[obj->idx].y;
    pos.z = ((Ctx_b120_01E044A0 *)self)->pts[obj->idx].z;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        pk->v[0].z = pk->v[1].z = pk->v[2].z = pk->v[3].z = 0xFFFFFF;
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), (u32)depth[0]);
    }
}
