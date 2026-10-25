#include "common.h"
/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */
#pragma opt_loop_invariants off

/* shape b117:01E00CB0, 239 insns: the effect scene's step (the frame test 48/49/50 stays three compares: -O3,p): sets
   the scene colour to dark red, counts the frame (0x3B8C); frame 1 spawns 0x1E01D00; frames 48..50 spawn twelve
   0x1E01070 and nineteen 0x1E019D0 at the camera point, frame 49 also thirty-three 0x1E01640 and 0x1E01780; frames
   26..44 spawn thirteen 0x1E01290; frame 28 measures a 21-step drift from joint 0x3B78 (20 up) to the camera, spawns
   0x1E01490 on the joint and fills the 10-point trail at 0x3A70 with it; frames 28..44 spawn five 0x1E01BB0; every
   spawn gets a random turn (0x3B82) */

typedef struct {
    u8 pad0[0x80];
    f32 px, py, pz;
    u8 pad8C[0xD0 - 0x8C];
    f32 dx, dy, dz;
    u8 padDC[0x3A70 - 0xDC];
    Vec4f tr[10];
    u8 pad3B10[0x3B34 - 0x3B10];
    u8 col[4];
    u8 pad3B38[0x3B78 - 0x3B38];
    s16 joint;
    u8 pad3B7A[8];
    s16 ang;
    u8 pad3B84[8];
    s16 t;
} Scene_b117_01E00CB0;

static s32 func_01E02480_b117();
static s32 func_01E01070_b117();
static s32 func_01E01290_b117();
extern void b117_01E01490(void);
static s32 func_01E01640_b117();
static s32 func_01E01780_b117();
static s32 func_01E019D0_b117();
static s32 func_01E01BB0_b117();
static s32 func_01E01D00_b117();

static void func_01E00CB0_b117(Scene_b117_01E00CB0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    Vec4f w;
    s32 i;
    s32 j;
    s32 k;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 1) {
        func_01E02480_b117(g, (s32)func_01E01D00_b117, 0);
    }
    func_001F5F90(func_001F5380(), &v);
    if (g->t == 48 || g->t == 49 || g->t == 50) {
        for (i = 0; i < 12; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)func_01E01070_b117, 0);
        }
        for (i = 0; i < 19; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)func_01E019D0_b117, 0);
        }
    }
    if (g->t == 49) {
        for (i = 0; i < 33; i++) {
            g->ang = func_0019A5C8() % 360;
            g->px = v.x;
            g->py = v.y;
            g->pz = v.z;
            func_01E02480_b117(g, (s32)func_01E01640_b117, 0);
        }
        func_01E02480_b117(g, (s32)func_01E01780_b117, 0);
    }
    if (g->t > 25 && g->t < 45) {
        for (i = 0; i < 13; i++) {
            g->ang = func_0019A5C8() % 360;
            func_01E02480_b117(g, (s32)func_01E01290_b117, 0);
        }
    }
    if (g->t == 28) {
        func_001F5620(func_001F53A0(), g->joint, &w);
        g->dx = (v.x - w.x) / 21.0f;
        g->dy = (20.0f + v.y - w.y) / 21.0f;
        g->dz = (v.z - w.z) / 21.0f;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    if (g->t == 28) {
        for (j = 0; j < 1; j++) {
            g->px = v.x;
            g->py = *(f32 *)(u32)&v.y;
            g->pz = *(f32 *)(u32)&v.z;
            func_01E02480_b117(g, (s32)b117_01E01490, 0);
            for (k = 0; k < 10; k++) {
                g->tr[k].x = v.x;
                g->tr[k].y = *(f32 *)(u32)&v.y;
                g->tr[k].z = *(f32 *)(u32)&v.z;
            }
        }
    }
    if (g->t >= 28 && g->t < 45) {
        for (i = 0; i < 5; i++) {
            g->ang = func_0019A5C8() % 360;
            func_01E02480_b117(g, (s32)func_01E01BB0_b117, 0);
        }
    }
}
