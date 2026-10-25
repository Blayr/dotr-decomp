#include "common.h"

/* shape b774:01E00080, 595 insns: B774_W_S, the effect scene's step: colour 0x80,0,0,0, counts the frame (0x371E);
   openers at 1 and 39; the focus P (0x610) is mirrored past joint 0x36B2 from joint 0x36B0 at 80 and 170..191
   (R, 0x630, at 180), then drifts toward the camera joint 0x36C0 from 181 to 254 and shakes by 2 from 255 around its
   copy Q (0x620); level-gated spawns on P; two growth values (0x36F4, 0x36F8) ramp over frames 80..230 */

typedef struct {
    u8 pad0[0x40];
    Vec4f pos;
    u8 pad50[0x610 - 0x50];
    Vec4f p;
    Vec4f q;
    Vec4f r;
    u8 pad640[0x36B0 - 0x640];
    s16 ja;
    s16 jb;
    u8 pad36B4[0x36C0 - 0x36B4];
    s16 jcam;
    u8 pad36C2[0x36D0 - 0x36C2];
    s32 level;
    u8 col[4];
    u8 pad36D8[0x36F4 - 0x36D8];
    f32 grow;
    f32 size;
    u8 pad36FC[0x370E - 0x36FC];
    s16 spin;
    s16 f3710;
    u8 pad3712[4];
    s16 idx;
    s16 a0;
    s16 a1;
    u8 pad371C[2];
    s16 t;
    u8 pad3720[4];
    u8 trig[1];
} Scene_b774_01E00080;

static void func_01E00080_b774(Scene_b774_01E00080 *g) {
    extern void b774_01E009D0(void);
    extern void b774_01E00E50(void);
    extern void b774_01E011C0(void);
    extern void b774_01E014A0(void);
    extern void b774_01E015D0(void);
    extern void b774_01E01760(void);
    extern void b774_01E018C0(void);
    extern void b774_01E01B70(void);
    extern void b774_01E01CD0(void);
    extern void b774_01E01E30(void);
    extern void b774_01E02080(void);
    extern void b774_01E02160(void);
    extern void b774_01E021E0(void);
    extern void b774_01E02D50(Scene_b774_01E00080 *, void (*)(void), s32);
    extern void b774_01E02E70(Scene_b774_01E00080 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    f32 *pb;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 1) {
        b774_01E02D50(g, b774_01E02080, 0);
    }
    if (g->t == 39) {
        b774_01E02D50(g, b774_01E02160, 0);
    }
    if (g->t == 39) {
        b774_01E02D50(g, b774_01E021E0, 0);
    }
    func_001F5620(func_001F53A0(), g->ja, &a);
    func_001F5620(func_001F53A0(), g->jb, pb = (f32 *)(u32)&b);
    if (g->t < 192 && (g->t == 80 || g->t >= 170)) {
        a.x = pb[0] - a.x;
        a.y = b.y - a.y;
        a.z = b.z - a.z;
        g->p.x = pb[0] + a.x;
        g->p.y = b.y + a.y;
        g->p.z = b.z + a.z;
    }
    if (g->t == 180) {
        a.x = pb[0] - a.x;
        a.y = b.y - a.y;
        a.z = b.z - a.z;
        g->r.x = pb[0] + a.x;
        g->r.y = b.y + a.y;
        g->r.z = b.z + a.z;
    }
    if (g->t % 2 == 1 && g->level > 35 && g->t > 80) {
        for (i = 0; i < 1; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = g->p.x;
            g->pos.y = g->p.y;
            g->pos.z = g->p.z;
            b774_01E02D50(g, b774_01E01760, 0);
        }
    }
    if (g->t == 80) {
        for (i = 0; i < 1; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = g->p.x;
            g->pos.y = g->p.y;
            g->pos.z = g->p.z;
            b774_01E02D50(g, b774_01E015D0, 0);
        }
    }
    if (g->t > 80 && g->level > 30) {
        for (i = 0; i < 1; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = g->p.x;
            g->pos.y = g->p.y;
            g->pos.z = g->p.z;
            b774_01E02D50(g, b774_01E011C0, 0);
        }
    }
    if (g->t == 80) {
        b774_01E02D50(g, b774_01E00E50, 0);
    }
    if (g->t == 80) {
        b774_01E02D50(g, b774_01E01E30, 0);
    }
    if (g->t == 80) {
        for (i = 0; i < 10; i++) {
            g->idx = i;
            b774_01E02D50(g, b774_01E009D0, 0);
        }
    }
    if (g->t > 185 && g->t < 247) {
        g->pos.x = g->p.x;
        g->pos.y = g->p.y;
        g->pos.z = g->p.z;
        b774_01E02E70(g, b774_01E01CD0, 0);
    }
    if (g->t > 250 && g->level > 30) {
        g->pos.x = g->p.x;
        g->pos.y = g->p.y;
        g->pos.z = g->p.z;
        b774_01E02D50(g, b774_01E014A0, 0);
    }
    if (g->t > 80 && g->level > 30) {
        g->pos.x = g->p.x;
        g->pos.y = g->p.y;
        g->pos.z = g->p.z;
        b774_01E02D50(g, b774_01E018C0, 0);
    }
    if (g->t > 255 && g->level > 30) {
        g->pos.x = g->p.x;
        g->pos.y = g->p.y;
        g->pos.z = g->p.z;
        b774_01E02D50(g, b774_01E01B70, 0);
    }
    func_001F5620(func_001F53A0(), g->ja, &a);
    func_001F5620(func_001F5380(), g->jcam, &a);
    if (g->t > 180 && g->t < 255) {
        g->p.y += (a.y - g->r.y) / 200.0f;
        g->p.z += (a.z - g->r.z) / 100.0f;
        g->p.x += (a.x - g->r.x) / 100.0f;
    }
    if (g->t >= 80 && g->t < 140) {
        if (g->t == 80) {
            g->grow = 1.0f;
        }
        if (g->t == 85) {
            g->grow = 2.0f;
        }
        if (g->t == 90) {
            g->grow = 3.0f;
        }
        if (g->t == 95) {
            g->grow = 4.0f;
        }
        if (g->t == 130) {
            g->grow = 10.0f;
        }
        if (g->size < 90.0f) {
            g->size += 2.0f;
        }
    }
    if (g->t >= 140 && g->t < 171) {
        if (g->grow < 30.0f) {
            g->grow += 1.0f;
        }
        if (g->size < 180.0f) {
            g->size += 3.0f;
        }
    }
    if (g->t >= 182 && g->t < 186) {
        if (g->grow < 32.0f) {
            g->grow += 1.0f;
        }
        if (g->size < 210.0f) {
            g->size += 5.0f;
        }
    }
    if (g->t >= 190 && g->t < 231) {
        if (g->grow < 50.0f) {
            g->grow += 1.0f;
        }
        if (g->size < 300.0f) {
            g->size += 4.0f;
        }
    }
    g->f3710 = 8;
    if (g->t == 254) {
        g->q = g->p;
        g->a0 = func_0019A5C8() % 360;
        g->a1 = func_0019A5C8() % 360;
    }
    if (g->t >= 255) {
        g->p = g->q;
        g->p.x += 2.0f * func_00108030((s32)g->trig, g->a0, 1);
        g->p.y += 2.0f * func_00108030((s32)g->trig, g->a1, 1);
        g->a0 = func_0019A5C8() % 360;
        g->a1 = func_0019A5C8() % 360;
    }
}
