#include "common.h"

/* shape b517:01E01B10, 356 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, builds both trig
   tables, notes the mode and a 260-tick life, picks four joints, loads textures 10-15, 0 and 5:0-1, notes the camera's
   side, sets the scale to 0.1 and fills the offset tables (-15..14, a flat run 100..179, -8..7 above; -20..19);
   otherwise it runs the event step, updates the 400 effects and draws the two kinds with texture 5:0, and returns 1, 3
   or 6 at the script's beats or 8 when the life ends */

typedef struct {
    u8 pad0[0x10];
    Vec4f v10;
    u8 pad20[0x24];
    s32 (*fn)(void *, void *);
    u8 pad48[0xE];
    s16 frame;
    s16 live;
    u8 pad5A[0x16];
} Fx_b517_01E01B10;

typedef struct {
    u8 pad0[0x10];
    f32 scale[3];
    u8 pad1C[4];
    f32 v20[3];
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    f32 rect[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 trigD8[0x188];
    s32 texs[16];
    Fx_b517_01E01B10 fx[400];
    u8 padB1A0[0xB1D0 - 0x2A0 - 400 * 0x70];
    s32 tex2[2];
    u8 padB1D8[0x18];
    s32 life;
    u8 padB1F4[8];
    s32 ot2;
    u8 padB200[0x28];
    s16 joint[3];
    u8 padB22E[0xA];
    s16 joint3;
    u8 padB23A[0x20];
    s16 side;
    s16 mode;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
} Scene_b517_01E01B10;

static s32 func_01E01B10_b517(s32 arg0, s32 arg) {
    Scene_b517_01E01B10 *g = (Scene_b517_01E01B10 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void b517_01E01440();
    extern s32 b517_01E015D0(void *, void *);
    extern s32 b517_01E01960(void *, void *);
    extern void b517_01E00920(void *, void *, s32, void *);
    extern void b517_01E00E90(void *, void *, s32, void *);
    s16 n;
    s16 i;
    s16 j;
    s32 k;
    f32 r[4];
    f32 r2[4];
    s32 cam[4];

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0xB5D0);
        func_00107C10((u8 *)g + 0xB460);
        func_00107C10(g->trigD8);
        g->mode = arg;
        g->life = 260;
        g->joint[0] = func_001F5560(func_001F53A0(), 0x1D, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->joint3 = func_001F5560(func_001F5380(), 1, 1);
        for (k = 10; k < 16; k++) {
            g->texs[k] = func_00202BF0(4, k);
        }
        g->texs[0] = func_00202BF0(4, 0);
        for (k = 0; k < 2; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), cam);
        g->side = cam[1] / 180.0f;
        g->scale[0] = 0.1f;
        g->scale[1] = 0.1f;
        g->scale[2] = 0.1f;
        for (n = 0; n < 256; n++) {
            g->rnd[n] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->rnd[i] = 0;
        }
        for (j = 180; j < 256; j++) {
            g->rnd[j] = func_0019A5C8() % 16 - 8;
        }
        for (j = 0; j < 256; j++) {
            g->rnd2[j] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    b517_01E01440(g, 0);
    for (i = 0; i < 400; i++) {
        if (g->fx[i].live != 0 && g->fx[i].fn != NULL) {
            g->fx[i].fn(g, &g->fx[i]);
        }
    }
    for (i = 0; i < 400; i++) {
        if (g->fx[i].live != 0) {
            n++;
            if (g->fx[i].fn == b517_01E015D0) {
                func_00106080(r, 0x14, g->fx[i].frame, 0);
                g->rect[0] = r[0];
                g->rect[1] = r[1];
                g->rect[2] = r[2];
                g->rect[3] = r[3];
                g->hC0 = 5;
                g->tex = g->tex2[0];
                g->hB8 = 1;
                g->v20[0] = g->fx[i].v10.x;
                g->v20[1] = g->fx[i].v10.y;
                g->v20[2] = g->fx[i].v10.z;
                g->hBE = 0;
                b517_01E00920(g, &g->fx[i], 0x10, (u8 *)g + 0xB460);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == b517_01E01960) {
                g->tex = g->tex2[0];
                func_00106080(r2, 0x14, g->fx[i].frame, 0);
                g->rect[0] = r2[0];
                g->rect[1] = r2[1];
                g->rect[2] = r2[2];
                g->rect[3] = r2[3];
                g->hB8 = 10;
                g->hB0 = 0;
                b517_01E00E90(g, &g->fx[i], 0x10, (u8 *)g + 0xB460);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->life != 0) {
        g->life--;
    }
    if (g->timer == 80) {
        return 1;
    }
    if (g->timer == 250) {
        return 3;
    }
    if (g->timer >= 91 && g->timer < 240) {
        return 6;
    }
    if (g->life > 0) {
        return 0;
    }
    return 8;
}
