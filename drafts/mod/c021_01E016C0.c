#include "common.h"

/* shape c021:01E016C0, 355 insns: a falling ribbon node in the scene's orbit rings: turns -4 a tick (wrapped); finds
   the first ring above its height and takes its place between that ring and the one below (func_001098E0, twice:
   0x40 and its position), shrinking its radii toward 10i+5 / 11i+5 from phase 8; radii shrink by the scene speed
   (g+0x3898) or 1, it sinks by the speed and its top follows 13 above; at the bottom it unlinks and ends; under
   radius 6 it fades; once (0x8E) below height 180 it hands itself to the scene as the light target and, before
   tick 180, spawns a c021:01E03060 node of itself; fades in 15 (before phase 8), out 16 (timer < 18) or in 10 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[8];
    s16 ang;
    s16 r;
} Ring_c021_01E016C0;

typedef struct {
    u8 pad0[0x118];
    Ring_c021_01E016C0 ring[6];
} Rings_c021_01E016C0;

typedef struct {
    u8 pad0[0xC0];
    s32 wC0, wC4, wC8;
    u8 padCC[0x3350 - 0xCC];
    Vec4f light;
    u8 pad3360[0x10];
    Rings_c021_01E016C0 rings;
    u8 pad3518[0x3578 - 0x3518];
    s32 timer;
    u8 col[4];
    u8 pad3580[8];
    void *target;
    f32 f358C;
    f32 f3590;
    f32 f3594;
    f32 f3598;
    u8 pad359C[0x3898 - 0x359C];
    f32 speed;
    u8 pad389C[0x38A6 - 0x389C];
    s16 lang;
    u8 pad38A8[8];
    s16 h38B0;
    u8 pad38B2[2];
    s16 h38B4;
    u8 pad38B6[4];
    s16 phase;
    u8 pad38BC[8];
    s16 h38C4;
} Game_c021_01E016C0;

typedef struct Node_c021_01E016C0 {
    Vec4f pos;
    u8 pad10[0x30];
    Vec4f v40;
    u8 pad50[0x10];
    f32 bot;
    f32 top;
    s32 w68;
    struct Node_c021_01E016C0 *link;
    u8 pad70[0xC];
    u8 c7C[4];
    u8 c80[4];
    s16 state;
    u8 c86;
    u8 c87;
    u8 pad88[4];
    s16 ang;
    s16 once;
    u8 pad90[2];
    s16 h92;
} Node_c021_01E016C0;

static void func_01E03060_c021();

static s32 func_01E016C0_c021(Game_c021_01E016C0 *g, Node_c021_01E016C0 *o) {
    extern void func_00106DD0(void *, f32, f32, f32);
    extern Vec4f func_001098E0(Vec4f *, Vec4f *, void *, void *);
    Vec4f up;
    Vec4f c;
    s32 i;
    Rings_c021_01E016C0 *rings;

    rings = &g->rings;
    func_00106DD0(&up, 0.0f, o->bot, 0.0f);
    c.y = 0.0f;
    o->ang -= 4;
    if (o->ang <= 360) {
        o->ang %= 360;
    }
    for (i = 1; i < 8; i++) {
        if (rings->ring[i].y > o->bot) {
            c.x = rings->ring[0].x;
            c.z = rings->ring[0].z;
            o->v40 = func_001098E0(&c, &up, &rings->ring[i - 1], &rings->ring[i]);
            o->pos = func_001098E0(&c, &up, &rings->ring[i - 1], &rings->ring[i]);
            if (g->phase > 7) {
                if (o->c86 >= i * 10 + 5) {
                    o->c86 -= 3;
                }
                if (o->c87 >= i * 11 + 5) {
                    o->c87 -= 3;
                }
            }
            i = 8;
        }
    }
    if (g->speed < 2.0f) {
        if (o->c86 > 3) {
            o->c86 -= 1;
        }
    } else if (o->c86 > 3) {
        o->c86 = (u32)o->c86 - g->speed;
    }
    if (g->speed < 2.0f) {
        if (o->c87 > 3) {
            o->c87 -= 1;
        }
    } else if (o->c87 > 3) {
        o->c87 = (u32)o->c87 - g->speed;
    }
    if (o->bot > 0.0f) {
        o->bot -= g->speed;
        if (o->top - o->bot >= 13.0f) {
            o->top -= g->speed;
        }
    } else {
        o->top -= g->speed;
        if (o->top < o->bot) {
            o->top = o->bot;
            if (o->link != NULL) {
                o->link->w68 = 0;
            }
            o->state = 0;
        }
    }
    if (o->c87 < 6) {
        if (o->c7C[3] > 0x10) {
            o->c7C[3] -= 0x10;
        }
        if (o->c80[3] > 0x10) {
            o->c80[3] -= 0x10;
        }
    }
    if (o->once > 0 && o->top < 180.0f) {
        g->target = o;
        g->f3594 = 160.0f;
        g->f3590 = 160.0f;
        g->col[3] = o->c7C[3];
        g->col[0] = o->c7C[0];
        g->col[1] = o->c7C[1];
        g->col[2] = o->c7C[2];
        g->h38B0 = 1;
        g->f3598 = o->top;
        g->h38B4 = 1;
        g->light = o->pos;
        g->wC4 = 0;
        g->wC0 = 0;
        g->wC8 = 0;
        g->lang = o->ang + 15;
        if (o->h92 != 0) {
            g->h38C4 = 0;
        } else {
            g->h38C4 = 1;
        }
        if (g->phase < 180) {
            func_01E03060_c021(g, func_01E016C0_c021);
        }
        o->once = 0;
    }
    if (g->phase < 8) {
        if (o->c7C[3] < 0x50) {
            o->c7C[3] += 0xF;
        }
        if (o->c80[3] < 0x50) {
            o->c80[3] += 0xF;
        }
    } else if (g->timer < 18) {
        if (o->c7C[3] > 0x10) {
            o->c7C[3] -= 0x10;
        }
        if (o->c80[3] > 0x10) {
            o->c80[3] -= 0x10;
        }
    } else {
        if (o->c7C[3] < 0x50) {
            o->c7C[3] += 0xA;
        }
        if (o->c80[3] < 0x50) {
            o->c80[3] += 0xA;
        }
    }
    if (g->timer < 11) {
        o->state = 0;
    }
    return 0;
}
