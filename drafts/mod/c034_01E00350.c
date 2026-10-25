#include "common.h"

/* shape c034:01E00350, 176 insns: c015:01E002E0 family scene step: on a code (>= 0) clears the scene, fills a 91-entry table (ctx+0xDDC) with func_001A6A88 of each degree in radians, keeps the code and a 43-tick timer; else steps it (c034:01E00080) and, from stage 9, runs the 10 slots' step callbacks, aims the camera 50 above the model's anchor (func_001E11B0) and 32 to one side, sets the light levels 0.6/0.3/0.6 and draws each slot twice; under stage 8 burns 22 func_001F5380 calls; returns 8 when the timer runs out */

typedef struct {
    f32 x, y, z, w;
} V4_c034_01E00350;

typedef struct Slot_c034_01E00350 {
    u8 pad0[8];
    void (*draw)(void *, struct Slot_c034_01E00350 *, void *, s32);
    void (*fn)(void *, struct Slot_c034_01E00350 *);
    u8 pad10[0xC];
    s16 used;
    u8 pad1E[6];
} Slot_c034_01E00350;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x90];
    f32 fD0;
    f32 fD4;
    f32 fD8;
    u8 padDC[0x110 - 0xDC];
    Slot_c034_01E00350 slot[10];
    u8 pad278[0xD74 - 0x278];
    s32 timer;
    u8 padD78[8];
    s32 ot;
    u8 padD84[0xDCC - 0xD84];
    s16 code;
    u8 padDCE[2];
    s16 stage;
    u8 padDD2[0xDDC - 0xDD2];
    f32 tbl[91];
} Ctx_c034_01E00350;

extern void c034_01E00080(Ctx_c034_01E00350 *, s32);

static s32 func_01E00350_c034(s32 arg0, s32 code) {
    Ctx_c034_01E00350 *g = (Ctx_c034_01E00350 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_001E11B0(s32, s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    V4_c034_01E00350 a;
    V4_c034_01E00350 b;
    u8 pkt[0x90];
    s32 i;
    s32 k;
    void (*d)(void *, Slot_c034_01E00350 *, void *, s32);

    g->ot = func_00207500();
    if (code >= 0) {
        b.x = b.y = b.z = 0.0f;
        func_00195108(g, 0xF50);
        for (i = 0; i < 91; i++) {
            g->tbl[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->code = code;
        g->timer = 43;
        return 0;
    }
    c034_01E00080(g, 0);
    if (g->stage > 8) {
        for (i = 0; i < 10; i++) {
            if (g->slot[i].used != 0) {
                if (g->slot[i].fn != NULL) {
                    g->slot[i].fn(g, &g->slot[i]);
                }
            }
        }
        func_001F5BD0(func_001F5380(), &a);
        k = func_001F5380() >> 8;
        func_001E11B0(k, func_001F5380() & 0xF, &a);
        b.x = a.x;
        b.y = a.y;
        b.z = a.z;
        b.y += 50.0f;
        if (func_001F5380() >> 8 == 0) {
            b.z -= 32.0f;
        } else {
            b.z += 32.0f;
        }
        g->fD8 = 0.6f;
        g->fD0 = 0.6f;
        g->fD4 = 0.3f;
        func_0020EB40(g->cam);
        func_0020C940(g, NULL, NULL, &b);
        func_0020BC00(g->cam, g);
        for (i = 0; i < 10; i++) {
            if (g->slot[i].used != 0) {
                d = g->slot[i].draw;
                if (d != NULL) {
                    d(g, &g->slot[i], pkt, 0);
                    d(g, &g->slot[i], pkt, 1);
                }
            }
        }
    }
    if (g->stage < 8) {
        for (i = 0; i < 22; i++) {
            func_001F5380();
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
