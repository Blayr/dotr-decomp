#include "common.h"

/* shape b600:01E01990, 343 insns, 1 copy: b600's scene manager: with a code it clears the scene and its two models,
   two joints, a 421-tick countdown, grey 0x80, a pink beam (texture from 0x103290, rect 0x80 x 0x80, 20 segments)
   and a 256-point spark cloud (texture 15, rect 0x20 at (0xB0, 0x60)); otherwise it aims the second model between
   the camera and joint 1 until tick 390, fades the scene grey out until 400 then back, tints the screen until 96,
   from 173 draws the flickering beam (fading after 400), from 197 lights the cloud, grows each live point by 1.3
   and re-rolls it past life 16; returns 2 at 400, 1 at 187, 6 from 197 to 399, 8 when the countdown runs out */

typedef struct Pt_b600_01E01990 {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 life;
} Pt_b600_01E01990;

typedef struct Game_b600_01E01990 {
    u8 m0[0x70];
    s32 tex;
    u8 b, g, r, a;
    s32 w78;
    f32 f7C;
    s16 rect[8];
    u8 pad90[0x120];
    s16 h1B0;
    s16 h1B2;
    f32 f1B4;
    void *p1B8;
    s16 h1BC;
    s16 seg;
    f32 f1C0;
    u8 pad1C4[0x40C];
    u8 m5D0[0x10];
    Vec4f v5E0;
    Vec4f v5F0;
    u8 pad600[0x40];
    u8 m640[0x20];
    u8 m660[0x50];
    s32 tex2;
    s32 w6B4;
    u8 b2, g2, r2, a2;
    void *p6BC;
    s16 rect2[8];
    f32 f6D0;
    f32 f6D4;
    f32 f6D8;
    s16 count2;
    u8 b6DE;
    u8 b6DF;
    Pt_b600_01E01990 pts[256];
    s32 count;
    s32 clock;
    s32 code;
    s32 j0;
    s32 j1;
    s32 grey;
} Game_b600_01E01990;

static s32 func_01E01990_b600(s32 arg0, s32 code) {
    Game_b600_01E01990 *g = (Game_b600_01E01990 *)arg0;
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void func_00103290();
    extern void func_00103260();
    extern void func_001F5F90();
    extern void func_001F5620();
    extern void func_00103DB0();
    extern s32 func_00103470();
    extern s32 func_001032C0();
    extern void func_001F6D00();
    extern void func_001F71A0();
    extern void func_001043F0(void *, f32);
    extern void b600_01E00410();
    extern void b600_01E01270();
    s32 tex __attribute__((aligned(16)));
    u8 c0[4];
    u8 c1[4];
    f32 m[4];
    f32 b[4];
    Vec4f v;
    f32 *pb;
    s32 ot;
    s32 i;

    ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108((s32)g, 0x1700);
        func_00103890(g);
        func_00103890(g->m5D0);
        func_00103890(g->m640);
        g->j0 = func_001F5560(func_001F53A0(), 3, 1);
        g->j1 = func_001F5560(func_001F53A0(), 1, 0);
        g->count = 421;
        g->clock = 1;
        g->code = code;
        g->grey = 0x80;
        func_00103290(&tex, 0);
        g->tex = tex;
        g->r = 0x80;
        g->g = 0x40;
        g->b = 0x60;
        g->a = 0x80;
        g->w78 = 0;
        g->f7C = 2.5f;
        g->h1B0 = 0x20;
        g->h1B2 = 0;
        g->f1B4 = 2.0f;
        g->rect[0] = 0;
        g->rect[1] = 0;
        g->rect[2] = 0x80;
        g->rect[3] = 0x80;
        g->rect[4] = 0;
        g->rect[5] = 0;
        g->rect[6] = 0x80;
        g->rect[7] = 0x80;
        g->p1B8 = g->pad1C4 + 0xC;
        g->h1BC = 20;
        g->seg = 0;
        g->f1C0 = 1.0f;
        func_01E01170_b600((void *)&g->tex, tex);
        func_00103260(&tex, 0xF);
        g->tex2 = tex;
        g->w6B4 = 3;
        g->r2 = 0x80;
        g->g2 = 0x40;
        g->b2 = 0x60;
        g->a2 = 0;
        g->f6D0 = 0.3f;
        g->f6D4 = 11.0f;
        g->rect2[0] = 0xB0;
        g->rect2[1] = 0x60;
        g->rect2[2] = 0x20;
        g->rect2[3] = 0x20;
        g->rect2[4] = 0xB0;
        g->rect2[5] = 0x60;
        g->rect2[6] = 0x100;
        g->rect2[7] = 0x100;
        g->p6BC = g->pts;
        g->f6D8 = 10.0f;
        g->count2 = 0x100;
        g->b6DE = 1;
        g->b6DF = 0;
        func_01E00250_b600((void *)&g->tex2, 12, 3.0f);
        return 0;
    }
    if (g->clock < 390) {
        func_001F5F90(func_001F5380(), m);
        func_001F5620(func_001F53A0(), g->j1, pb = (f32 *)(u32)b);
        func_00103DB0(m, pb, &g->v5E0);
        func_001F5620(func_001F53A0(), g->j0, &g->v5F0);
    }
    func_001F5F90(func_001F5380(), g->m660);
    func_001038D0(g);
    func_001038D0(g->m5D0);
    func_001038D0(g->m640);
    if (g->clock < 400) {
        func_00103470(&g->grey, 0x20, 4);
    } else {
        func_001032C0(&g->grey, 0x80, 4);
    }
    func_001F6D00(g->grey);
    if (g->clock >= 173) {
        func_01E00120_b600();
    }
    if (g->clock < 96) {
        c1[0] = 0x80;
        c1[1] = 0x80;
        c1[2] = 0x80;
        c0[3] = 0x80;
        c0[0] = 0x80;
        c0[1] = 0x80;
        c0[2] = 0x80;
        c1[3] = 0;
        func_001F71A0(func_001F53A0(), 3, 0, c0, c1, 0);
    }
    if (g->clock >= 173) {
        g->b = func_0019A5C8() % 64 + 64;
        b600_01E01270(ot, &g->tex, g->m5D0);
        if (g->clock > 400) {
            func_00103470(&g->a, 0, 0x10);
        }
        g->seg++;
    }
    if (g->clock == 197) {
        g->a2 = 0x80;
    }
    b600_01E00410(ot, &g->tex2, g->m640);
    if (g->clock > 392) {
        func_00103470(&g->a2, 0, 8);
    }
    for (i = 0; i < g->count2; i++) {
        if (g->pts[i].life < 0) {
            continue;
        }
        g->pts[i].x *= 1.3f;
        g->pts[i].y *= 1.3f;
        g->pts[i].z *= 1.3f;
        if (g->pts[i].life > 16) {
            func_001043F0(&v, 1.0f);
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].x = v.x;
            g->pts[i].life = -(func_0019A5C8() % 12);
            if (g->clock >= 197) {
                g->pts[i].a = 0x80;
            } else {
                g->pts[i].a = 0;
            }
        }
    }
    g->clock++;
    g->count--;
    if (g->clock == 400) {
        return 2;
    }
    if (g->clock == 187) {
        return 1;
    }
    if (g->clock >= 197 && g->clock < 400) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
