#include "common.h"

/* shape c531:01E01040, 273 insns: the c531 module's main step: with a code it clears the scene, keeps a 20-tick timer
   and the target model (busy), and sets up three animated boards: each coordinate gets the effect position (from the
   target or, for model 0, the other side), scale 2.6, turn 0x4000 and a height of 10 x (k + 1) (models past 5) or
   10 x (k + 4); each board's animation is rect 32 x 32 from a 128 x 64 sheet, grey, 2 frames, texture 6, set up by
   c531:01E00120 at size 50..59; otherwise it draws the boards (c531:01E00460) fading them in by 0x20 and growing
   for 12 ticks, then shrinking by 0.2 and fading out, and on the last board it squashes the model (scale x/z down
   by 0.3, y up by 0.6) and fades the card by 0x30; returns 2 on tick 17 and 8 when the timer ends */

typedef struct {
    f32 sx, sy, sz;
    u8 padC[4];
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c531_01E01040;

typedef struct {
    u8 pad0[8];
    s32 w8;
    u8 padC[0x94];
} Board_c531_01E01040;

typedef struct {
    s16 rect[8];
    u8 pad10[0x20];
    f32 f30;
    u8 b, g, r, a;
    s32 w38;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Anim_c531_01E01040;

typedef struct {
    Crd_c531_01E01040 crd[3];
    Board_c531_01E01040 board[3];
    Anim_c531_01E01040 anim[3];
    f32 msc[4];
    u8 crgba[4];
    s32 model;
    s32 timer;
    u8 pad46C[4];
    s32 tick;
} Scene_c531_01E01040;

extern void c531_01E00120(Anim_c531_01E01040 *, Board_c531_01E01040 *, s32, f32);
extern void c531_01E00460(s32, Anim_c531_01E01040 *, Board_c531_01E01040 *, Crd_c531_01E01040 *);

static s32 func_01E01040_c531(s32 arg0, s32 code) {
    Scene_c531_01E01040 *g = (Scene_c531_01E01040 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_00103890(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_001038D0(void *);
    extern void func_001032C0(void *, u32, u32);
    extern void func_00103540(void *, f32, f32);
    extern void func_00103470(void *, u32, s32);
    extern void func_00103390(void *, f32, f32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F6340(s32, void *);
    extern void func_001F62B0(s32, void *);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x480);
        g->timer = 20;
        g->tick = 0;
        g->model = func_001F5380();
        func_001F5970(g->model, 1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->crd[i]);
            if ((u8)g->model == 0) {
                func_001F53B0(1, &g->crd[i].pos);
            } else {
                func_001F53B0(0, &g->crd[i].pos);
            }
        }
        func_00103260(&tex, 6);
        for (i = 0; i < 3; i++) {
            g->anim[i].w38 = 1;
            g->anim[i].rect[0] = 0;
            g->anim[i].rect[1] = 0;
            g->anim[i].rect[2] = 0x20;
            g->anim[i].rect[3] = 0x20;
            g->anim[i].rect[4] = 0;
            g->anim[i].rect[5] = 0;
            g->anim[i].rect[6] = 0x80;
            g->anim[i].rect[7] = 0x40;
            g->anim[i].f30 = 1.0f;
            g->anim[i].r = 0x80;
            g->anim[i].g = 0x80;
            g->anim[i].b = 0x80;
            g->anim[i].a = 0;
            g->anim[i].h48 = 0;
            g->anim[i].h4A = 0;
            g->anim[i].h4E = 2;
            g->anim[i].h4C = g->anim[i].h4E - 1;
            g->anim[i].h50 = 0;
            g->anim[i].h52 = 999;
            g->board[i].w8 = 1;
            c531_01E00120(&g->anim[i], &g->board[i], tex, 50.0f + func_0019A5C8() % 10);
            g->crd[i].sx = g->crd[i].sy = g->crd[i].sz = 2.6f;
            g->crd[i].rot[0] = 0x4000;
            if ((u8)g->model > 5) {
                g->crd[i].pos.y = 10.0f * (i + 1);
            } else {
                g->crd[i].pos.y = 10.0f * (i + 4);
            }
        }
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->crd[i]);
        g->crd[i].rot[0] = 0x4000;
        c531_01E00460(ot, &g->anim[i], &g->board[i], &g->crd[i]);
        if (g->tick < 12) {
            func_001032C0(&g->anim[i].a, 0x80, 0x20);
            func_00103540(&g->crd[i].sx, 1.0f, 0.3f);
            func_00103540(&g->crd[i].sy, 1.0f, 0.3f);
            func_00103540(&g->crd[i].sz, 1.0f, 0.3f);
        } else {
            g->crd[i].sx -= 0.2f;
            g->crd[i].sy -= 0.2f;
            g->crd[i].sz -= 0.2f;
            func_00103470(&g->anim[i].a, 0, 0x20);
            if (i == 2) {
                if (func_001F5EC0(g->model) != 0) {
                    func_001F6340(g->model, g->msc);
                    func_00103540(&g->msc[0], 0.0f, 0.3f);
                    func_00103540(&g->msc[2], 0.0f, 0.3f);
                    func_00103390(&g->msc[1], 3.0f, 0.6f);
                    func_001F62B0(g->model, g->msc);
                }
                if (func_001F5AF0(g->model) != 0) {
                    func_001F5E40(g->model, g->crgba);
                    func_00103470(&g->crgba[3], 0, 0x30);
                    func_001F5DE0(g->model, g->crgba);
                }
            }
        }
    }
    g->tick++;
    g->timer--;
    if (g->tick == 17) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
