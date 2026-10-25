#include "common.h"

/* shape b170:01E00C60, 267 insns, 1 copy: the module's scene manager: with a scene id (>= 0) it clears the scene, sets the
   310-frame countdown, reads four model ids and the camera turn, scale 0.1 and two 256-byte random jitter tables; otherwise
   it runs the step (b170:01E00570), every live effect's handler, draws the trail (b170:01E00760) and the two sprite kinds,
   counts down and returns the scene's next step by its frame (90, 250, 240, 101..234) or 8 when the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 kind;
    u8 pad52[6];
    s16 used;
    u8 pad5A[0x16];
} Fx_b170_01E00C60;

typedef struct {
    u8 pad0[0x10];
    f32 scale[3];
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[0x32];
    s16 hB6;
    u8 padB8[0x20];
    u8 trD8[0x1C8];
    Fx_b170_01E00C60 fx[50];
    u8 pad1880[0x30];
    u8 trail[0x5BF0];
    Vec4f pt[2];
    u8 pad74C0[0x160];
    s32 count;
    u8 pad7624[8];
    s32 ot;
    u8 pad7630[0x10];
    f32 f7640;
    u8 pad7644[0x10];
    s16 m54;
    s16 m56;
    s16 m58;
    u8 pad765A[0xA];
    s16 m64;
    u8 pad7666[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit0[0x100];
    s8 jit1[0x100];
} Scene_b170_01E00C60;

static s32 func_01E00C60_b170(s32 arg0, s32 id) {
    s16 i;
    Scene_b170_01E00C60 *g = (Scene_b170_01E00C60 *)arg0;
    extern void func_00107C10(void *);
    extern void func_00195108(void *, s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_00207500();
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_01E00760_b170();
    extern s32 func_01E00980_b170();
    extern s32 func_01E00B00_b170();
    extern void func_01E00110_b170();
    extern void func_01E00570_b170();
    extern void b170_01E011D0();
    Vec4f pos;
    s32 rot[4];
    s16 k;

    i = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x7A00);
        func_00107C10((u8 *)g + 0x788C);
        func_00107C10(g->trD8);
        g->id = id;
        g->count = 0x136;
        g->m54 = func_001F5560(func_001F53A0(), 0x29, 1);
        g->m56 = func_001F5560(func_001F53A0(), 0x1E, 0);
        g->m58 = func_001F5560(func_001F53A0(), 1, 0);
        g->m64 = func_001F5560(func_001F5380(), 1, 1);
        func_001F6160(func_001F53A0(), rot);
        g->turn = rot[1] / 180.0f;
        g->scale[0] = 0.1f;
        g->scale[1] = 0.1f;
        g->scale[2] = 0.1f;
        for (; i < 0x100; i++) {
            g->jit0[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit1[i] = func_0019A5C8() % 40 - 20;
        }
        g->f7640 = 250.0f;
        return 0;
    }
    func_01E00570_b170(g, 0);
    g->hB6 = g->frame;
    for (k = 0; k < 50; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 50; k++) {
        if (g->fx[k].used != 0) {
            i++;
            if (g->fx[k].fn == func_01E00760_b170) {
                b170_01E011D0(g, &g->fx[k], g->trail, 1);
            }
            if (g->fx[k].fn == func_01E00980_b170) {
                if (g->fx[k].kind == 0) {
                    pos = g->pt[0];
                } else if (g->fx[k].kind == 1) {
                    pos = g->pt[1];
                }
                if (g->frame < 0xA0) {
                    func_01E00110_b170(g, &g->fx[k], 0x21, &pos);
                } else {
                    func_01E00110_b170(g, &g->fx[k], 0x11, &pos);
                }
            }
            if (g->fx[k].fn == func_01E00B00_b170) {
                pos = g->fx[k].pos;
                func_01E00110_b170(g, &g->fx[k], 0x11, &pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 90) {
        return 1;
    }
    if (g->frame == 250) {
        return 4;
    }
    if (g->frame == 240) {
        return 2;
    }
    if (g->frame > 100 && g->frame < 235) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
