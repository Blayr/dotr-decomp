#include "common.h"

/* shape b197:01E01A10, 383 insns: b197's scene manager: with a scene id (>= 0) it clears the scene, resets its three
   camera blocks, takes two model handles, sets the 170-frame countdown and frame 1, and sets up two rising particle
   emitters (48 sprites from ctx+0x140, 18 from ctx+0x850: white, 64 x 64 rects, each particle starting -i frames
   late); otherwise it tracks the model and the player, steps the cameras, tints the model white until frame 80, from
   frame 62 runs emitter A (rising 4 a frame to 150, fading from 154) and 37..80 emitter B (rising 1, fading from 50),
   counts and returns 2 / 1 / 6 at frames 154 / 90 / 100..153, 8 once the countdown runs out */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 life;
} Part_b197_01E01A10;

typedef struct {
    s32 tex;
    u32 flags;
    u8 col[4];
    f32 f0C;
    u8 pad10[0x10];
    f32 vx, vy, vz;
    u8 pad2C[4];
    s16 rect[8];
    Part_b197_01E01A10 *p;
    void *p2;
    s32 p3;
    f32 f4C;
    f32 f50;
    u8 pad54[6];
    s16 n;
    s16 h5C;
    s16 h5E;
} Emit_b197_01E01A10;

typedef struct {
    u8 pad0[0x10];
    Vec4f a;
    Vec4f b;
    u8 pad30[0x40];
} Cam_b197_01E01A10;

typedef struct {
    Cam_b197_01E01A10 cam0;
    Cam_b197_01E01A10 cam1;
    Emit_b197_01E01A10 ea;
    Part_b197_01E01A10 pa[48];
    u8 pad440[0x780 - 0x440];
    Cam_b197_01E01A10 cam2;
    Emit_b197_01E01A10 eb;
    Part_b197_01E01A10 pb[18];
    u8 pad970[0x20];
    s32 count;
    s32 timer;
    s32 id;
    s32 m0;
    s32 m1;
} Scene_b197_01E01A10;

