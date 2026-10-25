#include "common.h"

/* shape b361:01E01CA0, 323 insns, 1 copy: the module's scene manager: with a scene id (>= 0) it clears the scene, sets the
   220-frame countdown, reads three model ids, texture 5:0 and the camera turn, a 256-byte jitter table and a 256-byte
   step table (100 zeros, 80 of 0..4, the rest +-0..3 by the second camera's turn); otherwise it runs the script step
   (b361:01E00920), the five effect kinds, draws the b361:01E00B80 sprites and b361:01E00D00 discs, the flash pass when
   a flash is live, counts down and returns the next step by frame (90, 210, 195, 101..189) or 8 when it runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x3E];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b361_01E01CA0;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x208];
    Fx_b361_01E01CA0 fx[210];
    u8 pad5EC0[0x60];
    s32 tex[1];
    u8 pad5F24[0x1C];
    s32 count;
    u8 pad5F44[8];
    s32 ot;
    u8 pad5F50[0x28];
    s16 m78;
    s16 m7A;
    s16 m7C;
    u8 pad5F7E[0x14];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 step[0x100];
    u8 pad6198[0x10];
} Scene_b361_01E01CA0;

static s32 func_01E01CA0_b361(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_01E00920_b361();
    extern s32 func_01E00B80_b361();
    extern s32 func_01E00D00_b361();
    extern s32 func_01E00DF0_b361();
    extern s32 func_01E00F70_b361();
    extern s32 func_01E01040_b361();
    extern s32 b361_01E01140();
    extern s32 func_01E01A00_b361();
    extern s32 func_01E022E0_b361();
    extern s32 func_01E024D0_b361();
    extern s32 func_01E026D0_b361();
    s16 n;
    Scene_b361_01E01CA0 *g = (Scene_b361_01E01CA0 *)arg0;
    f32 pos[4];
    s32 rm[4];
    s32 ang[4];
    s32 ang2[4];
    u8 buf[0x90];
    s32 k;
    s32 i;
    s16 t;

    n = 0;
    k = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x6310);
        func_00107C10((u8 *)g + 0x6198);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 220;
        g->m78 = func_001F5560(func_001F53A0(), 1, 1);
        g->m7A = func_001F5560(func_001F53A0(), 1, 0);
        g->m7C = func_001F5560(func_001F53A0(), 1, 0);
        for (; n < 1; n++) {
            g->tex[n] = func_00202BF0(5, n);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 100; i++) {
            g->step[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->step[i] = func_0019A5C8() % 5;
        }
        func_001F6160(func_001F53A0(), ang2);
        t = ang2[1] / 180.0f;
        for (k = 180; k < 0x100; k++) {
            if (t != 0) {
                g->step[k] = func_0019A5C8() % 4;
            } else {
                g->step[k] = -(func_0019A5C8() % 4);
            }
        }
        return 0;
    }
    func_01E00920_b361(g, 0);
    for (i = 0; i < 210; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E00B80_b361) {
                func_01E00B80_b361(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00D00_b361) {
                func_01E00D00_b361(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00DF0_b361) {
                func_01E00DF0_b361(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00F70_b361) {
                func_01E00F70_b361(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01040_b361) {
                func_01E01040_b361(g, &g->fx[i]);
            }
            if (g->fx[i].fn == b361_01E01140) {
                n++;
            }
            if (g->fx[i].fn == func_01E01A00_b361) {
                n++;
            }
        }
    }
    for (i = 0; i < 210; i++) {
        if (g->fx[i].used != 0) {
            k++;
            if (g->fx[i].fn == func_01E00B80_b361) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                pos[0] = g->fx[i].x;
                pos[1] = g->fx[i].y;
                pos[2] = g->fx[i].z;
                func_01E022E0_b361(g, &g->fx[i], 0, pos);
            }
            if (g->fx[i].fn == func_01E00D00_b361) {
                func_01E024D0_b361(g, &g->fx[i], buf, 0);
                g->hB8 = 0;
            }
        }
    }
    if (n != 0) {
        func_01E026D0_b361(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 90) {
        return 1;
    }
    if (g->frame == 210) {
        return 4;
    }
    if (g->frame == 195) {
        return 2;
    }
    if (g->frame > 100 && g->frame < 190) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
