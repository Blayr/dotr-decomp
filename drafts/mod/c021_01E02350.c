#include "common.h"

/* shape c021:01E02350, 308 insns: c056:01E00800-style scene manager. code >= 0 initialises (clear 0x3910 bytes, the
   sine table, the 18-step cos/sin tables at 0, 20 .. and 20, 40 .., phase 0, code, timer 0xCC, texture 15, the 22
   models via c021:01E01C50, fade 0x80, the pad state); otherwise runs the scene step, from phase 9 every live
   slot's update, then draws every live slot with the scene scale (slots of c021:01E00B90 take their own turned and
   scaled transform); before phase 8 the 22 cards are shown by the pad bits and the fade drops 12, after it the 22
   objects run c021:01E01F60 (timer > 10) or c021:01E01E10 with the fade rising 16; the first quiet frame caps the
   timer at 30; the timer counts down, 8 when done */

typedef struct {
    u8 pad0[0x20];
    u8 rot[0x10];
    Vec4f pos;
    u8 pad40[0x30];
    s32 (*draw)(void *, void *, void *, s32);
    void (*fn)(void *, void *);
    u8 pad78[0xC];
    s16 used;
    u8 pad86[0xE];
} Slot_c021_01E02350;

typedef struct {
    u8 b[0x70];
} Obj_c021_01E02350;

typedef struct {
    u8 pad0[0x40];
    u8 m40[0x40];
    s32 tex[16];
    u8 padC0[0x120 - 0xC0];
    Slot_c021_01E02350 slot[65];
    u8 pad26C0[0x26C0 - 0x120 - 65 * 0x94];
    Obj_c021_01E02350 obj[22];
    u8 pad3260[0x3360 - 0x26C0 - 22 * 0x70];
    f32 scale[4];
    u8 pad3370[0x3578 - 0x3370];
    s32 timer;
    u8 pad357C[8];
    s32 ot;
    u8 pad3588[0x35E4 - 0x3588];
    u8 sin[0x3750 - 0x35E4];
    f32 c[20];
    f32 s[20];
    f32 c2[20];
    f32 s2[20];
    u8 pad3890[0x38A0 - 0x3890];
    u32 bits;
    u8 pad38A4[6];
    s16 capped;
    s16 busy;
    s16 fade;
    u8 pad38B0[6];
    s16 code;
    u8 pad38B8[2];
    s16 phase;
} Ctx_c021_01E02350;

static s32 func_01E00080_c021();
static s32 func_01E00B90_c021();
static void func_01E01C50_c021();
static s32 func_01E01E10_c021();
static s32 func_01E01F60_c021();

static s32 func_01E02350_c021(Ctx_c021_01E02350 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00107C10(void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern u32 func_001F5380();
    extern void func_00107180(s32, s32, s32, s32);
    extern void func_00107280(s32, void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00205C40(void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_001F6CF0(s32);
    f32 rot[4];
    Vec4f pos;
    f32 sc[4];
    u8 pkt[0x90];
    s32 k;
    s32 (*draw)(void *, void *, void *, s32);
    s32 i;
    s32 n;
    s32 d;
    Ctx_c021_01E02350 *q;
    s32 d2;
    s32 m;
    f32 a;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3910);
        func_00107C10(g->sin);
        d2 = 20;
        for (i = 0, d = 0, q = g; i < 18; i++) {
            a = 3.1415927f * d / 180.0f;
            q->c[0] = func_001A6A88(a);
            q->s[0] = func_001A6898(a);
            a = 3.1415927f * d2 / 180.0f;
            q->c2[0] = func_001A6A88(a);
            q->s2[0] = func_001A6898(a);
            d += 20;
            q = (Ctx_c021_01E02350 *)((f32 *)q + 1);
            d2 += 20;
        }
        g->phase = 0;
        g->code = code;
        g->timer = 0xCC;
        for (k = 15; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        func_01E01C50_c021(g);
        g->fade = 0x80;
        g->bits = 0x3FF7FE;
        g->bits = func_001F5380();
        return 0;
    }
    func_01E00080_c021(g, 0);
    if (g->phase > 8) {
        for (i = 0; i < 65; i++) {
            if (g->slot[i].used != 0) {
                if (g->slot[i].fn != NULL) {
                    g->slot[i].fn(g, &g->slot[i]);
                }
            }
        }
    }
    func_00106DD0(g->scale, 1.5f, 0.5f, 1.5f);
    func_00106DD0(sc, 1.5f, 0.3f, 1.5f);
    for (i = 0; i < 65; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_0020EB40(g->m40);
            if (g->slot[i].fn != (void *)func_01E00B90_c021) {
                func_0020C940(g, g->scale, g->slot[i].rot, NULL);
                func_0020BC00(g->m40, g);
            } else {
                func_00205C40(rot);
                pos = g->slot[i].pos;
                func_00108950(&pos, g->slot[i].rot, 0, g->sin);
                func_0020C940(g, sc, rot, &pos);
                func_0020BC00(g->m40, g);
            }
            draw = g->slot[i].draw;
            if (draw != NULL) {
                draw(g, &g->slot[i], pkt, 0);
                draw(g, &g->slot[i], pkt, 1);
            }
        }
    }
    if (g->phase < 8) {
        for (i = 0; i < 22; i++) {
            m = i;
            if (i > 10) {
                m = i + 245;
            }
            func_00107180(m, 0, g->timer, 1);
            if (!((g->bits >> (21 - i)) & 1)) {
                func_00107280(m, &g->obj[i], 0);
            }
        }
        g->fade -= 12;
        if (g->fade < 0) {
            g->fade = 0;
        }
        g->busy = 1;
    } else if (g->timer > 10) {
        for (i = 0; i < 22; i++) {
            func_01E01F60_c021(g, &g->obj[i], i);
        }
    } else {
        for (i = 0; i < 22; i++) {
            func_01E01E10_c021(g, &g->obj[i], i);
        }
        g->fade += 16;
        if (g->fade > 0x80) {
            g->fade = 0x80;
        }
    }
    func_001F6CF0((u8)g->fade);
    if (g->busy == 0 && g->capped == 0) {
        g->capped = 1;
        if (g->timer > 30) {
            g->timer = 30;
        }
    }
    g->busy = 0;
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