static s32 func_01E01A10_b197(s32 arg0, s32 id) {
    Scene_b197_01E01A10 *g = (Scene_b197_01E01A10 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00103290(void *, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103DB0(void *, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_01E00120_b197();
    Vec4f a;
    Vec4f b;
    s32 t[2];
    u8 c1[4];
    u8 c2[4];
    Vec4f *p;
    Vec4f *pb;
    s32 h;
    s32 target;
    s32 i;

    target = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x9B0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        g->m0 = func_001F5560(func_001F53A0(), 8, 1);
        g->m1 = func_001F5560(func_001F53A0(), 1, 0);
        g->count = 170;
        g->timer = 1;
        g->id = id;
        func_00103290(t, 0);
        g->ea.tex = t[0];
        g->ea.flags = 0xF8000003;
        g->ea.col[0] = g->ea.col[1] = g->ea.col[2] = 0x80;
        g->ea.col[3] = 0x80;
        g->ea.f0C = 2.0f;
        g->ea.vx = 0.0f;
        g->ea.vy = 0.0f;
        g->ea.vz = 0.0f;
        g->ea.rect[0] = 0;
        g->ea.rect[1] = 0;
        g->ea.rect[2] = 64;
        g->ea.rect[3] = 64;
        g->ea.rect[4] = 0;
        g->ea.rect[5] = 0;
        g->ea.rect[6] = 64;
        g->ea.rect[7] = 64;
        g->ea.p = g->pa;
        g->ea.p2 = (u8 *)g + 0x460;
        g->ea.p3 = 0;
        g->ea.f50 = 3.0f;
        g->ea.f4C = 15.0f;
        g->ea.n = 48;
        g->ea.h5C = 1;
        g->ea.h5E = 0;
        for (i = 0; i < g->ea.n; i++) {
            g->pa[i].life = -i;
            g->pa[i].c = 0x30;
            g->pa[i].d = 0;
            g->pa[i].x = g->pa[i].y = g->pa[i].z = 0.0f;
        }
        g->eb.tex = t[0];
        g->eb.flags = 0x78000003;
        g->eb.col[0] = g->eb.col[1] = g->eb.col[2] = 0x80;
        g->eb.col[3] = 0x80;
        g->eb.f0C = 2.0f;
        g->eb.vx = 0.0f;
        g->eb.vy = 0.0f;
        g->eb.vz = 0.0f;
        g->eb.rect[0] = 0;
        g->eb.rect[1] = 0;
        g->eb.rect[2] = 64;
        g->eb.rect[3] = 64;
        g->eb.rect[4] = 0;
        g->eb.rect[5] = 0;
        g->eb.rect[6] = 64;
        g->eb.rect[7] = 64;
        g->eb.p = g->pb;
        g->eb.p2 = 0;
        g->eb.p3 = 0;
        g->eb.f50 = 30.0f;
        g->eb.f4C = 15.0f;
        g->eb.n = 18;
        g->eb.h5C = 1;
        g->eb.h5E = 0;
        for (i = 0; i < g->eb.n; i++) {
            g->pb[i].life = -i;
            g->pb[i].c = 0x30;
            g->pb[i].d = 0;
            g->pb[i].x = g->pb[i].y = g->pb[i].z = 0.0f;
        }
        return 0;
    }
    func_001F5620(func_001F53A0(), g->m0, &a);
    func_001F5F90(func_001F5380(), pb = (Vec4f *)(u32)&b);
    func_001F5620(func_001F53A0(), g->m0, &g->cam1.b);
    func_00103DB0(pb, &a, &g->cam1.a);
    p = func_001F9AD0(0);
    pb->x = p->x;
    b.y = p->y;
    b.z = p->z;
    func_001F5620(func_001F53A0(), g->m0, &g->cam2.b);
    func_00103DB0(pb, &a, &g->cam2.a);
    func_001038D0(&g->cam0);
    func_001038D0(&g->cam1);
    func_001038D0(&g->cam2);
    if (g->timer < 81) {
        h = func_001F53A0();
        c2[0] = 0x80;
        c2[1] = 0x80;
        c2[2] = 0x80;
        c1[3] = 0x80;
        c1[0] = 0x80;
        c1[1] = 0x80;
        c1[2] = 0x80;
        c2[3] = 0;
        func_001F71A0(h, 3, 0, c1, c2, 0);
    }
    if (g->timer >= 62) {
        func_01E00120_b197(target, &g->ea, &g->cam1);
        if (g->timer >= 154) {
            func_00103470(&g->ea.col[3], 0, 8);
        }
        for (i = 0; i < g->ea.n; i++) {
            if (g->pa[i].life < 0) {
                continue;
            }
            if (i % 2 == 0) {
                g->pa[i].c = 0x80;
            } else {
                g->pa[i].c = 0x40;
            }
            g->pa[i].y += 4.0f;
            if (g->pa[i].y < 150.0f) {
                g->pa[i].life = 0;
            }
            if (g->pa[i].y >= 150.0f) {
                if (g->pa[i].life > 8) {
                    g->pa[i].y = 0.0f;
                    g->pa[i].x = 0.0f;
                    g->pa[i].z = 0.0f;
                    g->pa[i].life = 0;
                } else {
                    g->pa[i].y = 150.0f;
                }
            }
        }
    }
    if (g->timer >= 37 && g->timer < 81) {
        func_01E00120_b197(target, &g->eb, &g->cam2);
        if (g->timer >= 50) {
            func_00103470(&g->eb.col[3], 0, 8);
        }
        for (i = 0; i < g->eb.n; i++) {
            if (g->pb[i].life < 0) {
                continue;
            }
            if (g->pb[i].life > 8) {
                func_00103470(&g->pb[i].c, 0, 8);
            } else if (i % 2 == 0) {
                g->pb[i].c = 0x80;
            } else {
                g->pb[i].c = 0x40;
            }
            g->pb[i].y += 1.0f;
        }
    }
    g->timer++;
    g->count--;
    if (g->timer == 154) {
        return 2;
    }
    if (g->timer == 90) {
        return 1;
    }
    if (g->timer >= 100 && g->timer < 154) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
