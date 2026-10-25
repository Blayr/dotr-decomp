#include "common.h"

/* shape b506:01E01BA0, 351 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, builds both trig
   tables, loads textures 14-15 and 5:0, picks seven of the unit's joints, notes the camera's side, the mode, a
   170-tick life and 256 random offsets (-15..14); otherwise it runs the event step, updates and draws the 30 objects,
   updates the 350 effects and draws the three kinds with their textures (the 01E01540 ones as screen glows 30 to
   the camera's side), and returns the phase codes 1/4/2/6 at the script's beats or 8 when the life ends */

typedef struct {
    u8 pad0[0x88];
    s16 live;
    u8 pad8A[0xE];
} Obj_b506_01E01BA0;

typedef struct {
    u8 pad0[0x10];
    Vec4f v10;
    u8 pad20[0x24];
    s32 (*fn)(void *, void *);
    u8 pad48[0xE];
    s16 frame;
    s16 live;
    u8 pad5A[0x16];
} Fx_b506_01E01BA0;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    f32 rect[4];
    u8 padA4[0x34];
    u8 trigD8[0x1B8];
    s32 texs[16];
    Obj_b506_01E01BA0 obj[30];
    Fx_b506_01E01BA0 fx[350];
    u8 padB0C0[0xBF80 - 0x14A0 - 350 * 0x70];
    s32 tex2[1];
    u8 padBF84[0x1C];
    s32 life;
    u8 padBFA4[8];
    s32 ot2;
    u8 padBFB0[0x34];
    f32 level;
    u8 padBFE8[0x24];
    s16 joint[7];
    u8 padC01A[0xE];
    s16 mode;
    s16 side;
    s16 timer;
    s8 rnd[256];
    u8 padC12E[2];
    u8 trig[1];
} Scene_b506_01E01BA0;

static s32 func_01E01BA0_b506(s32 arg0, s32 arg) {
    Scene_b506_01E01BA0 *g = (Scene_b506_01E01BA0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00205440(void *, s32, void *, void *);
    extern void b506_01E00960();
    extern s32 b506_01E00E70(void *, void *);
    extern void b506_01E02460(void *, void *, void *, s32);
    extern s32 b506_01E01240(void *, void *);
    extern s32 b506_01E01540(void *, void *);
    extern s32 b506_01E016D0(void *, void *);
    extern void b506_01E004D0(void *, void *, s32, void *);
    extern void b506_01E00790(void *, void *, s32, f32);
    s32 n;
    s32 i;
    s32 k;
    Vec4f v;
    f32 r[4];
    f32 r2[4];
    s32 cam[4];
    u8 buf[0x18];
    u8 w[0x78];

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0xC2A0);
        func_00107C10(g->trig);
        func_00107C10(g->trigD8);
        for (n = 14; n < 16; n++) {
            g->texs[n] = func_00202BF0(4, n);
        }
        for (i = 0; i < 1; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        g->joint[0] = func_001F5560(func_001F53A0(), 19, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x81, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x24, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x50, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 14, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 15, 0);
        g->joint[6] = func_001F5560(func_001F53A0(), 0x23, 0);
        func_001F6160(func_001F53A0(), cam);
        g->side = cam[1] / 180.0f;
        g->mode = arg;
        g->life = 170;
        for (n = 0; n < 256; n++) {
            g->rnd[n] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b506_01E00960(g, 0);
    for (i = 0; i < 30; i++) {
        if (g->obj[i].live != 0) {
            b506_01E00E70(g, &g->obj[i]);
        }
    }
    for (i = 0; i < 30; i++) {
        if (g->obj[i].live != 0) {
            n++;
            b506_01E02460(g, &g->obj[i], buf, 0);
            b506_01E02460(g, &g->obj[i], buf, 1);
        }
    }
    for (i = 0; i < 350; i++) {
        if (g->fx[i].live != 0 && g->fx[i].fn != NULL) {
            g->fx[i].fn(g, &g->fx[i]);
        }
    }
    for (k = 0; k < 350; k++) {
        if (g->fx[k].live != 0) {
            n++;
            if (g->fx[k].fn == b506_01E01240) {
                g->tex = g->texs[15];
                func_00106080(r, 0x9B, g->fx[k].frame, 0);
                g->rect[0] = r[0];
                g->rect[1] = r[1];
                g->rect[2] = r[2];
                g->rect[3] = r[3];
                b506_01E004D0(g, &g->fx[k], 0x20, &g->fx[k].v10);
            }
            if (g->fx[k].fn == b506_01E01540) {
                func_001F5F90(func_001F5380(), &v);
                if (g->side != 0) {
                    v.z -= 30.0f;
                } else {
                    v.z += 30.0f;
                }
                func_00205440(&v, 0, w, &g->level);
                b506_01E00790(g, &g->fx[k], 0x20, g->level);
            }
            if (g->fx[k].fn == b506_01E016D0) {
                g->tex = g->tex2[0];
                func_00106080(r2, 0x14, g->fx[k].frame, 0);
                g->rect[0] = r2[0];
                g->rect[1] = r2[1];
                g->rect[2] = r2[2];
                g->rect[3] = r2[3];
                b506_01E004D0(g, &g->fx[k], 0x20, &g->fx[k].v10);
            }
        }
    }
    if (g->life != 0) {
        g->life--;
    }
    if (g->timer == 77) {
        return 1;
    }
    if (g->timer == 135) {
        return 4;
    }
    if (g->timer == 100) {
        return 2;
    }
    if (g->timer >= 88 && g->timer < 97) {
        return 6;
    }
    if (g->life > 0) {
        return 0;
    }
    return 8;
}
