#include "common.h"

/* shape c544:01E01F60, 331 insns, 1 copy: c544's scene manager: with a code it clears the scene (5-tick count, 46-tick
   timer, grey 0x80), reads the effect position, sets up 8 blue trails (texture 15, delays 5, 7, .., 19), a blue glow
   sprite and a white second sprite on texture 11; otherwise it steps the model and its emitter, fades the scene grey
   after tick 36, and while the emitter is lit redraws each trail (the glow follows a trail's last point when its
   delay runs out), re-rolling a trail's points once it fades; returns 8 when the timer ends */

typedef struct Pt_c544_01E01F60 {
    f32 x, y, z, w;
} Pt_c544_01E01F60;

typedef struct Trail_c544_01E01F60 {
    u8 hdr[4];
    u8 b, g, r, a;
    u8 pad8[4];
    s16 delay;
    u8 padE[2];
    s16 h80;
    s16 h82;
    s16 h84;
    s16 h86;
    s16 h88;
    s16 h8A;
    u8 pad1C[0x10];
    f32 f9C;
    Pt_c544_01E01F60 pts[5];
} Trail_c544_01E01F60;

typedef struct Emit_c544_01E01F60 {
    s16 rect[8];
    u8 pad10[0x20];
    f32 scale;
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
} Emit_c544_01E01F60;

typedef struct Game_c544_01E01F60 {
    u8 pad0[0x20];
    u8 pos[0x50];
    Trail_c544_01E01F60 trail[8];
    u8 d470[8];
    s32 w478;
    u8 pad47C[8];
    f32 f484;
    u8 pad488[0x88];
    Emit_c544_01E01F60 e2;
    s32 tex;
    u8 pad574[4];
    f32 size;
    u8 b, g, r, a;
    f32 at[3];
    u8 pad58C[4];
    Emit_c544_01E01F60 e1;
    s32 count;
    s32 timer;
    s32 code;
    s32 w5FC;
    u8 grey;
} Game_c544_01E01F60;

static s32 func_01E01F60_c544(s32 arg0, s32 code) {
    Game_c544_01E01F60 *g = (Game_c544_01E01F60 *)arg0;
    extern void func_00103260();
    extern void func_001F53B0();
    extern void func_001F6CF0();
    extern s32 func_00103470();
    extern s32 func_001032C0();
    extern void c544_01E00B00(void *, void *, s32, f32);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 j;

    ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108((s32)g, 0x610);
        g->w5FC = 0;
        g->count = 5;
        g->timer = 46;
        g->code = code;
        g->grey = 0x80;
        func_00103890(g);
        func_001F53B0(0, g->pos);
        func_00103260(&tex, 0xF);
        for (i = 0; i < 8; i++) {
            g->trail[i].h80 = 10;
            g->trail[i].h82 = 0;
            g->trail[i].h84 = 0x2C;
            g->trail[i].h86 = 0x80;
            g->trail[i].h88 = 10;
            g->trail[i].h8A = 0;
            g->trail[i].f9C = 11.0f;
            g->trail[i].r = 0x60;
            g->trail[i].g = 0x60;
            g->trail[i].b = 0xB0;
            g->trail[i].a = 0x80;
            func_01E01A20_c544((void *)&g->trail[i], tex, 160.0f);
            g->trail[i].delay = i * 2 + 5;
        }
        g->e1.scale = 1.0f;
        g->e1.w38 = 3;
        g->e1.rect[0] = 0xB0;
        g->e1.rect[1] = 0x40;
        g->e1.rect[2] = 0x20;
        g->e1.rect[3] = 0x20;
        g->e1.rect[4] = 0xB0;
        g->e1.rect[5] = 0x40;
        g->e1.rect[6] = 0x80;
        g->e1.rect[7] = 0x40;
        g->e1.h48 = 0;
        g->e1.h4A = 0;
        g->e1.h4E = 2;
        g->e1.h52 = 999;
        g->e1.h50 = 0;
        g->e1.h4C = g->e1.h4E - 1;
        g->e1.r = 0x60;
        g->e1.g = 0x60;
        g->e1.b = 0xB0;
        g->e1.a = 0x80;
        g->tex = tex;
        g->at[2] = 0.0f;
        g->at[1] = 0.0f;
        g->at[0] = 0.0f;
        g->size = 10.0f;
        g->r = 0x80;
        g->g = 0x80;
        g->b = 0x80;
        g->a = 0x80;
        g->at[1] = 5.5f;
        func_00103260(&tex, 0xB);
        g->e2.scale = 1.0f;
        g->e2.w38 = 3;
        g->e2.rect[0] = 0;
        g->e2.rect[1] = 0;
        g->e2.rect[2] = 0x40;
        g->e2.rect[3] = 0x40;
        g->e2.rect[4] = 0;
        g->e2.rect[5] = 0;
        g->e2.rect[6] = 0x80;
        g->e2.rect[7] = 0x40;
        g->e2.h48 = 0;
        g->e2.h4A = 1;
        g->e2.h4E = 1;
        g->e2.h52 = 999;
        g->e2.h50 = 0;
        g->e2.h4C = g->e2.h4E - 1;
        g->e2.r = 0x80;
        g->e2.g = 0x80;
        g->e2.b = 0x80;
        g->e2.a = 0;
        g->w478 = 1;
        c544_01E00B00(&g->e2, g->d470, tex, 50.0f);
        g->f484 = 160.0f;
        return 0;
    }
    func_001039A0(g);
    func_001F6CF0(g->grey);
    func_01E00E40_c544(ot, (void *)&g->e2, (void *)g->d470, (void *)g);
    if (g->timer > 36) {
        func_00103470(&g->grey, 0x20, 0x10);
    }
    if (g->timer < 10) {
        func_00103470(&g->e2.a, 0, 0x10);
        func_001032C0(&g->grey, 0x80, 0x10);
    } else if (!func_001032C0(&g->e2.a, 0x80, 0x10)) {
        for (i = 0; i < 8; i++) {
            if (g->trail[i].a < 0x60) {
                g->trail[i].h80 = g->trail[i].h88 + g->trail[i].h84;
            } else if (g->trail[i].a < 0x40) {
                g->trail[i].h80 = g->trail[i].h88 + g->trail[i].h84 * 2;
            }
            if (g->trail[i].delay == 0) {
                g->at[1] = 5.5f - g->trail[i].pts[4].z;
                g->at[0] = g->trail[i].pts[4].x;
                g->at[2] = g->trail[i].pts[4].z;
                g->e1.a = g->trail[i].a;
                func_01E00270_c544(ot, (void *)&g->e1, (void *)&g->tex, (void *)g);
            }
            func_01E01B70_c544(ot, (void *)&g->trail[i], (void *)g);
            if (g->trail[i].delay) {
                g->trail[i].delay--;
            } else if (!func_00103470(&g->trail[i].a, 0, 0x10)) {
                g->trail[i].delay = 5;
                g->trail[i].a = 0x80;
                for (j = 0; j < 5; j++) {
                    if (j == 4) {
                        g->trail[i].pts[j].x = func_0019A5C8() % 30 - 15;
                        g->trail[i].pts[j].z = func_0019A5C8() % 30 - 15;
                    } else {
                        g->trail[i].pts[j].x = func_0019A5C8() % 40 - 20;
                        g->trail[i].pts[j].z = func_0019A5C8() % 30 - 15;
                    }
                }
            }
        }
    }
    if (g->count) {
        g->count--;
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
