#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mod/b563", func_01E00080_b563);

/* shape b563:01E02180, 215 insns: fills the next of the 4 slots of group k (slot index ctx+0xF0[k], wrapping): marks
   it live (byte 1, word 1), 32 random points 1.2 x a random row/column of the main table D_0028BC10[4][32][3] (y
   through func_001A6970), w 1; the slot's position is the group's point ctx+0x30[k]; counts ctx+0xE0[k] up */

typedef struct {
    u8 on;
    u8 pad1[3];
    s32 w4;
    u8 pad8[0x48];
    Vec4f pos;
    Vec4f v[32];
} Ent_b563_01E02180;

typedef struct {
    Ent_b563_01E02180 e[4];
} Grp_b563_01E02180;

typedef struct {
    u8 pad0[0x30];
    Vec4f pos[11];
    s32 cnt[4];
    s32 cur[4];
    Grp_b563_01E02180 grp[1];
} Ctx_b563_01E02180;

static void func_01E02180_b563(s32 arg0, s32 k) {
    extern f32 D_0028BC10[4][32][3];
    extern f32 func_001A6970(f32);
    Ctx_b563_01E02180 *g = (Ctx_b563_01E02180 *)arg0;
    s32 i;

    g->grp[k].e[g->cur[k]].on = 1;
    g->grp[k].e[g->cur[k]].w4 = 1;
    for (i = 0; i < 32; i++) {
        g->grp[k].e[g->cur[k]].v[i].x =
            1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][0];
        g->grp[k].e[g->cur[k]].v[i].y =
            1.2f * func_001A6970(D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][1]);
        g->grp[k].e[g->cur[k]].v[i].z =
            1.2f * D_0028BC10[(func_0019A5C8() >> 23) % 4][(func_0019A5C8() >> 23) % 32][2];
        g->grp[k].e[g->cur[k]].v[i].w = 1.0f;
    }
    g->grp[k].e[g->cur[k]].pos = g->pos[k];
    g->cnt[k]++;
    g->cur[k]++;
    if (g->cur[k] >= 4) {
        g->cur[k] = 0;
    }
}
