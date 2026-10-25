#include "common.h"

/* shape b112:01E04480, 237 insns: b045:01E00E30 with 12 sprites, scale 0.1 at the object, rot[1] = -(rot[1] / 180) through the 64-bit divide (func_001A0660), y tables a 40th, and z = (table byte / 20, at least 1) * the drop between the self+0xD4 points 0 and 2, a 20th; y is then reset to 0xC * sin(0x30). Was: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b112_01E04480;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b112_01E04480 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b112_01E04480;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b112_01E04480;

static void func_01E00080_b112();

static void func_01E04480_b112(u8 *self, Obj_b112_01E04480 *obj, Pk_b112_01E04480 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b112_01E04480 uv;
    s32 *rp;
    s16 i;
    Vec4f *t;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    u8 k;
    Vec4f *u;
    s64 q;

    func_00207500();
    t = *(Vec4f **)(self + 0xD4);
    u = &t[2];
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b112(pk, self + 0x94, 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, 0, &pos);
    func_00205C40((s32)rot);
    rp = &rot[1];
    q = func_001A0660(*rp, 180);
    *rp = q;
    *rp = -q;
    for (i = 0; i < 12; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 40.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        k = (u8)((u32)((u8 *)p)[obj->tab + 180] / 20);
        if (k == 0) {
            k = 1;
        }
        func_00107070(m, 2, (f32)k * -(u->z - t->z) / 20.0f * (obj->scale + h));
        func_00107070(m, 1, obj->dz * func_00108030(self + 0xD8, obj->scale, 1));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}
