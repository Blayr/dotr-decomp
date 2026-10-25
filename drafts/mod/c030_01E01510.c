#include "common.h"

/* shape c030:01E01510, 233 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, builds a 91-entry sine
   table, sets the timer to 38 and loads texture 15; otherwise it runs every live slot's update, then lights and draws
   each (four light settings by kind), keeps the 22 units' draws going and counts the timer down (8 when it ends) */

typedef struct {
    f32 x, y, z;
} V3_c030_01E01510;

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x28];
    void (*draw)(void *, void *, void *, s32);
    void (*update)(void *, void *);
    u8 pad60[8];
    s16 live;
    u8 pad6A[6];
    s16 kind;
    u8 pad72[0xA];
} Slot_c030_01E01510;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x50];
    s32 tex[20];
    u8 lightE0[0x10];
    s32 timer;
    u8 padF4[8];
    s32 ot;
    u8 pad100[4];
    void *fn;
    u8 pad108[0x50];
    f32 sin[91];
    u8 pad2C4[0x1C];
    s16 mode;
    u8 pad2E2[2];
    s16 h2E4;
    u8 pad2E6[0x4E];
    Slot_c030_01E01510 slot[65];
    u8 unit[22][0x70];
} Scene_c030_01E01510;

static s32 func_01E01510_c030(s32 arg0, s32 arg) {
    Scene_c030_01E01510 *g = (Scene_c030_01E01510 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_01E00080_c030();
    extern void func_01E01110_c030(void *);
    extern void func_01E012A0_c030(void *, void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_001F5EC0(s32);
    extern void func_001F5AF0(s32);
    void (*draw)(void *, void *, void *, s32);
    u8 buf[0x90];
    Vec4f v;
    Vec4f at;
    s32 k;
    s32 n;
    s32 i;
    s32 id;

    n = 0;
    g->ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0x2DA0);
        g->fn = func_01E00080_c030;
        for (k = 0; k < 91; k++) {
            g->sin[k] = func_001A6A88(3.1415927f * k / 180.0f);
        }
        g->mode = arg;
        g->timer = 0x26;
        for (k = 15; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        func_01E01110_c030(g);
        return 0;
    }
    func_01E00080_c030(g, 0);
    if (g->h2E4 > 0) {
        for (i = 0; i < 65; i++) {
            if (g->slot[i].live != 0 && g->slot[i].update != NULL) {
                g->slot[i].update(g, &g->slot[i]);
            }
        }
        func_001F5BD0(func_001F5380(), &v);
        at.x = v.x;
        at.y = v.y;
        at.z = v.z;
        for (i = 0; i < 65; i++) {
            if (g->slot[i].live != 0) {
                n++;
                func_0020EB40(g->m40);
                if (g->slot[i].kind == 0) {
                    func_00106DD0(g->lightE0, 1.6f, 4.0f, 1.6f);
                }
                if (g->slot[i].kind == 1) {
                    func_00106DD0(g->lightE0, 1.2f, 8.0f, 1.2f);
                }
                if (g->slot[i].kind == 2) {
                    func_00106DD0(g->lightE0, 1.0f, 11.0f, 1.0f);
                }
                if (g->slot[i].kind == 3) {
                    func_00106DD0(g->lightE0, 1.6f, 1.0f, 1.6f);
                }
                func_0020C940(g, g->lightE0, &g->slot[i].pos, &at);
                func_0020BC00(g->m40, g);
                draw = g->slot[i].draw;
                if (draw != NULL) {
                    draw(g, &g->slot[i], buf, 0);
                    draw(g, &g->slot[i], buf, 1);
                }
            }
        }
    }
    if (g->h2E4 >= 0) {
        if (g->timer >= 4) {
            for (i = 0; i < 22; i++) {
                func_01E012A0_c030(g, g->unit[i], i);
            }
        }
        if (g->timer < 10) {
            for (i = 0; i < 22; i++) {
                id = i < 11 ? i : i + 0xF5;
                if (func_001F5380() != id && *(s32 *)((u8 *)g + 0x4478) < 10) {
                    func_001F5EC0(id);
                    func_001F5AF0(id);
                }
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->timer > 0) {
        return 0;
    }
    return 8;
}
