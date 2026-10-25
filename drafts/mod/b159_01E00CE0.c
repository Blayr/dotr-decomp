#include "common.h"

/* shape b159:01E00CE0, 351 insns, 1 copy: the module's scene manager (b136:01E019D0 family): with a scene id (>= 0) it
   clears the scene, sets the 120-frame countdown, reads three joints and textures 4:2, 4:14 and 4:15; otherwise at frame
   45 it fills the 9-point trail with joint A, pushes the joint history, runs the script step and the effects (the
   b159:01E00A90 glow written out), draws them two passes each, raises two fog levels by 0.01 up to 0.5 from frame 21,
   counts down and returns the next step by frame (45, 65, 55) or 8 when it runs out */

typedef struct {
    u8 pad0[0x24];
    s32 (*fn)();
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 used;
    s16 h38;
    u8 pad3A[6];
} Fx_b159_01E00CE0;

typedef struct {
    u8 pad0[0xC0];
    f32 fog0;
    f32 fogY;
    f32 fog1;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x174];
    Fx_b159_01E00CE0 fx[220];
    u8 pad3984[0xDC];
    Vec4f pt[9];
    u8 pad3AF0[0x10];
    s32 count;
    u8 pad3B04[8];
    s32 ot;
    u8 pad3B10[0x40];
    s16 jointA;
    s16 jointB;
    s16 jointC;
    u8 pad3B56[0xC];
    s16 id;
    s16 frame;
    u8 pad3B66[2];
    u8 crd[0x178];
} Scene_b159_01E00CE0;

static s32 func_01E00CE0_b159(s32 arg0, s32 id) {
    Scene_b159_01E00CE0 *g = (Scene_b159_01E00CE0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, Vec4f *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_01E00080_b159();
    extern s32 func_01E00150_b159();
    extern s32 func_01E004C0_b159();
    extern s32 func_01E006E0_b159();
    extern s32 func_01E008D0_b159();
    extern s32 func_01E008E0_b159();
    extern s32 func_01E00A90_b159();
    extern s32 func_01E00B30_b159();
    extern s32 func_01E01380_b159();
    extern s32 func_01E01520_b159();
    extern s32 b159_01E016C0();
    extern s32 func_01E01B30_b159();
    Vec4f cam;
    Vec4f a;
    s32 buf[4];
    u8 pk[0x90];
    s32 n;
    s32 i;
    Vec4f *p;

    n = 0;
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3CE0);
        func_00107C10(g->crd);
        g->id = id;
        g->count = 120;
        g->fog0 = 0.0f;
        g->fogY = 0.0f;
        g->fog1 = 0.0f;
        g->jointA = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->jointB = func_001F5560(func_001F53A0(), 0x38, 0);
        g->jointC = func_001F5560(func_001F53A0(), 0xD, 0);
        for (i = 2; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    if (g->frame == 45) {
        p = g->pt;
        func_001F5620(func_001F53A0(), g->jointA, &a);
        for (i = 0; i < 9; i++) {
            p->x = a.x;
            p->y = a.y;
            p->z = a.z;
            p++;
        }
    }
    func_01E00080_b159(g->pt + 9, 10, g->jointA);
    func_01E00150_b159(g, 0);
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E004C0_b159) {
                func_01E004C0_b159(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E006E0_b159) {
                func_01E006E0_b159(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E008E0_b159) {
                func_01E008E0_b159(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00A90_b159) {
                func_001076F0(g->fx[i].col, 0x1F, 0x10, 0x50);
                if (g->fx[i].used == 1) {
                    g->fx[i].h38 = 5;
                    g->fx[i].used = 2;
                }
                func_001F5620(func_001F53A0(), g->jointA, buf);
                g->fx[i].col[3] = 0x30;
                g->fx[i].tick = 10;
                if (g->count == 0x32) {
                    g->fx[i].used = 0;
                }
            }
            if (g->fx[i].fn == func_01E00B30_b159) {
                func_01E00B30_b159(g, &g->fx[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &cam);
    cam.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E004C0_b159) {
                func_01E01520_b159(g, &g->fx[i], pk, 0);
                func_01E01520_b159(g, &g->fx[i], pk, 1);
            }
            if (g->fx[i].fn == func_01E006E0_b159) {
                func_01E01380_b159(g, &g->fx[i], pk, 0);
                func_01E01380_b159(g, &g->fx[i], pk, 1);
            }
            if (g->fx[i].fn == func_01E008D0_b159) {
                func_01E01380_b159(g, &g->fx[i], pk, 0);
                func_01E01380_b159(g, &g->fx[i], pk, 1);
            }
            if (g->fx[i].fn == func_01E008E0_b159) {
                func_01E01380_b159(g, &g->fx[i], pk, 0);
                func_01E01380_b159(g, &g->fx[i], pk, 1);
            }
            if (g->fx[i].fn == func_01E00A90_b159) {
                b159_01E016C0(g, &g->fx[i], pk, 0);
                b159_01E016C0(g, &g->fx[i], pk, 1);
            }
            if (g->fx[i].fn == func_01E00B30_b159) {
                func_01E01B30_b159(g, &g->fx[i], pk, 0);
                func_01E01B30_b159(g, &g->fx[i], pk, 1);
            }
        }
    }
    if (g->frame > 20) {
        if (g->fog0 < 0.5) {
            g->fog0 += 0.01f;
        }
        g->fogY = 0.1f;
        if (g->fog1 < 0.5) {
            g->fog1 += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 45) {
        return 1;
    }
    if (g->frame == 65) {
        return 4;
    }
    if (g->frame == 55) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
