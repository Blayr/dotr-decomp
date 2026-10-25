#include "common.h"

/* shape b060:01E013C0, 305 insns: b060's scene manager: with a scene id (>= 0) it clears the scene, resets the camera
   block, keeps the id, sets the 180-frame countdown, zeroes the three fade values, takes two model handles and loads
   textures 13..15 and 2; otherwise it runs the module's step and every live node's update (by its callback), draws
   every live node twice (callback -> draw function) 25 below the player's point, from frame 21 eases fades 0xC0 and
   0xC8 up to 0.5 by 0.01 (0xC4 = 0.1), counts down and returns 1 / 4 / 2 / 6 at frames 107 / 145 / 132 / 118..126,
   8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[8];
} Node_b060_01E013C0;

typedef struct {
    u8 pad0[0xC0];
    f32 fC0;
    f32 fC4;
    f32 fC8;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x284 - 0x110];
    Node_b060_01E013C0 node[220];
    u8 pad3984[0x3B00 - 0x3984];
    s32 count;
    u8 pad3B04[8];
    s32 ot;
    u8 pad3B10[0x38];
    s16 h3B48;
    s16 h3B4A;
    u8 pad3B4C[0xE];
    s16 id;
    s16 timer;
    u8 pad3B5E[2];
    u8 cam[0x170];
} Scene_b060_01E013C0;

static s32 func_01E013C0_b060(s32 arg0, s32 id) {
    Scene_b060_01E013C0 *g = (Scene_b060_01E013C0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_01E00080_b060();
    extern s32 func_01E009B0_b060();
    extern s32 func_01E00BB0_b060();
    extern s32 func_01E00D80_b060();
    extern s32 func_01E00ED0_b060();
    extern s32 func_01E01080_b060();
    extern s32 func_01E01220_b060();
    extern void b060_01E019B0();
    extern void b060_01E01B50();
    extern void b060_01E01D00();
    extern void b060_01E01EB0();
    Vec4f v;
    u8 buf[0x90];
    s32 n;
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3CD0);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 180;
        g->fC0 = 0.0f;
        g->fC4 = 0.0f;
        g->fC8 = 0.0f;
        g->h3B48 = func_001F5560(func_001F53A0(), 40, 1);
        g->h3B4A = func_001F5560(func_001F53A0(), 2, 0);
        for (i = 13; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        return 0;
    }
    func_01E00080_b060(g, 0);
    for (i = 0; i < 220; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E009B0_b060) {
                func_01E009B0_b060(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00BB0_b060) {
                func_01E00BB0_b060(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00D80_b060) {
                func_01E00D80_b060(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00ED0_b060) {
                func_01E00ED0_b060(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01080_b060) {
                func_01E01080_b060(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01220_b060) {
                func_01E01220_b060(g, &g->node[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E009B0_b060) {
                b060_01E01B50(g, &g->node[i], buf, 0);
                b060_01E01B50(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00BB0_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00D80_b060) {
                b060_01E01EB0(g, &g->node[i], buf, 0);
                b060_01E01EB0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E00ED0_b060) {
                b060_01E01D00(g, &g->node[i], buf, 0);
                b060_01E01D00(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E01080_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
            if (g->node[i].fn == func_01E01220_b060) {
                b060_01E019B0(g, &g->node[i], buf, 0);
                b060_01E019B0(g, &g->node[i], buf, 1);
            }
        }
    }
    if (g->timer >= 21) {
        if (g->fC0 < 0.5) {
            g->fC0 += 0.01f;
        }
        g->fC4 = 0.1f;
        if (g->fC8 < 0.5) {
            g->fC8 += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 107) {
        return 1;
    }
    if (g->timer == 145) {
        return 4;
    }
    if (g->timer == 132) {
        return 2;
    }
    if (g->timer >= 118 && g->timer < 127) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
