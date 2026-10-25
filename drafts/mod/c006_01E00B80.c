#include "common.h"

/* shape c006:01E00B80, 223 insns: the c006 module's main step: with a code it clears the scene, fills the cosine table
   (0..90 degrees at ctx+0x29A4), keeps the code and a 162-tick timer, textures (4,2) and (4,15), sets up the cards
   (c006:01E00710) and keeps the target's view mask; otherwise it runs the scene step (c006:01E00080) and every live
   slot's handler (80 of 0x58 bytes), draws the slots at the camera point (func_001F9D30) turned a quarter, scale
   (0.5, 0.2, 0.5), two passes each; above tick 10 it runs the 22 card followers (c006:01E008F0), below it hands each
   live, unmasked card (id, or id + 245 past 10) back to the model: scale 0.15, not busy, its position and turn, card
   on 0x18; counts down and returns 8 when the timer ends */

typedef struct {
    f32 x, y, z, w;
} V4_c006_01E00B80;

typedef struct Slot_c006_01E00B80 {
    u8 pad0[0x30];
    s32 (*draw)(void *, struct Slot_c006_01E00B80 *, void *, s32);
    s32 (*fn)(void *, struct Slot_c006_01E00B80 *);
    u8 pad38[0x10];
    s16 used;
    u8 pad4A[0xE];
} Slot_c006_01E00B80;

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x68];
} Card_c006_01E00B80;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x68];
    s32 texA8;
    u8 padAC[0x30];
    s32 texDC;
    s32 rot[4];
    u8 padF0[0x10];
    V4_c006_01E00B80 sc;
    Slot_c006_01E00B80 slot[80];
    Card_c006_01E00B80 card[22];
    u8 pad2630[0x2780 - 0x2630];
    s32 crot[22][4];
    u8 pad28E0[0x2910 - 0x28E0];
    s32 timer;
    u8 pad2914[8];
    s32 ot;
    u8 pad2920[0x295C - 0x2920];
    u32 mask;
    u8 pad2960[0x296C - 0x2960];
    s16 code;
    u8 pad296E[0x29A4 - 0x296E];
    f32 cos[91];
} Ctx_c006_01E00B80;

extern void c006_01E00080(Ctx_c006_01E00B80 *, s32);
extern void c006_01E00710(Ctx_c006_01E00B80 *);
extern s32 c006_01E008F0(Ctx_c006_01E00B80 *, Card_c006_01E00B80 *, s32);

static s32 func_01E00B80_c006(s32 arg0, s32 code) {
    Ctx_c006_01E00B80 *g = (Ctx_c006_01E00B80 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_001F5380(void);
    extern V4_c006_01E00B80 *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_001F5EC0(s32);
    extern void func_00107370(s32, s32, f32);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5C40(s32, void *);
    extern void func_00107650(s32, s32);
    s32 n;
    V4_c006_01E00B80 pos;
    u8 pkt[0x90];
    s32 (*draw)();
    s32 i;
    s32 id;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2B10);
        for (i = 0; i < 91; i++) {
            g->cos[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->code = code;
        g->timer = 162;
        g->texA8 = func_00202BF0(4, 2);
        g->texDC = func_00202BF0(4, 15);
        c006_01E00710(g);
        g->mask = func_001F5380();
        return 0;
    }
    c006_01E00080(g, 0);
    for (i = 0; i < 80; i++) {
        if (g->slot[i].used != 0) {
            draw = g->slot[i].fn;
            if (draw != NULL) {
                draw(g, &g->slot[i]);
            }
        }
    }
    pos.x = pos.y = pos.z = 0.0f;
    pos.y = 50.0f;
    pos = *func_001F9D30(0);
    func_00205C40((s32)g->rot);
    g->rot[0] += 0x4000;
    g->sc.y = 0.2f;
    g->sc.x = 0.5f;
    g->sc.z = 0.5f;
    func_00205C40((s32)g->rot);
    for (i = 0; i < 80; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            draw = g->slot[i].draw;
            if (draw != NULL) {
                draw(g, &g->slot[i], pkt, 0);
                draw(g, &g->slot[i], pkt, 1);
            }
        }
    }
    if (g->timer > 10) {
        for (i = 0; i < 22; i++) {
            c006_01E008F0(g, &g->card[i], i);
        }
    } else {
        for (i = 0; i < 22; i++) {
            id = i;
            if (i > 10) {
                id = i + 245;
            }
            if (!((g->mask >> (21 - i)) & 1)) {
                if (g->timer < 10) {
                    if (func_001F5EC0(id) != 0) {
                        func_00107370(id, 0, 0.15f);
                    }
                    if (func_001F5AF0(id) != 0) {
                        func_001F5970(id, 0);
                        g->card[i].w4 = 0;
                        func_001F5B70(id, &g->card[i]);
                        func_001F5C40(id, g->crot[i]);
                        func_00107650(id, 0x18);
                    }
                }
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
