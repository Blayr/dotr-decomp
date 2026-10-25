#include "common.h"
#include "mod/b136.c"

/* shape b136:01E019D0, 330 insns, 1 copy: the module's scene manager: with a scene id (>= 0) it clears the scene, sets the
   258-frame countdown and loads textures 4:0..15; otherwise it runs the script step (b136:01E002E0) and the seven effect
   kinds (the b136:01E01950 fog until frame 94), draws them (two passes each; the embers with texture 15 as sprites),
   from frame 21 raises two fog levels by 0.01 up to 0.5, counts down and returns the next step by frame (120, 230,
   131..224) or 8 when it runs out */

typedef struct {
    u8 pad0[0x24];
    s32 (*fn)();
    u8 pad28[0xE];
    s16 used;
    u8 pad38[8];
} Fx_b136_01E019D0;

typedef struct {
    u8 pad0[0xC0];
    f32 fog0;
    f32 fogY;
    f32 fog1;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x174];
    Fx_b136_01E019D0 fx[180];
    u8 pad2F84[0x67C];
    s32 count;
    u8 pad3604[8];
    s32 ot;
    u8 pad3610[0x4A];
    s16 id;
    s16 frame;
    u8 pad365E[6];
    u8 crd[0x16C];
} Scene_b136_01E019D0;

static s32 func_01E019D0_b136(s32 arg0, s32 id) {
    Scene_b136_01E019D0 *g = (Scene_b136_01E019D0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, Vec4f *);
    extern s32 func_01E00080_b136();
    extern s32 b136_01E002E0();
    extern s32 func_01E008C0_b136();
    extern s32 func_01E00AE0_b136();
    extern s32 b136_01E00CA0();
    extern s32 func_01E014B0_b136();
    extern s32 func_01E01670_b136();
    extern s32 func_01E01780_b136();
    extern s32 func_01E01840_b136();
    extern s32 func_01E02020_b136();
    extern s32 b136_01E020D0();
    extern s32 func_01E02400_b136();
    extern s32 b136_01E01950();
    extern void func_001F7170(s32, s32, void *, void *, s32);
    Vec4f cam;
    s32 spr[4];
    u8 buf[0x90];
    F_b136_01E01950 b;
    F_b136_01E01950 a;
    s32 n;
    s32 i;

    n = 0;
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x37D0);
        func_00107C10(g->crd);
        g->id = id;
        g->count = 258;
        g->fog0 = 0.0f;
        g->fogY = 0.0f;
        g->fog1 = 0.0f;
        for (i = 0; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    b136_01E002E0(g, 0);
    for (i = 0; i < 180; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E008C0_b136) {
                func_01E008C0_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00AE0_b136) {
                func_01E00AE0_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == b136_01E00CA0) {
                b136_01E00CA0(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E014B0_b136) {
                func_01E014B0_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01670_b136) {
                func_01E01670_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01780_b136) {
                func_01E01780_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01840_b136) {
                func_01E01840_b136(g, &g->fx[i]);
            }
            if (g->fx[i].fn == b136_01E01950) {
                a = D_01E02600_b136;
                b = D_01E02608_b136;
                func_001F7170(6, 2, &a, &b, 0);
                if (g->frame == 94) {
                    g->fx[i].used = 0;
                }
            }
        }
    }
    func_001F5F90(func_001F5380(), &cam);
    cam.z -= 25.0f;
    for (i = 0; i < 180; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E008C0_b136) {
                b136_01E020D0(g, &g->fx[i], buf, 0);
                b136_01E020D0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00AE0_b136) {
                func_01E02400_b136(g, &g->fx[i], buf, 0);
                func_01E02400_b136(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == b136_01E00CA0) {
                func_01E02020_b136(g, &g->fx[i], buf, 0);
                func_01E02020_b136(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E014B0_b136) {
                spr[0] = g->tex[15];
                spr[2] = 0;
                spr[1] = 0x99;
                spr[3] = 0;
                func_01E00080_b136(g->ot, &g->fx[i], spr);
            }
            if (g->fx[i].fn == func_01E01670_b136) {
                b136_01E020D0(g, &g->fx[i], buf, 0);
                b136_01E020D0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01780_b136) {
                b136_01E020D0(g, &g->fx[i], buf, 0);
                b136_01E020D0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01840_b136) {
                b136_01E020D0(g, &g->fx[i], buf, 0);
                b136_01E020D0(g, &g->fx[i], buf, 1);
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
    if (g->frame == 120) {
        return 1;
    }
    if (g->frame == 230) {
        return 3;
    }
    if (g->frame > 130 && g->frame < 225) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
