#include "common.h"

/* shape c062:01E039E0, 127 insns: scene setup: five model ids picked from a random word's 3-bit fields (+0x100 in mode
   1); lights/slots 0..10 and 256..266 switched on and placed; then each of the five entries gets a random turn, its
   model's frame, position, a 0x4000 rotation, colour (alpha 0x80) and a tenth scale */

typedef struct {
    s32 w0;
    s32 w4;
    u8 pad8[0x1C];
    s32 turn;
    u8 pad28[8];
    s32 rot[4];
    Vec4f scale;
    u8 pad50[0x10];
    u8 col[4];
    s32 w64;
    u8 pad68[8];
} Ent_c062_01E039E0;

typedef struct {
    u8 pad0[0x5A50];
    Ent_c062_01E039E0 ent[5];
    u8 pad5C80[0x7E0];
    Vec4f light[22];
    u8 pad65C0[0x2BC];
    s32 ids[5];
    u8 pad6890[0xC];
    s32 cnt[5];
    u8 pad68B0[0x8A];
    s16 mode;
} Scene_c062_01E039E0;

static void func_01E039E0_c062(Scene_c062_01E039E0 *g) {
    extern s32 func_001F5380(void);
    extern void func_001F5970(s32, s32);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5D10(s32, void *);
    s32 r;
    s16 i;
    s32 k;
    Ent_c062_01E039E0 *e;
    s32 id;

    r = func_001F5380();
    if (g->mode == 0) {
        g->ids[0] = 0;
        g->ids[2] = (r >> 6) & 7;
        g->ids[1] = (r >> 9) & 7;
        g->ids[4] = r & 7;
        g->ids[3] = (r >> 3) & 7;
    } else if (g->mode == 1) {
        g->ids[0] = 0x100;
        g->ids[2] = ((r >> 6) & 7) + 0x100;
        g->ids[1] = ((r >> 9) & 7) + 0x100;
        g->ids[4] = (r & 7) + 0x100;
        g->ids[3] = ((r >> 3) & 7) + 0x100;
    }
    for (i = 0; i < 22; i++) {
        k = i;
        if (k > 10) {
            k += 0xF5;
        }
        func_001F5970(k, 1);
        func_001F5CA0(k, &g->light[i]);
    }
    for (i = 0; i < 5; i++) {
        id = g->ids[i];
        e = &g->ent[i];
        g->ent[i].w64 = 0;
        e->turn = func_0019A5C8() % 360;
        g->cnt[i] = 30;
        func_001F5BD0(id, e);
        e->w4 = 0;
        func_001F5B70(id, e);
        func_001F5CA0(id, e->rot);
        e->rot[1] = 0;
        e->rot[0] = 0x4000;
        func_001F5C40(id, e->rot);
        func_001F5E40(id, e->col);
        e->col[3] = 0x80;
        e->scale.x = 0.1f;
        e->scale.y = 0.1f;
        e->scale.z = 0.1f;
        func_001F5D10(id, &e->scale);
    }
}
