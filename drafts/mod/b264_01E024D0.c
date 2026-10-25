#include "common.h"

/* shape b264:01E024D0, 323 insns: B264_W_S, the scene script: 20 points ride joint 0xDE88 from frame 201 until their
   start frame 228 + 15 i, then each takes a velocity toward the model's root over 39 frames and a small random jitter
   and flies for 40 frames; 8 segment steps (next - this) / 5; each start frame (< 346) spawns 0x1E02C20, 0x1E02D50 and
   two 0x1E03030 for the next index; from frame 77 every 4th frame one of 16 0x1E03200; frame 1 spawns 0x1E03AA0 */

typedef struct {
    u8 pad0[0xD930];
    Vec4f pts[20];
    Vec4f vel[20];
    Vec4f jit[20];
    Vec4f seg[8];
    u8 padDD70[0xDE88 - 0xDD70];
    s16 joint;
    u8 padDE8A[0xDEB4 - 0xDE8A];
    s16 n4;
    u8 padDEB6[2];
    s16 cur;
    s16 next;
    u8 padDEBC[4];
    s16 t;
} Scene_b264_01E024D0;

static s32 func_01E02C20_b264();
static s32 func_01E02D50_b264();
static s32 func_01E03030_b264();
static s32 func_01E03200_b264();
static s32 func_01E03AA0_b264();
static s32 func_01E04670_b264();

static void func_01E024D0_b264(Scene_b264_01E024D0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[8];
    s16 i;

    g->t++;
    for (i = 0; i < 20; i++) {
        if (g->t > 200 && g->t < 228 + i * 15) {
            func_001F5620(func_001F53A0(), g->joint, &g->pts[i]);
        } else if (g->t >= 228 + i * 15) {
            if (g->t == 228 + i * 15) {
                func_001F5F90(func_001F5380(), v);
                g->vel[i].z = (v[2] - g->pts[i].z) / 39.0f;
                g->vel[i].y = (v[1] - g->pts[i].y) / 39.0f;
                g->jit[i].x = (func_0019A5C8() >> 4) % 20 - 10;
                g->jit[i].y = (func_0019A5C8() >> 4) % 20 - 10;
                g->jit[i].z = (func_0019A5C8() >> 4) % 20 - 10;
                g->jit[i].x /= 20.0f;
                g->jit[i].y /= 20.0f;
                g->jit[i].z /= 20.0f;
            }
            if (g->t < 268 + i * 15) {
                g->pts[i].z += g->vel[i].z;
                g->pts[i].y += g->vel[i].y;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        g->seg[i].x = (g->pts[i + 1].x - g->pts[i].x) / 5.0f;
        g->seg[i].y = (g->pts[i + 1].y - g->pts[i].y) / 5.0f;
        g->seg[i].z = (g->pts[i + 1].z - g->pts[i].z) / 5.0f;
    }
    for (i = 0; i < 20; i++) {
        if (g->t < 346 && g->t == 228 + i * 15) {
            g->cur = g->next;
            func_01E04670_b264(g, (s32)func_01E02C20_b264, 0);
            func_01E04670_b264(g, (s32)func_01E02D50_b264, 0);
            func_01E04670_b264(g, (s32)func_01E03030_b264, 0);
            func_01E04670_b264(g, (s32)func_01E03030_b264, 0);
            g->next++;
        }
    }
    if (g->t > 76 && g->t % 4 == 1 && g->n4 < 16) {
        g->cur = g->n4;
        func_01E04670_b264(g, (s32)func_01E03200_b264, 0);
        g->n4++;
    }
    if (g->t == 1) {
        func_01E04670_b264(g, (s32)func_01E03AA0_b264, 0);
    }
}
