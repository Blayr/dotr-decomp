#include "common.h"

/* shape b531:01E01970, 299 insns: b018:01E00920's fragment strip with a count (ctx+0xB8, 20 when 0), a local GS packet,
   UV mode ctx+0xBE, no turn, an upright quad of the object's size moved through three joints (func_00109100 on
   ctx+0xD8); mode 0 draws depth-sorted, 1 pushes all four corners to the far plane and draws at 0, 2 draws at -1 */

typedef struct {
    f32 s;
    f32 t;
} St_b531_01E01970;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u64 pad;
} Xyz_b531_01E01970;

typedef struct {
    u8 pad0[0x20];
    Xyz_b531_01E01970 v[4];
} Pv_b531_01E01970;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b531_01E01970 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
    u8 pad58[0x38];
} Pk_b531_01E01970;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[6];
    Vec4f pos;
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b531_01E01970;

static void func_01E01970_b531(u8 *self, Obj_b531_01E01970 *obj, s32 mode, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100(void *, void *, s32, void *);
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    Pk_b531_01E01970 pkt;
    St_b531_01E01970 uv;
    Pk_b531_01E01970 *pk;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;

    func_00207500();
    pk = (Pk_b531_01E01970 *)(u32)&pkt;
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pkt.st.t = 0;
    pkt.q0 = 0;
    pkt.q1 = 0;
    pkt.q2 = 0;
    pkt.q3 = 0;
    func_00107740(&uv, obj->tex);
    pkt.st = uv;
    func_01E00100_b531((Pk_b003_01E00080 *)pk, (Rect_b003_01E00080 *)(self + 0x94), *(s16 *)(self + 0xBE));
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = *(s16 *)(self + 0xB8) ? *(s16 *)(self + 0xB8) : 20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = *(f32 *)(self + 0x20);
    pos.y = *(f32 *)(self + 0x24);
    pos.z = *(f32 *)(self + 0x28);
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        func_00107070(m, 0, p[obj->tab] / 20.0f * (obj->scale + h));
        func_00107070(m, 1, p[obj->tab + 100] / 20.0f * (obj->scale + h));
        func_00107070(m, 2, p[obj->tab + 180] / 20.0f * (obj->scale + h));
        m[9] = 0.0f;
        m[13] = 0.0f;
        m[8] = -(obj->size >> 1);
        m[12] = obj->size >> 1;
        m[10] = 0.0f;
        m[14] = 0.0f;
        func_00109100(m, &obj->pos, 0, self + 0xD8);
        func_00109100(m, &obj->pos, 1, self + 0xD8);
        func_00109100(m, &obj->pos, 2, self + 0xD8);
        if (mode == 0) {
            if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
                func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
                ((Pv_b531_01E01970 *)pk)->v[0].z = ((Pv_b531_01E01970 *)pk)->v[1].z =
                    ((Pv_b531_01E01970 *)pk)->v[2].z = ((Pv_b531_01E01970 *)pk)->v[3].z = 0xFFFFFF;
                func_002075F0((s32)pk, *(s32 *)(self + 0x80), 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
                func_002075F0((s32)pk, *(s32 *)(self + 0x80), -1);
            }
        }
    }
}
