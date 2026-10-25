#include "common.h"

/* shape c059:01E03B00, 156 insns: draws a pair of mirrored sprites (scale 3) under the camera's turned-back yaw: mode 0
   sets the material (frame 0x50 at +0x2E, colour 0x24 twice, scene texture 0x2628); otherwise the second copy sits at
   the negated x/z, the height follows the node's arc (0x0A*y - k*y*y) and then its swing (0x2A times the table's sine
   of y), and each is sent at the node's turn */

typedef struct {
    s16 x, y, z;
    u8 pad6[4];
    s16 hA;
    u8 padC[4];
    s32 rot[4];
    u8 pad20[4];
    u8 col[4];
    u8 pad28[2];
    s16 swing;
    u8 pad2C[2];
    s16 frame;
} Node_c059_01E03B00;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x210];
    u8 m[0x23D8];
    void *tex;
    u8 pad262C[0x45C];
    f32 k;
    u8 pad2A8C[0x40];
    s32 ot;
    u8 pad2AD0[0x60];
    u8 table[0x10];
} Scene_c059_01E03B00;

static void func_01E03B00_c059(Scene_c059_01E03B00 *g, Node_c059_01E03B00 *o, void *pk, s32 mode) {
    extern void func_00106080();
    extern void func_00109100();
    extern void func_00106ED0();
    extern void func_00106FA0();
    extern void func_00108FF0();
    extern void func_00205C40();
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    f32 m[4];
    s32 rot[4];
    s16 i;
    s16 j;

    if (mode == 0) {
        func_00106080(m, 0x50, o->frame, m);
        func_00107790(pk, o->col, 1);
        func_00107790(pk, o->col, 2);
        func_00108500(pk, m, 0);
        func_00208700(pk, g->tex, 1);
    } else {
    func_00205C40(rot);
    rot[1] = 0;
    rot[0] = -rot[0] / 180;
    rot[2] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++) {
            func_00108CE0(g->m, 3.0f, 3.0f);
            func_00109100(g->m, rot, 1, g->table);
            if (i == 0) {
                v.x = o->x;
                v.z = o->z;
            } else {
                v.x = -o->x;
                v.z = -o->z;
            }
            v.y = (f32)(o->hA * o->y) - (f32)o->y * (g->k * (f32)o->y);
            v.y = o->swing * func_00108030(g->table, o->y, 0);
            func_00106ED0(g->m, o->rot, 0);
            func_00106FA0(g->m, &v, 0);
            func_00108FF0(g->m, pk, g->m40, g->ot);
        }
    }
    }
}
