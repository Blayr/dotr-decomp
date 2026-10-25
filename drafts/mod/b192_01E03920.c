#include "common.h"

/* shape b192:01E03920, 177 insns: b361:01E022E0 family sprite draw: blended (0x48) 9-qword packet with the object's colour, alphas cleared, rect via b192:01E00330 from texture 0x14 at its angle 0x34 and the scene texture (g+0x330); scale 0.1 at its position plus a tenth of 0x8..0xC; four quads of size x size pushed 120 out at angles 0x3A + 0/90/180/270 (g+0x375C), depth-tested into g+0x361C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b192_01E03920;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b192_01E03920 c;
    u8 pad18[0xF];
    u8 a27;
    u8 pad28[0xF];
    u8 a37;
    u8 pad38[0xF];
    u8 a47;
    u8 pad48[0xF];
    u8 a57;
} Pk_b192_01E03920;

typedef struct {
    u8 pad0[0x330];
    s32 tex;
    u8 pad334[0x361C - 0x334];
    s32 ot;
    u8 pad3620[0x375C - 0x3620];
    u8 trig[1];
} Game_b192_01E03920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
    s16 h3A;
} Fx_b192_01E03920;

static void func_01E03920_b192(Game_b192_01E03920 *g, Fx_b192_01E03920 *o, Pk_b192_01E03920 *p) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    f32 x;
    f32 y;
    f32 ax, ay, az;
    s16 i;
    s16 ang = 0;
    Rgbaq_b192_01E03920 uv __attribute__((aligned(8)));

    func_00106080(rm, 0x14, o->h34, rm);
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    *(s32 *)&p->c.q = 0;
    p->a27 = 0;
    p->a37 = 0;
    p->a47 = 0;
    p->a57 = 0;
    func_00107740(&uv, o->col);
    p->c = uv;
    func_01E00330_b192((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)rm, 0);
    func_00208700(p, g->tex, 1);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    for (i = 0; i < 4; i++) {
        func_00108CE0(quad, o->size, o->size);
        x = 120.0f * func_00108030(g->trig, (s16)(ang + o->h3A), 0);
        y = 120.0f * func_00108030(g->trig, (s16)(ang + o->h3A), 1);
        func_00107070(quad, 0, x);
        func_00107070(quad, 1, y);
        ang += 90;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0((s32)p, g->ot, (u32)depth[0]);
        }
    }
}
