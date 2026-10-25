#include "common.h"

/* shape c532:01E01040, 263 insns: c532's scene manager (c514:01E01040 family) with three boards: with a scene id
   (>= 0) it clears the scene, sets a 20-frame countdown, binds the camera's model, sets up three sprite objects
   (side by the model's first byte), three rects (texture 6, 0x20 wide, grey, 2 frames) with their anims at
   50..59, scale 0.1 and heights 10/20/30 (40/50/60 for model ids 0..5); otherwise it steps each board, eases the
   scales to 1 for 12 ticks (and on the last board eases the model's position and fades its colour), then grows
   them by 0.3 and fades them out; returns 8 when the countdown runs out */

typedef struct {
    f32 sc[3];
    u8 padC[4];
    s32 w10;
    u8 pad14[0xC];
    Vec4f pos;
    u8 pad30[0x40];
} Obj_c532_01E01040;

typedef struct {
    s32 v[4];
    u8 pad10[0x90];
} Anim_c532_01E01040;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    u8 col[4];
    s32 w38;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Rect_c532_01E01040;

typedef struct {
    Obj_c532_01E01040 obj[3];
    Anim_c532_01E01040 anim[3];
    Rect_c532_01E01040 rect[3];
    f32 p[3];
    u8 pad45C[4];
    u8 col[4];
    s32 model;
    s32 count;
    u8 pad46C[4];
    s32 tick;
} Scene_c532_01E01040;

extern void c532_01E00120(void *, void *, s32, f32);
extern void c532_01E00460(s32, void *, void *, void *);

static s32 func_01E01040_c532(s32 arg0, s32 id) {
    Scene_c532_01E01040 *g = (Scene_c532_01E01040 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_00103260(void *, s32);
    extern void func_001F53B0(s32, void *);
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_00103390(f32 *, f32, f32);
    extern void func_00103540(f32 *, f32, f32);
    extern void func_00103470(u8 *, s32, s32);
    extern void func_001032C0(u8 *, s32, s32);
    extern s32 func_001F5EC0(s32);
    extern void func_001F6340(s32, f32 *);
    extern void func_001F62B0(s32, f32 *);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5E40(s32, u8 *);
    extern void func_001F5DE0(s32, u8 *);
    s32 t[4];
    s32 ot;
    s32 i;

    ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x480);
        g->count = 20;
        g->tick = 0;
        g->model = func_001F5380();
        func_001F5970(g->model, 1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->obj[i]);
            if (*(u8 *)&g->model == 0) {
                func_001F53B0(1, &g->obj[i].pos);
            } else {
                func_001F53B0(0, &g->obj[i].pos);
            }
        }
        func_00103260(t, 6);
        for (i = 0; i < 3; i++) {
            g->rect[i].w38 = 1;
            g->rect[i].r[0] = 0;
            g->rect[i].r[1] = 0;
            g->rect[i].r[2] = 0x20;
            g->rect[i].r[3] = 0x20;
            g->rect[i].r[4] = 0;
            g->rect[i].r[5] = 0;
            g->rect[i].r[6] = 0x80;
            g->rect[i].r[7] = 0x40;
            g->rect[i].f30 = 1.0f;
            g->rect[i].col[0] = g->rect[i].col[1] = g->rect[i].col[2] = 0x80;
            g->rect[i].col[3] = 0x80;
            g->rect[i].h48 = 0;
            g->rect[i].h4A = 0;
            g->rect[i].h4E = 2;
            g->rect[i].h4C = g->rect[i].h4E - 1;
            g->rect[i].h50 = 0;
            g->rect[i].h52 = 999;
            g->anim[i].v[2] = 1;
            c532_01E00120(g->rect[i].r, &g->anim[i], t[0], 50.0f + func_0019A5C8() % 10);
            g->obj[i].sc[0] = g->obj[i].sc[1] = g->obj[i].sc[2] = 0.1f;
            g->obj[i].w10 = 0x4000;
            if (*(u8 *)&g->model > 5) {
                g->obj[i].pos.y = 10.0f * (i + 1);
            } else {
                g->obj[i].pos.y = 10.0f * (i + 4);
            }
        }
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->obj[i]);
        g->obj[i].w10 = 0x4000;
        c532_01E00460(ot, g->rect[i].r, &g->anim[i], &g->obj[i]);
        if (g->tick < 12) {
            func_00103390(&g->obj[i].sc[0], 1.0f, 0.2f);
            func_00103390(&g->obj[i].sc[1], 1.0f, 0.2f);
            func_00103390(&g->obj[i].sc[2], 1.0f, 0.2f);
            if (i == 2) {
                if (func_001F5EC0(g->model) != 0) {
                    func_001F6340(g->model, g->p);
                    func_00103390(&g->p[0], 1.0f, 0.3f);
                    func_00103390(&g->p[2], 1.0f, 0.3f);
                    func_00103540(&g->p[1], 1.0f, 0.6f);
                    func_001F62B0(g->model, g->p);
                }
                if (func_001F5AF0(g->model) != 0) {
                    func_001F5E40(g->model, g->col);
                    func_001032C0(&g->col[3], 0x80, 0x30);
                    func_001F5DE0(g->model, g->col);
                }
            }
        } else {
            g->obj[i].sc[0] += 0.3f;
            g->obj[i].sc[1] += 0.3f;
            g->obj[i].sc[2] += 0.3f;
            func_00103470(&g->rect[i].col[3], 0, 0x20);
        }
    }
    g->tick++;
    if (--g->count <= 0) {
        return 8;
    }
    return 0;
}
