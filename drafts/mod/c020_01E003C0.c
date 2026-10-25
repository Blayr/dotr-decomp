#include "common.h"

/* shape c020:01E003C0, 203 insns: the c020 module's main step (c017:01E010C0 family): with a code it clears the scene,
   fills the 0..90 degree table (ctx+0x3250) and four 9-step tables at 0, 40, .. 320 and 40, 80, .. 360 degrees
   (func_001A6A88 / func_001A6898), keeps the code and a 90-tick timer; otherwise it runs the scene setup
   (c020:01E00080), steps the 220 entries of 0x38 bytes (c020:01E001C0 for plain ones; others swing 4 x the table at
   their phase, the phase climbs 30 to 180 while two counters grow, and past 90 both sizes shrink by 28 until it ends),
   then draws each live one twice through c020:01E00A80 or c020:01E00E50; counts down and returns 8 at the end */

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[0x14];
    s16 h28;
    s16 h2A;
    s16 used;
    s16 phase;
    s16 h30;
    s16 h32;
    s16 h34;
    u8 pad36[2];
} Ent_c020_01E003C0;

typedef struct {
    u8 pad0[0x170];
    Ent_c020_01E003C0 ent[220];
    s32 timer;
    u8 pad3194[8];
    s32 ot;
    u8 pad31A0[0x320E - 0x31A0];
    s16 code;
    u8 pad3210[0x3250 - 0x3210];
    f32 tab[91];
    f32 s0[10];
    f32 c0[10];
    f32 s1[10];
    f32 c1[10];
} Ctx_c020_01E003C0;

extern void c020_01E00080(Ctx_c020_01E003C0 *, s32);
extern void c020_01E001C0(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *);
extern void c020_01E00A80(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *, void *, s32);
extern void c020_01E00E50(Ctx_c020_01E003C0 *, Ent_c020_01E003C0 *, void *, s32);

static s32 func_01E003C0_c020(s32 arg0, s32 code) {
    Ctx_c020_01E003C0 *g = (Ctx_c020_01E003C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern f32 func_001A6A88(f32);
    extern f32 func_001A6898(f32);
    extern f32 func_00108030(void *, s16, s32);
    s32 n;
    u8 pkt[0x90];
    s32 i;
    s32 j;
    s32 b;
    f32 t;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3460);
        for (; n < 91; n++) {
            g->tab[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        b = 40;
        for (j = 0, n = 0; j < 9; j++) {
            t = 3.1415927f * n / 180.0f;
            g->s0[j] = func_001A6A88(t);
            g->c0[j] = func_001A6898(t);
            t = 3.1415927f * b / 180.0f;
            g->s1[j] = func_001A6A88(t);
            g->c1[j] = func_001A6898(t);
            n += 40;
            b += 40;
        }
        g->code = code;
        g->timer = 90;
        return 0;
    }
    c020_01E00080(g, 0);
    for (i = 0; i < 220; i++) {
        if (g->ent[i].used != 0) {
            if (g->ent[i].f10 == 0) {
                c020_01E001C0(g, &g->ent[i]);
            } else {
                g->ent[i].h30 = 4.0f * func_00108030(g->tab, g->ent[i].phase, 0);
                if (g->ent[i].phase < 180) {
                    g->ent[i].phase += 30;
                    g->ent[i].h34 += 1;
                    g->ent[i].h32 += 2;
                }
                if (g->ent[i].phase > 90) {
                    if (g->ent[i].h28 > 30) {
                        g->ent[i].h28 -= 28;
                    }
                    if (g->ent[i].h2A > 30) {
                        g->ent[i].h2A -= 28;
                    } else {
                        g->ent[i].used = 0;
                    }
                }
            }
        }
    }
    for (i = 0; i < 220; i++) {
        if (g->ent[i].used != 0) {
            n++;
            if (g->ent[i].f10 == 0) {
                c020_01E00A80(g, &g->ent[i], pkt, 0);
                c020_01E00A80(g, &g->ent[i], pkt, 1);
            } else {
                c020_01E00E50(g, &g->ent[i], pkt, 0);
                c020_01E00E50(g, &g->ent[i], pkt, 1);
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
