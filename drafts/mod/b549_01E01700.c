#include "common.h"

/* shape b549:01E01700, 246 insns: the effect scene's step: counts the frame (0xB2B8) and marks joint 0xB244 at 0xB1D0;
   frames 151..351 move the scene point onto the mark; frames 120..287 spawn three flakes (0x1E01AE0 first, then
   0x1E02280) around the mark jittered by -2.5..2.4; up to frame 287 each of joints 0xB246/0xB248 spawns 0x1E020C0
   jittered by -5..4.9 in x and z, rising (or, for the second, sinking) 0..2.4, nudged 2 in z by the scene side
   (0xB2B4) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f cam;
    u8 padB1E0[0xB244 - 0xB1E0];
    s16 ja;
    s16 ids[2];
    u8 padB24A[0x6A];
    s16 side;
    u8 padB2B6[2];
    s16 t;
} Scene_b549_01E01700;

extern s32 b549_01E02CE0(Scene_b549_01E01700 *, s32, s32);
extern void b549_01E01AE0(void);
extern void b549_01E020C0(void);
extern void b549_01E02280(void);

static void func_01E01700_b549(Scene_b549_01E01700 *g) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 d;
    f32 c;
    f32 a;
    s32 n;
    s16 i;

    g->t++;
    func_001F5620(func_001F53A0(), g->ja, &g->cam);
    if (g->t > 150 && g->t < 352) {
        func_001F5620(func_001F53A0(), g->ja, &g->cam);
        g->pos = g->cam;
    }
    if (g->t >= 120 && g->t < 288) {
        for (i = 0; i < 3; i++) {
            g->pos = g->cam;
            d = func_0019A5C8() % 50 - 25;
            n = func_0019A5C8() % 50 - 25;
            d /= 10.0f;
            g->pos.x += d;
            d = n;
            d /= 10.0f;
            g->pos.y += d;
            if (i == 0) {
                b549_01E02CE0(g, (s32)b549_01E01AE0, 0);
            } else {
                b549_01E02CE0(g, (s32)b549_01E02280, 0);
            }
        }
    }
    if (g->t < 288) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->ids[i], &g->pos);
            a = func_0019A5C8() % 100 - 50;
            c = func_0019A5C8() % 100 - 50;
            if (i == 0) {
                d = func_0019A5C8() % 25;
            }
            if (i == 1) {
                d = -func_0019A5C8() % 25;
            }
            a /= 10.0f;
            g->pos.x += a;
            d /= 10.0f;
            g->pos.y += d;
            c /= 10.0f;
            g->pos.z += c;
            if (g->side != 0) {
                g->pos.z += 2.0f;
            } else {
                g->pos.z -= 2.0f;
            }
            b549_01E02CE0(g, (s32)b549_01E020C0, 0);
        }
    }
}
