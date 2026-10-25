#include "common.h"

/* shape b743:01E01C70, 275 insns, 1 copy: B743_W_S, the scene's spawner: steps the scene clock; on odd ticks 154..200
   spawns trail pairs at the joint point (30 on tick 154, else 1), each tick moves the point at random, on odd ticks
   52..153 spawns two spark pairs, on tick 59 two glows (kinds 1 and 2), on tick 1 the fade */

typedef struct Game_b743_01E01C70 {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xD47C - 0x260];
    s16 joint;
    u8 padD47E[0xD59A - 0xD47E];
    s16 kind;
    s16 count;
    u8 padD59E[4];
    s16 clock;
} Game_b743_01E01C70;

static s32 func_01E028D0_b743();
static s32 func_01E02D60_b743();
static s32 func_01E03080_b743();
static s32 func_01E033E0_b743();
static s32 func_01E03820_b743();

static void func_01E01C70_b743(Game_b743_01E01C70 *g) {
    extern s32 func_001F53A0();
    extern void func_001F5620();
    extern s32 func_0019A5C8();
    extern s32 b743_01E020C0();
    s16 n;
    s16 i;

    g->clock++;
    if (g->clock >= 0x9A && g->clock < 0xC9 && g->clock % 2 == 1) {
        n = g->clock == 0x9A ? 30 : 1;
        for (i = 0; i < n; i++) {
            func_001F5620(func_001F53A0(), g->joint, &g->pos);
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 50 - 25;
            g->kind = g->count;
            func_01E043D0_b743((void *)g, (s32)b743_01E020C0, 0);
            func_01E043D0_b743((void *)g, (s32)func_01E02D60_b743, 0);
            g->count++;
            if (g->count >= 120) {
                g->count = 0;
            }
        }
    }
    func_001F5620(func_001F53A0(), g->joint, &g->pos);
    g->pos.x += func_0019A5C8() % 80 - 40;
    g->pos.z += func_0019A5C8() % 80 - 40;
    g->pos.y += func_0019A5C8() % 150 + 100;
    if (g->clock >= 0x34 && g->clock < 0x9A && g->clock % 2 == 1) {
        n = g->clock < 100 ? (s16)2 : (s16)2;
        for (i = 0; i < n; i++) {
            g->kind = g->count;
            func_01E043D0_b743((void *)g, (s32)func_01E028D0_b743, 0);
            func_01E043D0_b743((void *)g, (s32)func_01E03080_b743, 0);
            g->count++;
            if (g->count >= 120) {
                g->count = 0;
            }
        }
    }
    if (g->clock == 0x3B) {
        g->kind = 1;
        func_01E043D0_b743((void *)g, (s32)func_01E033E0_b743, 0);
        g->kind = 2;
        func_01E043D0_b743((void *)g, (s32)func_01E033E0_b743, 0);
    }
    if (g->clock == 1) {
        func_01E043D0_b743((void *)g, (s32)func_01E03820_b743, 0);
    }
}
